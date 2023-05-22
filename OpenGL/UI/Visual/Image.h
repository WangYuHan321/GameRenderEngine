#pragma once
#include "../Widgets/AWidget.h"
#include "../Internel/UI_Common.h"
class Image :
    public AWidget
{

public:
    Image(uint32_t p_textureID, const Vector2& p_size);

protected:
    void _Draw_Impl() override;

public:
    UTextureID textureID;
    Vector2 size;
};

