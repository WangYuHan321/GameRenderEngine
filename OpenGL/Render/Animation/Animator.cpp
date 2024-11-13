#include "Animator.h"
#include "../../Core/ECS/Components/CModelRenderer.h"

Animator::Animator(Actor& p_actor) :
	m_actor(&p_actor),
	isStop(true)
{
	finalBoneMatrix.reserve(MAX_BONE_NUM);
	for (unsigned int i = 0U; i < MAX_BONE_NUM; i++)
		finalBoneMatrix.push_back(Matrix4(1.0f));
}

//void Animator::CalculateBoneTransform(aiNode* node, Matrix4& parentTransform)
//{
	//std::string nodeName = node->mName.C_Str();
	//glm::mat4 nodeTransform = AiMatToGlmMat(node->mTransformation);
	//Model* pModel = m_actor->get 

	//Bone* Bone = m_animation->GetBoneByName(nodeName);

	//if (Bone)
	//{
	//	Bone->Update(currentTime, 1);
	//	nodeTransform = Bone->GetLocalTransform(currentTime, 1);
	//}

	//glm::mat4 globalTransformation = parentTransform * nodeTransform;

	//auto boneInfoMap = m_animation->GetBoneMap();
	//if (boneInfoMap.find(nodeName) != boneInfoMap.end())
	//{
	//	int index = bone;
	//	glm::mat4 offset = boneInfoMap[nodeName]->GetLocalTransform(currentTime, 1);
	//	finalBoneMatrix[index] = globalTransformation * offset;
	//}

	//for (int i = 0; i < node->mNumChildren; i++)
	//	CalculateBoneTransform(node->mChildren[i], globalTransformation);

//}

void Animator::Update(float dt)
{
	currentTime += dt;
	if (currentTime > endTime)
		currentTime = 0.0f;

	float timeLength = endTime - startTime;
	float len = m_animation->GetDuration() / timeLength;
	float curRealTime = currentTime * len;





}