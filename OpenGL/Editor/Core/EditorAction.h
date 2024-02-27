#pragma once

#include "Context.h"
#include "EditorRender.h"
#include "PanelsManager.h"
#include "../../Global/ServiceLocator.h"

#undef CreateEvent

#define EDITOR_BIND(method, ...) std::bind(&EditorAction::method, ServiceLocator::getInstance()->Get<EditorAction>(), ##__VA_ARGS__)

#define EDITOR_PANEL(type, id) ServiceLocator::getInstance()->Get<EditorAction>().GetPanelsManager().GetPanelAs<type>(id)

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


private:
	Context& m_context;
	PanelsManager& m_panelMgr;
	EditorRender& m_renderer;


};


