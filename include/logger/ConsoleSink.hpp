#pragma once
#include "LogSink.hpp"

/**
* @brief A log sink that writes messages to the standard output stream (console).
*
* ConsoleSink is typically used to display logs during development
* and debugging. Typically, message formatting (time, level, color)
* is performed on the Logger side, while the sink only outputs the resulting string.
*/
class ConsoleSink : public LogSink
{
public:

    /**
    * @brief Writes the generated message to the console.
    *
    * The implementation must send the string to std::cout or std::cerr.
    * The message is already considered fully formatted by the logger.
    *
    * @param message The completed text log message.
    */
    void write(const std::string& message) override;
};