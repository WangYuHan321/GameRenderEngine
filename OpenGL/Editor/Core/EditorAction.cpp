#include "EditorAction.h"

#include "../Panels/SceneView.h"
#include "../Panels/Inspector.h"
#include "../../File/ConfigManager.h"
#include "../../Global/ServiceLocator.h"
#include "../../Core/ECS/Components/CModelRenderer.h"
#include "../../Core/ECS/Components/CMaterialRenderer.h"
#include "../../Render/Resource/Loader/Async/AsynLoaderManager.h"

EditorAction::EditorAction(Context& p_context, EditorRender& p_editorRender, PanelsManager& p_panelMgr):
	m_context(p_context),
	m_renderer(p_editorRender),
	m_panelMgr(p_panelMgr)

{
	ServiceLocator::getInstance()->Provide<EditorAction>(*this);

	m_context.m_sceneMgr->CurrentSceneSourcePathChangedEvent += [this](const std::string& p_newPath)
	{
		//std::string titleExtra = " - " + (p_newPath.empty() ? "Untitled Scene" : GetResourcePath(p_newPath));
		Log("CurrentSceneSourcePathChangedEvent");
	};

}

Context& EditorAction::GetContext()
{
	return m_context;
}

PanelsManager& EditorAction::GetPanelsManager()
{
	return m_panelMgr;
}

void EditorAction::SelectActor(Actor& p_target)
{
	EDITOR_PANEL(Inspector, "Inspector").FocusActor(p_target);//EDITOR_LANGUAGE(MENU_INSPECTOR)
}

void EditorAction::UnselectActor()
{
	EDITOR_PANEL(Inspector, "Inspector").UnFocus();//EDITOR_LANGUAGE(MENU_INSPECTOR)
}

Actor& EditorAction::CreateActorWithModel(std::string p_model, bool p_focuseonCreation, Actor* p_parent, std::string p_name)
{
	auto& instance = CreateEmptyActor(false, p_parent, p_name);

	auto& modelRenderer = instance.AddComponent<CModelRenderer>();

	auto model = m_context.modelMgr[p_model];
	if (model)
		modelRenderer.SetModel(model);

	auto& materialRenderer = instance.AddComponent<CMaterialRenderer>();
	const auto material = m_context.materialMgr["Default.opmat"];

	if (material)
		materialRenderer.FillWithMaterial(*material);

	if (p_focuseonCreation)
		SelectActor(instance);

	return instance;
}

Actor& EditorAction::CreateActorWithAsynModel(std::string p_model, bool p_focuseonCreation, Actor* p_parent, std::string p_name)
{
	auto& instance = CreateEmptyActor(false, p_parent, p_name);
	auto& modelRenderer = instance.AddComponent<CModelRenderer>();

	//asyn load model 
	auto model = m_context.modelMgr.GetDefaultResource( ConfigManager::getInstance()->GetEditorPath() + "\\Models\\" + p_model );
	m_context.modelMgr.m_resourceChangedEvent += [this, &instance, p_model]
	{
		CModelRenderer* pModelComponent = instance.GetComponent<CModelRenderer>();
		if (pModelComponent)
			pModelComponent->SetModel(m_context.modelMgr[p_model]);
	};

	m_context.asynLoaderMgr.AddModel(ConfigManager::getInstance()->GetEditorPath() + "\\Models\\" + p_model);
	// asyn load model
	
	if (model)
		modelRenderer.SetModel(model);

	auto& materialRenderer = instance.AddComponent<CMaterialRenderer>();
	const auto material = m_context.materialMgr["Default.opmat"];

	if (material)
		materialRenderer.FillWithMaterial(*material);

	if (p_focuseonCreation)
		SelectActor(instance);
	
	return  instance;
}

Actor& EditorAction::CreateEmptyActor(bool p_focusOnCreation, Actor* p_parent, std::string p_name)
{
	auto currentScene = m_context.m_sceneMgr->GetActiveScene();
	auto instance = p_name.empty() ? currentScene->CreateActor() : currentScene->CreateActor(p_name);

	if (p_parent)
		instance->SetParent(*p_parent);

	if (p_focusOnCreation)
		SelectActor(*instance);

	LOG_INFO("Actor created");

	return *instance;
}

void EditorAction::CreateFontActor()
{
	GLOBALSERVICE(FontManager).CreateFontActor();
}

bool EditorAction::IsAnyActorSelected() const
{
	return (EDITOR_PANEL(Inspector, "Inspector").GetCurrentActor() != nullptr);//EDITOR_LANGUAGE(MENU_INSPECTOR))
}

Actor& EditorAction::GetSelectedActor() const
{
	return *EDITOR_PANEL(Inspector, "Inspector").GetCurrentActor();//EDITOR_LANGUAGE(MENU_INSPECTOR))
}

EEditorMode EditorAction::GetCurrentEditorMode() const
{
	return m_editorMode;
}

void EditorAction::SetEditorMode(EEditorMode p_newEditorMode)
{
	m_editorMode = p_newEditorMode;
	EditorModeChangedEvent.Invoke(m_editorMode);
}

void EditorAction::StartPlay()
{
	m_context.m_sceneMgr->GetActiveScene()->Play();
}

void EditorAction::Exit()
{
	m_context.m_window.get()->SetShouldClose(true);
}
