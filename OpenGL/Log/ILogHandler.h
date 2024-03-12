#pragma once

#include<stdio.h>
#include<iostream>
#include<stdarg.h>

#define MAX_ARGNUM 1024

enum class LogLevel
{
	Log_Default,
	Log_Info,
	Log_Warning,
	Log_Error
};

enum class LogMode
{
	Default,
	Console,
	File,
	History,
	All
};

struct LogData {
	std::string message;
	LogLevel logLevel;
	std::string date;
};

class ILogHandler
{
	friend class Logger;

private:
	virtual void Log(const LogData& error) = 0;
};

static void Log(std::string mes, ...)
{
	char buffer[MAX_ARGNUM] = { 0 };
	va_list ap;
	va_start(ap, mes);
	vsprintf(buffer, mes.c_str(), ap);
	va_end(ap);
	printf("%s", buffer);
}


