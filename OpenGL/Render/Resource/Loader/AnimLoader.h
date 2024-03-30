#pragma once

#include <string>
#include <vector>
#include <GLM/glm.hpp>
#include "../Parser/AssimpParser.h"

class AnimLoader : public CSingleton<AnimLoader>
{
public:

	std::vector<Animation*> Create(const std::string& p_filepath, EModelParserFlags p_parserFlags = EModelParserFlags::NONE);

	bool Destroy(std::vector<Animation*> p_modelInstance);

private:
	AssimpParser __ASSIMP;
};

