#include "ShaderLoader.h"
//#include "../../Util/common.h"

CShader ShaderLoader::Load(std::string name, std::string vsPath, std::string fsPath, std::vector<std::string> defindes)
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