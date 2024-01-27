#pragma once

#include<string>
#include "../../../Event/Event.h"
#include"../API/ISerializable.h"
#include"../ECS/Components/AComponent.h"


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

	int64_t GetParentID() const;

	int64_t GetID()const ;

	virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_actorsRoot) override;

	virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_actorsRoot) override;

public:
	Event<AComponent&> ComponentAddedEvent;
	Event<AComponent&> ComponentRemovedEvent;
	
	Event<Actor&> CreateEvent;
	Event<Actor&> DestroyedEvent;
private:
	//È¥³ýcopy¹¹Ôì
	Actor(const Actor& p_actor) = delete;

private:
	int64_t	m_actorID;
	std::string m_name;
	std::string m_tag;
	bool m_active = true;
	bool& m_playing;

	Actor* m_parent = nullptr;

	std::vector<std::shared_ptr<AComponent>> m_components;

public:
	
};

