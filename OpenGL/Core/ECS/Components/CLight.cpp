#include "CLight.h"
#include "../Actor.h"


CLight::CLight(Actor& p_owner):
	AComponent(p_owner),
	m_data(p_owner.m_transform.GetFTransform(), {})
{
}

const Light& CLight::GetData() const
{
	return m_data;
}

void CLight::SetColor(const Color3& p_color)
{
	m_data.color = p_color;
}

void CLight::SetColor(const Color4& p_color)
{
	m_data.color = Color3(p_color.r, p_color.g, p_color.b);
}

void CLight::SetIntensity(float p_intensity)
{
	m_data.intensity = p_intensity;
}

float CLight::GetIntensity() const
{
	return m_data.intensity;
}

Color3 CLight::GetColor() const
{
	return m_data.color;
}

std::string CLight::GetName()
{
	return "BaseLight";
}

void CLight::OnInspector(WidgetContainer& p_root)
{
	GUIDrawer::DrawColor(p_root, "Color", reinterpret_cast<Color4&>(m_data.color));
	GUIDrawer::DrawScalar<float>(p_root, "Intensity", m_data.intensity, 0.005f, GUIDrawer::_MIN_FLOAT, GUIDrawer::_MAX_FLOAT);
}

void CLight::OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
	Serializer::SerializeColor3(p_doc, p_node, "color", m_data.color);
	Serializer::SerializeFloat(p_doc, p_node, "intensity", m_data.intensity);
}

void CLight::OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
	Serializer::DeserializeColor3(p_doc, p_node, "color", m_data.color);
	Serializer::DeserializeFloat(p_doc, p_node, "intensity", m_data.intensity);
}