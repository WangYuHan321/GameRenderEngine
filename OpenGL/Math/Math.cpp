#include "Math.h"
#include "../../Util/common.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#define TO_RADIANS(value) value * PI / 180.f
#define TO_DEGREES(value) value * 180.f / PI

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
                     0,0,0, 1);
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

aiVector3D GlmVecToAiVec(const glm::vec3& vec)
{
    return aiVector3D(vec.x, vec.y, vec.z);
}

aiQuaternion GlmQuatToAiQuat(const glm::quat& pOrientation)
{
    return aiQuaternion(pOrientation.w, pOrientation.x, pOrientation.y, pOrientation.z);
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

glm::vec3 EulerAngles(glm::quat p_target)
{

    if (p_target == glm::quat{ 0.5f, 0.5f, -0.5f, 0.5f }) return { 90.0f, 90.0f, 0.0f };
    if (p_target == glm::quat{ 0.5f, 0.5f, 0.5f, -0.5f }) return { -90.0f, -90.0f, 0.0f };

    // roll (x-axis rotation)
    const float sinr_cosp = +2.0f * (p_target.w * p_target.x + p_target.y * p_target.z);
    const float cosr_cosp = +1.0f - 2.0f * (p_target.x * p_target.x + p_target.y * p_target.y);
    const float roll = atan2(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    float pitch = 0.f;
    const float sinp = +2.0f * (p_target.w * p_target.y - p_target.z * p_target.x);
    if (fabs(sinp) >= 1)
        pitch = static_cast<float>(copysign(PI / 2.0f, sinp)); // use 90 degrees if out of range
    else
        pitch = asin(sinp);

    // yaw (z-axis rotation)
    const float siny_cosp = +2.0f * (p_target.w * p_target.z + p_target.x * p_target.y);
    const float cosy_cosp = +1.0f - 2.0f * (p_target.y * p_target.y + p_target.z * p_target.z);
    const float yaw = atan2(siny_cosp, cosy_cosp);

    return TO_DEGREES(glm::vec3(roll, pitch, yaw)); // XYZ
}

std::tuple<glm::vec3, glm::quat, glm::vec3> DecomposeTransform(const glm::mat4& transform)
{
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(transform, scale, rotation, translation, skew, perspective);
    return { translation, rotation, scale };
}

glm::vec3 Lerp(glm::vec3 start, glm::vec3 end, float alpha)
{
    return (start + (end - start) * alpha);
}

glm::mat4 AiMatToGlmMat(const aiMatrix4x4& from)
{
    glm::mat4 to;
    // the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
    to[0][0] = from.a1;
    to[1][0] = from.a2;
    to[2][0] = from.a3;
    to[3][0] = from.a4;
    to[0][1] = from.b1;
    to[1][1] = from.b2;
    to[2][1] = from.b3;
    to[3][1] = from.b4;
    to[0][2] = from.c1;
    to[1][2] = from.c2;
    to[2][2] = from.c3;
    to[3][2] = from.c4;
    to[0][3] = from.d1;
    to[1][3] = from.d2;
    to[2][3] = from.d3;
    to[3][3] = from.d4;

    return to;
}

glm::vec3 ScreenToWorld(glm::vec2 screenPos, float val, glm::mat4 view, glm::mat4 proj)
{
    glm::vec3 ray_ndc(screenPos.x, screenPos.y, val);
    glm::vec4 ray_clip = glm::vec4(ray_ndc.x, ray_ndc.y, ray_ndc.z, 1.0f);
    glm::vec4 ray_eye = glm::inverse(proj) * ray_clip;
    glm::vec4 ray_world = glm::inverse(view) * ray_eye;

    if (ray_world.w != 0.0f)
    {
        ray_world.x /= ray_world.w;
        ray_world.y /= ray_world.w;
        ray_world.z /= ray_world.w;
    }
    return ray_world;
}

glm::vec3 GetScreenToWorldRay(glm::vec2 screenPos, float near, float far, glm::mat4 view, glm::mat4 proj)
{
    glm::vec3 startRay = ScreenToWorld(screenPos, near, view, proj);
    glm::vec3 endRay = ScreenToWorld(screenPos, far, view, proj);

    return glm::normalize(endRay - startRay);
}

bool HitSphere(const Vector3& center, float radius, const Ray& r) {
    Vector3 oc = r.p0 - center;
    float a = glm::dot(r.dir, r.dir);//2
    float b = 2.0f * glm::dot(r.dir, oc);
    float c = dot(oc, oc) - radius * radius;
    float discriminate = b * b - 4 * a * c;
    if (discriminate < 0)
        return false;
    else
        return (-b - sqrtf(discriminate)) / (2.0f * a) > 0;//1
}
