#pragma once
#include "ILogHandler.h"
class ConsoleHandler :
    public ILogHandler
{
public:
    void Log(const LogData& p_logData);
    std::string GetLogHeader(LogLevel p_logLevel);
private:
    std::string const __DEFAULT_HEADER = " ";
    std::string const __INFO_HEADER = "[INFO] ";
    std::string const __WARNING_HEADER = "[WARNING] ";
    std::string const __ERROR_HEADER = "[ERROR] ";
};

