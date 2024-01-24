#pragma once

#include "../../UI/Panel/PanelWindow.h"
#include "../../Math/Math.h"
#include "../../Camera/Camera.h"
#include<glm/gtc/quaternion.hpp>

class Image;
class RenderTarget;

class AView : public PanelWindow
{

public:
	AView
	(
		const std::string& p_title,
		bool p_opened,
		const PanelWindowSetting& p_panelSetting
	);

	virtual void Update(float p_deltaTime);

	void _Draw_Impl() override;

	virtual void _Render_Impl() = 0;


	void Render();

	void SetCameraPosition(glm::vec3& p_position);

	void SetCameraRotation(glm::quat& p_rotation);

protected:

	Camera m_camera;
	glm::vec3 m_camPos;
	glm::quat m_camRot;
	Image *m_img;

	RenderTarget* m_renderTarget;
};

