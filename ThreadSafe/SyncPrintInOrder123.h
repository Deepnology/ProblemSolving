#ifndef _SYNC_PRINT_IN_ORDER_123_H
#define _SYNC_PRINT_IN_ORDER_123_H
#include "Debug.h"
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <future>
#include <thread>
/*
Leetcode: Print In Order
 */
class SyncPrintInOrder123_Atomic
{
    std::atomic<bool> atomic1;
    std::atomic<bool> atomic2;
public:
    SyncPrintInOrder123_Atomic() : atomic1(false), atomic2(false)
    {

    }
    void first(std::function<void()> printFirst)
    {
        printFirst();
        atomic1.store(true, std::memory_order_release);
    }
    void second(std::function<void()> printSecond)
    {
        while (!atomic1.load(std::memory_order_acquire));
        printSecond();
        atomic2.store(true, std::memory_order_release);

    }
    void third(std::function<void()> printThird)
    {
        while (!atomic2.load(std::memory_order_acquire));
        printThird();
    }
    void Test()
    {
        std::thread t1([this]{first([](){std::cout << "first" << std::endl;});});
        std::thread t2([this]{second([](){std::cout << "second" << std::endl;});});
        std::thread t3([this]{third([](){std::cout << "third" << std::endl;});});
        t1.join();
        t2.join();
        t3.join();
    }
};
class SyncPrintInOrder123_PromiseFuture
{
    std::promise<void> p1;
    std::promise<void> p2;
public:
    SyncPrintInOrder123_PromiseFuture()
    {

    }
    void first(std::function<void()> printFirst)
    {
        printFirst();
        p1.set_value();
    }
    void second(std::function<void()> printSecond)
    {
        p1.get_future().wait();
        printSecond();
        p2.set_value();

    }
    void third(std::function<void()> printThird)
    {
        p2.get_future().wait();
        printThird();
    }
    void Test()
    {
        std::thread t1([this]{first([](){std::cout << "first" << std::endl;});});
        std::thread t2([this]{second([](){std::cout << "second" << std::endl;});});
        std::thread t3([this]{third([](){std::cout << "third" << std::endl;});});
        t1.join();
        t2.join();
        t3.join();
    }
};
/*
class SyncPrintInOrder123_Semaphore
{
    sem_t s1;
    sem_t s2;
public:
    SyncPrintInOrder123_Semaphore()
    {
        sem_init(&s1, 0, 0);
        sem_init(&s2, 0, 0);
    }
    void first(std::function<void()> printFirst)
    {
        printFirst();
        sem_post(&s1);
    }
    void second(std::function<void()> printSecond)
    {
        sem_wait(&s1);
        printSecond();
        sem_post(&s2);
    }
    void third(std::function<void()> printThird)
    {
        sem_wait(&s2);
        printThird();
    }
};
 */
class SyncPrintInOrder123_MutexCondition
{
    std::mutex mutex;
    std::condition_variable condition;
    int cur = 1;
public:
    SyncPrintInOrder123_MutexCondition()
    {

    }
    void first(std::function<void()> printFirst)
    {
        std::unique_lock<std::mutex> lock(mutex);
        printFirst();
        cur = 2;
        condition.notify_all();
    }
    void second(std::function<void()> printSecond)
    {
        std::unique_lock<std::mutex> lock(mutex);
        while (cur != 2)
            condition.wait(lock);//release lock and check again
        printSecond();
        cur = 3;
        condition.notify_all();
    }
    void third(std::function<void()> printThird)
    {
        std::unique_lock<std::mutex> lock(mutex);
        while (cur != 3)
            condition.wait(lock);//release lock and check again
        printThird();
    }
    void Test()
    {
        std::thread t1([this]{first([](){std::cout << "first" << std::endl;});});
        std::thread t2([this]{second([](){std::cout << "second" << std::endl;});});
        std::thread t3([this]{third([](){std::cout << "third" << std::endl;});});
        t1.join();
        t2.join();
        t3.join();
    }
};
#endif
