#include "GameView.h"

//#include"../../Scene/Scene.h"
#include"../Core/EditorAction.h"
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
		//auto cam = EDITOR_CONTEXT(m_renderer)->GetCamera();
		if (true)
		{

		}
		else
		{
			
		}


	}


}

void GameView::_Render_Impl()
{

}