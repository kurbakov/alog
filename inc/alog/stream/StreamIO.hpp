#pragma once

#include <ctime>
#include <format>
#include <iostream>
#include <source_location>
#include <string_view>

#include "StreamBase.hpp"
#include "alog/Defs.hpp"


namespace alog {
    class StreamIO : public StreamBase {
    public:
        void log(uint64_t tv_sec, uint64_t tv_usec, Level level, std::source_location sl, std::thread::id tid, const char *log) override {
            auto tm_now = localtime((time_t*)&tv_sec);
            strftime(getTimeBuffer().data(), getTimeBuffer().size(), getTimeFormat().data(), tm_now);

            std::cout
                << getTimeBuffer().data() << "." << tv_usec << " "
                << LevelToStr(level) << " [" << tid << "] "
                << sl.file_name() << ":" << sl.column() << " | "
                << log << std::endl;
        }
    };
}// namespace alog