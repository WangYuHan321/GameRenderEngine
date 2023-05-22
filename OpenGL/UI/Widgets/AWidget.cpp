#include "AWidget.h"

uint64_t AWidget::_WIDGET_ID_INCREMENT = 0;

AWidget::AWidget()
{
	m_widgetID = "##" + std::to_string(_WIDGET_ID_INCREMENT++);
}

void AWidget::Draw()
{
	if (enabled)
	{
		_Draw_Impl();

		if (m_autoExecutePlugins)
			ExecutePlugins();

		if (!lineBreak)
			ImGui::SameLine();
	}
}

void AWidget::Destroy()
{
	m_destroyed = true;
}
