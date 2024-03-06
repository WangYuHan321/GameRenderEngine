#pragma once

#include "../../../Util/common.h"

class RenderTarget;

class CascadeShadowMap
{
private:
	typedef struct ShadowMap
	{
		Matrix4 proj;
		Matrix4 depth;
		RenderTarget* shadowMap;
	} ShadowMap;

private:

	int currentLevel;
	ShadowMap m_pShadowMap[5];

	Matrix4 biasMatrix;

public:
	CascadeShadowMap();
	~CascadeShadowMap();

	void InitShadowMap(int level, float minX, float maxX, float miny, float maxY, float minz, float maxZ);
};

