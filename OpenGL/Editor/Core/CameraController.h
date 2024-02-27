#pragma once

#include<queue>
#include "../Panels/AView.h"

class Context;
class Window;
class Actor;
class InputManager;

class CameraController
{
public:
	CameraController(AView& p_view,
		Camera& p_camera,
		Vector3& p_position,
		Quaternion& p_quat,
		bool p_enableFocusInputs = false);

	void HandleInputs(float p_deltaTime);

	void MoveToTarget(Actor& p_actor);

private:
	void HandleCameraFPSMouse(Vector2 mouseOffset, bool isMouseFirst);

private:
	Window& m_window;
	AView& m_view;

	Camera& m_camera;
	Vector3& m_camPos;
	Quaternion& m_camQuat;

	std::queue<std::tuple<Vector3, Quaternion>> m_cameraDestinantion;

	// Û±Í”“ª˜øÿ÷∆
	std::pair<double, double> m_oldDelta;
	std::pair<double, double> m_newDelta;
	bool m_mouseIsRightPresssed = true;
	float m_mouseSensitivity = 0.02f;
	// Û±Í”“ª˜øÿ÷∆
	
	InputManager& m_inputMgr;
};

