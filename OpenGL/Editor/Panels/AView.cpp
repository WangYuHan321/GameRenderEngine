#include "AView.h"
#include "../../Render/RenderTarget.h"
#include "../../Editor/Core/EditorAction.h"
#include "../../UI/Visual/Image.h"

AView::AView
(
	const std::string& p_title,
	bool p_opened,
	const PanelWindowSetting& p_panelSetting
):
	PanelWindow(p_title, p_opened, p_panelSetting),
	m_editorRenderer(EDITOR_RENDERER())
{
	m_camPos = { -10.0f, 3.0f, 10.0f };
	m_camRot = glm::quat({ 0.0f, 135.0f, 0.0f });
	m_renderTarget = new RenderTarget(1, 1, GL_HALF_FLOAT, 1, true);


	m_img = &CreateWidget<Image>(m_renderTarget->GetColorTexture(0)->ID, ImVec2(0.f, 0.f));
	scrollable = false;
}

void AView::Update(float p_deltaTime)
{
	ImVec2 size(GetSize().x - 0.f, GetSize().y - 25.f);
	m_img->size = size;
	m_renderTarget->Resize(size.x, size.y);
}

void AView::_Draw_Impl()
{
	//设置窗口的padding为0是图片控件充满窗口
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	PanelWindow::_Draw_Impl();
	ImGui::PopStyleVar();
}

void AView::Render()
{
	ImVec2 size(GetSize().x - 0.f, GetSize().y - 25.f);

	//EDITOR_CONTEXT(shapeDrawer)->SetViewProjection(m_camera.GetProjectionMatrix() * m_camera.GetViewMatrix());

	//EDITOR_CONTEXT(m_renderer)->SetViewPort(0, 0, winWidth, winHeight);
	_Render_Impl();
}

void AView::SetCameraPosition(glm::vec3& p_position)
{
	m_camPos = p_position;
}

void AView::SetCameraRotation(glm::quat& p_rotation)
{
	m_camRot = p_rotation;
}

void AView::PrepareCamera()
{
	ImVec2 size(GetSize().x - 0.f, GetSize().y - 25.f);

	m_camera.CalculateProjectMatrix(size.x, size.y);
}