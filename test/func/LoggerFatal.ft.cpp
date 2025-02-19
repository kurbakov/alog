#include <alog/Logger.hpp>

int main()
{
    alog::initLogger<alog::Stream::IO>();

    LOG_FATAL("Should crash! {}", 10);

    return 0;
}
