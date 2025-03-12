#pragma once

#include "Bone.h"
#include <map>
#include "../../Util/common.h"

class Model;

enum class AnimType
{
	None,
	Assimp,
	Json,
	Raw
};

struct AssimpNodeData
{
	glm::mat4 transformation;
	std::string name;
	int childrenCount;
	std::vector<AssimpNodeData> children;
};

class Animation
{
public:
	Animation() = default;
	Animation(const char* filePath);

	//void GetAnimation(aiAnimation* ai_anim, aiNode* ai_root_node, float factor, float isLinear);
	float GetTickDeltaTime()const ;
	float GetDuration()const;
	AssimpNodeData GetRootNode() { return m_nodeRoot; }
	std::map<std::string, Bone*> GetBoneMap() { return nameBoneMap; }
	Bone* GetBoneByName(std::string name);

	void ReadHierarchyData(AssimpNodeData& dest, aiNode* node);

public:

	float duration{ 0.0f };
	float tickTime{ 0.0f };
	int fps{ 0 };
	std::string name;
	std::map<std::string, Bone*> nameBoneMap;
	std::map<std::string, Matrix4> nameBindPoseMap;
	AssimpNodeData m_nodeRoot;
	AnimType animType;
	std::string path;
	int id{ -1 };
};

