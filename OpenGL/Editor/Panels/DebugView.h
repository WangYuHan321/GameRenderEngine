#pragma once
#include "AView.h"

class Image;
class InputManager;

class DebugView :
	public AView
{

public:

	DebugView
	(
		const std::string& p_title,
		bool p_opened,
		const PanelWindowSetting& p_windowSettings
	);

	virtual void Update(float p_deltaTime) override;
	virtual void _Render_Impl() override;

private:

	void ShowShadowMap(int id);
	void ShowFont(int id);

protected:
	InputManager& m_inputMgr;
};

