#pragma once

class ForwardRenderer;
class DeferredRender;
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

	/*ForwardRenderer* m_forwardRenderer;
	DeferredRenderer* m_deferredRenderer;*/
};

