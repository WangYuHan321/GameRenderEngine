#include "OpenGLPipelineState.h"
bool OpenGLPipelineStateManager::InitializePipelineState(PipelineState** ppPipelineState)
{
	bool result = false;

	OpenGLPipelineState* p_newState = new OpenGLPipelineState(**ppPipelineState);
	
	return result;
}

void OpenGLPipelineStateManager::DestroyPipelineState(PipelineState& ppPipelineState)
{

}