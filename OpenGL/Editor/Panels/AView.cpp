#include "AView.h"
#include "../../Render/RenderTarget.h"
#include "../../UI/Visual/Image.h"

AView::AView
(
	const std::string& p_title,
	bool p_opened,
	const PanelWindowSetting& p_panelSetting
):
PanelWindow(p_title, p_opened, p_panelSetting)
{
	m_camPos = { -10.0f, 3.0f, 10.0f };
	m_camRot = glm::quat({ 0.0f, 135.0f, 0.0f });

	m_img = &CreateWidget<Image>(m_renderTarget->GetColorTexture(0)->ID, Vector2(0.f, 0.f));
	scrollable = false;
}

void AView::Update(float p_deltaTime)
{
	Vector2 size(GetSize().x - 0.f, GetSize().y - 25.f);
	m_img->size = size;
	m_renderTarget->Resize(size.x, size.y);
}

void AView::_Draw_Impl()
{
	//���ô��ڵ�paddingΪ0��ͼƬ�ؼ���������
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	PanelWindow::_Draw_Impl();
	ImGui::PopStyleVar();
}

void AView::Render()
{

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