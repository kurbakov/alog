#pragma once

#include <cstdint>
#include <format>
#include <string_view>
#include <sys/time.h>

#include "concurrency/RingBuffer.hpp"
#include "memory/FixSizePool.hpp"


namespace alog {

    enum class Level : uint8_t {
        DEBUG = 0,
        INFO,
        WARN,
        ERROR,
        FATAL,
        Last,
    };

    std::string_view LevelToStr(Level &level) {
        std::array<std::string_view, static_cast<size_t>(Level::Last)> map{
                "DEBUG", "INFO", "WARN", "ERROR", "FATAL"};

        return map[static_cast<uint8_t>(level)];
    }

    enum class Stream : uint8_t {
        DevNull = 0,
        IO,
        File,
    };

    struct Metadata {
        const Level level;
        const std::source_location location;
        const std::string_view fmt;
    };

    struct Event {
        Level level;
        std::source_location location;
        std::thread::id tid;
        uint64_t tv_sec;
        uint64_t tv_usec;
        const char *msg;
    };
}// namespace alog
