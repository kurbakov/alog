#pragma once

#include <format>
#include <iostream>
#include <memory.h>
#include <thread>

#include "ALogConfig.hpp"
#include "concurrency/RingBuffer.hpp"
#include "memory/FixSizePool.hpp"
#include "time/Clock.hpp"

namespace alog {

class Channel final {
public:
    template <typename... Args>
    bool send(const Metadata* meta, const std::thread::id& id, Args&&... args)
    {
        char* buffer = static_cast<char*>(m_pool.allocate());
        if (not buffer) {
            return false;
        }

        std::vformat_to(buffer, meta->fmt, std::make_format_args(args...));

        Event ev {
            .meta = meta,
            .tid = id,
            .tv = alog::microsecond_time(),
            .msg = buffer,
        };

        return m_queue.tryPush(ev);
    }

    bool send(const Metadata* meta, const std::thread::id& id);

    bool recv(Event& log);

    [[nodiscard]] bool empty() const;

    void free(char* mem);

private:
    RingBuffer<Event, ALOG_CHANNEL_LEN> m_queue;
    FixSizePool<ALOG_LANE_LEN, ALOG_CHANNEL_LEN> m_pool;
};
} // namespace alog
