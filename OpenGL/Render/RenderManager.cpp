#include "RenderManager.h"

#include "BaseRenderer.h"
#include "Deferred/DeferredRenderer.h"
#include "Forward/ForwardRenderer.h"


RenderManager::RenderManager():
	m_renderType(RenderType::Forward)
{
	m_forwardRenderer = new ForwardRenderer();
	m_deferredRenderer = new DeferredRenderer();
}

RenderManager::~RenderManager()
{
	delete m_forwardRenderer;
	delete m_deferredRenderer;
}

void RenderManager::SetActiveRenderer(RenderType& renderType)
{
	m_renderType = renderType;
	SwitchToRendererByCurType();
}

void RenderManager::SwitchToRendererByCurType()
{
	if (m_renderType == RenderType::Forward)
		m_acitiveRenderer = m_forwardRenderer;
	else if (m_renderType == RenderType::Forward)
		m_acitiveRenderer = m_deferredRenderer;
}

