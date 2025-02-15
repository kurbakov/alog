#include <benchmark/benchmark.h>

#include <alog/time/Clock.hpp>

static void BM_GetTime_Second(benchmark::State& state)
{
    for (auto _ : state) {
        auto ts = alog::second_time();
        benchmark::DoNotOptimize(ts);
    }
}

static void BM_GetTime_Chrono(benchmark::State& state)
{
    for (auto _ : state) {
        auto ts = alog::chrono_time();
        benchmark::DoNotOptimize(ts);
    }
}

static void BM_GetTime_Nanos(benchmark::State& state)
{
    for (auto _ : state) {
        auto ts = alog::nanosecond_time();
        benchmark::DoNotOptimize(ts);
    }
}

static void BM_GetTime_Micros(benchmark::State& state)
{
    for (auto _ : state) {
        auto ts = alog::microsecond_time();
        benchmark::DoNotOptimize(ts);
    }
}

static void BM_GetTime_CpuCycleClock(benchmark::State& state)
{
    for (auto _ : state) {
        auto ts = alog::cpu_cycle_clock();
        benchmark::DoNotOptimize(ts);
    }
}

BENCHMARK(BM_GetTime_Second);
BENCHMARK(BM_GetTime_Chrono);
BENCHMARK(BM_GetTime_Nanos);
BENCHMARK(BM_GetTime_Micros);
BENCHMARK(BM_GetTime_CpuCycleClock);
