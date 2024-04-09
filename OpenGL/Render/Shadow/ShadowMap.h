#pragma once

class RenderTarget;
class CDirectionalLight;

class ShadowMap
{

public:

	ShadowMap();
	~ShadowMap();

	void BeginShadow();
	void EndShadow();

	int previousFrameBuffer;

private:

	RenderTarget* m_renderTarget;

};

