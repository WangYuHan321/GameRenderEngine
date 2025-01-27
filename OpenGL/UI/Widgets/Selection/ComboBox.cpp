#include "ComboBox.h"


ComboBox::ComboBox(int p_currentChoice):
	currentChoice(p_currentChoice),
	DataWidget<int>(currentChoice)
{

}


void ComboBox::_Draw_Impl()
{
	if (choices.find(currentChoice) == choices.end())
	{
		currentChoice = choices.begin()->first;
	}

	if (ImGui::BeginCombo(m_widgetID.c_str(), choices[currentChoice].c_str()))
	{
		for (const auto& [key, value] : choices)
		{
			bool selected = key == currentChoice;

			if (ImGui::Selectable(value.c_str(), selected))
			{
				if (!selected)
				{
					ImGui::SetItemDefaultFocus();
					currentChoice = key;
					ValueChangedEvent.Invoke(currentChoice);
					this->NotifyChange();
				}
			}
		}

		ImGui::EndCombo();
	}
}