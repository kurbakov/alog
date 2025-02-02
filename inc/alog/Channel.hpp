#pragma once

#include <format>
#include <iostream>
#include <memory.h>
#include <thread>

#include "ALogConfig.hpp"

namespace alog {

    class Channel {
    public:
        template<typename... Args>
        bool send(const Metadata *meta, const std::thread::id &id, timeval tv, Args &&...args) {
            char *buffer = static_cast<char *>(m_pool.allocate());
            if (not buffer) {
                return false;
            }

            std::vformat_to(buffer, meta->fmt, std::make_format_args(args...));

            Event ev{
                    .level = meta->level,
                    .location = meta->location,
                    .tid = id,
                    .tv_sec = (uint64_t) tv.tv_sec,
                    .tv_usec = (uint64_t) tv.tv_usec,
                    .msg = buffer,
            };

            return m_queue.tryPush(ev);
        }

        bool send(const Metadata *meta, const std::thread::id &id, timeval tv) {
            char *buffer = static_cast<char *>(m_pool.allocate());
            if (not buffer) {
                return false;
            }

            memcpy(buffer, meta->fmt.data(), meta->fmt.length());
            buffer[meta->fmt.length()] = '\0';

            Event ev{
                    .level = meta->level,
                    .location = meta->location,
                    .tid = id,
                    .tv_sec = (uint64_t) tv.tv_sec,
                    .tv_usec = (uint64_t) tv.tv_usec,
                    .msg = buffer,
            };

            return m_queue.tryPush(ev);
        }


        bool recv(Event &log) {
            return m_queue.tryPop(log);
        }

        [[nodiscard]] bool empty() const { return m_queue.empty(); }

        void free(char *mem) {
            m_pool.free(mem);
        }

    private:
        RingBuffer<Event, ALOG_CHANNEL_LEN> m_queue;
        FixSizePool<ALOG_LANE_LEN, ALOG_CHANNEL_LEN> m_pool;
    };
}// namespace alog