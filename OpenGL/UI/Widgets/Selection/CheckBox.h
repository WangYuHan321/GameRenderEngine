#pragma once

#include "../DataWidget.h"
#include "../../Event/Event.h"

class CheckBox :
	public DataWidget<bool>
{
public:
	CheckBox(bool p_valuer = false, const std::string& p_lable = "");

protected:
	void _Draw_Impl();

public:
	bool value;
	std::string label;
	Event<bool> ValueChangedEvent;
};

