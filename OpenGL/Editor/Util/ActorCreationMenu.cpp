#include "ActorCreationMenu.h"
#include "../Core/EditorAction.h"

std::function<void()> Combine(std::function<void()> p_a, std::optional<std::function<void()>> p_b)
{
    if (p_b.has_value())
    {
        return [=]()
        {
            p_a();
            p_b.value()();
        };
    }

    return p_a;
}

std::function<void()> ActorWithModelComponentCreationHandler(Actor* p_parent, const std::string& p_modelName, std::optional<std::function<void()>> p_onItemClicked)
{
    return Combine(EDITOR_BIND(CreateActorWithModel,  p_modelName + ".fbx", true, p_parent, p_modelName), p_onItemClicked);
}

std::function<void()> ActorWithAsynLoadModelComponentCreationHandler(Actor* p_parent, const std::string& p_modelName, std::optional<std::function<void()>> p_onItemClicked)
{
    return Combine(EDITOR_BIND(CreateActorWithAsynModel, p_modelName + ".fbx", true, p_parent, p_modelName), p_onItemClicked);
}

void ActorCreationMenu::GenerateActorCreationMenu(MenuList& p_menuList, Actor* p_parent, std::optional<std::function<void()>> p_onItemClicked)
{
	p_menuList.CreateWidget<MenuItem>(EDITOR_LANGUAGE(MENU_CREATE_EMPTY)).ClickedEvent += Combine(EDITOR_BIND(CreateEmptyActor, true, p_parent, ""), p_onItemClicked);
    p_menuList.CreateWidget<MenuItem>(EDITOR_LANGUAGE(MENU_CREATE_FONT)).ClickedEvent += Combine(EDITOR_BIND(CreateFontActor), p_onItemClicked);

	auto& primitives = p_menuList.CreateWidget<MenuList>(EDITOR_LANGUAGE(MENU_PRIMITIVE));

    primitives.CreateWidget<MenuItem>(EDITOR_LANGUAGE(MENU_CUBE)).ClickedEvent += ActorWithModelComponentCreationHandler(p_parent, "Cube", p_onItemClicked);
    primitives.CreateWidget<MenuItem>(EDITOR_LANGUAGE(MENU_SPHERE)).ClickedEvent += ActorWithModelComponentCreationHandler(p_parent, "Sphere", p_onItemClicked);
    primitives.CreateWidget<MenuItem>(EDITOR_LANGUAGE(MENU_CYLINDER)).ClickedEvent += ActorWithModelComponentCreationHandler(p_parent, "Cylinder", p_onItemClicked);
    primitives.CreateWidget<MenuItem>(EDITOR_LANGUAGE(MENU_PLANE)).ClickedEvent += ActorWithModelComponentCreationHandler(p_parent, "Plane", p_onItemClicked);
    primitives.CreateWidget<MenuItem>(EDITOR_LANGUAGE(MENU_CONE)).ClickedEvent += ActorWithModelComponentCreationHandler(p_parent, "Cone", p_onItemClicked);
    primitives.CreateWidget<MenuItem>(EDITOR_LANGUAGE(MENU_VERTICALPLANE)).ClickedEvent += ActorWithModelComponentCreationHandler(p_parent, "Vertical_Plane", p_onItemClicked);
    primitives.CreateWidget<MenuItem>(EDITOR_LANGUAGE(MENU_TORUS)).ClickedEvent += ActorWithModelComponentCreationHandler(p_parent, "Torus", p_onItemClicked);
    primitives.CreateWidget<MenuItem>(EDITOR_LANGUAGE(MENU_CERBERUS)).ClickedEvent += ActorWithAsynLoadModelComponentCreationHandler(p_parent, "Camera", p_onItemClicked);
}