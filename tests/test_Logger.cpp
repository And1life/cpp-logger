#include <gtest/gtest.h>
#include "../include/logger/Logger.hpp"

class TestSink : public LogSink
{
public:

    std::vector<std::string> messages;

    void write(const std::string& message) override
    {
        messages.push_back(message);
    }

};

TEST(LoggerTest, LogsMessageAtOrAboveLevel)
{
    Logger logger;
    auto sink = std::make_shared<TestSink>();
    logger.addSink(sink);

    logger.setLevel(Level::INFO);

    LOG_DEBUG(logger, "debug");
    LOG_INFO(logger, "info");
    LOG_ERROR(logger, "error");

    ASSERT_EQ(sink->messages.size(), 2);
    EXPECT_NE(sink->messages[0].find("info"), std::string::npos);
    EXPECT_NE(sink->messages[1].find("error"), std::string::npos);

}

TEST(LoggerTest, IncludesLevelAndMessageInFormat)
{
    Logger logger;
    auto sink = std::make_shared<TestSink>();
    logger.addSink(sink);

    logger.setLevel(Level::DEBUG);
    LOG_WARN(logger, "hello warning");

    ASSERT_EQ(sink->messages.size(), 1);
    EXPECT_NE(sink->messages[0].find("WARNING"), std::string::npos);
    EXPECT_NE(sink->messages[0].find("hello warning"), std::string::npos);
}

TEST (LoggerTest, IncludesLocationWhenProvided)
{
    Logger logger;
    auto sink = std::make_shared<TestSink>();
    logger.addSink(sink);
    logger.setLevel(Level::DEBUG);

    logger.info("info message","src/main.cpp", 42);

    ASSERT_EQ(sink->messages.size(), 1);
    EXPECT_NE(sink->messages[0].find("main.cpp"), std::string::npos);
    EXPECT_NE(sink->messages[0].find("42"), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 