#include "GizmoBehaviour.h"
GizmoBehaviour::EDirection GizmoBehaviour::GetDirection() const
{
	return m_direction;
}

bool GizmoBehaviour::IsPicking() const
{
	return m_target;
}

Vector2 GizmoBehaviour::GetScreenDirection(const Matrix4& p_viewMatrix, const Matrix4& p_projectionMatrix, const Vector2& p_viewSize) 
{
	Vector3 test = GetRealDirection();
	auto start = m_originTransform.GetWorldPosition();
	auto end = m_originTransform.GetWorldPosition() + test * 0.01f;

	auto start2D = Vector2(0, 0);
	{
		auto clipSpacePos = p_projectionMatrix * (p_viewMatrix * Vector4{ start.x, start.y, start.z, 1.0f });
		auto ndcSpacePos = Vector3{ clipSpacePos.x, clipSpacePos.y, clipSpacePos.z } / clipSpacePos.w;
		auto windowSpacePos = ((Vector2{ ndcSpacePos.x, ndcSpacePos.y } + 1.0f) / 2.0f);
		windowSpacePos.x *= p_viewSize.x;
		windowSpacePos.y *= p_viewSize.y;
		start2D = windowSpacePos;
	}

	auto end2D = Vector2(0, 0);
	{
		auto clipSpacePos = p_projectionMatrix * (p_viewMatrix * Vector4{ end.x, end.y, end.z, 1.0f });
		auto ndcSpacePos = Vector3{ clipSpacePos.x, clipSpacePos.y, clipSpacePos.z } / clipSpacePos.w;
		auto windowSpacePos = ((Vector2{ ndcSpacePos.x, ndcSpacePos.y } + 1.0f) / 2.0f);
		windowSpacePos.x *= p_viewSize.x;
		windowSpacePos.y *= p_viewSize.y;
		end2D = windowSpacePos;
	}

	auto result = end2D - start2D;

	result.y *= -1; // Screen coordinates are reversed, so we inverse the Y

	return glm::normalize(result);
}

void GizmoBehaviour::ApplyTranslation(const Matrix4& p_viewMatrix, const Matrix4& p_projectionMatrix, const Vector2& p_viewSize)
{
	auto unitsPerPixel = 0.001f * m_distanceToActor;
	auto originPosition = m_originTransform.GetLocalPosition();

	auto screenDirection = GetScreenDirection(p_viewMatrix, p_projectionMatrix, p_viewSize);

	auto totalDisplacement = m_currentMouse - m_originMouse;
	auto translationCoefficient = glm::dot(totalDisplacement, screenDirection) * unitsPerPixel;

	Vector3 testt = GetRealDirection() * translationCoefficient;

	Log("org mouse = %f %f \n", m_originMouse.x, m_originMouse.y);
	Log("mouse = %f %f \n", m_currentMouse.x, m_currentMouse.y);
	Log("xx = %f\n", m_distanceToActor);

	m_target->m_transform.SetLocalPosition(originPosition + GetRealDirection(true) * translationCoefficient);
}

Vector3 GizmoBehaviour::GetRealDirection(bool p_relative) 
{
	auto result = Vector3(0, 0, 0);

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
	m_distanceToActor = glm::distance(p_cameraPos, m_target->m_transform.GetWorldPosition());
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
