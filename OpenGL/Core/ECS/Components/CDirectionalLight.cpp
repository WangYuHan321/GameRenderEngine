#include "CDirectionalLight.h"

CDirectionalLight::CDirectionalLight(Actor& p_owner):
	CLight(p_owner)
{
	m_data.type = static_cast<float>(Light::Type::Directional);
}

std::string CDirectionalLight::GetName()
{
	return "DirectionalLight";
}

void CDirectionalLight::OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
	CLight::OnSerialize(p_doc, p_node);
}

void CDirectionalLight::OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
	CLight::OnDeserialize(p_doc, p_node);
}

void CDirectionalLight::OnInspector(WidgetContainer& p_root)
{
	CLight::OnInspector(p_root);

}