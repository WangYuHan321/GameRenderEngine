#pragma once

#include "../../UI/Panel/PanelWindow.h"

class Group;

class TimeLine : public PanelWindow
{
public:
	TimeLine(const std::string& p_title,
		bool p_opened,
		const PanelWindowSetting p_windowSetting);

	void InitBar();
	void InitSequencer();

private:

	Group* m_barGroup;
	Group* m_sequencerGroup;
};

