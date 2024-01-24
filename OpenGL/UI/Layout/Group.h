#pragma once

#include <array>
#include "../Widgets/AWidget.h"
#include "../Internel/WidgetContainer.h"

class Group : public AWidget, public WidgetContainer
{
protected:
	virtual void _Draw_Impl() override;
};

