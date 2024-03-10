#pragma once

#include <array>
#include "../../Event/Event.h"
#include "../DataWidget.h"

template< typename T, size_t _Size>
class DragMultipleScalars : public DataWidget<std::array<T, _Size>>
{
	static_assert(std::is_scalar<T>::value, "Invalid DragSingleScalar T (Scalar expected)");

public:
	DragMultipleScalars(
		ImGuiDataType p_dataType,
		T p_min,
		T p_max,
		T p_value,
		float p_speed,
		const std::string& p_label,
		const std::string& p_format
	) :
		DataWidget<std::array<T, _Size>>(values), m_dataType(p_dataType), min(p_min), max(p_max), speed(p_speed), label(p_label), format(p_format) 
	{
		values.fill(p_value);
	}


	void _Draw_Impl() override
	{
		if (max < min)
			max = min;

		for (size_t i = 0; i < _Size; ++i)
		{
			if (values[i] < min)
				values[i] = min;
			else if (values[i] > max)
				values[i] = max;
		}

		if (ImGui::DragScalarN((label + this->m_widgetID).c_str(), m_dataType, values.data(), _Size, speed, &min, &max, format.c_str()))
		{
			ValueChangedEvent.Invoke(values);
			this->NotifyChange();
		}
	}

public:
	T min;
	T max;
	float speed;
	std::array<T, _Size> values;
	std::string label;
	std::string format;
	Event<std::array<T, _Size>&> ValueChangedEvent;

private:
	ImGuiDataType m_dataType;
};

