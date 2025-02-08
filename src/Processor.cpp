#include "alog/Processor.hpp"

namespace alog {
    Processor *Processor::m_instance = nullptr;

    Processor::Processor() {
        m_runnerThread = std::thread([&]() {
            run();
        });
    }

    void Processor::run() {
        m_isRunning.store(true);

        Event ev;
        while (m_isRunning.load()) {
            std::lock_guard<mutex_t> guard(m_channelsLock);
            for (auto *channel: m_channels) {
                if (not channel) {
                    break;
                }

                if (channel->recv(ev)) {
                    auto msg = ev.msg !=
                               nullptr ? ev.msg : ev.meta->fmt;
                    m_stream->log(ev.tv.tv_sec, ev.tv.tv_usec, ev.meta->level, ev.meta->location, ev.tid, msg.data());
                    channel->free(const_cast<char *>(ev.msg));
                    ev.msg = nullptr;
                }
            }
        }
    }

    void Processor::stop() {
        m_isRunning.store(false);
        m_runnerThread.join();
    }

    void Processor::set_stream(StreamBase *stream) {
        m_stream.reset(stream);
    }


    void Processor::subscribe(Channel *channel) {
        // add channel
        std::lock_guard<mutex_t> lock(m_channelsLock);
        m_channels.insert(channel);
    }

    void Processor::unsubscribe(Channel *channel) {
        // remove a channel
        std::lock_guard<mutex_t> guard(m_channelsLock);
        m_channels.erase(channel);
    }


} // ns alog