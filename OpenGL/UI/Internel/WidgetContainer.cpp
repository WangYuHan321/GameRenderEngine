#include <algorithm>
#include "WidgetContainer.h"

void WidgetContainer::RemoveWidget(AWidget& p_widget)
{
	auto found = std::find_if(m_widgets.begin(), m_widgets.end(), [&p_widget](std::pair<AWidget*, MemoryMode>& p_pair)
		{
			return p_pair.first == &p_widget;
		});

	if (found != m_widgets.end())
	{
		if (found->second == MemoryMode::INTERNAL_MANAGMENT)
			delete found->first;

		m_widgets.erase(found);
	}
}

void WidgetContainer::RemoveAllWidgets() {
	std::for_each(m_widgets.begin(), m_widgets.end(), [](auto& pair)
		{
			if (pair.second == MemoryMode::INTERNAL_MANAGMENT)
				delete pair.first;
		});

	m_widgets.clear();
}

void WidgetContainer::CollectGarbages()
{
	m_widgets.erase(std::remove_if(m_widgets.begin(), m_widgets.end(), [](std::pair<AWidget*, MemoryMode>& p_item)
		{
			bool toDestroy = p_item.first && p_item.first->IsDestroyed();

			if (toDestroy && p_item.second == MemoryMode::INTERNAL_MANAGMENT)
				delete p_item.first;

			return toDestroy;
		}), m_widgets.end());
}

void WidgetContainer::DrawWidgets()
{
	CollectGarbages();

	if (m_reversedDrawOrder)
	{
		for (auto it = m_widgets.crbegin(); it != m_widgets.crend(); ++it)
			it->first->Draw();
	}
	else
	{
		for (const auto& widget : m_widgets)
			widget.first->Draw();
	}
}

void WidgetContainer::ReverseDrawOrder(const bool reversed)
{
	m_reversedDrawOrder = reversed;
}

void WidgetContainer::ConsiderWidget(AWidget& p_widget, bool p_manageMemory)
{
	m_widgets.emplace_back(std::make_pair(&p_widget, p_manageMemory ? MemoryMode::INTERNAL_MANAGMENT : MemoryMode::EXTERNAL_MANAGMENT));
	p_widget.SetParent(this);
}

void WidgetContainer::UnconsiderWidget(AWidget& p_widget)
{
	auto found = std::find_if(m_widgets.begin(), m_widgets.end(), [&p_widget](std::pair<AWidget*, MemoryMode>& p_pair)
		{
			return p_pair.first == &p_widget;
		});

	if (found != m_widgets.end())
	{
		p_widget.SetParent(nullptr);
		m_widgets.erase(found);
	}
}
