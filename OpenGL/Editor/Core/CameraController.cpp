#include "CameraController.h"

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


void CameraController::HandleInputs(float p_deltaTime)
{
	if (m_view.IsHovered())
	{

	}
}
