#include "DeferredRenderer.h"
#include "../RenderTarget.h"

DeferredRenderer::DeferredRenderer()
{
	Initialize();
}

DeferredRenderer::~DeferredRenderer()
{
	delete m_renderGBuffer;
}

void DeferredRenderer::Initialize()
{
	m_renderGBuffer = new RenderTarget(2048, 2048, GL_UNSIGNED_BYTE, 8, true);
	for (int i = 0; i < 8; i++)
	{
		m_gBufferInfo = m_renderGBuffer->GetColorTexture(i);
	}
	m_gBufferDepth = m_renderGBuffer->GetDepthStencilTexture();
}

void DeferredRenderer::DoRender()
{




}

void DeferredRenderer::OnReSize(uint32 width, uint32 height)
{
	m_renderGBuffer->Resize(width, height);
}