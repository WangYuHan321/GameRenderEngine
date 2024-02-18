#include "PanelWindow.h"

PanelWindow::PanelWindow(const std::string& p_name,
	bool m_opened,
	const PanelWindowSetting& p_panelSetting):
	name(p_name),
	m_opened(m_opened),
	resizeable(p_panelSetting.resizable),
	closeable(p_panelSetting.closable),
	movable(p_panelSetting.movable),
	scrollable(p_panelSetting.scrollable),
	dockable(p_panelSetting.dockable),
	hideBackground(p_panelSetting.hideBackground),
	forceHorizontalScrollbar(p_panelSetting.forceHorizontalScrollbar),
	forceVerticalScrollbar(p_panelSetting.forceVerticalScrollbar),
	allowHorizontalScrollbar(p_panelSetting.allowHorizontalScrollbar),
	bringToFrontOnFocus(p_panelSetting.bringToFrontOnFocus),
	collapsable(p_panelSetting.collapsable),
	allowInputs(p_panelSetting.allowInputs)
{
}

void PanelWindow::Open()
{
	if (!m_opened)
	{
		m_opened = true;
		OpenEvent.Invoke();
	}
}

void PanelWindow::Close()
{
	if (m_opened)
	{
		m_opened = false;
		CloseEvent.Invoke();
	}
}

void PanelWindow::SetOpened(bool p_value)
{
	if (p_value != m_opened)
	{
		m_opened = p_value;

		if (m_opened)
			OpenEvent.Invoke();
		else
			CloseEvent.Invoke();
	}
}

void PanelWindow::_Draw_Impl()
{
	if (m_opened)
	{
		int windowFlags = ImGuiWindowFlags_None;

		if (!resizeable)				windowFlags |= ImGuiWindowFlags_NoResize;
		if (!movable)					windowFlags |= ImGuiWindowFlags_NoMove;
		if (!dockable)					windowFlags |= ImGuiWindowFlags_NoDocking;
		if (hideBackground)				windowFlags |= ImGuiWindowFlags_NoBackground;
		if (forceHorizontalScrollbar)	windowFlags |= ImGuiWindowFlags_AlwaysHorizontalScrollbar;
		if (forceVerticalScrollbar)		windowFlags |= ImGuiWindowFlags_AlwaysVerticalScrollbar;
		if (allowHorizontalScrollbar)	windowFlags |= ImGuiWindowFlags_HorizontalScrollbar;
		if (!bringToFrontOnFocus)		windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
		if (!collapsable)				windowFlags |= ImGuiWindowFlags_NoCollapse;
		if (!allowInputs)				windowFlags |= ImGuiWindowFlags_NoInputs;
		if (!scrollable)                windowFlags |= ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar;
		if (!titleBar)					windowFlags |= ImGuiWindowFlags_NoTitleBar;

		if (minSize.x < 0.f || minSize.y < 0.f)
			minSize = { 0.f, 0.f };
		if (maxSize.x < 0.f || maxSize.y < 0.f)
			maxSize = { 10000.0f, 10000.0f };

		ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
		if (ImGui::Begin((name + m_panelID).c_str(), closeable ? &m_opened : nullptr, windowFlags))
		{
			m_hovered = ImGui::IsWindowHovered();
			m_focused = ImGui::IsWindowFocused();

			auto scrollY = ImGui::GetScrollY();

			m_scrolledToBottom = scrollY == ImGui::GetScrollMaxY();
			m_scrolledToTop = scrollY == 0.0f;

			if (!m_opened)
				CloseEvent.Invoke();

			Update();
			
			if (m_mustScrollToBottom)
			{
				ImGui::SetScrollY(ImGui::GetScrollMaxY());
				m_mustScrollToBottom = false;
			}

			if (m_mustScrollToTop)
			{
				ImGui::SetScrollY(0.0f);
				m_mustScrollToTop = false;
			}

			DrawWidgets();
		}

	}
}
