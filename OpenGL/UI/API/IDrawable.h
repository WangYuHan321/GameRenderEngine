#pragma once

//�ӿ� �����κ�һ���ɻ��Ƶ�class  from Overload

class IDrawable
{
public:
	virtual void Draw() = 0;
protected:
	virtual ~IDrawable() = default;
};
