#include "CheckBox.h"
CheckBox::CheckBox(bool p_valuer, const std::string& p_lable):
	DataWidget<bool>(p_valuer),value(p_valuer), label(p_lable)
{
}

void CheckBox::_Draw_Impl()
{
	bool previousValue = value;

	ImGui::Checkbox((label + m_widgetID).c_str(), &value);

	if (value)
	{
		ValueChangedEvent.Invoke(value);
		this->NotifyChange();
	}
}