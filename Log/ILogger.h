#ifndef ILOGGER_H
#define ILOGGER_H

#include <string>

class ILogger
{
public:
    virtual ~ILogger() {}

    virtual void LogWarning(std::string message, std::string file, unsigned int line) = 0;
    virtual void LogError(std::string message, std::string file, unsigned int line) = 0;
    virtual void LogInfo(std::string message, std::string file, unsigned int line) = 0;
    virtual void LogFatal(std::string message, std::string file, unsigned int line) = 0;
};


#endif //ILOGGER_H
