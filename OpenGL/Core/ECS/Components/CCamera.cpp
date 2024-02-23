#include "CCamera.h"

CCamera::CCamera(Actor& p_actor):
	AComponent(p_actor)
{
}

CCamera::~CCamera()
{
}

std::string CCamera::GetName()
{
	return "CCamera";
}

void CCamera::OnInspector(WidgetContainer& p_root)
{

}

void CCamera::OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{

}

void CCamera::OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{

}