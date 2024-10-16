#pragma once

#include "../PipelineStateManager.h"

class OpenGLPipelineStateManager : PipelineStateManager
{
public:
	OpenGLPipelineStateManager() = default;

protected:
	virtual bool InitializePipelineState(PipelineState** ppPipelineState) final;
	virtual void DestroyPipelineState(PipelineState& pipelineState) final;
};
