#include "../include/logger/Logger.hpp"
#include "../include/logger/ConsoleSink.hpp"

int main(int argc, char const *argv[])
{
    Logger logger;
    logger.addSink(std::make_shared<ConsoleSink>());
    logger.debug("debug message");
    logger.info("info message");
    logger.warning("warning message");
    logger.error("error message");
    logger.critical("critical message");

    return 0;
}
