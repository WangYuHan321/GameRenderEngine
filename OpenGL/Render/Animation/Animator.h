#pragma once

#include "../../Util/common.h"
#include "Animation.h"
#include "../../Core/ECS/Components/CTransform.h"

static unsigned int MAX_BONE_NUM = 128;

class Animator
{
public:
	Animator(Actor& p_actor);

	void CalculateBoneTransform(aiNode* node, Matrix4& parentTransform);
	void ReSetAnimation(Animation& animation);
	std::vector<Matrix4> GetFinalBoneMatrix() const;
	void Update(float dt);

private:
	bool isStop{ true };
	float currentTime{ 0.0f };
	float startTime{ 0.0f };
	float endTime{ 0.0f };
	float factor{ 1.0f };
	float fps{ 24.0f };
	float direction{ 1.0f };
	Animation* m_animation;

	Actor* m_actor;

	std::vector<Matrix4> finalBoneMatrix;

};

