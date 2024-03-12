#include "ModelLoader.h"
#include "../../Mesh/Model.h"
#include "../Parser/AssimpParser.h"


Model* ModelLoader::Create(const std::string& p_filepath, EModelParserFlags p_parserFlags)
{
	Model* result = new Model();

	if (__ASSIMP.LoadModel(p_filepath, result->m_meshes, result->m_materialNames, p_parserFlags))
	{
		result->ComputeBoundingSphere();
		return result;
	}

	delete result;

}

bool ModelLoader::ModelLoader::Destroy(Model*& p_modelInstance)
{
	if (p_modelInstance)
	{
		delete p_modelInstance;
		p_modelInstance = nullptr;

		return true;
	}

	return false;
}