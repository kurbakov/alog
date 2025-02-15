#include "alog/concurrency/SpinLock.hpp"

namespace alog {
SpinLock::SpinLock()
    : m_flag(false)
{
}

void SpinLock::lock() noexcept
{
    static constexpr timespec ns { 0, 1 };
    static constexpr int sleep_each_attempts = 8;

    for (int i = 0; m_flag.load(std::memory_order_relaxed) || m_flag.exchange(true, std::memory_order_acquire); ++i) {
        if (i == sleep_each_attempts) {
            // Sleep to lat the scheduler understand that we are
            // waiting and let other tasks get into the execution

            // if we do not sleep, scheduler will assume we are very busy and
            // put us high in priority. As the result we will have to wait longer
            i = 0;
            nanosleep(&ns, nullptr);
        }
    }
}

bool SpinLock::try_lock() noexcept
{
    // First do a relaxed load to check if lock is free in order to prevent
    // unnecessary cache misses if someone does while(!try_lock())
    return !m_flag.load(std::memory_order_relaxed) && !m_flag.exchange(true, std::memory_order_acquire);
}

void SpinLock::unlock()
{
    m_flag.store(false, std::memory_order_release);
}
} // ns alog
