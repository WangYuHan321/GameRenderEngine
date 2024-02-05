#pragma once
#include <string>
#include <vector>
#include "EModelParserFlags.h"

class Mesh;

class IModelParser
{
public:
	virtual bool LoadModel(const std::string& p_fileName, std::vector<Mesh*>& p_meeshes, 
		std::vector<std::string>& p_materials, EModelParserFlags p_flags) = 0;
};

