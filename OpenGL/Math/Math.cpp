#include "Math.h"

float lerp(float x, float y, float a)
{
    return x * (1 - a) + y * a;
}

glm::vec3 lerp(glm::vec3 begin, glm::vec3 end, float a)
{
    glm::vec3 result;
    result.x = begin.x * (1 - a) + end.x * a;
    result.y = begin.y * (1 - a) + end.y * a;
    result.z = begin.z * (1 - a) + end.z * a;
    return result;
}

float Deg2Rad(float degrees)
{
    return degrees / 180.0f * PI;
}

glm::mat4& translate(glm::mat4& result, const glm::vec3& translation)
{
    glm::mat4 mat;
    mat[3] = glm::vec4(translation, 1.0f);
    result = result * mat;
    return result;
}

glm::mat4& scale(glm::mat4& result, const glm::vec3& scale)
{
    for (std::size_t i = 0; i < 3; ++i) {
        result[i][i] *= scale[i];
    }
    return result;
}

