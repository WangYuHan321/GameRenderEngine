#include "AViewControllable.h"
AViewControllable::AViewControllable(const std::string& p_title,
	bool p_opend,
	const PanelWindowSetting& p_windowSetting,
	bool p_enableFocusInputs):
	AView(p_title, p_opend, p_windowSetting),
	m_cameraController(*this,
		m_camera,
		m_camPos, 
		m_camRot, 
		p_enableFocusInputs)
{
}

void AViewControllable::Update(float p_deltaTime)
{
	m_cameraController.HandleInputs(p_deltaTime);

	AView::Update(p_deltaTime);
}

CameraController& AViewControllable::GetCameraController()
{
	return m_cameraController;
}