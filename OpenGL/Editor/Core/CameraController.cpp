#include "CameraController.h"

#include "../Core/EditorAction.h"

CameraController::CameraController(AView& p_view,
Camera& p_camera,
Vector3& p_position,
Quaternion& p_quat,
bool p_enableFocusInputs):
		m_inputMgr(*EDITOR_CONTEXT(m_inputMgr)),
		m_window(*EDITOR_CONTEXT(m_window)),
		m_view(p_view),
		m_camera(p_camera),
		m_camPos(p_position),
		m_camQuat(p_quat)
{
	m_camera.SetPerspective(Deg2Rad(60.0f),
		m_window.GetWindowSize().x / m_window.GetWindowSize().y, 0.001f, 100000.0f);
}