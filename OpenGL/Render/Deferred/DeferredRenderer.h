#pragma once
#include "../BaseRenderer.h"

class RenderTarget;
class Material;
class Texture;
class Mesh;

class DeferredRenderer : public BaseRenderer
{
	using Drawable = std::tuple<Matrix4, Mesh*, Material*, Matrix4>;
	using OpaqueDrawables = std::multimap<float, Drawable, std::less<float>>;
	using TransparentDrawables = std::multimap<float, Drawable, std::greater<float>>;

public:
	DeferredRenderer();
	~DeferredRenderer();

	void Initialize();
	virtual void DoRender() override;
	virtual void OnReSize(uint32 width, uint32 height) override;

private:
	RenderTarget* m_renderGBuffer;

	Texture* m_gBufferInfo;
	Texture* m_gBufferDepth;
};

