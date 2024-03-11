#include "MaterialManager.h"

#include "Loader/MaterialLoader.h"

Material* MaterialManager::CreateResource(const std::string& p_path)
{
	Material* pMaterial = MaterialLoader::getInstance()->Create(p_path);

	if (pMaterial)
		return pMaterial;

	return nullptr;
}

void MaterialManager::DestroyResource(const std::string& p_path)
{

}
