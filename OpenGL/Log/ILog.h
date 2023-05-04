#pragma once

#include<stdio.h>
#include<iostream>
#include<stdarg.h>

#define MAX_ARGNUM 1024

class ILog
{
	virtual void OutputError(const char* error) = 0;
};

class TipWindowLog : ILog {
public:
	virtual void OutputError(const char* error) override
	{
		//::MessageBox(nullptr, error, L"error title", 0);
		printf(error);
	}
};

class GlobalLog : public ILog
{
public:

	GlobalLog()
	{
	}

	virtual void OutputError(const char* error) override
	{
		std::cout << error << std::endl;
	}
};

static TipWindowLog GTipWindowLog;
static GlobalLog gLog;

static void Log(std::string mes, ...)
{
	char buffer[MAX_ARGNUM] = { 0 };
	va_list ap;
	va_start(ap, mes);
	vsprintf_s(buffer, mes.c_str(), ap);
	va_end(ap);
	printf("%s", buffer);
}


