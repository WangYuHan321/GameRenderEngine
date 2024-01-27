#pragma once
#include "../Widgets/AWidget.h"
#include "../Internel/UI_Common.h"
class Image :
    public AWidget
{

public:
    Image(uint32_t p_textureID, const ImVec2& p_size);

protected:
    void _Draw_Impl() override;

public:
    UTextureID textureID;
    ImVec2 size;
};

