#pragma once

#include "../../Util/common.h"
#include "../PipelineState.h"
#include "../PipelineStateManager.h"

struct OpenGLPipelineState : public PipelineState
{
	uint32 mProgramID = 0;
	OpenGLPipelineState(PipelineState& rhs) : PipelineState(rhs) {}
	OpenGLPipelineState(PipelineState&& rhs) : PipelineState(std::move(rhs)) {}
};

class OpenGLPipelineStateManager : PipelineStateManager
{
public:
	OpenGLPipelineStateManager() = default;

protected:
	virtual bool InitializePipelineState(PipelineState** ppPipelineState) final;
	virtual void DestroyPipelineState(PipelineState& pipelineState) final;
};

