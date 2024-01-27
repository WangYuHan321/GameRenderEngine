#include "Behaviour.h"

Event<Behaviour*> Behaviour::CreateEvent;
Event<Behaviour*> Behaviour::DestroyedEvent;

Behaviour::Behaviour(Actor& p_owner, const std::string& p_name):
	AComponent(p_owner),
	name(p_name)
{
	CreateEvent.Invoke(this);
}

Behaviour::~Behaviour()
{
	DestroyedEvent.Invoke(this);
}

void Behaviour::OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
}

void Behaviour::OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
}

void Behaviour::OnInspector(WidgetContainer& p_root)
{

}

std::string Behaviour::GetName()
{
	return "Behaviour";
}