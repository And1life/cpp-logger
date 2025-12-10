#include "../include/logger/Logger.hpp"
#include "../include/utils/TimeUtils.hpp"
#include <algorithm>

void Logger::setLevel(Level level) noexcept
{
    if (currentLevel == level)
    {
        return;
    }
    std::lock_guard<std::mutex> lock(mutex);
    currentLevel = level;
}

void Logger::addSink(std::shared_ptr<LogSink> sink)
{
    std::lock_guard<std::mutex> lock(mutex);
    sinks.push_back(sink);
}

void Logger::removeSink(std::shared_ptr<LogSink> sink)
{
    std::lock_guard<std::mutex> lock(mutex);
    sinks.erase(std::remove(sinks.begin(), sinks.end(), sink), sinks.end() );
}

void Logger::debug(const std::string &message, const std::string& file, int line)
{
    log(Level::DEBUG, message, file, line);
}

void Logger::info(const std::string &message, const std::string& file, int line)
{
    log(Level::INFO, message, file, line);
}

void Logger::warning(const std::string &message, const std::string& file, int line)
{
    log(Level::WARNING, message, file, line);
}

void Logger::error(const std::string &message, const std::string& file, int line)
{
    log(Level::ERROR, message, file, line);
}

void Logger::critical(const std::string &message, const std::string& file, int line)
{
    log(Level::CRITICAL, message, file, line);
}

void Logger::log(Level level, const std::string &message, const std::string& file, int line)
{
    if (level < currentLevel)
    {
        return;
    }
    
    std::string formattedMessage = formatMessage(level, message, file, line);

    std::lock_guard<std::mutex> lock(mutex);
    for (auto &&sink : sinks)
    {
        sink->write(formattedMessage);
    }
    
}

std::string Logger::formatMessage(Level level, const std::string &message, const std::string& file, int line)
{
    
    std::string levelStr;
    switch (level)
    {
        case Level::DEBUG :     levelStr = "DEBUG"; break;
        case Level::INFO :      levelStr = "INFO"; break;
        case Level::WARNING :   levelStr = "WARNING"; break;
        case Level::ERROR :     levelStr = "ERROR"; break;
        case Level::CRITICAL :  levelStr = "CRITICAL"; break;
        default :               levelStr = "UNKNOWN";
    }

    std::string location;
    if (!file.empty() && line != -1)
    {
        location = " [" + getFileName(file) + ":" + std::to_string(line) + "] ";
    }
    

    std::string color = getLevelColor(level);

    return TimeUtils::formatLogTime() + color + " [" + levelStr + "] " + RESET_COLOR + location + message ;
}

std::string Logger::getLevelColor(Level level)
{
    switch (level)
    {
    case Level::DEBUG :      return "\033[90m";
    case Level::INFO :       return "\033[0m";
    case Level::WARNING :    return "\033[33m";
    case Level::ERROR :      return "\033[31m";
    case Level::CRITICAL :   return "\033[1;31m";
    default:                 return "\033[0m";
    
    }
}
std::string Logger::getFileName(const std::string &filePath)
{
    size_t lastSlash = filePath.find_last_of("/\\");
    return (lastSlash == std::string::npos) ? filePath : filePath.substr(lastSlash + 1);
}