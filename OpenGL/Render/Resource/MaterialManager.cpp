#include "MaterialManager.h"
#include "../../File/ConfigManager.h"
#include "Loader/MaterialLoader.h"

Material* MaterialManager::CreateResource(const std::string& p_path)
{
	string realPath = ConfigManager::getInstance()->GetEditorPath() + "\\Material\\" + p_path;
	Material* pMaterial = MaterialLoader::getInstance()->Create(realPath);

	if (pMaterial)
		return pMaterial;

	return nullptr;
}

void MaterialManager::DestroyResource(const std::string& p_path)
{

}
