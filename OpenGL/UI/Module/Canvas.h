#pragma once
#include "../API/IDrawable.h"
#include "../Panel/APanel.h"

class Canvas : public IDrawable
{
public:
	void AddPanel(APanel& p_panel);

	void Draw()override;

private:
	std::vector<std::reference_wrapper<APanel>> m_panels;
	bool m_isDockspace = false;
};

