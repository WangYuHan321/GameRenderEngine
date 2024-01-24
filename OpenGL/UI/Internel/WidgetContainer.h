#pragma once

#include "../Widgets/AWidget.h"
#include "UI_MemoryModel.h"

class WidgetContainer
{
public:

	void RemoveWidget(AWidget& p_widget);

	void RemoveAllWidgets();

	void CollectGarbages();

	void DrawWidgets();

	void ReverseDrawOrder(const bool reversed);// «∑Ò∞¥’’À≥–Ú‰÷»æ

	void ConsiderWidget(AWidget& p_widget, bool p_manageMemory = true);

	void UnconsiderWidget(AWidget& p_widget);

	template <typename T, typename ... Args>
	T& CreateWidget(Args&&... p_args)
	{
		m_widgets.emplace_back(new T(p_args...), MemoryMode::INTERNAL_MANAGMENT);
		T& instance = *reinterpret_cast<T*>(m_widgets.back().first);
		instance.SetParent(this);
		return instance;
	}

	std::vector<std::pair<AWidget*, MemoryMode>>& GetWidgets() { return m_widgets; }
protected:
	std::vector<std::pair<AWidget*, MemoryMode>> m_widgets;
	bool m_reversedDrawOrder = false;
};


