#include "Animation.h"
#include <filesystem>

Animation::Animation(const char* filePath) :
	path(filePath)
{
}

void Animation::GetAnimation(aiAnimation* ai_anim, const aiNode* ai_root_node, float factor, float isLinear)
{
	std::filesystem::path pathStr = std::filesystem::path(path.c_str());
	std::string animName = pathStr.filename().string();
	uint32 size = nameBoneMap.size();
	std::vector<aiNodeAnim*> channels;

	float duration = 0.0f;
	for (auto& name_bone : nameBoneMap)
	{
		const aiNode* node = ai_root_node->FindNode(name_bone.first.c_str());
		if (node && name_bone.second->GetTimes().size() != 0)
		{
			LOG("find node:" + name_bone.first);
			channels.emplace_back(new aiNodeAnim());
			name_bone.second->Copy(*channels.back(), node->mTransformation, factor, isLinear);
			auto time_end = *std::next(name_bone.second->GetTimes().end(), -1);
			duration = std::max(duration, time_end);
		}
	}

}