#include"GLCache.h"

GLCache::GLCache()
{
}

GLCache::~GLCache()
{
}

void GLCache::SetDepthTest(bool enable)
{
	if (m_depthTest != enable)
	{
		m_depthTest = enable;
		if (m_depthTest)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
	}
}

void GLCache::SetDepthFunction(GLenum depthFunc)
{
	if (m_depthFunc != depthFunc)
	{
		m_depthFunc = depthFunc;
		glEnable(m_depthFunc);
	}
}

void GLCache::SetBlend(bool enbale)
{
	if (m_blend != enbale)
	{
		m_blend = enbale;
		if (m_blend)
			glEnable(GL_BLEND);
		else
			glDisable(GL_BLEND);
	}
}

void GLCache::SetBlendFunc(GLenum src, GLenum dst)
{
	if (m_BleandSrc != src || m_BlendDst != dst)
	{
		glBlendFunc(src, dst);
	}
}
void GLCache::SetCull(bool enable)
{
	if (m_cullFace != enable)
	{
		m_cullFace = enable;
		if (m_cullFace)
			glEnable(GL_CULL_FACE);
		else
			glDisable(GL_CULL_FACE);
	}
}

void GLCache::SetCullFace(GLenum face)
{
	if (m_ForntFace != face)
	{
		m_ForntFace = face;
		glCullFace(face);
	}
}

void GLCache::SetPolyonMode(GLenum mode)
{
	if (m_PolygonMode != mode)
	{
		m_PolygonMode = mode;
		glPolygonMode(GL_FRONT_AND_BACK, mode);
	}
}

void GLCache::SwitchShader(uint32 id)
{
	if (m_actieveShaderID != id)
	{
		glUseProgram(id);
	}
}