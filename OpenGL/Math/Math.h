#pragma once


#include<tuple>
#include<GLM/glm.hpp>
#include <Assimp/scene.h>
#include<glm/matrix.hpp>

struct Ray;

const float PI = 3.14159265359f;
const float TAU = 6.28318530717f;

#define TO_RADIANS(value) value * PI / 180.f

float lerp(float x, float y, float a);

glm::vec3 lerp(glm::vec3 begin, glm::vec3 end, float a);

float Deg2Rad(float degrees);

glm::mat4 Translate(const glm::vec3& translation);

glm::mat4 Scale(const glm::vec3& scale);

glm::quat Normalize(const glm::quat& quat);

aiVector3D GlmVecToAiVec(const glm::vec3& vec);

aiQuaternion GlmQuatToAiQuat(const glm::quat& pOrientation);

glm::quat Vector3ToQuat(glm::vec3 v);

glm::vec3 EulerAngles(glm::quat p_target);

std::tuple<glm::vec3, glm::quat, glm::vec3> DecomposeTransform(const glm::mat4& transform);

glm::vec3 Lerp(glm::vec3 start, glm::vec3 end, float alpha);

glm::mat4 AiMatToGlmMat(const aiMatrix4x4& from);

glm::vec3 ScreenToWorld(glm::vec2 screenPos, float val, glm::mat4 view, glm::mat4 proj);//�����߹�һ��

glm::vec3 GetScreenToWorldRay(glm::vec2 screenPos, float near, float far, glm::mat4 view, glm::mat4 proj);

bool HitSphere(const glm::vec3& center, float radius, const Ray& r);


