#include "Animation.h"
#include "Bone.h"
#include "../Resource/Loader/AnimLoader.h"
#include <Assimp/assimp_glm_helpers.h>
#include <filesystem>

Animation::Animation(const char* filePath) :
	path(filePath)
{
}

float Animation::GetTickDeltaTime()const
{
	return tickTime;
}

float Animation::GetDuration()const
{
	return duration;
}

Bone* Animation::GetBoneByName(std::string name)
{
	if (nameBoneMap.find(name) != nameBoneMap.end())
	{
		return nameBoneMap[name];
	}
	return nullptr;
}

void Animation::ReadHierarchyData(AssimpNodeData& dest, aiNode* node)
{
	dest.name = node->mName.data;
	dest.transformation = AssimpGLMHelpers::ConvertMatrixToGLMFormat(node->mTransformation);
	dest.childrenCount = node->mNumChildren;

	for (int i = 0; i < node->mNumChildren; i++)
	{
		AssimpNodeData newData;
		ReadHierarchyData(newData, node->mChildren[i]);
		dest.children.push_back(newData);
	}
}
