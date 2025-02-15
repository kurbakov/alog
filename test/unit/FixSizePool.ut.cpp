#include "alog/memory/FixSizePool.hpp"

#include <thread>

#include <gtest/gtest.h>

TEST(FixSizePool, alloc)
{
    alog::FixSizePool<64, 16> pool;
    void* mem = pool.allocate();
    EXPECT_NE(nullptr, mem);

    pool.free(mem);
}

TEST(FixSizePool, full)
{
    alog::FixSizePool<64, 8> pool;
    std::vector<void*> mem;
    for (int i = 0; i < 8; ++i) {
        void* ptr = pool.allocate();
        EXPECT_NE(nullptr, ptr);
        mem.push_back(ptr);
    }

    EXPECT_EQ(nullptr, pool.allocate()) << "Once the pool is empty, it should return a nullptr";

    for (void* ptr : mem) {
        pool.free(ptr);
    }
}

TEST(FixSizePool, allocAfterFree)
{
    alog::FixSizePool<64, 8> pool;
    std::vector<void*> mem;
    for (int i = 0; i < 8; ++i) {
        void* ptr = pool.allocate();
        EXPECT_NE(nullptr, ptr);
        mem.push_back(ptr);
    }

    pool.free(mem.back());
    mem.pop_back();

    void* ptr = pool.allocate();
    EXPECT_NE(nullptr, ptr) << "After in empty pool we return 1 memory element, we should be able to allocate it again";
}
