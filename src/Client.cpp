#include "alog/Client.hpp"

namespace alog {
Client::Client()
    : m_tid(std::this_thread::get_id())
{
    auto* processor = Processor::get();
    if (processor) {
        processor->subscribe(&m_channel);
    }
}

Client::~Client()
{
    while (not m_channel.empty()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    if (auto* processor = Processor::get(); processor) {
        processor->unsubscribe(&m_channel);
    }
}

void Client::log(const Metadata* meta)
{
    m_channel.send(meta, m_tid);
}
} // ns alog
