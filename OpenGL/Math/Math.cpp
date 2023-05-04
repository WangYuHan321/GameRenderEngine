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
