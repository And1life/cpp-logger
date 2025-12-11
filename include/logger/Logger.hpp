#pragma once
#include "LogSink.hpp"
#include "Level.hpp"
#include <mutex>
#include <memory>
#include <vector>


#define LOG_DEBUG(logger, message) \
    (logger).debug(message, __FILE__, __LINE__)


#define LOG_INFO(logger, message) \
    logger.info(message, __FILE__, __LINE__)


#define LOG_WARN(logger, message) \
    logger.warning(message, __FILE__, __LINE__)


#define LOG_ERROR(logger, message) \
    logger.error(message, __FILE__, __LINE__)


#define LOG_CRIT(logger, message) \
    logger.critical(message, __FILE__, __LINE__)


class Logger
{
public:
    
    void setLevel(Level level) noexcept;
    void addSink(std::shared_ptr<LogSink> sink);
    void removeSink(std::shared_ptr<LogSink> sink);

    void debug(const std::string& message, const std::string& file, int line);
    void info(const std::string& message, const std::string& file, int line);
    void warning(const std::string& message, const std::string& file, int line);
    void error(const std::string& message, const std::string& file, int line);
    void critical(const std::string& message, const std::string& file, int line);

private:
    Level currentLevel = Level::DEBUG;
    std::vector<std::shared_ptr<LogSink>> sinks;
    std::mutex mutex;

    void log(Level level, const std::string& message, const std::string& file = "", int line = -1);
    std::string formatMessage(Level level, const std::string& message, const std::string& file, int line);
    std::string getLevelColor(Level level);
    std::string getFileName(const std::string& filePath);
    const std::string RESET_COLOR = "\033[0m";
};