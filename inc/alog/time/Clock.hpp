#pragma once

#include <cstdint>
#include <sys/time.h>
#include <chrono>

namespace alog {
    /**
     * For implementation of other ARCH please see:
     *  https://github.com/google/benchmark/blob/v1.1.0/src/cycleclock.h
     */
    inline __attribute__((always_inline)) uint64_t cpu_cycle_clock() {
#if defined(__i386__)
        int64_t ret;
        __asm__ volatile("rdtsc" : "=A"(ret));
        return ret;
#elif defined(__x86_64__) || defined(__amd64__)
        uint64_t low, high;
        __asm__ volatile("rdtsc" : "=a"(low), "=d"(high));
        return (high << 32) | low;
#endif
        return 0;
    }

    inline __attribute__((always_inline)) uint64_t second_time() { return time(nullptr); }

    inline __attribute__((always_inline)) timeval microsecond_time() {
        timeval tv{};
        gettimeofday(&tv, nullptr);

        return tv;
    }

    inline __attribute__((always_inline)) timespec nanosecond_time()
    {
        timespec timestamp{};
        clock_gettime(CLOCK_MONOTONIC, &timestamp);

        return timestamp;
    }

    inline __attribute__((always_inline)) auto chrono_time()
    {
        return std::chrono::high_resolution_clock::now();
    }


}// namespace alog