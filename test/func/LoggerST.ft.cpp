#include <alog/Logger.hpp>

int main()
{
    alog::initLogger<alog::Stream::IO>();

    for (int i = 0; i < 10; ++i) {
        LOG_INFO("Simple log to stdout {}", i);
    }

    return 0;
}
