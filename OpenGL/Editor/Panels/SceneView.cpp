#include "SceneView.h"
#include "../../Render/ForwardRenderer.h"
#include "../../../Render/RenderTarget.h"
#include "../../Editor/Core/EditorAction.h"

SceneView::SceneView(
	const std::string& p_title,
	bool p_opened,
	const PanelWindowSetting& p_windowSettings
		):
	AViewControllable(p_title, p_opened, p_windowSettings)
{
	m_camera.SetPerspective(45.0f, 0.5, 0.1f, 5000.0f);
}

void SceneView::Update(float p_deltaTime)
{
	AViewControllable::Update(p_deltaTime);

}

void SceneView::_Render_Impl()
{
	PrepareCamera();

	RenderScene(0);
}

void SceneView::RenderScene(uint8_t p_defaultRenderState)
{
	auto& baseRenderer = *dynamic_cast<ForwardRenderer*>(EDITOR_CONTEXT(m_renderer).get());

	uint8_t state = baseRenderer.FetchGLState();

	m_renderTarget->Bind();

	if (m_renderTarget->Width > 0 && m_renderTarget->Height > 0)
	{
		baseRenderer.Clear(true, true, true);

		m_editorRenderer.RenderCameras();
	}


	//m_editorRenderer.RenderScene(m_camPos, m_camera);

	//baseRenderer.ApplyStateMask(state);
	m_renderTarget->Unbind();
}
