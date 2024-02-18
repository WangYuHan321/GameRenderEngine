#include "Editor.h"
#include "../../Editor/Panels/GameView.h"
#include "../../Editor/Panels/SceneView.h"

Editor::Editor(Context& p_context):
	m_context(p_context),
	m_editorRender(p_context),
	m_panelsMgr(m_canvas),
	m_editorAction(m_context, m_editorRender, m_panelsMgr)
{
	SetUpUI();
}

void Editor::SetUpUI()
{
	PanelWindowSetting settings;
	settings.closable = true;
	settings.collapsable = true;
	settings.dockable = true;

	m_panelsMgr.CreatePanel<MenuBar>("Menu Bar");
	m_panelsMgr.CreatePanel<GameView>("Game View", true, settings);
	m_panelsMgr.CreatePanel<SceneView>("Scene View", true, settings);

	m_context.m_uiMgr->SetCanvas(m_canvas);
}

void Editor::PreUpdate()
{

	m_context.m_device->PollEvents();
	m_context.m_renderer->Clear();
}

void Editor::Update(float deltaTime)
{
	RenderViews(deltaTime);
	RenderEditorUI(deltaTime);
}

void Editor::PostUpdate()
{
	m_context.m_window->SwapBuffer();
	m_context.m_inputMgr->ClearEvents();
	++m_elapsedFrames;
}

void Editor::RenderViews(float p_deltaTime)
{
	auto& gameView = m_panelsMgr.GetPanelAs<GameView>("Game View");
	auto& sceneView = m_panelsMgr.GetPanelAs<SceneView>("Scene View");

	{
		gameView.Update(p_deltaTime);
		sceneView.Update(p_deltaTime);
	}

	if (gameView.IsOpened())
	{
		gameView.Render();
	}

	if (sceneView.IsOpened())
	{
		sceneView.Render();
	}

}

void Editor::RenderEditorUI(float p_deltaTime)
{
	m_editorAction.GetRenderer().RenderUI();
}


Editor::~Editor()
{

}