#include "MenuBar.h"
#include "../../../UI/Visual/Separator.h"

MenuBar::MenuBar()
{
	CreateWindowMenu();
}

void MenuBar::CreateWindowMenu()
{
	m_windowMenu = &CreateWidget<MenuList>("Window");
	m_windowMenu->CreateWidget<MenuItem>("Close all").ClickedEvent += std::bind(&MenuBar::OpenEveryWindows, this, false);
	m_windowMenu->CreateWidget<MenuItem>("Open all").ClickedEvent += std::bind(&MenuBar::OpenEveryWindows, this, true);
	m_windowMenu->CreateWidget<Separator>();

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