#include <thread>

#include <alog/Logger.hpp>

int main()
{
    alog::initLogger<alog::Stream::IO>();

    std::jthread t1 { []() {
        uint64_t tid = pthread_self();
        LOG_INFO("Simple log to stdout from TID: {}", tid);
    } };

    std::jthread t2 { []() {
        uint64_t tid = pthread_self();
        LOG_INFO("Simple log to stdout from TID: {}", tid);
    } };

    std::jthread t3 { []() {
        uint64_t tid = pthread_self();
        LOG_INFO("Simple log to stdout from TID: {}", tid);
    } };

    std::jthread t4 { []() {
        uint64_t tid = pthread_self();
        LOG_INFO("Simple log to stdout from TID: {}", tid);
    } };

    std::jthread t5 { []() {
        uint64_t tid = pthread_self();
        LOG_INFO("Simple log to stdout from TID: {}", tid);
    } };

    return 0;
}
