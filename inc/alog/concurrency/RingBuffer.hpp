#pragma once

#include <array>
#include <atomic>
#include <cassert>

// 64 bytes on x86-64 │ L1_CACHE_BYTES │ L1_CACHE_SHIFT │ __cacheline_aligned │ ...
constexpr std::size_t cacheline = 64;

using padding = std::array<char, cacheline>;

namespace alog {

    /**
     * Single producer - single consumer queue.
     * Based on: https://www.youtube.com/watch?v=K3P_Lmq6pw0
     * Code: https://github.com/CharlesFrasch/cppcon2023/tree/main
     * Slides:
     * https://github.com/CppCon/CppCon2023/blob/main/Presentations/SPSC_Lock-free_Wait-Free_Fifo_from_the_Ground_Up_CppCon_2023.pdf
     */
    template<class T, std::size_t S>
    class RingBuffer {
    private:
        static constexpr std::size_t m_idxMask = S - 1;
        std::array<T, S> m_buffer{};

        std::atomic_size_t m_pushIdx{0};
        [[maybe_unused]] padding m_padPush{};

        std::atomic_size_t m_popIdx{0};
        [[maybe_unused]] padding m_padPop{};

    public:
        RingBuffer() {
            // make sure capacity is n**2
            assert((S > 1) && ((S & (S - 1)) == 0));
        }

        [[nodiscard]] bool empty() const {
            auto popIdx = m_popIdx.load();
            auto pushIdx = m_pushIdx.load();

            return popIdx == pushIdx;
        }

        bool tryPush(const T &v) {
            auto popIdx = m_popIdx.load();
            auto pushIdx = m_pushIdx.load();

            // is full
            if (auto currLen = pushIdx - popIdx; S == currLen) {
                return false;
            }

            m_buffer[pushIdx & m_idxMask] = v;
            m_pushIdx.store(pushIdx + 1);

            return true;
        }

        bool tryPop(T &v) {
            auto popIdx = m_popIdx.load();
            auto pushIdx = m_pushIdx.load();

            if (popIdx == pushIdx) {
                return false;
            }

            v = m_buffer[popIdx & m_idxMask];
            m_popIdx.store(popIdx + 1);

            return true;
        }
    };
}// namespace alog
