#pragma once
#include "PipelineState.h"

class PipelineStateManager
{
	virtual bool RegisterPipelineState(PipelineState& pipeline);
	virtual bool UnregisterPipelineState(PipelineState& pipeline);

	PipelineState& GetPipeLineStateByName(std::string& name) { return mPipelineState[name]; }
protected:
	std::map<std::string, PipelineState> mPipelineState;

protected:
	virtual bool InitializePipelineState(PipelineState** ppPipelineState) {
		return true;
	}
	virtual void DestroyPipelineState(PipelineState& pipelineState) {}
};

