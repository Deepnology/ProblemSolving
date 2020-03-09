#ifndef _SYNC_PRINT_ZERO_ODD_ZERO_EVEN_H
#define _SYNC_PRINT_ZERO_ODD_ZERO_EVEN_H
#include "Debug.h"
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <future>
#include <thread>
/*
Leetcode: Print Zero Even Odd
 */
/*
class SyncPrintZeroOddZeroEven_Semaphore
{
    int n;
    sem_t sZero;
    sem_t sEven;
    sem_t sOdd;
    int cur;
public:
    SyncPrintZeroOddZeroEven_Semaphore(int n) {
        this->n = n;
        sem_init(&sZero, 0, 1);
        sem_init(&sEven, 0, 0);
        sem_init(&sOdd, 0, 0);
        cur = 0;
    }
    // printNumber(x) outputs "x", where x is an integer.
    void zero(std::function<void(int)> printNumber) {
        while (1)
        {
            sem_wait(&sZero);
            if (++cur > n)
            {
                sem_post(&sEven);
                sem_post(&sOdd);
                break;
            }
            printNumber(0);
            if (cur%2==0)
                sem_post(&sEven);
            else
                sem_post(&sOdd);
        }
    }
    void even(std::function<void(int)> printNumber) {
        while (1)
        {
            sem_wait(&sEven);
            if (cur > n) break;
            printNumber(cur);
            sem_post(&sZero);
        }
    }
    void odd(std::function<void(int)> printNumber) {
        while (1)
        {
            sem_wait(&sOdd);
            if (cur > n) break;
            printNumber(cur);
            sem_post(&sZero);
        }
    }
};
 */
class SyncPrintZeroOddZeroEven_MutexCondition
{
    int n;
    std::mutex mutex;
    std::condition_variable condition;
    int cur;
    bool printZero;
    bool printEven;
    bool printOdd;
public:
    SyncPrintZeroOddZeroEven_MutexCondition(int n) {
        this->n = n;
        cur = 0;
        printZero = true;
        printEven = false;
        printOdd = false;
    }
    // printNumber(x) outputs "x", where x is an integer.
    void zero(std::function<void(int)> printNumber) {
        while (1)
        {
            std::unique_lock<std::mutex> lock(mutex);
            while (!printZero)
                condition.wait(lock);//release and check again
            printZero = false;
            if (++cur > n)
            {
                printEven = true;
                printOdd = true;
                condition.notify_all();
                break;
            }
            printNumber(0);
            if (cur%2==0)
                printEven = true;
            else
                printOdd = true;
            condition.notify_all();
        }
    }
    void even(std::function<void(int)> printNumber) {
        while (1)
        {
            std::unique_lock<std::mutex> lock(mutex);
            while (!printEven)
                condition.wait(lock);//release lock and check again
            printEven = false;
            if (cur > n) break;
            printNumber(cur);
            printZero = true;
            condition.notify_all();
        }
    }
    void odd(std::function<void(int)> printNumber) {
        while (1)
        {
            std::unique_lock<std::mutex> lock(mutex);
            while (!printOdd)
                condition.wait(lock);//release lock and check again
            printOdd = false;
            if (cur > n) break;
            printNumber(cur);
            printZero = true;
            condition.notify_all();
        }
    }

    void Test()
    {
        std::thread t1([this]{zero([](int n){ std::cout << n << std::endl; });});
        std::thread t2([this]{odd([](int n){ std::cout << n << std::endl; });});
        std::thread t3([this]{even([](int n){ std::cout << n << std::endl; });});
        t1.join();
        t2.join();
        t3.join();
    }
};
#endif
