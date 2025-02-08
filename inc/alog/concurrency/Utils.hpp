#pragma once

#include <iostream>
#include <pthread.h>

namespace alog {
    inline void set_cpu_affinity(int cpu_id) {
        cpu_set_t cpu_set;
        CPU_ZERO(&cpu_set);
        CPU_SET(cpu_id, &cpu_set);
        if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpu_set) != 0) {
            std::cerr << "Failed to set pthread_setaffinity_np for CPU ID: " << cpu_id << std::endl;
        }
    }
}// namespace alog