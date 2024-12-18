#include "Actor.h"

 Event<Actor&> Actor::CreateEvent;
 Event<Actor&> Actor::DestroyedEvent;
 Event<Actor&, Actor&> Actor::AttachEvent;// attach this�� other actor 
 Event<Actor&, Actor&> Actor::DettachEvent;// dettach this 

Actor::Actor(int64_t p_actionID, const std::string& p_name, const std::string& p_tag, bool& p_playing):
	m_actorID(p_actionID),
	m_name(p_name),
	m_tag(p_tag),
	m_playing(p_playing),
	m_children({}),
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
	std::for_each(m_components.begin(), m_components.end(), [](auto element) { element->OnAwake(); });
}

void Actor::OnStart()
{
	std::for_each(m_components.begin(), m_components.end(), [](auto element) { element->OnStart(); });
}

void Actor::OnEnable()
{
	std::for_each(m_components.begin(), m_components.end(), [](auto element) { element->OnEnable(); });
}

void Actor::OnDisable()
{
	std::for_each(m_components.begin(), m_components.end(), [](auto element) { element->OnDisable(); });
}

void Actor::OnDestroy()
{
	std::for_each(m_components.begin(), m_components.end(), [](auto element) { element->OnDestroy(); });
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
	return m_active;
}

void Actor::SetActive(bool act)
{
	m_active = act;
}

bool Actor::HasParent() const
{
	return m_parent != nullptr;
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
	m_parent->m_children.push_back(this);


	m_transform.SetParent(p_parent.m_transform);

	AttachEvent.Invoke(*this, p_parent);
}

void Actor::DetachFromParent()
{
	DettachEvent.Invoke(*this, *m_parent);

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

void Actor::SetName(const std::string& p_name)
{
	m_name = p_name;
}

std::string& Actor::GetTag()
{
	return m_tag;
}

void Actor::SetTag(const std::string& p_tag)
{
	m_tag = p_tag;
}

int64_t Actor::GetParentID() const
{
	return m_actorID;
}

std::vector<Actor*>& Actor::GetChildren()
{
	return m_children;
}

bool Actor::HasChildren()
{
	return m_children.size() > 0;
}

std::vector<std::shared_ptr<AComponent>> Actor::GetComponents()
{
	return m_components;
}

int64_t Actor::GetID()const
{
	return m_actorID;
}

void Actor::OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_actorsRoot)
{
	tinyxml2::XMLNode* actorNode = p_doc.NewElement("actor");
	

}

void Actor::OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_actorsRoot)
{

}