#include <benchmark/benchmark.h>

#include <alog/memory/FixSizePool.hpp>

static void BM_MemPool(benchmark::State& state)
{
    alog::FixSizePool<16, 16> pool;
    for (auto _ : state) {
        auto* ptr = pool.allocate();
        pool.free(ptr);

        benchmark::DoNotOptimize(ptr);
    }
}

BENCHMARK(BM_MemPool);
