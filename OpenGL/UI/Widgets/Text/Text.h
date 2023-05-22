#pragma once
#include "../DataWidget.h"

class Text : public DataWidget<std::string>
{
public:
	Text(const std::string& p_content = "");
	 

protected:
	virtual void _Draw_Impl() override;

public:
	std::string content;

};