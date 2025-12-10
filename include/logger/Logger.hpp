#pragma once
#include "LogSink.hpp"
#include <mutex>
#include <memory>
#include <vector>

class Logger
{
public:

    enum class Level { DEBUG, INFO, WARNING, ERROR, CRITICAL };
    
    void setLevel(Level level) noexcept;
    void addSink(std::shared_ptr<LogSink> sink);
    void removeSink(std::shared_ptr<LogSink> sink);

    void debug(const std::string& message);
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);
    void critical(const std::string& message);

private:
    Level currentLevel = Level::DEBUG;
    std::vector<std::shared_ptr<LogSink>> sinks;
    std::mutex mutex;

    void log(Level level, const std::string& message);
    std::string formatMessage(Level level, const std::string& message);
    std::string getLevelColor(Level level);
    const std::string RESET_COLOR = "\033[0m";
};