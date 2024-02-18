#include "SceneView.h"
#include "../../../Render/RenderTarget.h"
#include "../../Editor/Core/EditorAction.h"

SceneView::SceneView(
	const std::string& p_title,
	bool p_opened,
	const PanelWindowSetting& p_windowSettings
		):
	AViewControllable(p_title, p_opened, p_windowSettings)
{

}

void SceneView::Update(float p_deltaTime)
{
	AViewControllable::Update(p_deltaTime);

}

void SceneView::_Render_Impl()
{
	PrepareCamera();

	auto& baseRenderer = *EDITOR_CONTEXT(m_renderer).get();

	baseRenderer.DoRender();

	
	RenderScene(0);
}

void SceneView::RenderScene(uint8_t p_defaultRenderState)
{
	m_renderTarget->Bind();
	m_editorRenderer.RenderScene(m_camPos, m_camera);
	m_renderTarget->Unbind();
}
