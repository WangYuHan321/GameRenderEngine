#pragma once

#include "AViewControllable.h"

class ModelView :public AViewControllable
{
public:
	ModelView
	(
		const std::string& p_title,
		bool p_opened,
		const PanelWindowSetting& p_panelSetting
	);

	~ModelView();

	virtual void _Render_Impl() override;
};

