#include "OpenGLSatateManager.h"
#include "OpenGLPipelineState.h"
#include "../../Render/Resource/Loader/ShaderLoader.h"

bool LoadShaderByType(PipelineState& pipeline)
{
	switch (pipeline.pipelineType)
	{
	case PIPELINE_TYPE::GRAPHIC:
		ShaderLoader::getInstance()->Load(pipeline.pipelineStateName, pipeline.vertexShaderName, pipeline.pixelShaderName);
		break;
	case PIPELINE_TYPE::COMPUTE:
		break;
	default:
		return false;
	}

	return true;
}

bool OpenGLPipelineStateManager::InitializePipelineState(PipelineState** ppPipelineState)
{
	bool result = false;

	OpenGLPipelineState* p_newState = new OpenGLPipelineState(**ppPipelineState);

	result = LoadShaderByType(*p_newState);

	return result;
}

void OpenGLPipelineStateManager::DestroyPipelineState(PipelineState& ppPipelineState)
{
	OpenGLPipelineState* pPipelineState = dynamic_cast<OpenGLPipelineState*>(&ppPipelineState);
	glDeleteProgram(pPipelineState->mProgramID);
}