#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class ILogger;

// Copied from OpenCine and adjusted
class Logger final
{
private:
    ILogger* _loggerImplementation;

    Logger();

public:
    Logger(const Logger& rs) = delete;
    Logger& operator=(const Logger& rs) = delete;

    static Logger& GetInstance();

    ~Logger();

    void LogWarning(std::string message, std::string file, unsigned int line);
    void LogError(std::string message, std::string file, unsigned int line);
    void LogInfo(std::string message, std::string file, unsigned int line);
    void LogFatal(std::string message, std::string file, unsigned int line);
};

#define DAEMON_LOG_INFO(message) Logger::GetInstance().LogInfo(message, __FILE__, __LINE__)
#define DAEMON_LOG_WARNING(message) Logger::GetInstance().LogWarning(message, __FILE__, __LINE__)
#define DAEMON_LOG_ERROR(message) Logger::GetInstance().LogError(message, __FILE__, __LINE__)
#define DAEMON_LOG_FATAL(message) Logger::GetInstance().LogFatal(message, __FILE__, __LINE__)

#endif // LOGGER_H
