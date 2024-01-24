#pragma once

#include "Mesh.h"

class DebugScreenQuad : public Mesh
{
private:
	float cellXSizeValue;
	float cellYSizeValue;

public:
	//���ּ��� GBUffer 4 tile �ʹ���4 �߶�Ϊ��� generation of 0 index
	DebugScreenQuad(float cellXSize = 2.0f, float cellYSize = 2.0f);

	void FinalizeMesh(int index);
};

