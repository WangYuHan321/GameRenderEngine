#include "Math.h"
#include <glm/gtc/quaternion.hpp>

#define TO_RADIANS(value) value * PI / 180.f

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

glm::mat4 Translate(const glm::vec3& translation)
{
    glm::mat4 result(1, 0, 0, translation.x,
                     0, 1, 0, translation.y,
                     0, 0, 1, translation.z,
                     0, 0, 0, 1);
    return result;
}

glm::mat4 Scale(const glm::vec3& scale)
{
    glm::mat4 result(scale.x, 0, 0, 0,
                   0, scale.y, 0, 0,
                   0, 0, scale.z, 0,
                   0, 0, 0, 1);
    return result;
}

glm::quat Normalize(const glm::quat& _quat)
{
    glm::quat temp = _quat;
    const float reciprocate = 1.0f / sqrtf(_quat.x * _quat.x + _quat.y * _quat.y + _quat.z * _quat.z + _quat.w * _quat.w);
    temp.x *= reciprocate;
    temp.y *= reciprocate;
    temp.z *= reciprocate;
    temp.w *= reciprocate;

    return temp;
}

glm::quat Vector3ToQuat(glm::vec3 v)
{
    glm::quat temp(0.0f,0.0f, 0.0f, 0.0f);

    float yaw = TO_RADIANS(v.z) * 0.5f;
    float pitch = TO_RADIANS(v.y) * 0.5f;
    float roll = TO_RADIANS(v.x) * 0.5f;

    float cy = cos(yaw);
    float sy = sin(yaw);
    float cp = cos(pitch);
    float sp = sin(pitch);
    float cr = cos(roll);
    float sr = sin(roll);

    temp.x = sr * cp * cy - cr * sp * sy;
    temp.y = cr * sp * cy + sr * cp * sy;
    temp.z = cr * cp * sy - sr * sp * cy;
    temp.w = cr * cp * cy + sr * sp * sy;
    
    return temp;
}

