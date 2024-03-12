#include "EditorAction.h"

#include "../Panels/SceneView.h"
#include "../Panels/Inspector.h"
#include "../../Global/ServiceLocator.h"
#include "../../Core/ECS/Components/CModelRenderer.h"
#include "../../Core/ECS/Components/CMaterialRenderer.h"

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
	EDITOR_PANEL(Inspector, "Inspector").FocusActor(p_target);
}

Actor& EditorAction::CreateActorWithModel(std::string p_model, bool p_focuseonCreation, Actor* p_parent, std::string p_name)
{
	auto& instance = CreateEmptyActor(false, p_parent, p_name);

	auto& modelRenderer = instance.AddComponent<CModelRenderer>();

	auto model = m_context.modelMgr[p_model];
	if (model)
		modelRenderer.SetModel(model);

	auto& materialRenderer = instance.AddComponent<CMaterialRenderer>();
	const auto material = m_context.materialMgr["Data\\Engine\\Material\\Default.opmat"];

	if (material)
		materialRenderer.FillWithMaterial(*material);

	if (p_focuseonCreation)
		SelectActor(instance);

	return instance;
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

bool EditorAction::IsAnyActorSelected() const
{
	return (EDITOR_PANEL(Inspector, "Inspector").GetCurrentActor() != nullptr);
}

Actor& EditorAction::GetSelectedActor() const
{
	return *EDITOR_PANEL(Inspector, "Inspector").GetCurrentActor();
}

void EditorAction::StartPlay()
{
	m_context.m_sceneMgr->GetActiveScene()->Play();
}
