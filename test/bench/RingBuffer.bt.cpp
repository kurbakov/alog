#include <benchmark/benchmark.h>

#include <thread>

#include <alog/concurrency/RingBuffer.hpp>

static void pinThread(int cpu)
{
    if (cpu < 0) {
        return;
    }
    ::cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(cpu, &cpuset);
    if (::pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) == -1) {
        std::perror("pthread_setaffinity_rp");
        std::exit(EXIT_FAILURE);
    }
}

constexpr auto cpu1 = 1;
constexpr auto cpu2 = 2;

static void BM_RingBuffer(benchmark::State& state)
{
    alog::RingBuffer<int, 1024> buffer;

    auto consumer = std::jthread(
        [&buffer]() {
            pinThread(cpu1);

            int val;
            while (true) {
                while (not buffer.tryPop(val)) {
                    // loop untill the value is pulled!
                }
                benchmark::DoNotOptimize(val);

                if (val == -1) {
                    // once the queue has -1 -> break;
                    break;
                }
            }
        });

    // give some time to start the consumer thread
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // current thread is a producer
    pinThread(cpu2);

    int val = 0;
    for (auto _ : state) {
        while (auto again = not buffer.tryPush(val)) {
            benchmark::DoNotOptimize(again);
        }
        ++val;

        // wait till consumer cleans the queue
        while (auto again = not buffer.empty()) {
            benchmark::DoNotOptimize(again);
        }
    }
    int iterations = val;

    val = -1;
    while (not buffer.tryPush(val)) {
    }

    ++iterations;
    state.counters["ops/sec"] = benchmark::Counter(double(iterations), benchmark::Counter::kIsRate);
}

BENCHMARK(BM_RingBuffer);
