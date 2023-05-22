#include "APanel.h"

uint64_t APanel::__PANEL_ID_INCREMENT = 0;

APanel::APanel()
{
	m_panelID = "##" + std::to_string(__PANEL_ID_INCREMENT++);
}

void APanel::Draw()
{
	if(enable)
		_Draw_Impl();
}

const std::string& APanel::GetPanelID()
{
	return m_panelID;
}