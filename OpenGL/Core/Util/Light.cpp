#include "Light.h"
#include "../ECS/Components/CTransform.h"

Light::Light(const FTransform& p_tranform, Type p_type) :
	m_transform(p_tranform), 
	type(static_cast<float>(p_type))
{

}

Matrix4 Light::GenerateMatrix() const
{
	Matrix4 result;

	auto pos = m_transform.GetWorldPosition();
	result[0][0] = pos.x;
	result[0][1] = pos.y;
	result[0][2] = pos.z;

	auto forward = (Quaternion)m_transform.GetWorldRotation() * Vector3(0, 0, 1) ;
	result[1][0] = forward.x;
	result[1][1] = forward.y;
	result[1][2] = forward.z;

	result[2][0] = color.r;
	result[2][1] = color.g;
	result[2][2] = color.b;
	//result[2][3] = 0 * 255.f;

	result[3][0] = type;
	result[3][1] = cutoff;
	result[3][2] = outerCutoff;

	result[0][3] = constant;
	result[1][3] = linear;
	result[2][3] = quadratic;
	result[3][3] = intensity;

	return result;
}