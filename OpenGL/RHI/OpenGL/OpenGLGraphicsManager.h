#pragma once
#include "../GraphicsManager.h"
#include "../../Render/GLCache.h"

class OpenGLGraphicsManager : public GraphicsManager
{
public:
	OpenGLGraphicsManager();
	~OpenGLGraphicsManager();

public:

	void SetPipelineState(PipelineState& pipelineState) override;

private:
	GLCache m_glState;
};

