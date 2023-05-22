#pragma once

#include<GLM/glm.hpp>
#include "AButton.h"

class Button :
    public AButton
{
public:
    Button(const std::string & p_lable = "", const ImVec2& p_size = ImVec2(0.0f, 0.0f), bool p_disable = false);

protected:
    void _Draw_Impl()override;

public:
    std::string label;
    ImVec2 size;
    bool disable = false;

    Color4 idleColor;
    Color4 hoveredColor;
    Color4 clickedColor;

    Color4 textColor;
};

