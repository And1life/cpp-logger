#include "../include/logger/ConsoleSink.hpp"
#include <iostream>

void ConsoleSink::write(const std::string &message)
{
    std::cout << message << std::endl;
}