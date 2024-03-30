#include "AnimLoader.h"

std::vector<Animation*> AnimLoader::Create(const std::string& p_filepath, EModelParserFlags p_parserFlags)
{
	std::vector<Animation*> animation;
	__ASSIMP.LoadAnim(p_filepath, animation, p_parserFlags);
	return animation;
}

bool AnimLoader::Destroy(std::vector<Animation*> p_modelInstance)
{
	for(auto item : p_modelInstance)
	{
		for (auto it : item->nameBoneMap)
			delete it.second;

		delete item;
	}
	return true;
}