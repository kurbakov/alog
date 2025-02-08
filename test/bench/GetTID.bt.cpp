#include <benchmark/benchmark.h>

#include <alog/concurrency/Utils.hpp>

static void BM_GetTID_Posix(benchmark::State &state) {
    for (auto _: state) {
        auto tid = alog::get_tid_posix();
        benchmark::DoNotOptimize(tid);
    }
}

static void BM_GetTID_CPP(benchmark::State &state) {
    for (auto _: state) {
        auto tid = alog::get_tid_cpp();
        benchmark::DoNotOptimize(tid);
    }
}

static void BM_GetTID_C(benchmark::State &state) {
    for (auto _: state) {
        auto tid = alog::get_tid_c();
        benchmark::DoNotOptimize(tid);
    }
}

static void BM_GetTID_syscall(benchmark::State &state) {
    for (auto _: state) {
        auto tid = alog::get_tid_syscall();
        benchmark::DoNotOptimize(tid);
    }
}

BENCHMARK(BM_GetTID_Posix);
BENCHMARK(BM_GetTID_C);
BENCHMARK(BM_GetTID_CPP);
BENCHMARK(BM_GetTID_syscall);
