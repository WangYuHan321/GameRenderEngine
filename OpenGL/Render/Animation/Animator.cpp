#include "Animator.h"
Animator::Animator() :
	isStop(true)
{
	finalBoneMatrix.reserve(MAX_BONE_NUM);
	for (unsigned int i = 0U; i < MAX_BONE_NUM; i++)
		finalBoneMatrix.push_back(Matrix4(1.0f));
}

void Animator::Update(float dt)
{

}