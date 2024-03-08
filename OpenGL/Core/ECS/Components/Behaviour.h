
#include <sol.hpp>
#include "../Actor.h"
#include "../Components/AComponent.h"

class Behaviour : AComponent
{
public:
	
	Behaviour(Actor& p_owner, const std::string& p_name);

	~Behaviour();

	virtual void OnAwake();

	virtual void OnStart();

	virtual void OnEnable();

	virtual void OnDisable();

	virtual void OnDestroy();

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

	const std::string name;

private:
	sol::table m_object = sol::nil;
};

#include "Behaviour.inl"