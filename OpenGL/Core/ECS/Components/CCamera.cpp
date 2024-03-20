#include "CCamera.h"
#include "../../UI/Widgets/Selection/ComboBox.h"

CCamera::CCamera(Actor& p_actor):
	AComponent(p_actor)
{
}

CCamera::~CCamera()
{
}

Camera& CCamera::GetCamera()
{
	return m_camera;
}

float CCamera::GetFov()
{
	return m_camera.FOV;
}

void CCamera::SetFov(float fov)
{
	m_camera.FOV = fov;
}

float CCamera::GetSize()
{
	return m_camera.Size;
}

void CCamera::SetSize(float pSize)
{
	m_camera.Size = pSize;
}

float CCamera::GetFar()
{
	return m_camera.Far;
}

void CCamera::SetFar(float pFar)
{
	m_camera.Far = pFar;
}

float CCamera::GetNear()
{
	return m_camera.Near;
}

void CCamera::SetNear(float pNear)
{
	m_camera.Near = pNear;
}

Color4 CCamera::GetClearColor()
{
	return m_camera.ClearColor;
}

void CCamera::SetClearColor(Color4 p_clearColor)
{
	m_camera.ClearColor = p_clearColor;
}

std::string CCamera::GetName()
{
	return "CCamera";
}

void CCamera::OnInspector(WidgetContainer& p_root)
{
	GUIDrawer::DrawScalar<float>(p_root, GetLanguage(FIELD_OF_VIEW_TEXT), std::bind(&CCamera::GetFov, this), std::bind(&CCamera::SetFov, this, std::placeholders::_1));
	auto& fovWidget = *p_root.GetWidgets()[p_root.GetWidgets().size() - 1].first;
	auto& fovWidgetLabel = *p_root.GetWidgets()[p_root.GetWidgets().size() - 2].first;
	fovWidget.enabled = m_camera.Perspective; 
	fovWidgetLabel.enabled = m_camera.Perspective;

	GUIDrawer::DrawScalar<float>(p_root, GetLanguage(ORTHOGRAPHICS_SIZE), std::bind(&CCamera::GetSize, this), std::bind(&CCamera::SetSize, this, std::placeholders::_1));
	auto& sizeWidget = *p_root.GetWidgets()[p_root.GetWidgets().size() - 1].first;
	auto& sizeWidgetLabel = *p_root.GetWidgets()[p_root.GetWidgets().size() - 2].first;
	fovWidget.enabled = !m_camera.Perspective; 
	sizeWidgetLabel.enabled = !m_camera.Perspective;

	GUIDrawer::DrawScalar<float>(p_root, GetLanguage(NEAR_PANEL), std::bind(&CCamera::GetNear, this), std::bind(&CCamera::SetNear, this, std::placeholders::_1));
	GUIDrawer::DrawScalar<float>(p_root, GetLanguage(FAR_PANEL), std::bind(&CCamera::GetFar, this), std::bind(&CCamera::SetFar, this, std::placeholders::_1));
	GUIDrawer::DrawColor(p_root, GetLanguage(CLEAR_COLOR), [this]() {return GetClearColor(); }, [this](Color4 p_color) { SetClearColor({ p_color.r, p_color.g, p_color.b, 1.0f}); }, false);

	GUIDrawer::CreateTitle(p_root, GetLanguage(PROJECTION_MODE));
	auto& projectionMode = p_root.CreateWidget<ComboBox>(static_cast<int>(m_camera.Perspective));
	projectionMode.choices.emplace(0, "Orthographic");
	projectionMode.choices.emplace(1, "Perspective");
	projectionMode.ValueChangedEvent += [this, &fovWidget, &fovWidgetLabel, &sizeWidget, &sizeWidgetLabel](int p_choice)
	{
		m_camera.Perspective = static_cast<bool>(p_choice);
		fovWidget.enabled = fovWidgetLabel.enabled = m_camera.Perspective;
		sizeWidget.enabled = sizeWidgetLabel.enabled = !m_camera.Perspective;
	};

}

void CCamera::OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{

}

void CCamera::OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{

}