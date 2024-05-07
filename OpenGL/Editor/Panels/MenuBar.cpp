#include "MenuBar.h"
#include "../Util/ActorCreationMenu.h"
#include "../../../UI/Visual/Separator.h"
#include "../../Editor/Core/EditorAction.h"
#include "../../Core/Util/SystemCall.h"
#include "../../Editor/Core/EditorAction.h"

MenuBar::MenuBar()
{
	CreateFileMenu();
	CreateWindowMenu();
	CreateActorsMenu();
	CreateSwitchLanguage();
}

void MenuBar::CreateFileMenu()
{
	auto& fileMenu = CreateWidget<MenuList>(EDITOR_LANGUAGE(MENU_FILE));

	fileMenu.CreateWidget<MenuItem>(EDITOR_LANGUAGE(MENU_SAVE_SCENE)).ClickedEvent += std::bind(&MenuBar::SaveScene, this);
	fileMenu.CreateWidget<MenuItem>(EDITOR_LANGUAGE(MENU_LOAD_SCENE)).ClickedEvent += std::bind(&MenuBar::LoadScene, this);
	fileMenu.CreateWidget<MenuItem>(EDITOR_LANGUAGE(MENU_EXIT)).ClickedEvent += [] { EDITOR_CONTEXT(m_window)->SetShouldClose(true); };

	fileMenu.CreateWidget<Separator>();//增加下划线 间隔
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

void MenuBar::CreateSwitchLanguage()
{
	//LANGUAGE curLang = EDITOR_CONTEXT(xmlMgr).GetLanguageType();
	auto& languageMenu = CreateWidget<MenuList>(EDITOR_LANGUAGE(MENU_LANGUAGE));
	languageMenu.CreateWidget<MenuItem>(EDITOR_LANGUAGE(MENU_LANGUAGE_ZH_CN)).ClickedEvent += std::bind(&MenuBar::SwitchLanguage, this, (int)false);//中文
	languageMenu.CreateWidget<MenuItem>(EDITOR_LANGUAGE(MENU_LANGUAGE_EN_US)).ClickedEvent += std::bind(&MenuBar::SwitchLanguage, this, (int)true);
}

void MenuBar::RegisterPanel(const std::string& p_name, PanelWindow& p_panel)
{
	auto& menuItem = m_windowMenu->CreateWidget<MenuItem>(p_name, "", true, true);
	menuItem.ValueChangedEvent += std::bind(&PanelWindow::SetOpened, &p_panel, std::placeholders::_1);

	m_panels.emplace(p_name, std::make_pair(std::ref(p_panel), std::ref(menuItem)));
}

void MenuBar::SaveScene()
{
	SystemCall::ShowSaveFileDialog("test");
}

void MenuBar::LoadScene()
{
	SystemCall::ShowOpenFileDialog("test");
}

void MenuBar::OpenEveryWindows(bool p_state)
{
	for (auto& [name, panel] : m_panels)
		panel.first.get().SetOpened(p_state);
}

void MenuBar::SwitchLanguage(int type)
{
	LANGUAGE curLang = (LANGUAGE)type;

	EDITOR_CONTEXT(xmlMgr).SwitchLanguage(curLang);
}
