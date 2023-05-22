#pragma once
#include "../Widgets/AWidget.h"
#include "../../UI/UIManager.h"
#include "../Internel/UI_Common.h"

class ProgressBar :
    public AWidget
{
public:
    ProgressBar(float p_fraction = 0.0f, const Vector2& p_sze = Vector2( 0.0f, 0.0f) , const std::string&p_overlay = "");
protected:
    void _Draw_Impl()override;
public:
    float fraction;
    Vector2 size;
    std::string overlay;
};

