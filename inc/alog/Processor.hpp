#pragma once

#include <iostream>
#include <set>
#include <thread>

#include "Channel.hpp"
#include "Defs.hpp"

#include "concurrency/SpinLock.hpp"
#include "concurrency/Utils.hpp"

#include "stream/StreamBase.hpp"
#include "stream/StreamIO.hpp"


namespace alog {

    class Processor final {
        using mutex_t = SpinLock;

        static Processor *m_instance;
        std::set<Channel *> m_channels{};
        mutex_t m_channelsLock{};
        std::atomic_bool m_isRunning{false};
        std::thread m_runnerThread;
        std::unique_ptr<StreamBase> m_stream{nullptr};

        Processor();

        void run();
        void stop();

    public:
        static void init() {
            if (m_instance == nullptr) {
                m_instance = new Processor();
            }
        }

        static void deinit() {
            if (m_instance) {
                m_instance->stop();

                delete m_instance;
                m_instance = nullptr;
            }
        }

        static Processor *get() {
            return m_instance;
        }

        void set_stream(StreamBase *stream);

        void subscribe(Channel *channel);

        void unsubscribe(Channel *channel);
    };
}// namespace alog
