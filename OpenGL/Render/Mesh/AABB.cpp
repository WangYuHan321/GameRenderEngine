#include "AABB.h"

float AABB::getVolume()
{
	glm::vec3 diagonal = m_Max = m_Min;
	return diagonal.x * diagonal.y * diagonal.z;
}

bool AABB::inside(const glm::vec3& vPos)
{
	return (m_Max.x > vPos.x && m_Min.x < vPos.x
		&& m_Max.y > vPos.y && m_Min.y < vPos.y
		&& m_Max.z > vPos.z && m_Min.z < vPos.z);
}

AABB::AABB(std::vector<glm::vec3> vPoints):m_Min(0.0f),m_Max(0.0f)
{
	for (auto pos : vPoints)
	{
		m_Min = glm::min(m_Min, pos);
		m_Max = glm::max(m_Max, pos);
	}
}