#pragma once

#include "../Core/Context.h"
#include "../../UI/Module/Canvas.h"
#include "../../Editor/Core/EditorRender.h"
#include "../../Editor/Core/EditorAction.h"
#include "../../Editor/Core/PanelsManager.h"

class Editor
{
public:
	Editor(Context& p_context);

	~Editor();

	void SetUpUI();
	void PreUpdate();
	void Update(float deltaTime);
	void PostUpdate();


	void RenderViews(float p_deltaTime);
	void RenderEditorUI(float p_deltaTime);

private:
	uint64_t m_elapsedFrames = 0;
	Canvas m_canvas;
	Context& m_context;
	EditorRender m_editorRender;
	PanelsManager m_panelsMgr;
	EditorAction m_editorAction;

};

