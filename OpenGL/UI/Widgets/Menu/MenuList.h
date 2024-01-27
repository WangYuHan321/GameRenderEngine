#pragma once

#include "../../Event/Event.h"
#include "../../UI/Layout/Group.h"

class MenuList :public Group
{
public:

	MenuList(const std::string& p_name, bool p_locked = false);

protected:
	virtual void _Draw_Impl() override;

public:
	std::string name;
	bool locked;
	Event<> ClickedEvent;

private:
	bool m_opened;
};

