#pragma once

#include "Bone.h"
#include <map>
#include "../../Util/common.h"

enum class AnimType
{
	None,
	Assimp,
	Json,
	Raw
};

class Animation
{
public:
	Animation() = default;
	Animation(const char* filePath);

	void GetAnimation(aiAnimation* ai_anim, const aiNode* ai_root_node, float factor, float isLinear);

public:

	float duration{ 0.0f };
	int fps{ 0 };
	std::string name;
	std::map<std::string, Bone*> nameBoneMap;
	std::map<std::string, Matrix4> nameBindPoseMap;
	AnimType animType;
	std::string path;
	int id{ -1 };
};

