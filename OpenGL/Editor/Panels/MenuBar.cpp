#include "MenuBar.h"
#include "../Util/ActorCreationMenu.h"
#include "../../../UI/Visual/Separator.h"
#include "../../Editor/Core/EditorAction.h"

MenuBar::MenuBar()
{
	CreateWindowMenu();
	CreateActorsMenu();
}

void MenuBar::CreateWindowMenu()
{
	m_windowMenu = &CreateWidget<MenuList>(EDITOR_LANGUAGE(MENU_WINDOW));
	m_windowMenu->CreateWidget<MenuItem>(EDITOR_LANGUAGE(MENU_CLOSE_ALL)).ClickedEvent += std::bind(&MenuBar::OpenEveryWindows, this, false);
	m_windowMenu->CreateWidget<MenuItem>(EDITOR_LANGUAGE(MENU_OPEN_ALL)).ClickedEvent += std::bind(&MenuBar::OpenEveryWindows, this, true);
	m_windowMenu->CreateWidget<Separator>();//增加下划线 间隔

}

void MenuBar::CreateActorsMenu()
{
	auto& actorsMenu = CreateWidget<MenuList>(EDITOR_LANGUAGE(MENU_ACTOR));
	ActorCreationMenu::GenerateActorCreationMenu(actorsMenu);
}

void MenuBar::RegisterPanel(const std::string& p_name, PanelWindow& p_panel)
{
	auto& menuItem = m_windowMenu->CreateWidget<MenuItem>(p_name, "", true, true);
	menuItem.ValueChangedEvent += std::bind(&PanelWindow::SetOpened, &p_panel, std::placeholders::_1);

	m_panels.emplace(p_name, std::make_pair(std::ref(p_panel), std::ref(menuItem)));
}

void MenuBar::OpenEveryWindows(bool p_state)
{
	for (auto& [name, panel] : m_panels)
		panel.first.get().SetOpened(p_state);
}