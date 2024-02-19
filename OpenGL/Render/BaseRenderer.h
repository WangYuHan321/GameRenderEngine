#pragma once
#include "../../../Util/common.h"

class Camera;

class BaseRenderer
{
public:

	BaseRenderer();
	~BaseRenderer();

	virtual void Initialize();
	virtual void Clear();
	virtual void SetViewPort(uint32 x, uint32 y, uint32 width, uint32 height);

	virtual void DoRender() = 0;

	virtual void OnReSize(uint32 width, uint32 height) = 0;

protected:

};

