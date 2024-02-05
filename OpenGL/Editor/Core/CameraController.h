#pragma once

#include "../Panels/AView.h"

class Context;
class Window;
class InputManager;

class CameraController
{
public:
	CameraController(AView& p_view,
		Camera& p_camera,
		Vector3& p_position,
		Quaternion& p_quat,
		bool p_enableFocusInputs = false);


private:
	Window& m_window;
	AView& m_view;

	Camera& m_camera;
	Vector3& m_camPos;
	Quaternion& m_camQuat;

	InputManager& m_inputMgr;
};

