#pragma once
#include "../../UI/Panel/PanelWindow.h"
class ProjectSettings :
    public PanelWindow
{
public:
    ProjectSettings(
        const std::string& p_title,
        bool b_opened,
        const PanelWindowSetting& p_windowSet
    );

    template <typename T>
    std::function<T()> GenerateGatherer(const std::string& p_keyName)
    {
        return std::bind();
    }

    template <typename T>
    std::function<T()> GenerateProvider(const std::string& p_keyName)
    {
        return std::bind();
    }

};

