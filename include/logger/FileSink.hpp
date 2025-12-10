#pragma once

#include "LogSink.hpp"
#include <fstream>

class FileSink : public LogSink
{
public:

    explicit FileSink(const std::string& filename);
    ~FileSink() override;

    void write(const std::string& message) override;

private:

    std::ofstream file;
};