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