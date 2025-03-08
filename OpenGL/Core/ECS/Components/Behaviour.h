#pragma once
#include "../Actor.h"
#include "../Components/AComponent.h"
#ifdef WINDOWS_PLATFORM
#include <sol.hpp>
#endif

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

#ifdef WINDOWS_PLATFORM
	bool RegisterToLuaContext(sol::state& p_luaState, const std::string& p_scriptFolder);
#endif

	void UnregisterFromLuaContext();

#ifdef WINDOWS_PLATFORM
	template<typename... Args>
	void LuaCall(const std::string& p_functionName, Args&&... p_args);
#endif

	virtual void OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

	virtual void OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

	virtual void OnInspector(WidgetContainer& p_root) override;

	virtual std::string GetName() override;

	std::string GetScriptName() const;

public:

	static Event<Behaviour*> CreateEvent;
	static Event<Behaviour*> DestroyedEvent;

	std::string m_scriptName;

private:
#ifdef WINDOWS_PLATFORM
	sol::table m_object = sol::nil;
#endif
};

#ifdef WINDOWS_PLATFORM
	#include "Behaviour.inl"
#endif