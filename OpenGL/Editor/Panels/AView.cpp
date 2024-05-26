#include "AView.h"
#include "../../Render/RenderTarget.h"
#include "../../Editor/Core/EditorAction.h"
#include "../../UI/Visual/Image.h"
#include "../../Render/Forward/ForwardRenderer.h"

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
	m_camRot = Quaternion(Vector3ToQuat(Vector3(0.0f, 135.0f, 0.0f )));
	m_renderTarget = new RenderTarget(1, 1, GL_HALF_FLOAT, 1, true);


	m_img = &CreateWidget<Image>(m_renderTarget->GetColorTexture(0)->ID, ImVec2(0.f, 0.f));
	scrollable = false;
}

AView::~AView()
{
	if (m_renderTarget)
		delete m_renderTarget;
}

void AView::Update(float p_deltaTime)
{
	m_img->size = GetSafeSize();
	m_renderTarget->Resize(GetSafeSize().x, GetSafeSize().y);
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
	FillEngineUBO();

	ImVec2 size(GetSafeSize());

	EDITOR_CONTEXT(m_shapeDrawer)->SetViewProjection(m_camera.Projection * m_camera.View);

	dynamic_cast<ForwardRenderer*>(EDITOR_CONTEXT(m_renderer).get())->SetViewPort(0, 0, size.x, size.y);

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
	ImVec2 size(GetSafeSize());

	//1600 1200
	m_camera.CalculateProjectMatrix(size.x, size.y);
	m_camera.CalculateViewMatrix(m_camPos, m_camRot);

}

ImVec2 AView::GetSafeSize()
{
	auto result = ImVec2(GetSize().x, GetSize().y - 40.f); // 40 == title bar height
	return result;
}

void AView::FillEngineUBO()
{
	auto& engineUBO = *EDITOR_CONTEXT(m_engineUBO);

	size_t offset = sizeof(Matrix4);

	engineUBO.SetSubData(m_camera.View, sizeof(Matrix4));//这里可以用std::ref
	engineUBO.SetSubData(m_camera.Projection, 2 * sizeof(Matrix4));
	engineUBO.SetSubData(m_camPos, 3 * sizeof(Matrix4));
}
