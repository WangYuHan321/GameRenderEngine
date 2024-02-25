#include "ShaderLoader.h"
//#include "../../Util/common.h"

std::pair<std::string, std::string> ParseShader(std::string path)
{
    std::ifstream stream(path);

    enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

    std::string line;

    std::stringstream ss[2];

    ShaderType type = ShaderType::NONE;

    while (std::getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)			type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)	type = ShaderType::FRAGMENT;
        }
        else if (type != ShaderType::NONE)
        {
            ss[static_cast<int>(type)] << line << '\n';
        }
    }

    return
    {
        ss[static_cast<int>(ShaderType::VERTEX)].str(),
        ss[static_cast<int>(ShaderType::FRAGMENT)].str()
    };

}

CShader* ShaderLoader::Create(const std::string& pSource)
{
    string pNewSource = "Data\\Editor\\Shader\\" + pSource + ".glsl";

    std::pair<std::string, std::string> source = ParseShader(pNewSource);

    return LoadStream("EngineDefault", source.first, source.second);

}

CShader* ShaderLoader::CreateFromSource(std::string name, std::string vsSource, std::string fsSource)
{
    CShader* pNewShader = new CShader();

    pNewShader->CreateFromSource(name, vsSource, fsSource);

    return pNewShader;
}

CShader* ShaderLoader::LoadStream(std::string name, std::string vsPath, std::string fsPath)
{
    CShader* pShader = new CShader(name, vsPath, fsPath);

    return pShader;
}

CShader* ShaderLoader::Load(std::string name, std::string vsPath, std::string fsPath, std::vector<std::string> defindes)
{
	std::ifstream vsFile, fsFile;
    
	vsFile.open(vsPath);
	fsFile.open(fsPath);


	if (!vsFile.is_open() || !fsFile.is_open())
	{
        Log("open file vs %s error and fs %s error!\n", vsPath.c_str(), fsPath.c_str());
        std::cerr << "Error: " << strerror(errno);
	}
	
	std::string vsDirectory = vsPath.substr(0, vsPath.find_last_of("/\\"));
	std::string fsDirectory = fsPath.substr(0, fsPath.find_last_of("/\\"));
	std::string vsSource = readShader(vsFile, name, vsPath);
	std::string fsSource = readShader(fsFile, name, fsPath);

    CShader * pShader = new CShader(name, vsSource, fsSource, defindes);
    vsFile.close();
    fsFile.close();

    return pShader;
}

CShader ShaderLoader::Load1(std::string name, std::string vsPath, std::string fsPath, std::vector<std::string> defindes)
{
    std::ifstream vsFile, fsFile;

    vsFile.open(vsPath);
    fsFile.open(fsPath);


    if (!vsFile.is_open() || !fsFile.is_open())
    {
        Log("open file vs %s error and fs %s error!\n", vsPath.c_str(), fsPath.c_str());
        std::cerr << "Error: " << strerror(errno);
    }

    std::string vsDirectory = vsPath.substr(0, vsPath.find_last_of("/\\"));
    std::string fsDirectory = fsPath.substr(0, fsPath.find_last_of("/\\"));
    std::string vsSource = readShader(vsFile, name, vsPath);
    std::string fsSource = readShader(fsFile, name, fsPath);

    CShader shader(name, vsSource, fsSource, defindes);
    vsFile.close();
    fsFile.close();

    return shader;
}


std::string ShaderLoader::readShader(std::ifstream& file, const std::string& name, std::string path)
{
    std::string directory = path.substr(0, path.find_last_of("/\\"));
    std::string source, line;
    while (std::getline(file, line))
    {
        // if we encounter an #include line, include other shader source
        if (line.substr(0, 8) == "#include")
        {
            std::string includePath = directory + "/" + line.substr(9);
            std::ifstream includeFile(includePath);
            if (includeFile.is_open())
            {
                // we recursively read the shader file to support any shader include depth
                source += readShader(includeFile, name, includePath);
            }
            else
            {
                Log("Shader: " + name + ": include: " + includePath + " failed to open.");
            }
            includeFile.close();
        }
        else
            source += line + "\n";
    }
    return source;
}

bool ShaderLoader::Destroy(CShader* pShader)
{
    if (pShader)
    {
        delete pShader;
        pShader = nullptr;

        return true;
    }

    return false;
}