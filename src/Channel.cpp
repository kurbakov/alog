#include "alog/Channel.hpp"

namespace alog {

    bool Channel::send(const Metadata *meta, const std::thread::id &id) {
        Event ev{
                .meta = meta,
                .tid = id,
                .tv = alog::microsecond_time(),
                .msg = nullptr,
        };

        return m_queue.tryPush(ev);
    }


    bool Channel::recv(Event &log) {
        return m_queue.tryPop(log);
    }

    [[nodiscard]] bool Channel::empty() const { return m_queue.empty(); }

    void Channel::free(char *mem) {
        m_pool.free(mem);
    }
} // ns alog