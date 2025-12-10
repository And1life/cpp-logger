#pragma once

#include <chrono>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>

namespace TimeUtils {

inline std::time_t nowTimeT() {
    return std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now()
    );
}

inline std::string formatTime(
    std::time_t time,
    const std::string& format = "%Y-%m-%d %H:%M:%S"
) {
    std::tm tm = *std::localtime(&time);
    std::ostringstream oss;
    oss << std::put_time(&tm, format.c_str());
    return oss.str();
}

inline std::string formatNow(const std::string& format = "%Y-%m-%d %H:%M:%S") {
    return formatTime(nowTimeT(), format);
}

inline std::string formatLogTime() {
    return "[" + formatNow() + "]";
}

} 
