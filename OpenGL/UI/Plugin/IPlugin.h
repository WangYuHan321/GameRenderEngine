#pragma once

class IPlugin
{
public:
	virtual void Execute() = 0;
	void* userData = nullptr;
};