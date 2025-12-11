#pragma once
#include "LogSink.hpp"
#include "Level.hpp"
#include <mutex>
#include <memory>
#include <vector>

/**
* @def LOG_DEBUG
* @brief Logs a message with the DEBUG level, automatically suffixing the file and string.
*
* @param logger A Logger instance.
* @param message The message text.
*/
#define LOG_DEBUG(logger, message) \
    logger.debug(message, __FILE__, __LINE__)


/**
* @def LOG_INFO
* @brief Logs a message with the INFO level, automatically substituting the file and string.
*
* @param logger A Logger instance.
* @param message The message text.
*/
#define LOG_INFO(logger, message) \
    logger.info(message, __FILE__, __LINE__)


/**
* @def LOG_WARN
* @brief Logs a message with the WARNING level, automatically substituting the file and string.
*
* @param logger A Logger instance.
* @param message The message text.
*/
#define LOG_WARN(logger, message) \
    logger.warning(message, __FILE__, __LINE__)


/**
* @def LOG_ERROR
* @brief Logs a message with the ERROR level, automatically substituting the file and string.
*
* @param logger A Logger instance.
* @param message The message text.
*/
#define LOG_ERROR(logger, message) \
    logger.error(message, __FILE__, __LINE__)


/**
* @def LOG_CRIT
* @brief Logs a message with the CRITICAL level, automatically ssubstituting the file and string.
*
* @param logger A Logger instance.
* @param message The message text.
*/
#define LOG_CRIT(logger, message) \
    logger.critical(message, __FILE__, __LINE__)



/**
* @brief A simple logger with support for levels and multiple sinks.
*
* The logger formats the message (time, level, location) and transmits it to all
* registered sinks. Access to the internal state is protected by a mutex.
*/
class Logger
{
public:

    /**
    * @brief Sets the minimum logging level.
    *
    * Messages below the specified level are ignored.
    *
    * @param level The new minimum level.
    */
    void setLevel(Level level) noexcept;

    /**
    * @brief Registers a new log sink.
    *
    * @param sink A smart pointer to an object implementing the LogSink interface.
    */
    void addSink(std::shared_ptr<LogSink> sink);

    /**
    * @brief Removes a log sink.
    *
    * @param sink The sink to remove.
    */
    void removeSink(std::shared_ptr<LogSink> sink);

    /**
    * @brief Logs a message at the DEBUG level.
    *
    * @param message Message text.
    * @param file Source file name (usually __FILE__).
    * @param line Line number (usually __LINE__).
    */
    void debug(const std::string& message, const std::string& file, int line);

    /**
    * @brief Logs a message with the INFO level.
    */
    void info(const std::string& message, const std::string& file, int line);

    /**
    * @brief Logs a message with the WARNING level.
    */
    void warning(const std::string& message, const std::string& file, int line);

    /**
    * @brief Logs a message with the ERROR level.
    */    
    void error(const std::string& message, const std::string& file, int line);

    /**
    * @brief Logs a message with the CRITICAL level.
    */
    void critical(const std::string& message, const std::string& file, int line);

private:
    /// Current minimum logging level.
    Level currentLevel = Level::DEBUG;

    /// List of registered log receivers.
    std::vector<std::shared_ptr<LogSink>> sinks;

    /// Mutex to protect access to the list of receivers and the current level.
    std::mutex mutex;

    /**
    * @brief Internal logging method for all levels.
    *
    * Performs level checking, message formatting, and sending to all sinks.
    *
    * @param level Message level.
    * @param message Message text.
    * @param file Source file name (optional).
    * @param line Line number (optional, -1 if not specified).
    */
    void log(Level level,
             const std::string& message,
             const std::string& file = "",
             int line = -1);

    /**
    * @brief Formats the log message.
    *
    * Includes time, level color (for console), level name, location, and text.
    *
    * @param level Message level.
    * @param message Message text.
    * @param file Source file name.
    * @param line Line number.
    * @return Ready string to be output to the receiver.
    */
    std::string formatMessage(Level level, const std::string& message, const std::string& file, int line);

    /**
    * @brief Returns the ANSI color for the specified level.
    *
    * Used to colorize console output.
    *
    * @param level Message level.
    * @return A string with the ANSI color escape sequence.
    */
    std::string getLevelColor(Level level);

    /**
    * @brief Extracts the filename from the full path.
    *
    * @param filePath Full or relative path to the file.
    * @return Just the filename, without directories.
    */
    std::string getFileName(const std::string& filePath);

    /// ANSI‑последовательность сброса цвета.
    const std::string RESET_COLOR = "\033[0m";
};