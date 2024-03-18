#include "GameView.h"

//#include"../../Scene/Scene.h"
#include"../Core/EditorAction.h"
#include "../../Core/ECS/Actor.h"
#include "../../Core/ECS/Components/CCamera.h"
#include"../../Render/RenderTarget.h"

GameView::GameView
(
	const std::string& p_title,
	bool p_opened,
	const PanelWindowSetting& p_windowSettings
):
	AView(p_title, p_opened, p_windowSettings)
{

}

void GameView::Update(float p_deltaTime)
{
	AView::Update(p_deltaTime);

	auto currentScene = EDITOR_CONTEXT(m_sceneMgr)->GetActiveScene();

	if (currentScene)
	{
		auto cameraComponent = currentScene->FindMainCCamera();
		if (cameraComponent)
		{
			m_camera = cameraComponent->GetCamera();
			m_camPos = cameraComponent->owner.m_transform.GetWorldPosition();
			m_camRot = cameraComponent->owner.m_transform.GetWorldRotation();
			PrepareCamera();
		}
		else
		{
			m_camera.ClearColor = Color4(0.f, 0.f, 0.f, 1.f);
		}
	}


}

void GameView::_Render_Impl()
{
	auto baseRenderer = EDITOR_CONTEXT(m_renderer).get();
	auto currentScene = EDITOR_CONTEXT(m_sceneMgr)->GetActiveScene();

	m_renderTarget->Bind();

	dynamic_cast<ForwardRenderer*>(baseRenderer)->Clear(m_camera);
	m_editorRenderer.UpdateLights(*currentScene);
	m_editorRenderer.RenderScene(m_camPos, m_camera);

	m_renderTarget->Unbind();
}