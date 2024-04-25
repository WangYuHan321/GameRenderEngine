#include "ScriptInterpreter.h"
#include "LuaBinder.h"
#include "../../../File/ConfigManager.h"
#include "../ECS/Components/Behaviour.h"

ScriptInterpreter::ScriptInterpreter(const std::string& p_scriptRootFolder):
	m_scriptRootFolder(p_scriptRootFolder)
{
	CreateLuaContextAndBindGlobals();

	Behaviour::CreateEvent += std::bind(&ScriptInterpreter::Consider, this, std::placeholders::_1);
	Behaviour::DestroyedEvent += std::bind(&ScriptInterpreter::Unconsider, this, std::placeholders::_1);
}


ScriptInterpreter::~ScriptInterpreter()
{
}

void ScriptInterpreter::CreateLuaContextAndBindGlobals()
{
	if (!m_luaState)
	{
		m_luaState = std::make_unique<sol::state>();
		m_luaState->open_libraries(
			sol::lib::base, 
			sol::lib::package,
			sol::lib::coroutine,
			sol::lib::string,
			sol::lib::os,
			sol::lib::math,
			sol::lib::table,
			sol::lib::debug, 
			sol::lib::bit32,
			sol::lib::io,
			sol::lib::utf8);

		(*m_luaState)["package"]["path"] = ConfigManager::getInstance()->GetFontPath() + "/Util";



		LuaBinder::CallBinders(*m_luaState);
		m_isOk = true;

		std::for_each(m_behaviours.begin(), m_behaviours.end(), [this](Behaviour* behaviour)
			{
				if (!behaviour->RegisterToLuaContext(*m_luaState, m_scriptRootFolder))
				{
					m_isOk = false;
					LOG_ERROR("Load Script Error : " + behaviour->GetScriptName());
				}	
			});

	}
}

void ScriptInterpreter::DestroyLuaContext()
{
	if (m_luaState)
	{
		std::for_each(m_behaviours.begin(), m_behaviours.end(), [this](Behaviour* behaviour)
			{
				behaviour->UnregisterFromLuaContext();
			});

		m_luaState.reset();
		m_isOk = false;
	}
}


void ScriptInterpreter::Consider(Behaviour* p_toConsider)
{
	if (m_luaState)
	{
		m_behaviours.push_back(p_toConsider);

		if (!p_toConsider->RegisterToLuaContext(*m_luaState, m_scriptRootFolder))
		{
			m_isOk = false;
			LOG_ERROR("Load Script Error : " + p_toConsider->GetScriptName());
		}

	}
}

void ScriptInterpreter::Unconsider(Behaviour* p_toUnconsider)
{
	if (m_luaState)
		p_toUnconsider->UnregisterFromLuaContext();

	m_behaviours.erase(std::remove_if(m_behaviours.begin(), m_behaviours.end(), [p_toUnconsider](Behaviour* behaviour)
		{
			return p_toUnconsider == behaviour;
		}));

	RefreshAll();
}

void ScriptInterpreter::RefreshAll()
{
	DestroyLuaContext();
	CreateLuaContextAndBindGlobals();
}

bool ScriptInterpreter::IsOk() const
{
	return m_isOk;
}