#include "Console.h"
#include <algorithm>
#include "../../UI/Visual/Separator.h"
#include "../../UI/Widgets/Button/Button.h"
#include "../../UI/Widgets/Text/Text.h"
#include "../../UI/Widgets/Text/TextColored.h"
#include "../../UI/Widgets/Selection/ComboBox.h"
#include "../../Editor/Helper/GUIDrawer.h"
#include "../../Render/Shader/EShader.h"
#include "../../Render/Resource/Loader/MaterialLoader.h"
#include "../../UI/Layout/GroupCollapsable.h"
#include "../../Editor/Core/EditorAction.h"
#include "../../File/Path/PathParser.h"
#include "../../Log/ILogHandler.h"

Console::Console
(
	const std::string& p_title,
	bool p_opened,
	const PanelWindowSetting& p_panelSetting
)
{
	allowHorizontalScrollbar = true;

	m_logGroup = &CreateWidget<Group>();
	m_logGroup->ReverseDrawOrder(true);//ƒÊ–Úœ‘ æ

	auto& clearBtn = CreateWidget<Button>(EDITOR_LANGUAGE(CLEAR_TEXT));
	clearBtn.lineBreak = false;
	
	//LogEvent += std::bind(&Console::OnLogIntercepted, this, std::placeholders::_1);
}

std::pair<Color4, std::string> Console::GetWidgetSettingsFromLogData(const LogData& p_logData)
{
	Color4 logColor;
	std::string logHeader;
	std::string logDateFormated = "[";
	bool isSecondPart = false;
	std::for_each(p_logData.date.begin(), p_logData.date.end(), [&logDateFormated, &isSecondPart](char c)
		{
			if (isSecondPart)
				logDateFormated.push_back(c == '-' ? ':' : c);

			if (c == '_')
				isSecondPart = true;
		});

	logDateFormated += "] ";

	switch (p_logData.logLevel)
	{
	default:
		case LogLevel::Log_Default:	return { { 1.f, 1.f, 1.f, 1.f }, logDateFormated };
		case LogLevel::Log_Info:		return { { 0.f, 1.f, 1.f, 1.f }, logDateFormated };
		case LogLevel::Log_Warning:	return { { 1.f, 1.f, 0.f, 1.f }, logDateFormated };
		case LogLevel::Log_Error:		return { { 1.f, 0.f, 0.f, 1.f }, logDateFormated };
	}
}

//void Console::_Draw_Impl()
//{
//	PanelWindow::_Draw_Impl();
//	if (Logger::getInstance()->GetAllLogData().size() > 0)
//	{
//		std::vector<LogData> info = Logger::getInstance()->GetAllLogData();
//		for (auto item : info)
//		{
//			OnLogIntercepted(item);
//		}
//
//	}
//}

void Console::OnLogIntercepted(LogData p_logData)
{
	auto [logColor, logDate] = GetWidgetSettingsFromLogData(p_logData);

	auto& consoleItem1 = m_logGroup->CreateWidget<TextColored>(logDate + "\t" + p_logData.message, logColor);

	m_logTextWidgets[&consoleItem1] = p_logData.logLevel;
}

void Console::Clear()
{
	m_logTextWidgets.clear();
	m_logGroup->RemoveAllWidgets();
}
