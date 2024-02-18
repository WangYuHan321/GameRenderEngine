#pragma once
#include <GLM/glm.hpp>
#include "../../Util/common.h"
#include "CameraFrustum.h"

enum CAMERA_MOVEMENT {
    CAMERA_FORWARD,
    CAMERA_BACK,
    CAMERA_LEFT,
    CAMERA_RIGHT,
    CAMERA_UP,
    CAMERA_DOWN,
};

class Camera 
{
public:
    glm::mat4 Projection;
    glm::mat4 View;

    glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 Forward = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 Right = glm::vec3(1.0f, 0.0f, 0.0f);

    float FOV;//Ë®Æ½
    float Aspect;//´¹Ö±
    float Near;
    float Far;
    bool  Perspective;

    CameraFrustum Frustum;
private:
public:
    Camera();
    Camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up);

    void Update(float dt);

    void SetPerspective(float fov, float aspect, float near, float far);
    void SetOrthographic(float left, float right, float top, float bottom, float near, float far);

    void UpdateView();

    void CalculateProjectMatrix(uint32 p_windowWidth, uint32 p_windowHeight);


    float FrustumHeightAtDistance(float distance);
    float DistanceAtFrustumHeight(float frustumHeight);

};