#include "Actor.h"
Actor::Actor(int64_t p_actionID, const std::string& p_name, const std::string& p_tag, bool& p_playing):
	m_actorID(p_actionID),
	m_name(p_name),
	m_tag(p_tag),
	m_playing(p_playing)
{
	CreateEvent.Invoke(*this);
}

Actor::~Actor()
{
	DestroyedEvent.Invoke(*this);
}

void Actor::OnAwake()
{

}

void Actor::OnStart()
{

}

void Actor::OnEnable()
{

}

void Actor::OnDisable()
{

}

void Actor::OnDestroy()
{

}

void Actor::OnUpdate(float p_deltaTime)
{

}

void Actor::OnFixedUpdate(float p_deltaTime)
{

}

void Actor::OnLateUpdate(float p_deltaTime)
{

}

bool Actor::IsActive()
{
	return true;
}

void Actor::OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_actorsRoot)
{
	tinyxml2::XMLNode* actorNode = p_doc.NewElement("actor");
	

}

void Actor::OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_actorsRoot)
{

}