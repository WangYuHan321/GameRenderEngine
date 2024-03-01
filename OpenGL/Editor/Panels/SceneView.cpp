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
	m_camera.SetPerspective(Deg2Rad(60.0f), 0.5, 0.1f, 5000.0f);
}

void SceneView::Update(float p_deltaTime)
{
	AViewControllable::Update(p_deltaTime);

}

void SceneView::_Render_Impl()
{
	auto& baseRenderer = *dynamic_cast<ForwardRenderer*>(EDITOR_CONTEXT(m_renderer).get());

	PrepareCamera();

	uint8_t glState = baseRenderer.FetchGLState();
	RenderScene(glState);
}

void SceneView::RenderScene(uint8_t p_defaultRenderState)
{
	auto& baseRenderer = *dynamic_cast<ForwardRenderer*>(EDITOR_CONTEXT(m_renderer).get());

	uint8_t state = baseRenderer.FetchGLState();

	m_renderTarget->Bind();

	if (m_renderTarget->Width > 0 && m_renderTarget->Height > 0)
	{

		baseRenderer.SetStencilMask(0xFF);
		baseRenderer.Clear(true);
		glClearColor(0.2, 0.2, 0.2, 1);
		baseRenderer.SetStencilMask(0x00);
		
		Vector3 c(0.176f, 0.176f, 0.176f);
		m_editorRenderer.RenderGrid(m_camPos, c);
		m_editorRenderer.RenderCameras();
	}

	m_renderTarget->Unbind();
}

void SceneView::test(Actor& pAct)
{
	m_cameraController.MoveToTarget(pAct);
}