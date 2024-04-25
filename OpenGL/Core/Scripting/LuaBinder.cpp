#include "LuaBinder.h"
#include "LuaActorBinder.h"

void LuaBinder::CallBinders(sol::state& p_luaState)
{
	auto& L = p_luaState;

	LuaActorBinder::BindActor(L);
}