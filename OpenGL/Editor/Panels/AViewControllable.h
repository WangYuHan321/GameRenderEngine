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

	~AViewControllable() {}

	virtual void Update(float p_deltaTime);

	CameraController& GetCameraController();

protected:
	CameraController m_cameraController;

};

