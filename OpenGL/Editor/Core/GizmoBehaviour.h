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

	void StartPicking(Actor& p_target, Vector3& p_cameraPos, EGizmoOperation p_operation, EDirection direction);

	void StopPicking();

	void ApplyOperation(Matrix4&p_viewMatrix, Matrix4& p_projectMatrix, Vector2&p_viewSize);
};

