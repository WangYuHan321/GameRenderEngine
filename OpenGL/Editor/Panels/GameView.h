#pragma once
#include "AView.h"
class GameView :
    public AView
{

public:

	GameView
	(
		const std::string& p_title,
		bool p_opened,
		const PanelWindowSetting& p_windowSettings
	);

	virtual void Update(float p_deltaTime) override;
	virtual void _Render_Impl() override;
};

