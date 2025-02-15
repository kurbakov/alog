#include "alog/concurrency/RingBuffer.hpp"

#include <thread>

#include <gtest/gtest.h>

TEST(RingBuffer, push)
{
    alog::RingBuffer<int*, 2> queue;

    int* v = new int { 0 };
    EXPECT_TRUE(queue.tryPush(v));
    delete v;
}

TEST(RingBuffer, pushAndPop)
{
    alog::RingBuffer<int*, 16> queue;

    int* val = new int(0);
    EXPECT_TRUE(queue.tryPush(val));

    int* res = nullptr;

    EXPECT_TRUE(queue.tryPop(res));

    EXPECT_EQ(val, res);
    delete val;
}

TEST(RingBuffer, TwoThreads)
{
    alog::RingBuffer<int*, 64> queue;

    std::thread consumer(
        [&queue]() {
            int* recv_val = nullptr;
            while (true) {
                while (not queue.tryPop(recv_val)) {
                    // busy wait
                }

                if (*recv_val == -1) {
                    break;
                }
            }
        });

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    int* send_val = new int(1);
    while (*send_val < 512) {
        while (not queue.tryPush(send_val)) {
            // busy wait
        }

        *send_val += 1;
    }

    *send_val = -1;
    while (not queue.tryPush(send_val)) {
    }

    consumer.join();
}
