#pragma once
#include <unordered_map>
#include "../../UI/Widgets/Menu/MenuItem.h"
#include "../../UI/Widgets/Menu/MenuList.h"
#include "../../UI/Panel/PanelWindow.h"
#include "../../UI/Panel/PanelMenuBar.h"
class MenuBar :
    public PanelMenuBar
{
    using PanelMap = std::unordered_map<std::string, std::pair<std::reference_wrapper<PanelWindow>, std::reference_wrapper<MenuItem>>>;

public:

    MenuBar();
    void RegisterPanel(const std::string& p_name, PanelWindow& p_panel);

    void CreateWindowMenu();

    void CreateActorsMenu();

    void CreateSwitchLanguage();

    void OpenEveryWindows(bool p_state);

    void SwitchLanguage(int type);

private:
    PanelMap m_panels;

    MenuList* m_windowMenu = nullptr;
};

