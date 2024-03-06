#pragma once

#include<GLM/glm.hpp>
#include<glm/matrix.hpp>

struct Ray;

const float PI = 3.14159265359f;
const float TAU = 6.28318530717f;

float lerp(float x, float y, float a);

glm::vec3 lerp(glm::vec3 begin, glm::vec3 end, float a);

float Deg2Rad(float degrees);

glm::mat4 Translate(const glm::vec3& translation);

glm::mat4 Scale(const glm::vec3& scale);

glm::quat Normalize(const glm::quat& quat);

glm::quat Vector3ToQuat(glm::vec3 v);

glm::vec3 EulerAngles(glm::quat p_target);

glm::vec3 Lerp(glm::vec3 start, glm::vec3 end, float alpha);

glm::vec3 ScreenToWorld(glm::vec2 screenPos, float val, glm::mat4 view, glm::mat4 proj);//必须线归一化

glm::vec3 GetScreenToWorldRay(glm::vec2 screenPos, float near, float far, glm::mat4 view, glm::mat4 proj);

bool HitSphere(const glm::vec3& center, float radius, const Ray& r);


