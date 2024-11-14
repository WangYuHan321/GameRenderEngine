#include "OpenGLGraphicsManager.h"
#include "OpenGLPipelineState.h"

OpenGLGraphicsManager::OpenGLGraphicsManager():
	GraphicsManager()
{
}

OpenGLGraphicsManager::~OpenGLGraphicsManager()
{
}

void OpenGLGraphicsManager::SetPipelineState(PipelineState& pipelineState)
{
	OpenGLPipelineState* openglPipe = (OpenGLPipelineState*)&pipelineState;

	glUseProgram(openglPipe->mProgramID);

	switch (openglPipe->depthTestMode)
	{
	case DEPTH_TEST_MODE::NONE:
		m_glState.SetDepthTest(false);
		break;
	case DEPTH_TEST_MODE::LARGE:
		m_glState.SetDepthTest(true);
		m_glState.SetDepthFunction(GL_GREATER);
		break;
	case DEPTH_TEST_MODE::LARGE_EQUAL:
		m_glState.SetDepthTest(true);
		m_glState.SetDepthFunction(GL_GEQUAL);
		break;
    case DEPTH_TEST_MODE::LESS:
        m_glState.SetDepthTest(true);
        m_glState.SetDepthFunction(GL_LESS);
        break;
    case DEPTH_TEST_MODE::LESS_EQUAL:
        m_glState.SetDepthTest(true);
        m_glState.SetDepthFunction(GL_LEQUAL);
        break;
    case DEPTH_TEST_MODE::EQUAL:
        m_glState.SetDepthTest(true);
        m_glState.SetDepthFunction(GL_EQUAL);
        break;
    case DEPTH_TEST_MODE::NOT_EQUAL:
        m_glState.SetDepthTest(true);
        m_glState.SetDepthFunction(GL_NOTEQUAL);
        break;
    case DEPTH_TEST_MODE::NEVER:
        m_glState.SetDepthTest(true);
        m_glState.SetDepthFunction(GL_NEVER);
        break;
    case DEPTH_TEST_MODE::ALWAYS:
        m_glState.SetDepthTest(true);
        m_glState.SetDepthFunction(GL_ALWAYS);
        break;
    default:
        assert(0);
	}

    if (openglPipe->bDepthWrite)
        m_glState.SetDepthMask(true);
    else
        m_glState.SetDepthMask(false);

    switch (openglPipe->stencilTestMode)
    {
    }

    switch (openglPipe->cullFaceMode)
    {
    case CULL_FACE_MODE::NONE:
        m_glState.SetCull(false);
        break;
    case CULL_FACE_MODE::FRONT:
        m_glState.SetCull(true);
        m_glState.SetCullFace(GL_FRONT);
        break;
    case CULL_FACE_MODE::BACK:
        m_glState.SetCull(true);
        m_glState.SetCullFace(GL_BACK);
        break;
    default:
        assert(0);
    }






}
