#pragma once

#include "../../UI/Panel/PanelWindow.h"
#include "../../UI/Widgets/Button/ButtonImage.h"

class ToolBar : public PanelWindow
{
public:

	ToolBar
	(
		const std::string& p_title,
		bool p_opened,
		const PanelWindowSetting& p_panelSetting
	);

	void _Draw_Impl() override;

private:

	ButtonImage* m_playButton;
	ButtonImage* m_pauseButton;
	ButtonImage* m_stopButton;
	ButtonImage* m_nextButton;

};

