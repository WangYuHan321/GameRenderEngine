#pragma once

#include<GLM/glm.hpp>
#include<glm/matrix.hpp>

const float PI = 3.14159265359f;
const float TAU = 6.28318530717f;

float lerp(float x, float y, float a);

glm::vec3 lerp(glm::vec3 begin, glm::vec3 end, float a);

float Deg2Rad(float degrees);

glm::mat4& translate(glm::mat4& result, const glm::vec3& translation);

glm::mat4& scale(glm::mat4& result, const glm::vec3& scale);

