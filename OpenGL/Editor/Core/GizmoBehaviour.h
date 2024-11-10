#pragma once

#include "../../Core/ECS/Actor.h"

enum class EGizmoOperation
{
	TRANSLATE,
	ROTATE,
	SCALE
};

class GizmoBehaviour
{

public:

	enum class EDirection
	{
		X,
		Y,
		Z
	};

	EDirection GetDirection() const;

	bool IsPicking() const;

	void ApplyTranslation(const Matrix4& p_viewMatrix, const Matrix4& p_projectionMatrix, const Vector2& p_viewSize);

	Vector3 GetRealDirection(bool p_relative) ;

	void StartPicking(Actor& p_target, Vector3& p_cameraPos, EGizmoOperation p_operation, EDirection direction);

	void StopPicking();

	void SetCurrentMouse(Vector2 mouPos);

	void ApplyOperation(Matrix4&p_viewMatrix, Matrix4& p_projectMatrix, Vector2&p_viewSize);

private:
	bool m_firstMouse = true;
	float m_distanceToActor = 0.0f;
	Actor* m_target = nullptr;
	FTransform m_originTransform;
	EDirection m_direction;
	Vector2 m_originMouse;
	Vector2 m_currentMouse;
	EGizmoOperation m_curOperation;
};

