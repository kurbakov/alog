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
        static Processor *m_instance;
        std::set<Channel *> m_channels{};
        std::mutex m_channelsLock{};
        std::atomic_bool m_isRunning{false};
        std::thread m_runnerThread;
        std::unique_ptr<StreamBase> m_stream{nullptr};

        void run() {
            m_isRunning.store(true);

            Event ev;
            while (m_isRunning.load()) {
                std::lock_guard<std::mutex> guard(m_channelsLock);
                for (auto *channel: m_channels) {
                    if (not channel) {
                        break;
                    }

                    if (channel->recv(ev)) {
                        m_stream->log(ev.tv_sec, ev.tv_usec, ev.level, ev.location, ev.tid, ev.msg);
                        channel->free(const_cast<char *>(ev.msg));
                        ev.msg = nullptr;
                    }
                }
            }
        }

        void stop() {
            m_isRunning.store(false);
            m_runnerThread.join();
        }

        Processor() {
            m_runnerThread = std::thread([&]() {
                run();
            });
        }

    public:
        static void init() {
            if (m_instance == nullptr) {
                m_instance = new Processor();
            }
        }

        void set_stream(StreamBase *stream) {
            m_stream.reset(stream);
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

        void subscribe(Channel *channel) {
            // add channel
            std::lock_guard<std::mutex> lock(m_channelsLock);
            m_channels.insert(channel);
        }

        void unsubscribe(Channel *channel) {
            // remove a channel
            std::lock_guard<std::mutex> guard(m_channelsLock);
            m_channels.erase(channel);
        }
    };

    Processor *Processor::m_instance = nullptr;
}// namespace alog
