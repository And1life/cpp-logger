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
    if (file.is_open())
    {
        file << message << std::endl;
        file.flush();
    }
    

}