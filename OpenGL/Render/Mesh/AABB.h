#pragma once
#include"../../Util/common.h"

class Bounding {
public:
	virtual float getVolume() = 0;
};

class AABB : public Bounding
{
private:
	glm::vec3 m_Min;
	glm::vec3 m_Max;
public:
	AABB(std::vector<glm::vec3> vPoints);
	~AABB() = default;

	virtual float getVolume() override;
	bool inside(const glm::vec3& vPos);
};

