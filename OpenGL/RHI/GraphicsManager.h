#pragma once

#include "PipelineState.h"

class GraphicsManager
{
public:
	GraphicsManager();
	virtual ~GraphicsManager() {};


	virtual void SetPipelineState(PipelineState& pipelineState) = 0;

};

