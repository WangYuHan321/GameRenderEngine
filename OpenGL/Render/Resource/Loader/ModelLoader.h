#pragma once

#include <string>
#include <vector>
#include <GLM/glm.hpp>
#include "../Parser/AssimpParser.h"

class Model;
class Mesh;
class Material;

class ModelLoader : public CSingleton<ModelLoader>
{
public:

	Model* Create(const std::string& p_filepath, EModelParserFlags p_parserFlags = EModelParserFlags::NONE);

	bool Destroy(Model*& p_modelInstance);

private:
	AssimpParser __ASSIMP;

};

