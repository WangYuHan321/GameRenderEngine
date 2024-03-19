#pragma once

#include "../../UI/Panel/PanelWindow.h"
#include "../../Log/Logger.h"

class Group;
class TextColored;

class Console : public PanelWindow
{
public:
	Console
	(
		const std::string& p_title,
		bool p_opened,
		const PanelWindowSetting& p_panelSetting
	);

	std::pair<Color4, std::string> GetWidgetSettingsFromLogData(const LogData& p_logData);
	void OnLogIntercepted(LogData p_logData);
	void Clear();
//protected:
//	void _Draw_Impl() override;

private:
	Group* m_logGroup;
	std::unordered_map<TextColored*, LogLevel> m_logTextWidgets;

};

