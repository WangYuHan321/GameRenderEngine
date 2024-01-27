#pragma once

#include "../DataWidget.h"
#include "../../Event/Event.h"

class MenuItem : public DataWidget<bool>
{
public:
	MenuItem(const std::string& p_name, const std::string& p_shortcut = "", bool p_checkable = false, bool p_checked = false);

protected:
	void _Draw_Impl()override;

public:
	std::string name;
	std::string shortcut;
	bool checkable;
	bool checked;
	Event<> ClickedEvent;
	Event<bool> ValueChangedEvent;

private:
	bool m_selected;
};
