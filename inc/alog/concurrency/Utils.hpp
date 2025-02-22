#pragma once

#include <iostream>
#include <pthread.h>
#include <thread>
#include <threads.h>

namespace alog {

inline void setCpuAffinity(int cpu_id)
{
    cpu_set_t cpu_set;
    CPU_ZERO(&cpu_set);
    CPU_SET(cpu_id, &cpu_set);
    if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpu_set) != 0) {
        std::cerr << "Failed to set pthread_setaffinity_np for CPU ID: " << cpu_id << std::endl;
    }
}

inline __attribute__((always_inline)) auto getTidViaSyscall()
{
    return syscall(SYS_gettid);
}

inline __attribute__((always_inline)) auto getTidCppStyle()
{
    return std::this_thread::get_id();
}

inline __attribute__((always_inline)) auto getTidPosixStyle()
{
    return pthread_self();
}

inline __attribute__((always_inline)) auto getTidCStyleV1()
{
    return gettid();
}

inline __attribute__((always_inline)) auto getTidCStyleV2()
{
    return thrd_current();
}

} // namespace alog
