#include "CAmbientSphereLight.h"

CAmbientSphereLight::CAmbientSphereLight(Actor& p_actor):
	CLight(p_actor)
{
	m_data.intensity = 0.1f;
	m_data.constant = 1.0f;

	m_data.type = static_cast<float>(Light::Type::Ambient_Sphere);
}

std::string CAmbientSphereLight::GetName()
{
	return "Ambient Sphere Light";
}

void CAmbientSphereLight::SetRadius(float p_radius)
{
	m_data.constant = p_radius;
}

float CAmbientSphereLight::GetRadius() const
{
	return m_data.quadratic;
}

void CAmbientSphereLight::OnInspector(WidgetContainer& p_root)
{
	CLight::OnInspector(p_root);

	GUIDrawer::DrawScalar<float>(p_root, "Radius", m_data.constant, 0.1f, 0.f);
}

void CAmbientSphereLight::OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
	CLight::OnSerialize(p_doc, p_node);

	Serializer::SerializeFloat(p_doc, p_node, "radius", m_data.constant);
}

void CAmbientSphereLight::OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
	CLight::OnDeserialize(p_doc, p_node);

	Serializer::DeserializeFloat(p_doc, p_node, "radius", m_data.constant);
}
