#include "ConsoleHandler.h"
#include "ConsoleColor.h"



void ConsoleHandler::Log(const LogData& p_logData)
{
	switch (p_logData.logLevel)
	{
	case LogLevel::Log_Default:
		std::cout << COLOR_WHIT;
		break;
	case LogLevel::Log_Info:
		std::cout << COLOR_BLUE;
		break;
	case LogLevel::Log_Warning:
		std::cout << COLOR_YELLOW;
		break;
	case LogLevel::Log_Error:
		std::cout << COLOR_RED;
		break;
	}

	std::ostream& output = p_logData.logLevel == LogLevel::Log_Error ? std::cerr : std::cout;

	output << GetLogHeader(p_logData.logLevel) << p_logData.date << " " << p_logData.message << std::endl;

	std::cout << COLOR_DEFAULT;
}

std::string ConsoleHandler::GetLogHeader(LogLevel p_logLevel)
{
	switch (p_logLevel)
	{
	case LogLevel::Log_Default:	return __DEFAULT_HEADER;
	case LogLevel::Log_Info:		return __INFO_HEADER;
	case LogLevel::Log_Warning:	return __WARNING_HEADER;
	case LogLevel::Log_Error:		return __ERROR_HEADER;
	}

	return "";
}