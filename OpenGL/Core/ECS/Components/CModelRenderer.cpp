#include "CModelRenderer.h"

CModelRenderer::CModelRenderer(Actor& p_owner):
	AComponent(p_owner)
{
	m_modelChangedEvent += [this]
	{

	};
}

void CModelRenderer::SetModel(Model* p_model)
{
	m_model = p_model;
}

Model* CModelRenderer::GetModel() const
{
	return m_model;
}

std::string CModelRenderer::GetName()
{
	return "CModelRenderer";
}

void CModelRenderer::OnInspector(WidgetContainer& p_root)
{

}

void CModelRenderer::OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{

}

void CModelRenderer::OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{

}