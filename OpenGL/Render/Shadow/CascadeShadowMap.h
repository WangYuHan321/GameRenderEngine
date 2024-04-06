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
	ShadowMap m_pShadowMap[5];

	Matrix4 biasMatrix;

public:
	int previousFrameBuffer;

	CascadeShadowMap();
	~CascadeShadowMap();

	void BeginFrame(CDirectionalLight p_dirLight, const Camera* p_cam);
	void BeginShadowRender(int level);
	void EndShadowRender();
	void EndFrame(Material* p_material = nullptr);
	Matrix4 GetCurDepthMatrix4();


	void InitShadowMap(int level, float minX, float maxX, float miny, float maxY, float minz, float maxZ);
};

