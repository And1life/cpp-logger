#pragma once

#include "LogSink.hpp"
#include <fstream>
#include <regex>


class FileSink : public LogSink
{
public:

    explicit FileSink(const std::string& filename);
    ~FileSink() override;

    void write(const std::string& message) override;

private:

    static std::string stripAnsi(const std::string& message);
    std::ofstream file;
};