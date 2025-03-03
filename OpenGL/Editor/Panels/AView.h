#pragma once

#include "../../UI/Panel/PanelWindow.h"
#include "../../Math/Math.h"
#include "../../Camera/Camera.h"
#include<glm/gtc/quaternion.hpp>

class Image;
class EditorRender;
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

	virtual ~AView();

	virtual void Update(float p_deltaTime);

	void _Draw_Impl() override;

	virtual void _Render_Impl() = 0;


	void Render();

	void SetCameraPosition(glm::vec3& p_position);

	void SetCameraRotation(glm::quat& p_rotation);

	void PrepareCamera();

	void FillEngineUBO();

	ImVec2 GetSafeSize();

protected:

	Camera m_camera;
	Vector3 m_camPos;
	Quaternion m_camRot;
	Image *m_img;

	EditorRender& m_editorRenderer;

	RenderTarget* m_renderTarget;
};

