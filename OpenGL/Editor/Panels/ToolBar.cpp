#include "ToolBar.h"
#include "../../Editor/Core/EditorAction.h"

ToolBar::ToolBar
(
	const std::string& p_title,
	bool p_opened,
	const PanelWindowSetting& p_panelSetting
):PanelWindow(p_title, p_opened, p_panelSetting)
{
	m_playButton = &CreateWidget<ButtonImage>(EDITOR_CONTEXT(m_editorResource)->GetTexture("Button_Play")->ID, ImVec2 { 20, 20 }, 0);
	m_pauseButton = &CreateWidget<ButtonImage>(EDITOR_CONTEXT(m_editorResource)->GetTexture("Button_Pause")->ID, ImVec2 { 20, 20 }, 0);
	m_stopButton = &CreateWidget<ButtonImage>(EDITOR_CONTEXT(m_editorResource)->GetTexture("Button_Stop")->ID, ImVec2 { 20, 20 }, 0);
	m_nextButton = &CreateWidget<ButtonImage>(EDITOR_CONTEXT(m_editorResource)->GetTexture("Button_Next")->ID, ImVec2 { 20, 20 }, 0);

	m_playButton->lineBreak = false;
	m_pauseButton->lineBreak = false;
	m_stopButton->lineBreak = false;
	m_nextButton->lineBreak = false;

	m_playButton->ClickedEvent += EDITOR_BIND(StartPlay);

	m_pauseButton->ClickedEvent += [this] {
		LOG_INFO("Pause Game Clicked!!!");
	};

	m_stopButton->ClickedEvent += [this] {
		LOG_INFO("Stop Game Clicked!!!");
	};

	m_nextButton->ClickedEvent += [this] {
		LOG_INFO("Next Game Clicked!!!");
	};
}


void ToolBar::_Draw_Impl()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));

	PanelWindow::_Draw_Impl();

	ImGui::PopStyleVar();
}
