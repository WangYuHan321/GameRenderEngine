#pragma once
#include "Group.h"
#include "../../Event/Event.h"

class GroupCollapsable : public Group
{

public:
	GroupCollapsable(const std::string& p_name = "");

protected:
	virtual void _Draw_Impl() override;

public:

	std::string name;
	bool closeable = false;
	bool opened = true;

	Event<> CloseEvent;
	Event<> OpenEvent;

};

