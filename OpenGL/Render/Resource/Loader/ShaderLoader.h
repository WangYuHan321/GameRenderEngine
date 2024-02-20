#pragma once
#include "../../Util/Singleton.h"
#include "../../Shader/EShader.h"
class ShaderLoader : public CSingleton<ShaderLoader>
{

public:

	CShader* Create(const std::string& pSource);//仅支持顶点和片元着色器

	CShader* Load(std::string name,std::string vsPath, std::string fsPath,std::vector<std::string> defindes = std::vector<std::string>());

	CShader Load1(std::string name, std::string vsPath, std::string fsPath, std::vector<std::string> defindes = std::vector<std::string>());

	std::string readShader(std::ifstream& file, const std::string& name, std::string path);

	bool Destroy(CShader* pShader);
};

