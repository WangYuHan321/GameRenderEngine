#include "ContextualMenu.h"

void ContextualMenu::Execute()
{
	if (ImGui::BeginPopupContextItem())
	{
		DrawWidgets();
		ImGui::EndPopup();
	}
}

void ContextualMenu::Close()
{
	ImGui::CloseCurrentPopup();
}