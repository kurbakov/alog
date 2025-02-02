#pragma once

#include <chrono>
#include <pthread.h>
#include <thread>

#include "time/Clock.hpp"

#include "Channel.hpp"
#include "Defs.hpp"
#include "Processor.hpp"


namespace alog {
    class Client {
    public:
        Client() : m_tid(std::this_thread::get_id()) {
            auto *processor = Processor::get();
            if (processor) {
                processor->subscribe(&m_channel);
            }
        }

        ~Client() {
            while (not m_channel.empty()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }

            if (auto *processor = Processor::get(); processor) {
                processor->unsubscribe(&m_channel);
            }
        }

        template<class... Args>
        void log(const Metadata *meta, timeval tv, Args... args) {
            m_channel.send(meta, m_tid, tv, args...);
        }

        void log(const Metadata *meta, timeval tv) {
            m_channel.send(meta, m_tid, tv);
        }

    private:
        Channel m_channel;
        const std::thread::id m_tid;
    };
}// namespace alog
