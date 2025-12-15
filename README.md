# cpp-Logger — Simple Logging Library

A lightweight, thread-safe C++ logging library with multiple sinks, log levels, colored console output, and plain text file logging.

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![C++](https://img.shields.io/badge/C%2B%2B-11%2B-blue.svg)]()

---

## 📋 Requirements

Before you start, make sure you have the following installed:

- **C++ Compiler** (`g++`, `clang++`, or MSVC) with C++11 or higher support
- **CMake** (version 3.10 or higher) for building the project
- **Google Test** framework (optional) for running unit tests
- **Doxygen** (optional) for generating API documentation

---

## 📖 Description

**cpp-Logger** is an educational logging library that demonstrates modern C++ design patterns and best practices. It provides a flexible, extensible logging system with multiple output sinks, log level filtering, and automatic timestamp generation.

The main goals of the project are to:
- Understand the **sink pattern** in logging systems
- Learn **thread-safe** programming with mutexes
- Master **smart pointers** and polymorphism
- Practice **Doxygen documentation** and testing
- Implement clean, maintainable C++ code

---

## 🚀 Quick Start

### Step 1: Clone the Repository

```bash
git clone https://github.com/yourusername/cpp-Logger.git
cd cpp-Logger
```

### Step 2: 🔨 Build with CMake

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Step 3: Include Logger in Your Project

```cpp
#include "logger/Logger.hpp"
#include "logger/ConsoleSink.hpp"

int main() {
    Logger logger;
    auto sink = std::make_shared<ConsoleSink>();
    logger.addSink(sink);
    
    LOG_INFO(logger, "Hello from cpp-Logger!");
    return 0;
}
```

---

## 💡 Usage Examples

### Basic Setup with Console and File Output

```cpp
#include "logger/Logger.hpp"
#include "logger/ConsoleSink.hpp"
#include "logger/FileSink.hpp"

int main()
{
    Logger logger;

    // Console output with colors
    auto consoleSink = std::make_shared<ConsoleSink>();
    logger.addSink(consoleSink);

    // File output (plain text, no ANSI codes)
    auto fileSink = std::make_shared<FileSink>("logs/app.log");
    logger.addSink(fileSink);

    // Set minimum log level
    logger.setLevel(Level::INFO);

    // Log messages using convenient macros
    LOG_INFO(logger, "Application started");
    LOG_WARN(logger, "This is a warning");
    LOG_ERROR(logger, "An error occurred");

    return 0;
}
```

### Direct Method Calls

```cpp
logger.debug("Debug message", __FILE__, __LINE__);
logger.info("Information message", __FILE__, __LINE__);
logger.warning("Warning message", __FILE__, __LINE__);
logger.error("Error message", __FILE__, __LINE__);
logger.critical("Critical error", __FILE__, __LINE__);
```

### Managing Sinks

```cpp
auto sink1 = std::make_shared<ConsoleSink>();
auto sink2 = std::make_shared<FileSink>("output.log");

logger.addSink(sink1);
logger.addSink(sink2);

// Log goes to both sinks
logger.info("Message to all sinks", __FILE__, __LINE__);

// Remove a sink
logger.removeSink(sink1);
```

### Setting Log Levels

```cpp
logger.setLevel(Level::DEBUG);    // All messages logged
logger.setLevel(Level::INFO);     // INFO and above
logger.setLevel(Level::WARNING);  // WARNING and above
logger.setLevel(Level::ERROR);    // ERROR and CRITICAL only
logger.setLevel(Level::CRITICAL); // CRITICAL only
```

---

## 📁 Project Structure

```
cpp-Logger/
├── docs/
│   └── Doxyfile              # Doxygen configuration
├── include/
│   ├── logger/
│   |   ├── Logger.hpp        # Main Logger class
│   |   ├── LogSink.hpp       # Abstract sink interface
│   |   ├── ConsoleSink.hpp   # Console output sink
│   |   ├── FileSink.hpp      # File output sink
│   |   └── Level.hpp         # Log level enum   
|   └── utils/
|       └── TimeUtils.hpp     # Time formatting utilities
├── src/
│   ├── Logger.cpp            # Logger implementation
│   ├── ConsoleSink.cpp       # Console sink implementation
│   └── FileSink.cpp          # File sink implementation
├── tests/
|   └── CMakeLists.txt        # Build configuration
│   └── test_Logger.cpp       # Unit tests
├── .gitignore                # File to ignore unnecessary files
├── CMakeLists.txt            # Build configuration
└── README.md                 # This file
```


---


## 🎯 Features

| Feature | Status | Description |
|---------|--------|-------------|
| **Log Levels** | ✅ | DEBUG, INFO, WARNING, ERROR, CRITICAL |
| **Multiple Sinks** | ✅ | Console and file output simultaneously |
| **Colored Output** | ✅ | ANSI colors in console, stripped in files |
| **Thread-Safe** | ✅ | `std::mutex` protection |
| **Convenient Macros** | ✅ | `LOG_INFO`, `LOG_ERROR`, etc. with auto file/line |
| **Timestamps** | ✅ | Automatic time formatting |
| **Time Utilities** | ✅ | Flexible time formatting helpers |
| **Unit Tests** | ✅ | GoogleTest coverage |
| **Doxygen Docs** | ✅ | Full API documentation |

---

## 📊 Log Format

Default formatted message:

```text
[2025-12-11 19:00:00] [INFO] [main.cpp:42] Application started
```

**Console output:** Level part is colorized with ANSI escape codes.  
**File output:** ANSI codes are stripped, plain text only.

---

## 🧪 Testing

### Test Scenarios Covered

- ✅ Log level filtering (messages below threshold are ignored)
- ✅ Level and message presence in formatted output
- ✅ File location `[file:line]` formatting
- ✅ Writing to multiple sinks simultaneously

### Run Tests 

```bash
./build/test_Logger
```

---

## 📚 API Documentation

### Generate Doxygen Documentation

**Step 1: Install Doxygen**

**Linux:**
```bash
sudo apt-get install doxygen
```

**macOS:**
```bash
brew install doxygen
```

**Windows:**
Download from [doxygen.nl](https://www.doxygen.nl/download.html)

**Step 2: Generate Docs**

```bash
cd docs
doxygen Doxyfile
```

**Step 3: View Documentation**

```bash
# Linux/macOS
xdg-open docs/doxygen/html/index.html

# Windows
start docs/doxygen/html/index.html

# Or simply open file manually in browser
```

---

## 🏗️ Architecture

### Strategy Pattern

The library uses the **Strategy Pattern** for flexible output:

```
+----------------+       +-------------------+
|     Logger     |◄──────|  LogSink (abstract)|
|                |       |   write(Log msg)   |
+----------------+       +-------------------+
         │                         ▲
         │                         │
         ▼                         │
+----------------+       +-------------------+
|   addSink()    |──────►|  ConsoleSink     |
|   log(Level)   |       |  write()         |
+----------------+       +-------------------+
                              │
                              ▼
                         +-------------------+
                         |   FileSink        |
                         |    write()        |
                         +-------------------+

```

Each sink implements the `LogSink` interface:

```cpp
class LogSink {
public:
    virtual void write(const std::string& message) = 0;
};
```

### Thread Safety

The Logger uses `std::mutex` to protect concurrent access:

```cpp
std::lock_guard<std::mutex> lock(mutex);  // RAII lock
for (auto&& sink : sinks) {
    sink->write(formattedMessage);
}
```

---

## 💡 What You Will Learn

By studying and using this project, you will understand:

✅ **Design Patterns**
- Sink/Observer pattern
- Builder pattern (fluent API)
- Polymorphism and inheritance

✅ **Thread Safety**
- `std::mutex` and locks
- Race condition prevention
- Critical sections

✅ **Modern C++**
- Smart pointers (`std::shared_ptr`)
- Move semantics
- RAII principle

✅ **Testing & Documentation**
- Unit testing with GoogleTest
- API documentation with Doxygen
- Code quality practices

✅ **C++ Standard Library**
- String manipulation
- Regular expressions (ANSI code stripping)
- Chrono for time handling

---

## 🚀 Future Enhancements

Possible improvements and extensions:

- [ ] Asynchronous logging (background thread)
- [ ] Log rotation for files
- [ ] Different formatting patterns
- [ ] Syslog sink support
- [ ] Network sink (remote logging)
- [ ] Custom allocators
- [ ] Performance optimization

---

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch:
   ```bash
   git checkout -b feature/your-feature
   ```
3. Commit with Conventional Commits:
   ```bash
   git commit -m "feat(logger): add feature description"
   ```
4. Push and create a Pull Request

**Commit Types:**
- `feat:` new feature
- `fix:` bug fix
- `test:` add or update tests
- `docs:` documentation changes
- `refactor:` code refactoring

---

## 📝 License

This project is distributed under the **MIT License** — free for educational and commercial use.

```
MIT License

Copyright (c) 2025 Anatoly Dmitriev

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software...
```

See [LICENSE](LICENSE) file for full text.

---

## 🔗 Resources

- 📘 [C++ Reference — std::mutex](https://en.cppreference.com/w/cpp/thread/mutex)
- 📘 [C++ Reference — smart pointers](https://en.cppreference.com/w/cpp/memory)
- 📚 [Doxygen Manual](https://www.doxygen.nl/manual/index.html)
- 🧪 [Google Test Documentation](https://github.com/google/googletest)
- 📖 [Effective C++](https://en.wikipedia.org/wiki/Effective_C%2B%2B) by Scott Meyers

---

## 📞 Feedback

Have questions or suggestions?

- 🐛 [Report Issues](https://github.com/And1life/cpp-Logger/issues)
- 💬 Discussion (if enabled)
- 📧 Email: and1life@yandex.ru

---

**Thank you for using cpp-logger!** ⭐

If this project was helpful, please star it on GitHub! 🌟
