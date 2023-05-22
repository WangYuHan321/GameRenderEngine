#include "Logger.h"
#include "../Time/Date.h"

void Logger::Log(const std::string& p_message, LogLevel p_logLevel,
	LogMode p_logMode, std::string p_handlerId)
{
	LogData logData{ p_message, p_logLevel, Date::GetDateAsString() };

	switch (p_logMode)
	{
	case LogMode::Default:
	case LogMode::Console: LogToHandlerMap<ConsoleHandler>(Console_Handle_Map, logData, p_handlerId); break;
	case LogMode::File:		
	case LogMode::History: 	
	case LogMode::All:
		LogToHandlerMap<ConsoleHandler>(Console_Handle_Map, logData, p_handlerId);
		break;
	}
	//LogEvent.Invoke(logData);
}

ConsoleHandler& Logger::CreateConsoleHandler(std::string p_id)
{
	ConsoleHandler consoleHandler;
	Console_Handle_Map.emplace(p_id, consoleHandler);
	return Console_Handle_Map[p_id];
}

ConsoleHandler& Logger::GetConsoleHandler(std::string p_id)
{
	return Console_Handle_Map[p_id];
}
