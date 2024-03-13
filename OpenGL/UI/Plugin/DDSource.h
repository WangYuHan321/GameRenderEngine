#pragma once

#include <string>
#include "IPlugin.h"
#include "../../Event/Event.h"

template<typename T>
class DDSource : public IPlugin
{
public:
	DDSource
	(
		const std::string& p_identifier,
		const std::string& p_toolTip,
		T p_data
	) :
		identifier(p_identifier),
		toolTip(p_toolTip),
		data(p_data) {}

	virtual void Execute() override
	{
		ImGuiDragDropFlags src_flags = 0;
		
		src_flags |= ImGuiDragDropFlags_SourceNoDisableHover;//��ͣʱ��ʾԴ�ļ�
		src_flags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers; // draging �޷���

		if(!hasTooltip)
			src_flags |= ImGuiDragDropFlags_SourceNoPreviewTooltip;//�Ƿ���ʾui��ק��

		if (ImGui::BeginDragDropSource(src_flags))
		{
			if (!m_isDragged)
				DragStartEvent.Invoke();

			m_isDragged = true;

			if (!(src_flags & ImGuiDragDropFlags_SourceNoPreviewTooltip))
				ImGui::Text(toolTip.c_str());
			ImGui::SetDragDropPayload(identifier.c_str(), &data, sizeof(data));
			ImGui::EndDragDropSource();
		}
		else
		{
			if (m_isDragged)
				DragStopEvent.Invoke();

			m_isDragged = false;
		}
	}

public:
	std::string identifier;
	std::string toolTip;
	T data;

	Event<> DragStartEvent;
	Event<> DragStopEvent;

	bool hasTooltip = true;

private:
	bool m_isDragged;
};

