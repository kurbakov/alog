#include <iostream>

#include <alog/Logger.hpp>

int main () {
	alog::initLogger<alog::Stream::IO>();
    LOG_INFO("Simple INFO log to stdout");
    LOG_INFO("Simple INFO log to stdout with arg: {}", 10);

	return 0;
}