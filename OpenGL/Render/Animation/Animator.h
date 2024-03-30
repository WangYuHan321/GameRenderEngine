#pragma once

#include "../../Util/common.h"

class Animator
{
public:
	Animator();


	void Update(float dt);

private:
	bool isStop{ true };
	float currentTime{ 0.0f };
	float startTime{ 0.0f };
	float endTime{ 0.0f };
	float factor{ 1.0f };
	float fps{ 24.0f };
	float direction{ 1.0f };
	std::vector<Matrix4> finalBoneMatrix;

};

