#include "ProjectSettings.h"
#include "../../UI/Widgets/Button/Button.h"

ProjectSettings::ProjectSettings( const std::string& p_title,
    bool b_opened,
    const PanelWindowSetting& p_windowSet) 
   :PanelWindow(p_title, b_opened, p_windowSet)
{
    auto& saveButton = CreateWidget<Button>("Apply");
    saveButton.idleColor = { 0.0f, 0.5f, 0.0f, 1.0f };
    saveButton.ClickedEvent += [this]
    {
        Log("BUtton clicked!!!!!");
    };

    saveButton.lineBreak = false;

    auto& resetButton = CreateWidget<Button>("Reset");
    resetButton.idleColor = { 0.5f, 0.0f, 0.0f, 1.0f };
    resetButton.ClickedEvent += [this]
    {
        Log("BUtton clicked!!!!!");
    };

}