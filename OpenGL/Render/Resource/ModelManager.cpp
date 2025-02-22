#include "ModelManager.h"
#include "../../File/ConfigManager.h"
#include "../../Render/Resource/Loader/ModelLoader.h"

Model* ModelManager::CreateResource(const std::string& p_path)
{
	string realPath = ConfigManager::getInstance()->GetEditorPath() + "\\Models\\" + p_path;
	/*
	auto model = ModelLoader::getInstance()->Create(realPath,  EModelParserFlags::CALC_TANGENT_SPACE |
		EModelParserFlags::LIMIT_BONE_WEIGHTS |
		EModelParserFlags::TRIANGULATE |
		//EModelParserFlags::EMBED_TEXTURES | 
		//EModelParserFlags::FORCE_GEN_NORMALS |
		//EModelParserFlags::FLIP_UVS |
		//EModelParserFlags::SPLIT_LARGE_MESHES |
		EModelParserFlags::GEN_SMOOTH_NORMALS
		//(EModelParserFlags)209062219
	);
	*/

	auto model = ModelLoader::getInstance()->Create(realPath, (EModelParserFlags)209062219);

	return model;


}

void ModelManager::DestroyResource(const std::string& p_path)
{

}
