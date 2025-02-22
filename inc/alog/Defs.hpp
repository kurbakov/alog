#pragma once

#include <cstdint>
#include <ctime>
#include <source_location>
#include <string_view>
#include <thread>

namespace alog {
enum class Level : uint8_t {
    DEBUG = 0,
    INFO,
    WARN,
    ERROR,
    FATAL,
    Last,
};

inline std::string_view LevelToStr(const Level& level)
{
    std::array<std::string_view, static_cast<size_t>(Level::Last) + 1> map {
        "DEBUG", "INFO", "WARN", "ERROR", "FATAL", "UNKNOWN_LEVEL"
    };

    return map[static_cast<uint8_t>(level)];
}

enum class Stream : uint8_t {
    DevNull = 0,
    IO,
};

struct Metadata {
    const Level level;
    const std::source_location location;
    const std::string_view fmt;
};

struct Event {
    const Metadata* meta;
    std::thread::id tid;
    timeval tv;
    const char* msg;
};
} // namespace alog
