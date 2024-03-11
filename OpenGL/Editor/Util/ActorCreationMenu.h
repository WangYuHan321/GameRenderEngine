#pragma once

#include <functional>
#include <optional>

class Actor;
class MenuList;

class ActorCreationMenu
{
public:

	ActorCreationMenu() = delete;

	static void GenerateActorCreationMenu(MenuList& p_menuList, Actor* p_parent = nullptr, std::optional<std::function<void()>> p_onItemClicked = {});
};

