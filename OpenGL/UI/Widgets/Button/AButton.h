#pragma once

#include "../AWidget.h"
#include "../../../Event/Event.h"

class AButton : public AWidget
{
protected:
	void _Draw_Impl() override = 0;

public:
	Event<> ClickedEvent; 
};

