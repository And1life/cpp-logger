#include "Logger.hpp"

void Logger::setLevel(Level level) noexcept
{
    if (currentLevel == level)
    {
        return;
    }
    std::lock_guard<std::mutex> lock(mutex);
    currentLevel = level;
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
