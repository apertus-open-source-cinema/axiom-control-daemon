#include "DefaultLogger.h"

void DefaultLogger::LogWarning(std::string message, std::string file, unsigned int line)
{
    std::clog << "WARNING: " << message << std::endl;
}

void DefaultLogger::LogError(std::string message, std::string file, unsigned int line)
{
    std::clog << "ERROR: " << message << " (" << file << ":" << line << ")" << std::endl;
}

void DefaultLogger::LogInfo(std::string message, std::string file, unsigned int line)
{
    std::clog << "INFO: " << message << std::endl;
}

void DefaultLogger::LogFatal(std::string message, std::string file, unsigned int line)
{
    std::clog << "FATAL: " << message << " (" << file << ":" << line << ")" << std::endl;
}
