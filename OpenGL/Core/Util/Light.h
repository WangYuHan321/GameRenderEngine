#pragma once

#include "../../../Util/common.h"

class Light
{
public:
	enum class Type { Point, Directional, Spot, Ambient_Box, Ambient_Sphere };

	Light(const FTransform& p_tranform, Type p_type); 

	Matrix4 GenerateMatrix() const;

	Color3	color = { 1.f, 1.f, 1.f };
	float				intensity = 1.f;
	float				constant = 0.0f;
	float				linear = 0.0f;
	float				quadratic = 1.0f;
	float				cutoff = 12.f;
	float				outerCutoff = 15.f;
	float				type = 0.0f;

protected:
	const FTransform& m_transform;
};


