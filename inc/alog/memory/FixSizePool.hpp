#pragma once

#include <cstdint>

#include "alog/concurrency/RingBuffer.hpp"

namespace alog {
    template<uint64_t TSize, uint64_t TCount>
    class FixSizePool {
    public:
        FixSizePool() {
            m_memory = new char[TSize * TCount];
            char *memIdx = m_memory;
            for (int i = 0; i < TCount; ++i) {
                m_ringBuffer.tryPush(memIdx);
                memIdx += TSize;
            }
        }

        ~FixSizePool() {
            delete[] m_memory;
        }

        void *allocate() {
            void *res = nullptr;
            m_ringBuffer.tryPop(res);
            return res;
        }

        void free(void *mem) {
            if (is_part_of_pool(mem)) {
                m_ringBuffer.tryPush(mem);
            }
        }

    private:
        bool is_part_of_pool(void* mem) {
            return mem != nullptr && m_memory != nullptr && m_memory <= mem && mem <= m_memory + TSize*TCount;
        }

        char *m_memory = nullptr;
        RingBuffer<void *, TCount> m_ringBuffer;
    };

}// namespace alog
