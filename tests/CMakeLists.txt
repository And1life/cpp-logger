cmake_minimum_required(VERSION 3.10)
project(cpp-logger-tests)

# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Находим пакет Google Test (если не установлен, соберём его)
find_package(GTest QUIET)
if(NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
    )
    FetchContent_MakeAvailable(googletest)
endif()

# Указываем путь к библиотеке logger
link_directories(${CMAKE_BINARY_DIR})

# Собираем тесты для Logger
add_executable(test_Logger test_Logger.cpp)
target_link_libraries(test_Logger GTest::GTest GTest::Main logger)

enable_testing()
gtest_discover_tests(test_Logger)



