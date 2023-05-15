#pragma once

#include"Render/Shader/TextureCube.h"
#include"GLM/glm.hpp"

struct PBRCapture
{
	TextureCube* Irradiance = nullptr; // ·øÕÕ¶È ÌùÍ¼
	TextureCube* PrefilteredMap = nullptr;//Ä£ºı¶ÈÌùÍ¼

	glm::vec3 Position;
	float Radius;
};

