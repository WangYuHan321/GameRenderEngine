#pragma once

#include "../BaseCommandBuffer.h"

class OpenGLRenderCommand : public BaseCommandBuffer
{
public:
	OpenGLRenderCommand();
	virtual ~OpenGLRenderCommand();

public:

	void Initialize() override;
	virtual void Clean() override;

};

