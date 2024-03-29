#pragma once

#include "../../Util/common.h"
#include <assimp/scene.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <set>

struct KeyPosition
{
	Vector3 position;
	float time;
};

struct KeyRotation
{
	Quaternion quat;
	float time;
};

struct KeyScale
{
	Vector3 scale;
	float time;
};

class Bone
{

public:
	Bone() = default;
	Bone(const std::string& name, const aiNodeAnim* channel, const glm::mat4& inverseBindingPose);
	
	Matrix4 InterplatePosition(float time);
	Matrix4 InterplateRotation(float time);
	Matrix4 InterplateScale(float time);


	void Update(float animTime, float factor);
	Matrix4 GetLocalTransform(float animTime, float factor);
	void Copy(aiNodeAnim& channel, const aiMatrix4x4& binding_pose_transform, float factor, bool is_interpolated);

	std::set<float> GetTimes() { return times; }

private:

	std::string name = "";
	float factor;
	Matrix4 localTransform = Matrix4(1.0f);

	std::map<float, KeyPosition> positions;
	std::map<float, KeyRotation> rotations;
	std::map<float, KeyScale>    scales;
	std::set<float> times;
};

