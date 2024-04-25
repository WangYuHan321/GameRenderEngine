#include "Behaviour.h"

Event<Behaviour*> Behaviour::CreateEvent;
Event<Behaviour*> Behaviour::DestroyedEvent;

Behaviour::Behaviour(Actor& p_owner, std::string& p_name):
	AComponent(p_owner),
	m_scriptName(p_name)
{
	CreateEvent.Invoke(this);
}

Behaviour::~Behaviour()
{
	DestroyedEvent.Invoke(this);
}

void Behaviour::OnAwake()
{
	LuaCall("OnAwake");
}

void Behaviour::OnStart()
{
	LuaCall("OnStart");
}

void Behaviour::OnEnable()
{
	LuaCall("OnEnable");
}

void Behaviour::OnDisable()
{
	LuaCall("OnDisable");
}

void Behaviour::OnDestroy()
{
	LuaCall("OnDestroy");
}

bool Behaviour::RegisterToLuaContext(sol::state& p_luaState, const std::string& p_scriptFolder)
{
	auto result = p_luaState.safe_script_file(p_scriptFolder + "/" + m_scriptName, &sol::script_pass_on_error);

	if (!result.valid())
	{
		sol::error err = result;
		LOG_ERROR(err.what());
		return false;
	}
	else
	{
		if (result.return_count() == 1 && result[0].is<sol::table>())
		{
			m_object = result[0];
			m_object["owner"] = &owner;
			return true;
		}
		else
		{
			LOG_ERROR("'" + m_scriptName + "' missing return expression");
			return false;
		}
	}
}

void Behaviour::UnregisterFromLuaContext()
{
	m_object = sol::nil;
}

void Behaviour::OnSerialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
}

void Behaviour::OnDeserialize(tinyxml2::TinyXMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
}

void Behaviour::OnInspector(WidgetContainer& p_root)
{

}

std::string Behaviour::GetName()
{
	return "Behaviour";
}

std::string Behaviour::GetScriptName() const
{
	return m_scriptName;
}