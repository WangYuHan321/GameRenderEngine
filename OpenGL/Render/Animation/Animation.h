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

	//void GetAnimation(aiAnimation* ai_anim, aiNode* ai_root_node, float factor, float isLinear);
	float GetTickDeltaTime()const ;
	float GetDuration()const;
	aiNode* GetNodeRoot() { return m_nodeRoot; }

	std::map<std::string, Bone*> GetBoneMap() { return nameBoneMap; }
	Bone* GetBoneByName(std::string name);

public:

	float duration{ 0.0f };
	float tickTime{ 0.0f };
	int fps{ 0 };
	std::string name;
	std::map<std::string, Bone*> nameBoneMap;
	std::map<std::string, BoneInfo*>nameBoneInfoMap;
	std::map<std::string, Matrix4> nameBindPoseMap;
	aiNode* m_nodeRoot;
	AnimType animType;
	std::string path;
	int id{ -1 };
};

