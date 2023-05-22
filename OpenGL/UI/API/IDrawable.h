#pragma once

//接口 对于任何一个可绘制的class  from Overload

class IDrawable
{
public:
	virtual void Draw() = 0;
protected:
	virtual ~IDrawable() = default;
};
