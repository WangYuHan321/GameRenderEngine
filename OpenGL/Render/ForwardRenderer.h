#pragma once

class RenderTarget;

#include "BaseRenderer.h"
class ForwardRenderer :
    public BaseRenderer
{
public:
	virtual void DoRender() override;
	virtual void OnReSize(uint32 width, uint32 height) override;
	virtual void Initialize() override;
	virtual void Clear() override;

protected:


	void Clear(bool p_colorBuffer = true, bool p_deptBuffer = true, bool p_stencilColor = true);
	
private:
	RenderTarget* renderTarget;
	Camera* cam;
};

