#pragma once

#include"Render/Shader/TextureCube.h"
#include"GLM/glm.hpp"

struct PBRCapture
{
	TextureCube* Irradiance = nullptr; // ���ն� ��ͼ
	TextureCube* PrefilteredMap = nullptr;//ģ������ͼ

	glm::vec3 Position;
	float Radius;
};

