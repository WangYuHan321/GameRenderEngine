#pragma once
#include "../API/IDrawable.h"
#include "../Internel/WidgetContainer.h"

class APanel : public IDrawable, public WidgetContainer
{
public:

	APanel();

	void Draw() override;

	const std::string& GetPanelID();

protected:
	virtual void _Draw_Impl() = 0;

public:
	bool enable = true;

protected:
	std::string m_panelID;

private:
	static uint64_t __PANEL_ID_INCREMENT;

};

