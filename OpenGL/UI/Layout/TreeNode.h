#pragma once

#include "../../Event/Event.h"
#include "../Widgets/DataWidget.h"
#include "../Internel/WidgetContainer.h"

class TreeNode : public DataWidget<std::string>, public WidgetContainer
{
public:
	TreeNode(const std::string& p_name = "", bool p_arrClickToOpen = false);

	void Open();

	void Close();

	bool IsOpened() const;

protected:
	virtual void _Draw_Impl() override;

public:

	std::string name;
	bool selected = false;
	bool leaf = false;

	Event<> ClickedEvent;
	Event<> DoubleClickEvent;
	Event<> OpenedEvent;
	Event<> ClosedEvent;


private:
	bool m_arrowClickToOpen = false;
	bool m_shouldOpen = false;
	bool m_shouldClose = false;
	bool m_opened = false;

};

