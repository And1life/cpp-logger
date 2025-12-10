#include "../include/logger/Logger.hpp"
#include "../include/logger/ConsoleSink.hpp"

int main(int argc, char const *argv[])
{
    Logger logger;
    logger.addSink(std::make_shared<ConsoleSink>());
    logger.debug("first message");
    return 0;
}
