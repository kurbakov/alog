#pragma once

#include <chrono>
#include <cstdint>
#include <sys/time.h>

namespace alog {
/**
 * For implementation of other ARCH please see:
 *  https://github.com/google/benchmark/blob/v1.1.0/src/cycleclock.h
 */
inline __attribute__((always_inline)) uint64_t cpuCycleClock()
{
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

inline __attribute__((always_inline)) uint64_t timeInSecond() { return time(nullptr); }

inline __attribute__((always_inline)) timeval timeInMicrosecond()
{
    timeval tv {};
    gettimeofday(&tv, nullptr);

    return tv;
}

inline __attribute__((always_inline)) timespec timeInNanosecond()
{
    timespec timestamp {};
    clock_gettime(CLOCK_MONOTONIC, &timestamp);

    return timestamp;
}

inline __attribute__((always_inline)) auto timeChrono()
{
    return std::chrono::high_resolution_clock::now();
}

} // namespace alog
