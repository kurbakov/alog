#include <benchmark/benchmark.h>

#include <alog/concurrency/Utils.hpp>

static void BM_GetTID_Posix(benchmark::State& state)
{
    for (auto _ : state) {
        auto tid = alog::getTidPosixStyle();
        benchmark::DoNotOptimize(tid);
    }
}

static void BM_GetTID_CPP(benchmark::State& state)
{
    for (auto _ : state) {
        auto tid = alog::getTidCppStyle();
        benchmark::DoNotOptimize(tid);
    }
}

static void BM_GetTID_C_V1(benchmark::State& state)
{
    for (auto _ : state) {
        auto tid = alog::getTidCStyleV1();
        benchmark::DoNotOptimize(tid);
    }
}

static void BM_GetTID_C_V2(benchmark::State& state)
{
    for (auto _ : state) {
        auto tid = alog::getTidCStyleV2();
        benchmark::DoNotOptimize(tid);
    }
}

static void BM_GetTID_syscall(benchmark::State& state)
{
    for (auto _ : state) {
        auto tid = alog::getTidViaSyscall();
        benchmark::DoNotOptimize(tid);
    }
}

BENCHMARK(BM_GetTID_Posix);
BENCHMARK(BM_GetTID_C_V1);
BENCHMARK(BM_GetTID_C_V2);
BENCHMARK(BM_GetTID_CPP);
BENCHMARK(BM_GetTID_syscall);
