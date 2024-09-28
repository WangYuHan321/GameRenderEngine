#pragma once
#include "PipelineState.h"

class PipelineStateManager
{
	virtual bool RegisterPipelineState(PipelineState& pipeline);
	virtual bool UnregisterPipelineState(PipelineState& pipeline);

	PipelineState& GetPipeLineStateByName(std::string& name) { return mPipelineState[name]; }
private:
	std::map<std::string, PipelineState> mPipelineState;

};

