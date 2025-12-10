#include "LogSink.hpp"

class ConsoleSink : public LogSink
{
    void write(const std::string& message) override;
};