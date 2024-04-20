#pragma once

#include <sol.hpp>
#include "../Actor.h"
#include "../Components/AComponent.h"

class Behaviour : public AComponent
{
public:
	
	Behaviour(Actor& p_owner, std::string& p_name);

	~Behaviour();

	virtual void OnAwake() override;

	virtual void OnStart() override;

	virtual void OnEnable() override;

	virtual void OnDisable() override;

	virtual void OnDestroy() override;

	bool RegisterToLuaContext(sol::state& p_luaState, const std::string& p_scriptFolder);

	void UnregisterFromLuaContext();

	template<typename... Args>
	void LuaCall(const std::string& p_functionName, Args&&... p_args);

	virtual void OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

	virtual void OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

	virtual void OnInspector(WidgetContainer& p_root) override;

	virtual std::string GetName() override;

public:

	static Event<Behaviour*> CreateEvent;
	static Event<Behaviour*> DestroyedEvent;

	std::string name;

private:
	sol::table m_object = sol::nil;
};

#include "Behaviour.inl"