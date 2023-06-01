
#include <sol.hpp>
#include "../Actor.h"
#include "../Components/AComponent.h"

class Behaviour : AComponent
{
public:
	
	Behaviour(Actor& p_owner, const std::string& p_name);

	~Behaviour();

	template<typename... Args>
	void LuaCall(const std::string& p_functionName, Args&&... p_args);

	virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

	virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

	virtual void OnInspector(WidgetContainer& p_root) override;

public:

	Event<Behaviour*> CreateEvent;
	Event<Behaviour*> DestroyedEvent;

	const std::string name;

private:
	sol::table m_object = sol::nil;
};

#include "Behaviour.inl"