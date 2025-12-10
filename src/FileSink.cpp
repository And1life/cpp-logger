#include "../include/logger/FileSink.hpp"

FileSink::FileSink(const std::string &filename)
{
    file.open(filename, std::ios::app);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }   
}

FileSink::~FileSink()
{
    if (file.is_open())
    {
        file.close();
    }
}

void FileSink::write(const std::string &message)
{
    std::string new_message = stripAnsi(message);
    if (file.is_open())
    {
        file << new_message << std::endl;
        file.flush();
    }
}

std::string FileSink::stripAnsi(const std::string& message)
{
    static const std::regex esc("\x1B\\[[0-9;]*m");
    return std::regex_replace(message, esc, "");
}