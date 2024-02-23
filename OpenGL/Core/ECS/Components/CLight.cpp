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

void CLight::SetColor(const Vector3& p_color)
{
	m_data.color = p_color;
}

void CLight::SetIntensity(float p_intensity)
{
	m_data.intensity = p_intensity;
}

float CLight::GetIntensity() const
{
	return m_data.intensity;
}

Vector3 CLight::GetColor() const
{
	return m_data.color;
}

std::string CLight::GetName()
{
	return "BaseLight";
}

void CLight::OnInspector(WidgetContainer& p_root)
{
	Color4 tmpColor = Color4(m_data.color.r, m_data.color.g, m_data.color.b, 1.0f);
	GUIDrawer::DrawColor4(p_root, "Color", tmpColor);
	GUIDrawer::DrawScalar<float>(p_root, "Intensity", m_data.intensity, 0.005f, GUIDrawer::_MIN_FLOAT, GUIDrawer::_MAX_FLOAT);
}

void CLight::OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
	Serializer::SerializeVec3(p_doc, p_node, "color", m_data.color);
	Serializer::SerializeFloat(p_doc, p_node, "intensity", m_data.intensity);
}

void CLight::OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
	Serializer::DeserializeVec3(p_doc, p_node, "color", m_data.color);
	Serializer::DeserializeFloat(p_doc, p_node, "intensity", m_data.intensity);
}