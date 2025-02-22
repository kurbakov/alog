#include "alog/Processor.hpp"
#include "alog/concurrency/Utils.hpp"

#include "ALogConfig.hpp"

namespace alog {
Processor* Processor::m_instance = nullptr;

Processor::Processor()
{
    m_runnerThread = std::thread([&]() {
        run();
    });
}

void Processor::run()
{
    if constexpr (0 <= ALOG_CPU_ID) {
        set_cpu_affinity(ALOG_CPU_ID);
    }

    m_isRunning.store(true);

    Event ev;
    while (m_isRunning.load()) {
        std::lock_guard<mutex_t> guard(m_channelsLock);
        bool processed_events = false;
        for (auto* channel : m_channels) {
            if (channel && channel->recv(ev)) {
                // at least 1 event was processed
                processed_events = true;

                // check if the message was serialised or was directly copied from fmt
                auto msg = ev.msg != nullptr ? ev.msg : ev.meta->fmt;

                // push message into the output stream
                m_stream->log(ev.tv.tv_sec, ev.tv.tv_usec, ev.meta->level, ev.meta->location, ev.tid, msg.data());

                // free the memory
                channel->free(const_cast<char*>(ev.msg));
                ev.msg = nullptr;

                // stop the loop and any pending events processing
                if (ev.meta->level == Level::FATAL) {
                    m_isRunning = false;
                    break;
                }
            }
        }

        if (!processed_events) {
            // in case if all channels did not generate any logs, sleep
            std::this_thread::sleep_for(std::chrono::microseconds(100));
        }
    }

    if (ev.meta->level == Level::FATAL) {
        {
            std::lock_guard<mutex_t> guard(m_channelsLock);
            m_channels.clear();
        }

        // in case we stopped the loop on FATAL error
        std::exit(0);
    }
}

void Processor::stop()
{
    m_isRunning.store(false);
    m_runnerThread.join();
}

void Processor::set_stream(StreamBase* stream)
{
    m_stream.reset(stream);
}

void Processor::subscribe(Channel* channel)
{
    // add channel
    std::lock_guard<mutex_t> lock(m_channelsLock);
    m_channels.insert(channel);
}

void Processor::unsubscribe(Channel* channel)
{
    // remove a channel
    std::lock_guard<mutex_t> guard(m_channelsLock);
    m_channels.erase(channel);
}

} // ns alog
