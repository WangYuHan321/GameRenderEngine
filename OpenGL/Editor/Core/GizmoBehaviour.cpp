#include "GizmoBehaviour.h"
GizmoBehaviour::EDirection GizmoBehaviour::GetDirection() const
{
	return m_direction;
}

bool GizmoBehaviour::IsPicking() const
{
	return m_target;
}

void GizmoBehaviour::ApplyTranslation(const Matrix4& p_viewMatrix, const Matrix4& p_projectionMatrix, const Vector2& p_viewSize)
{
	auto unitsPerPixel = 0.001f * m_distanceToActor;
	auto originPosition = m_originTransform.GetLocalPosition();

	m_target->m_transform.SetLocalPosition(originPosition + GetRealDirection(true) * 0.01f);
}

Vector3 GizmoBehaviour::GetRealDirection(bool p_relative) 
{
	auto result = Vector3();

	switch (m_direction)
	{ 
	case GizmoBehaviour::EDirection::X:
		result = p_relative ? m_originTransform.GetWorldRight() : m_originTransform.GetLocalRight();
		break;
	case GizmoBehaviour::EDirection::Y:
		result = p_relative ? m_originTransform.GetWorldUp() : m_originTransform.GetLocalUp();
		break;
	case GizmoBehaviour::EDirection::Z:
		result = p_relative ? m_originTransform.GetWorldForward() : m_originTransform.GetLocalForward();
		break;
	}

	return result;
}

void GizmoBehaviour::StartPicking(Actor& p_target, Vector3& p_cameraPos, EGizmoOperation p_operation, EDirection direction)
{
	m_firstMouse = true;
	m_target = &p_target;
	m_curOperation = p_operation;
	m_direction = direction;
	m_originTransform = p_target.m_transform.GetFTransform();
}

void GizmoBehaviour::StopPicking()
{
	m_target = nullptr;
}

void GizmoBehaviour::SetCurrentMouse(Vector2 mouPos)
{
	if (m_firstMouse)
	{
		m_currentMouse = m_originMouse = mouPos;
		m_firstMouse = false;
	}
	else
	{
		m_currentMouse = mouPos;
	}
}

void GizmoBehaviour::ApplyOperation(Matrix4& p_viewMatrix, Matrix4& p_projectMatrix, Vector2& p_viewSize)
{
	switch (m_curOperation)
	{
	case EGizmoOperation::TRANSLATE:
			ApplyTranslation(p_viewMatrix, p_projectMatrix, p_viewSize);
			break;
	}
}
