#include "Actor.h"

 Event<Actor&> Actor::CreateEvent;
 Event<Actor&> Actor::DestroyedEvent;
 Event<Actor&, Actor&> Actor::AttachEvent;// attach this£¬ other actor 
 Event<Actor&> Actor::DettachEvent;// dettach this 

Actor::Actor(int64_t p_actionID, const std::string& p_name, const std::string& p_tag, bool& p_playing):
	m_actorID(p_actionID),
	m_name(p_name),
	m_tag(p_tag),
	m_playing(p_playing),
	m_transform(AddComponent<CTransform>())
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

Actor* Actor::GetParent() const
{
	return m_parent;
}

void Actor::SetParent(Actor& p_parent)
{
	DetachFromParent();

	m_parent = &p_parent;
	m_parentID = p_parent.m_actorID;
	m_transform.SetParent(p_parent.m_transform);

}

void Actor::DetachFromParent()
{
	DettachEvent.Invoke(*this);

	if (m_parent)
	{
		m_parent->m_children.erase(std::remove_if(m_parent->m_children.begin(), m_parent->m_children.end(), [this](Actor* p_element)
			{
				return p_element == this;
			}));
	}

	m_parent = nullptr;
	m_parentID = 0;

	m_transform.RemoveParent();
}

std::string& Actor::GetName()
{
	return m_name;
}

int64_t Actor::GetParentID() const
{
	return m_actorID;
}

std::vector<Actor*>& Actor::GetChildren()
{
	return m_children;
}

int64_t Actor::GetID()const
{
	return m_actorID;
}

void Actor::OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_actorsRoot)
{
	tinyxml2::XMLNode* actorNode = p_doc.NewElement("actor");
	

}

void Actor::OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_actorsRoot)
{

}