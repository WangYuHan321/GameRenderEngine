#pragma once

#include"Render/Shader/TextureCube.h"
#include"GLM/glm.hpp"

class PBRCapture
{
public:
	TextureCube* Irradiance = nullptr; // ���ն� ��ͼ
	TextureCube* PrefilteredMap = nullptr;//ģ������ͼ

	glm::vec3 Position;
	float Radius;
};

