#pragma once

#include <source_location>
#include <thread>

#include "Client.hpp"
#include "Defs.hpp"
#include "Processor.hpp"
#include "Utils.hpp"

#include "ALogConfig.hpp"
#include "stream/StreamIO.hpp"

namespace {
thread_local alog::Client client;
}

namespace alog {
template <Stream S>
void initLogger();

template <>
void initLogger<Stream::IO>()
{
    auto* processor = Processor::get();
    processor->setStream(new StreamIO());
}

template <>
void initLogger<Stream::DevNull>()
{
    auto* processor = Processor::get();
    processor->setStream(new StreamBase());
}

} // namespace alog

namespace {

#define LOG(severity, format, ...)                                                            \
    do {                                                                                      \
        static_assert(alog::placeholdersCount(format, "{}") == alog::argsCount(__VA_ARGS__)); \
        if constexpr (severity >= ALOG_LEVEL && severity < alog::Level::FATAL) {              \
            constexpr static alog::Metadata meta {                                            \
                .level = severity,                                                            \
                .location = std::source_location::current(),                                  \
                .fmt = format,                                                                \
            };                                                                                \
            client.log(&meta, ##__VA_ARGS__);                                                 \
        }                                                                                     \
        if constexpr (severity >= ALOG_LEVEL && severity == alog::Level::FATAL) {             \
            constexpr static alog::Metadata meta {                                            \
                .level = severity,                                                            \
                .location = std::source_location::current(),                                  \
                .fmt = format,                                                                \
            };                                                                                \
            auto st = alog::getStacktrace();                                                  \
            client.log(st, &meta, ##__VA_ARGS__);                                             \
        }                                                                                     \
    } while (0)

} // namespace

#define LOG_DEBUG(fmt, ...) LOG(alog::Level::DEBUG, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) LOG(alog::Level::INFO, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) LOG(alog::Level::WARN, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) LOG(alog::Level::ERROR, fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...) LOG(alog::Level::FATAL, fmt, ##__VA_ARGS__)
