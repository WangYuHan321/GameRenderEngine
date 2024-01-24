#pragma once

#include "Context.h"
#include "EditorRender.h"
#include "PanelsManager.h"
#include "../../Global/ServiceLocator.h"

#define EDITOR_CONTEXT(instance) ServiceLocator::getInstance()->Get<EditorAction>().GetContext().instance

enum class EEditorMode { EDIT, PLAY, PAUSE, FRAME_BY_FRAME };

class EditorAction
{
public:

	EditorAction(Context& p_context, EditorRender& p_editorRender, PanelsManager& p_panelMgr);

	EditorRender& GetRenderer() { return m_renderer; }

	Context& GetContext();


private:
	Context& m_context;
	PanelsManager& m_panelMgr;
	EditorRender& m_renderer;



};

