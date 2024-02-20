#pragma once

#include"BaseRenderer.h"

class ShapeDrawer
{
public:
	ShapeDrawer(BaseRenderer& p_renderer);
	~ShapeDrawer();

	void SetViewProjection(Matrix4& p_mat4);

	void DrawLine(Vector3& p_start, Vector3& p_end, Color3& p_color, float p_lineWidth = 1.0f);

	void DrawGrid(Vector3 p_viewPos, Color3& p_color, uint32 p_gridSize = 50, float p_linear = 0.0f, float p_quadratic = 0.0f, float p_fadeThreshold = 0.0f, float p_lineWidth = 1.0f);



};

