#pragma once

#include "AViewControllable.h"

class SceneView  :public AViewControllable
{
public:

	SceneView(
		const std::string& p_title,
		bool p_opened,
		const PanelWindowSetting& p_windowSettings
		);
	virtual void Update(float p_deltaTime) override;

	virtual void _Render_Impl() override;

	void RenderScene(uint8_t p_defaultRenderState);

	void test(Actor& pAct);

};

