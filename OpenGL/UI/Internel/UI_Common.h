#pragma once
#include<iostream>

using Vector2 = ImVec2;
using Vector4 = ImVec4;

inline Vector2 AddVector2(const Vector2& left, const Vector2& right)
{
	Vector2 result(0.0f, 0.0f);
	result.x = left.x + right.x;
	result.y = left.y + right.y;
	return result;
}

enum class HorizontalAlignment {
	Left,
	Center,
	Right
};

enum class VerticalAlignment {
	Top,
	Middle,
	Bottom
};


union UTextureID
{
	uint32_t ID;
	void* raw;
};

struct PanelWindowSetting
{
	bool closable = false;
	bool resizable = true;
	bool movable = true;
	bool docakable = false;
	bool scrollable = true;
	bool hideBackground = false;
	bool forceHorizontalScrollbar = false;
	bool forceVerticalScrollbar = false;
	bool allowHorizontalScrollbar = false;
	bool bringToFrontOnFocus = true;
	bool collapsable = false;
	bool allowInputs = true;
	bool titleBar = true;
	bool autoSize = false;
	PanelWindowSetting() = default;
	PanelWindowSetting(
		bool _closable,
		bool _resizable,
		bool _movable,
		bool _docakable,
		bool _scrollable,
		bool _hideBackground,
		bool _forceHorizontalScrollbar,
		bool _forceVerticalScrollbar,
		bool _allowHorizontalScrollbar,
		bool _bringToFrontOnFocus,
		bool _collapsable,
		bool _allowInputs,
		bool _titleBar,
		bool _autoSize
	) :
		closable(_closable),
		resizable(_resizable),
		movable(_movable),
		docakable(_docakable),
		scrollable(_scrollable),
		hideBackground(_hideBackground),
		forceHorizontalScrollbar(_forceHorizontalScrollbar),
		forceVerticalScrollbar(_forceVerticalScrollbar),
		allowHorizontalScrollbar(_allowHorizontalScrollbar),
		bringToFrontOnFocus(_bringToFrontOnFocus),
		collapsable(_collapsable),
		allowInputs(_allowInputs),
		titleBar(_titleBar),
		autoSize(_autoSize)
	{
	}
};
