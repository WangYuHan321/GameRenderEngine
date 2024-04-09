#pragma once

#include "../../../Util/common.h"

class Camera;
class Material;
class RenderTarget;
class CDirectionalLight;

typedef struct DebugOrthographics
{
	Vector3 pos;
	Vector3 forward;
	float nearPanel;
	float farPanel;
	Vector3 a;
	Vector3 b;
	Vector3 c;
	Vector3 d;
	Vector3 e;
	Vector3 f;
	Vector3 g;
	Vector3 h;
} DebugOrthographics;

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
	DebugOrthographics m_pDebugOrtho[2];

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
	DebugOrthographics GetOrthographicFrustum(int curLevel = 0);
};

