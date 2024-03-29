#include <string>
#include <vector>
#include "../../Animation/Bone.h"
#include "../../Animation/Animation.h"
#include "EModelParserFlags.h"

class IAnimParser
{
	virtual bool LoadAnim(const std::string& p_fileName, std::vector<Animation*>& p_anim, EModelParserFlags p_flags) = 0;
};