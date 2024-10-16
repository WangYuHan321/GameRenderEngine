#include "PipelineStateManager.h"

bool PipelineStateManager::RegisterPipelineState(PipelineState& pipeline)
{
	mPipelineState[pipeline.pipelineStateName] = pipeline;
	return true;
}

bool PipelineStateManager::UnregisterPipelineState(PipelineState& pipeline)
{
	mPipelineState.erase(pipeline.pipelineStateName);
	DestroyPipelineState(pipeline);
	return true;
}
