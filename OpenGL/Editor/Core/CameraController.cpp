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
		m_window.GetWindowSize().x / m_window.GetWindowSize().y, 0.1f, 100.0f);
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
			m_mouseIsRightPresssed = false;
			m_isFirstRightPressed = true;
		}

		if (m_inputMgr.IsMouseButtonPressed(EMouseButton::MOUSE_BUTTON_RIGHT))
		{
			m_mouseIsRightPresssed = true;
			if (m_isFirstRightPressed)
			{
				m_newDelta = m_inputMgr.GetMousePosition();
				m_oldDelta = m_newDelta;
				m_isFirstRightPressed = false;
			}
			else
			{
				m_newDelta = m_inputMgr.GetMousePosition();
				std::pair<double, double>  diff = { m_oldDelta.first - m_newDelta.first,
					m_newDelta.second - m_oldDelta.second  };
				m_oldDelta = m_newDelta;

				HandleCameraFPSMouse(Vector2(diff.first, diff.second), true);
			}
		}

		HandleCameraFPSKeyboard(p_deltaTime);
	}
}

void CameraController::HandleCameraFPSKeyboard(float p_deltaTime)
{
	//鼠标右击移动效果
	Vector3 m_targetSpeed = Vector3(0.f, 0.f, 0.f);
	Vector3 m_currentMovementSpeed = m_targetSpeed;

	if (m_mouseIsRightPresssed)
	{
		float velocity = m_cameraMoveSpeed * p_deltaTime * (1.0f);

		if (m_inputMgr.IsKeyPressed(EKey::KEY_W))
			m_targetSpeed += m_camQuat * Vector3(0.0f, 0.0f, 1.0f) * velocity;
		if (m_inputMgr.IsKeyPressed(EKey::KEY_S))
			m_targetSpeed += m_camQuat * Vector3(0.0f, 0.0f, 1.0f) * -velocity;
		if (m_inputMgr.IsKeyPressed(EKey::KEY_A))
			m_targetSpeed += m_camQuat * Vector3(1.0f, 0.0f, 0.0f) * velocity;
		if (m_inputMgr.IsKeyPressed(EKey::KEY_D) )
			m_targetSpeed += m_camQuat * Vector3(1.0f, 0.0f, 0.0f) * -velocity;
		if (m_inputMgr.IsKeyPressed(EKey::KEY_E))
			m_targetSpeed += Vector3(0.0f, velocity, 0.0f);
		if (m_inputMgr.IsKeyPressed(EKey::KEY_Q))
			m_targetSpeed += Vector3(0.0f, -velocity, 0.0f);
	}

	m_currentMovementSpeed = Lerp(m_currentMovementSpeed, m_targetSpeed, 10.0f * p_deltaTime);
	m_camPos += m_currentMovementSpeed;
}

void CameraController::HandleCameraFPSMouse(Vector2 p_mouseOffset, bool isMouseFirst)
{
	auto mouseOffset = p_mouseOffset * m_mouseSensitivity;
	Vector3 ypr =  EulerAngles(m_camQuat.m_quat);;

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
	m_cameraDestinantion.push({ p_target.m_transform.GetWorldPosition() - m_camQuat* Vector3(0.0f, 0.0f, 1.0f) * GetActorFocusDist(p_target), m_camQuat });
}
