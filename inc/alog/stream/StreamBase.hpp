#pragma once

#include <string_view>

namespace alog {
    class StreamBase {
        static constexpr std::string_view timeFormat{"%Y%m%d-%H:%M:%S"};

    public:
        virtual void log(uint64_t tv_sec, uint64_t tv_usec, Level level, const std::source_location sl, std::thread::id tid, const char *log) {
            // do nothing
        }
    };
}// namespace alog