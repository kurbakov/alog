#include <alog/Logger.hpp>

int main() {
    alog::initLogger<alog::Stream::IO>();

    LOG_DEBUG("Simple DEBUG log to stdout");
    LOG_INFO("Simple INFO log to stdout");
    LOG_WARN("Simple WARN log to stdout");
    LOG_ERROR("Simple ERROR log to stdout");
    LOG_FATAL("Simple FATAL log to stdout");

    return 0;
}