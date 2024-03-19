#pragma once

#include <string>
#include <map>
#include <vector>
#include "ILogHandler.h"
#include "ConsoleHandler.h"
//#include "../Event/Event.h"
#include "../Util/Singleton.h"

#define LOG(message)			Logger::getInstance()->Log(message, LogLevel::Log_Default,	LogMode::Console)
#define LOG_INFO(message)		Logger::getInstance()->Log(message, LogLevel::Log_Info,		LogMode::Console)
#define LOG_WARNING(message)	Logger::getInstance()->Log(message, LogLevel::Log_Warning,	LogMode::Console)
#define LOG_ERROR(message)	    Logger::getInstance()->Log(message, LogLevel::Log_Error,	LogMode::Console)

class Logger : public CSingleton<Logger>
{
public:
	void Log(const std::string& p_message, LogLevel p_logLevel = LogLevel::Log_Default,
		LogMode p_logMode = LogMode::Default, std::string p_handlerId = "default");

	ConsoleHandler& CreateConsoleHandler(std::string p_id);
	ConsoleHandler& GetConsoleHandler(std::string p_id);
	std::vector<LogData> GetAllLogData();

public:
	/*Event<const LogData&> LogEvent;*/

private:
	template<typename T>
	static void LogToHandlerMap(std::map<std::string, T>& p_map, const LogData& p_data, std::string p_id);

private:
	std::map<std::string, ConsoleHandler> Console_Handle_Map;


	std::vector<LogData> m_logData;
};

#include "Logger.inl"