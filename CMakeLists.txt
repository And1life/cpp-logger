cmake_minimum_required(VERSION 3.20)

project(cpp_logger LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Библиотека Logger
add_library(logger STATIC
    src/Logger.cpp
    src/ConsoleSink.cpp
    src/FileSink.cpp
)

target_include_directories(logger
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

# Пример использования (examples/example.cpp)
add_executable(logger_example
    examples/example.cpp
)

target_link_libraries(logger_example
    PRIVATE
        logger
)

add_subdirectory(tests)