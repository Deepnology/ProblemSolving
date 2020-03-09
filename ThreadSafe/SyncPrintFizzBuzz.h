#ifndef _SYNC_PRINT_FIZZ_BUZZ_H
#define _SYNC_PRINT_FIZZ_BUZZ_H
#include "Debug.h"
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <future>
#include <thread>
/*
Leetcode: Fizz Buzz Multithreaded
 */
/*
class SyncPrintFizzBuzz_Semaphore
{
private:
    int n;
    sem_t sFizz;
    sem_t sBuzz;
    sem_t sFB;
    sem_t sNum;
public:
    SyncPrintFizzBuzz_Semaphore(int n) {
        this->n = n;
        sem_init(&sFizz, 0, 0);
        sem_init(&sBuzz, 0, 0);
        sem_init(&sFB, 0, 0);
        sem_init(&sNum, 0, 1);
    }
    // printFizz() outputs "fizz".
    void fizz(std::function<void()> printFizz)
    {
        for (int i = 3; i <= n; i += 3)
        {
            sem_wait(&sFizz);
            printFizz();
            sem_post(&sNum);
            if ((i+3)%5==0)
                i+=3;//skip next FizzBuzz
        }
    }
    // printBuzz() outputs "buzz".
    void buzz(std::function<void()> printBuzz)
    {
        for (int i = 5; i <= n; i += 5)
        {
            sem_wait(&sBuzz);
            printBuzz();
            sem_post(&sNum);
            if ((i+5)%3==0)
                i+=5;//skip next FizzBuzz
        }
    }
    // printFizzBuzz() outputs "fizzbuzz".
    void fizzbuzz(std::function<void()> printFizzBuzz)
    {
        for (int i = 15; i <= n; i += 15)
        {
            sem_wait(&sFB);
            printFizzBuzz();
            sem_post(&sNum);
        }
    }
    // printNumber(x) outputs "x", where x is an integer.
    void number(std::function<void(int)> printNumber)
    {
        for (int i = 1; i <= n; ++i)
        {
            sem_wait(&sNum);
            if (i%15==0)
            {
                sem_post(&sFB);
            }
            else if (i%5==0)
            {
                sem_post(&sBuzz);
            }
            else if (i%3==0)
            {
                sem_post(&sFizz);
            }
            else
            {
                printNumber(i);
                sem_post(&sNum);
            }
        }
    }
};
 */
class SyncPrintFizzBuzz_MutexCondition
{
private:
    int n;
    std::mutex mutex;
    std::condition_variable condition;
    int cur;
public:
    SyncPrintFizzBuzz_MutexCondition(int n)
    {
        this->n = n;
        cur = 1;
    }
    // printFizz() outputs "fizz".
    void fizz(std::function<void()> printFizz)
    {
        while (1)
        {
            std::unique_lock<std::mutex> lock(mutex);
            while (!(cur%3==0 && cur%5!=0) && cur <= n)
                condition.wait(lock);
            if (cur > n) break;
            printFizz();
            //std::cout << "Fizz" << std::endl;
            ++cur;
            condition.notify_all();
        }
    }
    // printBuzz() outputs "buzz".
    void buzz(std::function<void()> printBuzz)
    {
        while (1)
        {
            std::unique_lock<std::mutex> lock(mutex);
            while (!(cur%3!=0 && cur%5==0) && cur <= n)
                condition.wait(lock);
            if (cur > n) break;
            printBuzz();
            //std::cout << "Buzz" << std::endl;
            ++cur;
            condition.notify_all();
        }
    }
    // printFizzBuzz() outputs "fizzbuzz".
    void fizzbuzz(std::function<void()> printFizzBuzz)
    {
        while (1)
        {
            std::unique_lock<std::mutex> lock(mutex);
            while (!(cur%3==0 && cur%5==0) && cur <= n)
                condition.wait(lock);
            if (cur > n) break;
            printFizzBuzz();
            //std::cout << "FizzBuzz" << std::endl;
            ++cur;
            condition.notify_all();
        }
    }
    // printNumber(x) outputs "x", where x is an integer.
    void number(std::function<void(int)> printNumber)
    {
        while (1)
        {
            std::unique_lock<std::mutex> lock(mutex);
            while (!(cur%3!=0 && cur%5!=0) && cur <= n)
                condition.wait(lock);
            if (cur > n) break;
            printNumber(cur);
            //std::cout << cur << std::endl;
            ++cur;
            condition.notify_all();
        }
    }


    void Test()
    {
        std::thread t1([this]{fizz([](){std::cout << "Fizz" << std::endl;});});
        std::thread t2([this]{buzz([](){std::cout << "Buzz" << std::endl;});});
        std::thread t3([this]{fizzbuzz([](){std::cout << "FizzBuzz" << std::endl;});});
        std::thread t4([this]{number([](int x){std::cout << x << std::endl;});});
        t1.join();
        t2.join();
        t3.join();
        t4.join();
    }
};
#endif
