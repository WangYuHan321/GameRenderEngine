#include"GLCache.h"
#include "../../Render/Mesh/Material.h"

GLCache::GLCache()
{
	glEnable(GL_DEPTH_TEST);
	SetDepthFunction(m_DepthFunc);

	glEnable(GL_CULL_FACE);
	glCullFace(m_CullFace);
	glFrontFace(m_ForntFace);

	glDisable(GL_BLEND);
	glBlendFunc(m_BleandSrc, m_BlendDst);
	glPolygonMode(GL_FRONT_AND_BACK, m_PolygonMode);

	glDepthMask(m_DepthWrite);
	glColorMask(m_ColorWrite, m_ColorWrite, m_ColorWrite , m_ColorWrite);
}

GLCache::~GLCache()
{
}

void GLCache::SetDepthTest(bool enable)
{
	if (m_depthTest != enable)
	{
		m_depthTest = enable;
		if (enable)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
	}
}

void GLCache::SetDepthFunction(GLenum depthFunc)
{
	if (m_DepthFunc != depthFunc)
	{
		m_DepthFunc = depthFunc;
		glDepthFunc(m_DepthFunc);
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
		m_BleandSrc = src;
		m_BlendDst = dst;
		glBlendFunc(src, dst);
	}
}
void GLCache::SetCull(bool enable)
{
	if (m_cull != enable)
	{
		m_cull = enable;
		if (m_cull)
			glEnable(GL_CULL_FACE);
		else
			glDisable(GL_CULL_FACE);
	}
}

void GLCache::SetCullFront(GLenum face)
{
	if (m_ForntFace != face)
	{
		m_ForntFace = face;
		glFrontFace(m_ForntFace);
	}
}

void GLCache::SetCullFace(GLenum face)
{
	if (m_CullFace != face)
	{
		m_CullFace = face;
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

void GLCache::SetColorMask(bool enable)
{
	if (m_ColorWrite != enable)
	{
		m_ColorWrite = enable;
		glColorMask(enable, enable, enable, enable);
	}
}

void GLCache::SetDepthMask(bool enable)
{
	if (m_DepthWrite != enable)
	{
		m_DepthWrite = enable;
		glDepthMask(enable);
	}
}

void GLCache::ApplyMaterial(Material& p_material)
{
	SetDepthTest(p_material.DepthTest);
	SetDepthMask(p_material.DepthWrite);
	SetDepthFunction(p_material.DepthCompare);

	SetCull(p_material.Cull);
	SetCullFace(p_material.CullFace);
	SetCullFront(p_material.CullWindingOrder);

	SetBlend(p_material.Blend);
	SetBlendFunc(p_material.BlendSrc, p_material.BlendDst);

	SetColorMask(p_material.ColorWrite);

}

void GLCache::SwitchShader(uint32 id)
{

}