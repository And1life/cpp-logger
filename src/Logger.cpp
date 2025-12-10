#include "../include/logger/Logger.hpp"
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

void Logger::debug(const std::string &message)
{
    log(Level::DEBUG, message);
}

void Logger::info(const std::string &message)
{
    log(Level::INFO, message);
}

void Logger::warning(const std::string &message)
{
    log(Level::WARNING, message);
}

void Logger::error(const std::string &message)
{
    log(Level::ERROR, message);
}

void Logger::critical(const std::string &message)
{
    log(Level::CRITICAL, message);
}

void Logger::log(Level level, const std::string &message)
{
    if (level < currentLevel)
    {
        return;
    }
    
    for (auto &&sink : sinks)
    {
        sink->write(message);
    }
    
}
