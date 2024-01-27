#pragma once
#include "BaseRenderer.h"
class ForwardRenderer :
    public BaseRenderer
{
public:
	virtual void DoRender() override;
	virtual void OnReSize(uint32 width, uint32 height) override;
	virtual void Initialize() override;
};

