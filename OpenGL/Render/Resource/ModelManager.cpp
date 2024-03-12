#include "ModelManager.h"
#include "../../Render/Resource/Loader/ModelLoader.h"

Model* ModelManager::CreateResource(const std::string& p_path)
{
	string realPath = p_path;

	auto model = ModelLoader::getInstance()->Create(realPath, (EModelParserFlags)209062219);

	return model;


}

void ModelManager::DestroyResource(const std::string& p_path)
{

}
