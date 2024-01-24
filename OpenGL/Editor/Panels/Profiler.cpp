#include "Profiler.h"
#include "../../../UI/Widgets/Selection/CheckBox.h"
#include "../../../UI/Widgets/Text/Text.h"
#include "../../../UI/Widgets/Text/TextColored.h"
#include "../../../UI/Widgets/Button/Button.h"

Profiler::Profiler(
	const std::string& p_title,
	bool p_opened,
	const PanelWindowSetting& p_windowSetting,
	float p_frequency
):
	PanelWindow(p_title, p_opened, p_windowSetting),
	m_frequency(p_frequency)
{
	allowHorizontalScrollbar = true;

	CreateWidget<Text>("Profile state: ").lineBreak = false;
	CreateWidget<CheckBox>(false, "").ValueChangedEvent += std::bind(&Profiler::Enable, this, std::placeholders::_1, false);

	m_fpsText = &CreateWidget<TextColored>("");
	m_captureResumeBtn = &CreateWidget<Button>("Capture");
	m_captureResumeBtn->idleColor = Color4(0.7f, 0.5f, 0.f, 1.f);
	m_captureResumeBtn->ClickedEvent += [this]
	{
		m_profilingMode = m_profilingMode == EProfilingMode::CAPTURE ? EProfilingMode::DEFAULT : EProfilingMode::CAPTURE;
		m_captureResumeBtn->label = m_profilingMode == EProfilingMode::CAPTURE ? "Resume" : "Capture";
	};
	m_elapsedFramesText = &CreateWidget<TextColored>("", Color4(1.f, 0.8f, 0.01f, 1));
	m_elapsedTimeText = &CreateWidget<TextColored>("", Color4(1.f, 0.8f, 0.01f, 1));
	/*m_separator = &CreateWidget<OvUI::Widgets::Visual::Separator>();*/
	m_actionList = &CreateWidget<Columns<5>>();
	m_actionList->widths = { 300.f, 100.f, 100.f, 100.f, 200.f };

	Enable(false, true);
}

void Profiler::Enable(bool p_value, bool p_disableLog)
{
	if (p_value)
	{

	}
}

void Profiler::Update(float m_deltaTime)
{

}

