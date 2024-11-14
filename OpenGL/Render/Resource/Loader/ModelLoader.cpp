#include "ModelLoader.h"
#include "../../Mesh/Model.h"
#include "../Parser/AssimpParser.h"


Model* ModelLoader::Create(const std::string& p_filepath, EModelParserFlags p_parserFlags)
{
	Model* result = new Model();

	if (__ASSIMP.LoadModelEx(p_filepath, *result, p_parserFlags))
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