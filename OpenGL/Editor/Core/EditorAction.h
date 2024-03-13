#pragma once

#include "Context.h"
#include "EditorRender.h"
#include "PanelsManager.h"
#include "../../Global/ServiceLocator.h"
#include "../../File/XmlManager.h"

#undef CreateEvent

#define EDITOR_EXEC(action) ServiceLocator::getInstance()->Get<EditorAction>().action
#define EDITOR_BIND(method, ...) std::bind(&EditorAction::method, ServiceLocator::getInstance()->Get<EditorAction>(), ##__VA_ARGS__)
#define EDITOR_EVENT(target)  ServiceLocator::getInstance()->Get<EditorAction>().target
#define EDITOR_PANEL(type, id) ServiceLocator::getInstance()->Get<EditorAction>().GetPanelsManager().GetPanelAs<type>(id)

#define EDITOR_LANGUAGE(id) ServiceLocator::getInstance()->Get<XmlManager>().GetLanguage(id)

#define EDITOR_RENDERER()		 ServiceLocator::getInstance()->Get<EditorAction>().GetRenderer()
#define EDITOR_CONTEXT(instance) ServiceLocator::getInstance()->Get<EditorAction>().GetContext().instance

enum class EEditorMode { EDIT, PLAY, PAUSE, FRAME_BY_FRAME };

class EditorAction
{
public:

	EditorAction(Context& p_context, EditorRender& p_editorRender, PanelsManager& p_panelMgr);

	EditorRender& GetRenderer() { return m_renderer; }

	Context& GetContext();

	PanelsManager& GetPanelsManager();

	void SelectActor(Actor& p_target);

	void UnselectActor();

	Actor& CreateActorWithModel(std::string model, bool p_focuseonCreation = true, Actor* p_parent = nullptr, std::string p_name = "");

	Actor& CreateEmptyActor(bool p_focusOnCreation = true, Actor* p_parent = nullptr, std::string p_name = "");

	bool IsAnyActorSelected() const;

	Actor& GetSelectedActor() const;

	void StartPlay();

public:
	Event<Actor&> ActorSelectedEvent;
	Event<Actor&> ActorUnSelectedEvent;
	Event<EEditorMode> EditorModeChangedEvent;
	Event<> playEvent;

private:
	Context& m_context;
	PanelsManager& m_panelMgr;
	EditorRender& m_renderer;


};


