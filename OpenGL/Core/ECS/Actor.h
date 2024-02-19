#pragma once

#include<string>
#include "../../../Event/Event.h"
#include"../API/ISerializable.h"
#include"../ECS/Components/AComponent.h"
#include"Components/CTransform.h"

class Actor : public ISerializable
{
public:
	Actor(int64_t p_actionID, const std::string& p_name, const std::string& p_tag, bool& p_playing);
	
	virtual ~Actor() override;

	void OnAwake();

	void OnStart();

	void OnEnable();

	void OnDisable();

	void OnDestroy();

	void OnUpdate(float p_deltaTime);

	void OnFixedUpdate(float p_deltaTime);

	void OnLateUpdate(float p_deltaTime);

	bool IsActive();

	Actor* GetParent() const;

	void SetParent(Actor& p_parent);

	void DetachFromParent();

	std::string& GetName();

	int64_t GetParentID() const;

	std::vector<Actor*>& GetChildren();

	int64_t GetID()const ;

	template<typename T>
	T* GetComponent();

	template<typename T>
	bool RemoveComponent(T& type);

	template<typename T, typename... Args>
	T& AddComponent(Args&&... p_args);

	virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_actorsRoot) override;

	virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_actorsRoot) override;

public:
	Event<AComponent&> ComponentAddedEvent;
	Event<AComponent&> ComponentRemovedEvent;
	
	static Event<Actor&> CreateEvent;
	static Event<Actor&> DestroyedEvent;
	static Event<Actor&, Actor&> AttachEvent;// attach this£¬ other actor 
	static Event<Actor&> DettachEvent;// dettach this 
private:
	//È¥³ýcopy¹¹Ôì
	Actor(const Actor& p_actor) = delete;

private:
	int64_t	m_actorID;
	std::string m_name;
	std::string m_tag;
	bool m_active = true;
	bool& m_playing;

	int64_t m_parentID = 0;
	Actor* m_parent = nullptr;
	std::vector<Actor*> m_children;

	std::vector<std::shared_ptr<AComponent>> m_components;

public:
	CTransform& m_transform;
};

#include "Actor.inl"