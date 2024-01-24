#pragma once

#include "Mesh.h"

class DebugScreenQuad : public Mesh
{
private:
	float cellXSizeValue;
	float cellYSizeValue;

public:
	//划分几块 GBUffer 4 tile 就传入4 高度为多高 generation of 0 index
	DebugScreenQuad(float cellXSize = 2.0f, float cellYSize = 2.0f);

	void FinalizeMesh(int index);
};

