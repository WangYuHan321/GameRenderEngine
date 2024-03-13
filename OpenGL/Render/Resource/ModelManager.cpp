#include "ModelManager.h"
#include "../../File/ConfigManager.h"
#include "../../Render/Resource/Loader/ModelLoader.h"

Model* ModelManager::CreateResource(const std::string& p_path)
{
	string realPath = ConfigManager::getInstance()->GetEditorPath() + "\\Models\\" + p_path;

	auto model = ModelLoader::getInstance()->Create(realPath, (EModelParserFlags)209062219);

	return model;


}

void ModelManager::DestroyResource(const std::string& p_path)
{

}
