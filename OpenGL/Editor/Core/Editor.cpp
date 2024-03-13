#include "Editor.h"
#include "../../File/ConfigManager.h"
#include "../../Editor/Panels/GameView.h"
#include "../../Editor/Panels/SceneView.h"
#include "../../Editor/Panels/Hierarchy.h"
#include "../../Editor/Panels/Inspector.h"
#include "../../Editor/Panels/ToolBar.h"
#include "../../Editor/Panels/AssetBrowser.h"
#include "../../Editor/Panels/MaterialEditor.h"

Editor::Editor(Context& p_context):
	m_context(p_context),
	m_editorRender(p_context),
	m_panelsMgr(m_canvas),
	m_editorAction(m_context, m_editorRender, m_panelsMgr)
{
	SetUpUI();

#ifdef USE_EDITOR
	m_context.m_sceneMgr->LoadEmptyLightedScene();
#endif
}

void Editor::SetUpUI()
{
	PanelWindowSetting settings;
	settings.closable = true;
	settings.collapsable = true;
	settings.dockable = true;
	
	m_panelsMgr.CreatePanel<MenuBar>("Menu Bar");
	m_panelsMgr.CreatePanel<Hierarchy>(EDITOR_LANGUAGE(MENU_HIERARCHY), true, settings);
	m_panelsMgr.CreatePanel<GameView>(EDITOR_LANGUAGE(MENU_GAME_VIEW), false, settings);
	m_panelsMgr.CreatePanel<SceneView>(EDITOR_LANGUAGE(MENU_SCENE_VIEW), true, settings);
	m_panelsMgr.CreatePanel<Inspector>(EDITOR_LANGUAGE(MENU_INSPECTOR), true, settings);
	m_panelsMgr.CreatePanel<ToolBar>(EDITOR_LANGUAGE(MENU_TOOLBAR), false, settings);
	m_panelsMgr.CreatePanel<AssetBrowser>(EDITOR_LANGUAGE(MENU_ASSET_BROWSER), true, settings, ConfigManager::getInstance()->GetEnginePath(),
		ConfigManager::getInstance()->GetProjectPath() + "\\Asset", ConfigManager::getInstance()->GetProjectPath() + "\\Script");
	m_panelsMgr.CreatePanel<MaterialEditor>(EDITOR_LANGUAGE(MENU_SCENE_VIEW), false, settings);

	m_canvas.MakeDockspace(true);
	m_context.m_uiMgr->SetCanvas(m_canvas);
}

void Editor::PreUpdate()
{

	m_context.m_device->PollEvents();
	m_context.m_renderer->Clear();
}

void Editor::Update(float deltaTime)
{
	PrepareRender(deltaTime);

	RenderViews(deltaTime);
	RenderEditorUI(deltaTime);
}

void Editor::PostUpdate()
{
	m_context.m_window->SwapBuffer();
	m_context.m_inputMgr->ClearEvents();
	++m_elapsedFrames;
}

void Editor::PrepareRender(float deltaTime)
{
	m_context.m_engineUBO->SetSubData(m_context.m_device->GetElapsedTime(), 3 * sizeof(Matrix4) + sizeof(Vector3));
}

void Editor::RenderViews(float p_deltaTime)
{
	auto& gameView = m_panelsMgr.GetPanelAs<GameView>(EDITOR_LANGUAGE(MENU_GAME_VIEW));
	auto& sceneView = m_panelsMgr.GetPanelAs<SceneView>(EDITOR_LANGUAGE(MENU_SCENE_VIEW));

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