#pragma once

class ForwardRenderer;
class DeferredRenderer;
class BaseRenderer;

enum RenderType
{
	Forward,
	Deferred,
};

class RenderManager
{
public:
	RenderManager();
	~RenderManager();

	void SetActiveRenderer(RenderType& renderType);


private:

	void SwitchToRendererByCurType();

	RenderType m_renderType;
	BaseRenderer* m_acitiveRenderer;

	ForwardRenderer* m_forwardRenderer;
	DeferredRenderer* m_deferredRenderer;
};

