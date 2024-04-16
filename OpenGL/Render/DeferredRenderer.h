#pragma once
#include "BaseRenderer.h"

class RenderTarget;

class DeferredRenderer : public BaseRenderer
{
public:
	DeferredRenderer();
	~DeferredRenderer();

	void Initialize();
	virtual void DoRender() override;
	virtual void OnReSize(uint32 width, uint32 height) override;

private:
	RenderTarget* m_renderGBuffer;
};

