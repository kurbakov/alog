#pragma once

#include <string_view>

namespace alog {
    class StreamBase {
        static constexpr std::string_view timeFormat{"%Y%m%d-%H:%M:%S"};
        std::array<char,32> timeBuffer {};

    public:
        auto& getTimeBuffer() {return timeBuffer;}
        auto getTimeFormat() {return timeFormat;}
        virtual void log(uint64_t tv_sec, uint64_t tv_usec, Level level, const std::source_location sl, std::thread::id tid, const char *log) {
            // do nothing
        }
    };
}// namespace alog