#pragma once

#include "../../../Util/common.h"

class Camera;
class Material;
class RenderTarget;
class CDirectionalLight;

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
	ShadowMap m_pShadowMap[2];

	Matrix4 biasMatrix;

public:
	int previousFrameBuffer;

	CascadeShadowMap();
	~CascadeShadowMap();

	void InitializeFrame(CDirectionalLight p_dirLight, const Camera* p_cam);
	void BeginShadowRender(int level);
	void SetShadowMap(Material* p_material);
	void EndShadowRender();
	Matrix4 GetCurDepthMatrix4();
	void Clear();


	void InitShadowMap(int level, float minX, float maxX, float miny, float maxY, float minz, float maxZ);

	int GetShadowMap(int curLevel);
};

