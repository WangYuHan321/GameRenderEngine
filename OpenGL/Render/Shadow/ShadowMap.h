#pragma once

#include "../../Util/common.h"
#include "CascadeShadowMap.h"

class RenderTarget;
class CDirectionalLight;
class Material;
class Camera;

class ShadowMap
{

public:

	ShadowMap();
	~ShadowMap();

	void Clear();
	void InitializeFrame(CDirectionalLight dirLight, const Camera* p_cam);
	void SetShadowMap(Material* p_materix);
	void BeginShadow();
	void EndShadow();

	Matrix4 GetCurDepthMatrix4();
	int GetShadowMap(int id);
	DebugOrthographics GetOrthographicFrustum(int curLevel = 0);

	int previousFrameBuffer;
	int previousViewport[4];

private:

	Matrix4 m_lightMatrix;
	RenderTarget* m_renderTarget;
	DebugOrthographics m_debugOrtho;

};

