#include "alog/Channel.hpp"

namespace alog {

bool Channel::send(const Metadata* meta, const std::thread::id& id)
{
    Event ev {
        .meta = meta,
        .tid = id,
        .tv = alog::timeInMicrosecond(),
        .msg = nullptr,
    };

    return m_queue.tryPush(ev);
}

bool Channel::send(const std::string& st, const Metadata* meta, const std::thread::id& id)
{
    char* buffer = static_cast<char*>(m_pool.allocate());
    if (not buffer) {
        return false;
    }

    std::vformat_to(buffer, "{}\n{}", std::make_format_args(meta->fmt, st));

    Event ev {
        .meta = meta,
        .tid = id,
        .tv = alog::timeInMicrosecond(),
        .msg = buffer,
    };

    return m_queue.tryPush(ev);
}

bool Channel::recv(Event& log)
{
    return m_queue.tryPop(log);
}

[[nodiscard]] bool Channel::empty() const { return m_queue.empty(); }

void Channel::free(char* mem)
{
    m_pool.free(mem);
}
} // ns alog
