#pragma once

#include "Text.h"
#include "../../Event/Event.h"

class TextClickable : public Text
{
public:
	TextClickable(const std::string content = "");
protected:
	virtual void _Draw_Impl() override;

public:
	Event<> ClickedEvent;
	Event<> DoubleClickedEvent;
};

