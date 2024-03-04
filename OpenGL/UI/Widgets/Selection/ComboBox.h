#pragma once

#include "../DataWidget.h"
#include "../../Event/Event.h"

class ComboBox : public DataWidget<int>
{
public:
	ComboBox(int p_currentChoice = 0);

protected:
	void _Draw_Impl()override;

public:
	std::map<int, std::string> choices;
	int currentChoice;

public:
	Event<int> ValueChangedEvent;
};

