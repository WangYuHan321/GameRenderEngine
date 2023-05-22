#pragma once

#include "../UI/Panel/PanelWindow.h"
#include "../UI/Layout/Columns.h"

class Button;
class TextColored;

class Profiler : public PanelWindow
{
public:
	Profiler(
		const std::string& p_title,
		bool p_opened,
		const PanelWindowSetting& p_windowSetting,
		float p_frequency
	);

	void Update(float m_deltaTime);
	void Enable(bool p_value, bool p_disableLog = false);

private:
	enum class EProfilingMode
	{
		DEFAULT,
		CAPTURE
	};

	EProfilingMode m_profilingMode = EProfilingMode::DEFAULT;
	float m_frequency;

	//AWidget* m_separator;
	Button* m_captureResumeBtn;
	TextColored* m_fpsText;
	TextColored* m_elapsedFramesText;
	TextColored* m_elapsedTimeText;
	Columns<5>* m_actionList;

};

