#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Util/common.h"

Camera::Camera():
FOV(45.0f),
Size(5.0f),
Near(0.1f),
Far(100.f),
ClearColor(0.f, 0.f, 0.f, 1.0f),
Perspective(true)
{

}

Camera::Camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up) : Position(position), Forward(forward), Up(up)
{
    UpdateView();
}

void Camera::Update(float dt)
{
    Frustum.Update(this);
}

void Camera::SetPerspective(float fov, float aspect, float near, float far)
{
    Perspective = true;
    FOV = fov;
    Aspect = aspect;
    Near = near;
    Far = far;

    Projection = glm::perspective(FOV, Aspect, Near, Far);
}

void Camera::SetOrthographic(float left, float right, float top, float bottom, float near, float far)
{
    Perspective = false;
    Near = near;
    Far = far;

    Projection = glm::ortho(left, right, top, bottom, near, far);
}

void Camera::UpdateView()
{
    View = glm::lookAt(Position, Position + Forward, Up);
}

void Camera::CalculateProjectMatrix(uint32 p_windowWidth, uint32 p_windowHeight)
{
    if (p_windowHeight != 0.0f)
    {
        Aspect = ((float)p_windowWidth / (float)p_windowHeight);
        SetPerspective(FOV, Aspect, Near, Far);
    }
}

void Camera::CalculateViewMatrix(Vector3 p_position, Quaternion p_rotation)
{
    Position = p_position;
    Up = p_rotation * DefaultUp;
    Forward = p_rotation * DefaultForward ;

    UpdateView();
}

float Camera::FrustumHeightAtDistance(float distance)
{
    if (Perspective)
    {
        return 2.0f * distance * tanf((FOV * 0.5f) / 180.0 * 3.141592653);
    }
    else
    {
        return Frustum.Top.D;
    }
}

float Camera::DistanceAtFrustumHeight(float frustumHeight)
{
    if (Perspective)
    {
        return frustumHeight * 0.5f / tanf((FOV * 0.5f) / 180.0 * 3.141592653);
    }
    else
    {
        return Frustum.Near.D;
    }
}