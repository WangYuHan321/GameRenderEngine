#pragma once
#include "Camera.h"

class FlyCamera: public Camera
{
public:
	float Yaw = 0.0f;
	float Pitch = 0.0f;

	float MovementSpeed = 10.0f;
	float MouseSensitivty = 0.1f;
	float Damping = 5.0f;
private:
	glm::vec3 m_TargetPosition = glm::vec3(0.0f);
	glm::vec3 m_WorldUp = glm::vec3(0.0f);
	float m_TargetYaw = 0.0f;
	float m_TargetPitch = 0.0f;

public:
	FlyCamera(glm::vec3 position, glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

	virtual void Update(float dt);

	virtual void InputKey(float dt, CAMERA_MOVEMENT direction);
	virtual void InputMouse(double deltaX, double deltaY);
	virtual void InputScroll(float deltaX, float deltaY);
};

