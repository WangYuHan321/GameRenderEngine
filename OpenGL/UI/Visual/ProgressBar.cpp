#include "ProgressBar.h"

ProgressBar::ProgressBar(float p_fraction, const Vector2& p_sze, const std::string& p_overlay):
	fraction(p_fraction), size(p_sze),overlay(p_overlay)
{
}

void ProgressBar::_Draw_Impl()
{
	ImGui::ProgressBar(fraction, size, !overlay.empty() ? overlay.c_str() : nullptr);
}