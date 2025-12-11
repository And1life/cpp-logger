#pragma once

/**
* @brief Severity levels of logger messages.
*
* Used to filter output messages and format the output.
*/
enum class Level 
{ 
    DEBUG,      ///< Debugging information for development, output most often.
    INFO,       ///< Normal informational messages about the application's progress.
    WARNING,    ///< Warnings about potential problems that are not critical to operation.
    ERROR,      ///< Errors in which some of the functionality did not work correctly.
    CRITICAL    ///< Critical errors after which the application may continue to work with difficulty or even terminate completely.
};