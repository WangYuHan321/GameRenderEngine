#pragma once

#include <sol.hpp>

class LuaBinder
{
public:
	static void CallBinders(sol::state& p_luaState);
};

