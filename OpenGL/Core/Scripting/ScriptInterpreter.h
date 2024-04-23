#pragma once

#include <vector>

#include <sol.hpp>

class Behaviour;

class ScriptInterpreter
{
public:
	ScriptInterpreter(const std::string& p_scriptRootFolder);
	~ScriptInterpreter();

	void CreateLuaContextAndBindGlobals();
	void DestroyLuaContext();

	void Consider(Behaviour* p_toConsider);
	void Unconsider(Behaviour* p_toUnconsider);

	void RefreshAll();

	bool IsOk() const;

private:
	std::unique_ptr<sol::state> m_luaState;
	std::string m_scriptRootFolder;
	std::vector<Behaviour*> m_behaviours;
	bool m_isOk;
};

