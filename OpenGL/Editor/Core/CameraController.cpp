#include "CameraController.h"

#include <math.h>
#include <algorithm>
#include "../Core/EditorAction.h"
#include "../../Core/ECS/Actor.h"
#include "../../Core/ECS/Components/CModelRenderer.h"


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

float GetActorFocusDist(Actor& p_actor)
{
	float distance = 4.0f;

	if (p_actor.IsActive())
	{
		if (auto modelRenderer = p_actor.GetComponent<CModelRenderer>())
		{
			const auto& actorPosition = p_actor.m_transform.GetWorldPosition();
			const auto& actorScale = p_actor.m_transform.GetWorldScale();
			const auto boundingSphere = &modelRenderer->GetModel()->GetBoundingSphere();
			const auto scaleFactor = std::max(std::max(actorScale.x, actorScale.y), actorScale.z);

			distance = std::max(distance, boundingSphere ? (boundingSphere->radius + glm::length(boundingSphere->position)) * scaleFactor * 2.0f : 10.0f);
		}

		for (auto child : p_actor.GetChildren())
			distance = std::max(distance, GetActorFocusDist(*child));
	}

	return distance;
}

Vector3 RemoveRoll(const Vector3& p_ypr)
{
	Vector3 result = p_ypr;

	if (result.z >= 179.0f || result.z <= -179.0f)
	{
		result.x += result.z;
		result.y = 180.0f - result.y;
		result.z = 0.0f;
	}

	if (result.x > 180.0f) result.x -= 360.0f;
	if (result.x < -180.0f) result.x += 360.0f;

	return result;
}

void CameraController::HandleInputs(float p_deltaTime)
{
	if (m_view.IsHovered())
	{
		if (!m_cameraDestinantion.empty())
		{
			auto& [destPos, destRotation] = m_cameraDestinantion.front();
			m_cameraDestinantion.pop();
			m_camera.Position = destPos;
			m_camQuat = destRotation;
		}

		if (m_inputMgr.IsMouseButtonReleased(EMouseButton::MOUSE_BUTTON_RIGHT))
		{
			m_mouseIsRightPresssed = true;
		}

		if (m_inputMgr.IsMouseButtonPressed(EMouseButton::MOUSE_BUTTON_RIGHT))
		{
			if (m_mouseIsRightPresssed)
			{
				m_newDelta = m_inputMgr.GetMousePosition();
				m_oldDelta = m_newDelta;
				m_mouseIsRightPresssed = false;
			}
			else
			{
				m_newDelta = m_inputMgr.GetMousePosition();
				std::pair<double, double>  diff = { m_oldDelta.first - m_newDelta.first,
					m_oldDelta.second - m_newDelta.second };
				HandleCameraFPSMouse(Vector2(diff.first, diff.second), true);
			}
		}


		if (m_inputMgr.IsKeyPressed(EKey::KEY_W)) { m_camPos = m_camPos + m_camera.Forward; }
		if (m_inputMgr.IsKeyPressed(EKey::KEY_S)) { m_camPos = m_camPos - m_camera.Forward; }
		if (m_inputMgr.IsKeyPressed(EKey::KEY_A)) { m_camPos = m_camPos + m_camera.Right; }
		if (m_inputMgr.IsKeyPressed(EKey::KEY_D)) { m_camPos = m_camPos - m_camera.Right; }
	}
}

void CameraController::HandleCameraFPSMouse(Vector2 p_mouseOffset, bool isMouseFirst)
{
	auto mouseOffset = p_mouseOffset * m_mouseSensitivity;

	Vector3 ypr = EulerAngles(m_camQuat);
	if (isMouseFirst)
	{
		ypr = RemoveRoll(ypr);
	}

	ypr.y -= mouseOffset.x;
	ypr.x += -mouseOffset.y;
	ypr.x = std::max(std::min(ypr.x, 90.0f), -90.0f);
	m_camQuat = Vector3ToQuat(ypr);
}

void CameraController::MoveToTarget(Actor& p_target)
{
	m_cameraDestinantion.push({ p_target.m_transform.GetWorldPosition() - m_camQuat * Vector3(0.0f, 0.0f, 1.0f) * GetActorFocusDist(p_target), m_camQuat });
}
