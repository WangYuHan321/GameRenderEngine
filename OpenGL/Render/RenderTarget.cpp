#include"RenderTarget.h"


RenderTarget::RenderTarget(uint32 width, uint32 height, GLenum type, uint32 attachemnts, bool depthandstencil) :
	Width(width),
	Height(height),
	Type(type),
	hasDepthAndStenCil(depthandstencil)
{
	glGenFramebuffersEXT(1, &ID);
	//glGenRenderbuffers(1, &RenderBufferID);
	glBindFramebufferEXT(GL_FRAMEBUFFER, ID);
	for (uint32 i = 0; i < attachemnts; i++)
	{
		Texture texture;
		texture.FilterMax = GL_LINEAR;
		texture.FilterMin = GL_LINEAR;
		texture.WrapS = GL_CLAMP_TO_EDGE;
		texture.WrapT = GL_CLAMP_TO_EDGE;
		texture.MipMapping = false;
		
		GLenum internalFormat = GL_RGBA;
		if (type == GL_HALF_FLOAT)
			internalFormat = GL_RGBA16F;
		else if (type == GL_FLOAT)
			internalFormat = GL_RGBA32F;
		texture.Generate(width, height, internalFormat, GL_RGBA, type, 0);
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, texture.ID, 0);
		m_colorAttachments.push_back(texture);
	}

	hasDepthAndStenCil = depthandstencil;
	if (hasDepthAndStenCil)
	{
		Texture texture;
		texture.FilterMax = GL_LINEAR;
		texture.FilterMin = GL_LINEAR;
		texture.WrapS = GL_CLAMP_TO_EDGE;
		texture.WrapT = GL_CLAMP_TO_EDGE;
		texture.MipMapping = false;

		texture.Generate(Width, Height, GL_DEPTH_STENCIL, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, 0);
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture.ID, 0);
		m_depthStencil = texture;
	}

	if (glCheckFramebufferStatusEXT(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		LOG_ERROR("Framebuffer not complete!");
	}

	glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
}

void RenderTarget::Resize(uint32 width, uint32 height)
{

	if (width <= 0 || height <= 0)
		return;

	Width = width;
	Height = height;

	//glBindRenderbuffer(GL_RENDERBUFFER, RenderBufferID);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_STENCIL, Width, Height);
	//glBindRenderbuffer(GL_RENDERBUFFER, 0);

	//Bind();
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RenderBufferID);
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RenderBufferID);
	//Unbind();

	for (uint32 i = 0; i < m_colorAttachments.size(); i++)
	{
		m_colorAttachments[i].ReSize(Width, Height);
	}
	if (hasDepthAndStenCil)
	{
		m_depthStencil.ReSize(Width, Height);
	}
}

Texture* RenderTarget::GetDepthStencilTexture()
{
	return &m_depthStencil;
}

Texture* RenderTarget::GetColorTexture(unsigned int index)
{
	if (index < m_colorAttachments.size())
		return &m_colorAttachments[index];
	else
	{
		LOG_ERROR("RenderTarget color texture requested, but not available: " + std::to_string(index));
		return nullptr;
	}
}

void RenderTarget::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, ID);
}

void RenderTarget::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}



