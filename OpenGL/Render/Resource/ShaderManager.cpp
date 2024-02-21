#include "ShaderManager.h"

#include "Loader/ShaderLoader.h"

 CShader* ShaderManager::CreateResource(const std::string& p_path)
{
	 CShader* pShader = ShaderLoader::getInstance()->Create(p_path);

	 if (pShader)
		 return pShader;

	 return nullptr;
}

 void ShaderManager::DestroyResource(const std::string& p_path)
{

}