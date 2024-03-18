#include "CCamera.h"

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
	auto currentProjectionMode = m_camera.Perspective;

	GUIDrawer::DrawScalar<float>(p_root, "Field of View", std::bind(&CCamera::GetFov, this), std::bind(&CCamera::SetFov, this, std::placeholders::_1));

}

void CCamera::OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{

}

void CCamera::OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{

}