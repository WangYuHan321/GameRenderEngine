#include "EditorAction.h"

#include "../../Global/ServiceLocator.h"

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