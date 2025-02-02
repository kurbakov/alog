#include <benchmark/benchmark.h>

#include <alog/Logger.hpp>

static void BM_LogGeneration_0_Args(benchmark::State &state) {
    alog::initLogger<alog::Stream::DevNull>();

    for (auto _: state) {
        LOG_INFO("Simple INFO log to stdout");
    }
}

static void BM_LogGeneration_1_Args(benchmark::State &state) {
    alog::initLogger<alog::Stream::DevNull>();

    for (auto _: state) {
        LOG_INFO("Simple INFO log to stdout {}", 999);
    }
}


static void BM_LogGeneration_2_Args(benchmark::State &state) {
    alog::initLogger<alog::Stream::DevNull>();

    for (auto _: state) {
        LOG_INFO("Simple INFO log to stdout {} {}", 888, 999);
    }
}

BENCHMARK(BM_LogGeneration_0_Args);
BENCHMARK(BM_LogGeneration_1_Args);
BENCHMARK(BM_LogGeneration_2_Args);
