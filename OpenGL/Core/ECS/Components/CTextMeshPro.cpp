#include "CTextMeshPro.h"

CTextMeshPro::CTextMeshPro(Actor& p_actor):
	AComponent(p_actor),
	m_inputText("")
{

}

CTextMeshPro::~CTextMeshPro()
{

}

std::string CTextMeshPro::GetContent()
{
	return m_inputText;
}

std::string CTextMeshPro::GetName()
{
	return "CInputTextPro";
}

void CTextMeshPro::OnInspector(WidgetContainer& p_root)
{
	//GUIDrawer::DrawString()
}

void CTextMeshPro::OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{

}

void CTextMeshPro::OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{

}