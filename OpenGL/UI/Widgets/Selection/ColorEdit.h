#pragma once

#include "../DataWidget.h"
#include "../../Event/Event.h"

class ColorEdit : public DataWidget<Color4>
{
public:
	/**
	* Constructor
	* @param p_enableAlpha
	* @param p_defaultColor
	*/
	ColorEdit(bool p_enableAlpha = false, const Color4& p_defaultColor = {});

protected:
	void _Draw_Impl() override;

public:
	bool enableAlpha;
	Color4 color;
	Event<Color4&> ColorChangedEvent;
};
