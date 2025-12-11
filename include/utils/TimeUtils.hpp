#pragma once

#include <chrono>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>


/**
* @brief Utilities for working with time and formatting timestamps.
*
* The functions in the TimeUtils namespace are used by the logger to obtain
* the current time and convert it to a human-readable string.
*/
namespace TimeUtils {


/**
* @brief Returns the current time in std::time_t format.
*
* The source is std::chrono::system_clock.
*
* @return The number of seconds since the epoch (Unix time).
*/
inline std::time_t nowTimeT() {
    return std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now()
    );
}

/**
* @brief Formats the passed time as a string.
*
* Wrapper over std::put_time and std::localtime with a custom format.
*
* @param time Time in std::time_t format.
* @param format A strftime-style format string (default "%Y-%m-%d %H:%M:%S").
* @return A formatted string with the date and time.
*/
inline std::string formatTime(
    std::time_t time,
    const std::string& format = "%Y-%m-%d %H:%M:%S"
) {
    std::tm tm = *std::localtime(&time);
    std::ostringstream oss;
    oss << std::put_time(&tm, format.c_str());
    return oss.str();
}

/**
* @brief Returns the current time as a formatted string.
*
* Equivalent to calling formatTime(nowTimeT(), format).
*
* @param format A strftime-style format string.
* @return A string containing the current date and time.
*/
inline std::string formatNow(const std::string& format = "%Y-%m-%d %H:%M:%S") {
    return formatTime(nowTimeT(), format);
}

/**
 * @brief Возвращает текущую метку времени для логов.
 *
 * Формирует строку в квадратных скобках, например "[2025-12-11 19:00:00]".
 *
 * @return Строка с текущей датой и временем в квадратных скобках.
 */
inline std::string formatLogTime() {
    return "[" + formatNow() + "]";
}

}   // namespace TimeUtils
