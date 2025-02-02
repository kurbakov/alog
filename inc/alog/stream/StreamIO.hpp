#pragma once

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
            std::cout << tv_sec << "." << tv_usec << " " << LevelToStr(level) << " [" << tid << "] " << sl.file_name() << ":" << sl.column() << " | " << log << std::endl;
        }
    };
}// namespace alog