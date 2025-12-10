#include "../include/logger/Logger.hpp"
#include "../include/logger/ConsoleSink.hpp"
#include "../include/logger/FileSink.hpp"


int main(int argc, char const *argv[])
{
    Logger logger;
    logger.addSink(std::make_shared<ConsoleSink>());
    logger.addSink(std::make_shared<FileSink>("/home/anatoliy/Desktop/app.log"));
    logger.addSink(std::make_shared<FileSink>("app.log"));
    LOG_DEBUG(logger,"debug message");
    LOG_INFO(logger, "info message");
    LOG_WARN(logger, "warning message");
    LOG_ERROR(logger, "error message");
    LOG_CRIT(logger, "critical message");

    return 0;
}
