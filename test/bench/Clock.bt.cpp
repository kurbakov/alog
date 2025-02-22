#include <benchmark/benchmark.h>

#include <alog/time/Clock.hpp>

static void BM_GetTime_Second(benchmark::State& state)
{
    for (auto _ : state) {
        auto ts = alog::timeInSecond();
        benchmark::DoNotOptimize(ts);
    }
}

static void BM_GetTime_Chrono(benchmark::State& state)
{
    for (auto _ : state) {
        auto ts = alog::timeChrono();
        benchmark::DoNotOptimize(ts);
    }
}

static void BM_GetTime_Nanos(benchmark::State& state)
{
    for (auto _ : state) {
        auto ts = alog::timeInNanosecond();
        benchmark::DoNotOptimize(ts);
    }
}

static void BM_GetTime_Micros(benchmark::State& state)
{
    for (auto _ : state) {
        auto ts = alog::timeInMicrosecond();
        benchmark::DoNotOptimize(ts);
    }
}

static void BM_GetTime_CpuCycleClock(benchmark::State& state)
{
    for (auto _ : state) {
        auto ts = alog::cpuCycleClock();
        benchmark::DoNotOptimize(ts);
    }
}

BENCHMARK(BM_GetTime_Second);
BENCHMARK(BM_GetTime_Chrono);
BENCHMARK(BM_GetTime_Nanos);
BENCHMARK(BM_GetTime_Micros);
BENCHMARK(BM_GetTime_CpuCycleClock);
