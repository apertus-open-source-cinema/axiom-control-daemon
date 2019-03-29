#ifndef DEFAULTLOGGER_H
#define DEFAULTLOGGER_H

#include <iostream>

#include "ILogger.h"

class DefaultLogger : public ILogger
{
public:
    void LogWarning(std::string message, std::string file, unsigned int line);

    void LogError(std::string message, std::string file, unsigned int line);

    void LogInfo(std::string message, std::string file, unsigned int line);

    void LogFatal(std::string message, std::string file, unsigned int line);
};

#endif // DEFAULTLOGGER_H
