#pragma once

#include <set>
#include <thread>

#include "Channel.hpp"
#include "Defs.hpp"

#include "concurrency/SpinLock.hpp"
#include "concurrency/Utils.hpp"
#include "stream/StreamBase.hpp"

namespace alog {

class Processor final {
    using mutex_t = SpinLock;

    static std::atomic<Processor*> m_instance;
    std::set<Channel*> m_channels {};
    mutex_t m_channelsLock {};
    std::atomic_bool m_isRunning { false };
    std::thread m_runnerThread;
    std::unique_ptr<StreamBase> m_stream { nullptr };

    Processor();

    void run();
    void stop();

    static void deinit()
    {
        if (m_instance) {
            if (m_instance.load()->isRunning()) {
                m_instance.load()->stop();

                delete m_instance;
                m_instance = nullptr;
            }
        }
    }

public:
    static void init()
    {
        // make sure the init is thread safe!
        // in case if 2 threads call init, we need to make sure m_instance set only once!
        if (m_instance.load() == nullptr) {
            auto* processor = new Processor();
            Processor* expected = nullptr;
            if (!m_instance.compare_exchange_weak(expected, processor, std::memory_order_acq_rel)) {
                delete processor;
            }
        }

        // add callbacks to make sure we stop processor on exit
        std::atexit([]() { Processor::deinit(); });
        std::at_quick_exit([]() { Processor::deinit(); });
    }

    static Processor* get()
    {
        if (m_instance.load() == nullptr) [[unlikely]] {
            Processor::init();
        }

        return m_instance.load();
    }

    bool isRunning()
    {
        return m_isRunning.load();
    }

    void setStream(StreamBase* stream);

    void subscribe(Channel* channel);

    void unsubscribe(Channel* channel);
};
} // namespace alog
