#pragma once

#include <atomic>

namespace alog {
/**
 * @brief The SpinLock class
 *
 * useful links:
 *  - https://rigtorp.se/spinlock/
 *  - https://www.youtube.com/watch?v=rmGJc9PXpuE
 */

class SpinLock {
public:
    SpinLock();

    /**
     * @brief lock
     *
     * Function will try to lock and if can't, will wait until the lock is aquired.
     */
    void lock() noexcept;

    /**
     * @brief try_lock
     *
     * Function will try to lock. if lock is aquired, will return True, on dailure will return False
     */
    bool try_lock() noexcept;

    /**
     * @brief unlock
     */
    void unlock();

private:
    /**
     * @brief _flag
     * True if locked, false if not locked
     */
    std::atomic_bool m_flag;
};
} // namespace alog
