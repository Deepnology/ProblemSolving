#ifndef _SYNC_PRINT_FOO_BAR_ALTER_H
#define _SYNC_PRINT_FOO_BAR_ALTER_H
#include "Debug.h"
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <future>
#include <thread>
/*
Leetcode: Print FooBar Alternatively
 */
/*
class SyncPrintFooBarAlter_Semaphore
{
    int n;
    sem_t s1;
    sem_t s2;
public:
    SyncPrintFooBarAlter_Semaphore(int n)
    {
        this->n = n;
        sem_init(&s1, 0, 1);
        sem_init(&s2, 0, 0);
    }
    void foo(std::function<void()> printFoo)
    {
        for (int i = 0; i < n; i++)
        {
            sem_wait(&s1);
            // printFoo() outputs "foo". Do not change or remove this line.
            printFoo();
            sem_post(&s2);
        }
    }
    void bar(std::function<void()> printBar)
    {
        for (int i = 0; i < n; i++) {
            sem_wait(&s2);
            // printBar() outputs "bar". Do not change or remove this line.
            printBar();
            sem_post(&s1);
        }
    }
};
 */
class SyncPrintFooBarAlter_Atomic
{
    int n;
    std::atomic<bool> a;
public:
    SyncPrintFooBarAlter_Atomic(int n) {
        this->n = n;
        a = true;
    }
    void foo(std::function<void()> printFoo) {
        for (int i = 0; i < n; i++) {
            while (!a.load(std::memory_order_acquire)) std::this_thread::yield();
            // printFoo() outputs "foo". Do not change or remove this line.
            printFoo();
            a.store(false, std::memory_order_release);
        }
    }
    void bar(std::function<void()> printBar) {

        for (int i = 0; i < n; i++) {
            while (a.load(std::memory_order_acquire)) std::this_thread::yield();
            // printBar() outputs "bar". Do not change or remove this line.
            printBar();
            a.store(true, std::memory_order_release);
        }
    }

    void Test()
    {
        std::thread t1([this]{foo([](){ std::cout << "Foo" << std::endl; });});
        std::thread t2([this]{bar([](){ std::cout << "Bar" << std::endl; });});
        t1.join();
        t2.join();
    }
};
class SyncPrintFooBarAlter_MutexCondition
{
    int n;
    std::mutex mutex;
    std::condition_variable condition;
    bool isFoo;
public:
    SyncPrintFooBarAlter_MutexCondition(int n) {
        this->n = n;
        isFoo = true;
    }
    void foo(std::function<void()> printFoo) {
        for (int i = 0; i < n; i++) {
            std::unique_lock<std::mutex> lock(mutex);
            while (!isFoo)
                condition.wait(lock);//release lock and check again
            // printFoo() outputs "foo". Do not change or remove this line.
            printFoo();
            isFoo = false;
            condition.notify_all();
        }
    }
    void bar(std::function<void()> printBar) {

        for (int i = 0; i < n; i++) {
            std::unique_lock<std::mutex> lock(mutex);
            while (isFoo)
                condition.wait(lock);//release lock and check again
            // printBar() outputs "bar". Do not change or remove this line.
            printBar();
            isFoo = true;
            condition.notify_all();
        }
    }

    void Test()
    {
        std::thread t1([this]{foo([](){ std::cout << "Foo" << std::endl; });});
        std::thread t2([this]{bar([](){ std::cout << "Bar" << std::endl; });});
        t1.join();
        t2.join();
    }
};
#endif
