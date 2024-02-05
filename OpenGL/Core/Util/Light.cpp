#include "Light.h"
#include "../ECS/Components/CTransform.h"

Light::Light(const FTransform& p_tranform, Type p_type) :
	m_transform(p_tranform), 
	type(static_cast<float>(p_type))
{

}