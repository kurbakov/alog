#pragma once

#include <thread>

#include "Channel.hpp"
#include "Processor.hpp"

namespace alog {
class Client {
public:
    Client();
    ~Client();

    void log(const Metadata* meta);

    template <class... Args>
    void log(const Metadata* meta, Args... args)
    {
        m_channel.send(meta, m_tid, args...);
    }

private:
    Channel m_channel;
    const std::thread::id m_tid;
};
} // namespace alog
