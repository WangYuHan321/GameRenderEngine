#pragma once

#include "AView.h"
#include "../Core/CameraController.h"

class AViewControllable : public AView
{

public:
	AViewControllable(const std::string& p_title,
		bool p_opend,
		const PanelWindowSetting& p_windowSetting,
		bool p_enableFocusInputs = false);

	virtual void Update(float p_deltaTime) override;

	CameraController& GetCameraController();

protected:
	CameraController m_cameraController;

};

