#pragma once

#include "IPlugin.h"
#include "../Internel/WidgetContainer.h"


class ContextualMenu : public IPlugin, public WidgetContainer
{
public:

	void Execute();

	void Close();

};

