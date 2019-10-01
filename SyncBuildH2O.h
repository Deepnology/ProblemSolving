#ifndef _SYNC_BUILD_H2O_H
#define _SYNC_BUILD_H2O_H
#include "Debug.h"
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <future>
#include <thread>
/*
Leetcode: Building H2O
 */
/*
class SyncBuildH2O_Semaphore
{
    sem_t sH;
    sem_t sO;
    int countH;
public:
    SyncBuildH2O_Semaphore() {
        sem_init(&sH, 0, 0);
        sem_init(&sO, 0, 1);
        countH = 0;
    }
    void hydrogen(std::function<void()> releaseHydrogen)
    {
        sem_wait(&sH);
        releaseHydrogen();
        ++countH;
        if (countH==2)
        {
            countH = 0;
            sem_post(&sO);
        }
    }
    void oxygen(std::function<void()> releaseOxygen)
    {
        sem_wait(&sO);
        releaseOxygen();
        sem_post(&sH);
        sem_post(&sH);
    }
};
 */
class SyncBuildH2O_MutexCondition
{
    std::mutex mutex;
    int countH;
    int countO;
    std::condition_variable condition;
public:
    SyncBuildH2O_MutexCondition()
    {
        countH = 0;
        countO = 0;
    }
    void hydrogen(std::function<void()> releaseHydrogen)
    {
        //while (1)
        {
            std::unique_lock<std::mutex> lock(mutex);
            while (countH==2)
                condition.wait(lock);

            // releaseHydrogen() outputs "H". Do not change or remove this line.
            releaseHydrogen();
            ++countH;

            if (countH==2&&countO==1)
            {
                countH=0;
                countO=0;
            }
            condition.notify_all();
        }
    }
    void oxygen(std::function<void()> releaseOxygen)
    {
        //while (1)
        {
            std::unique_lock<std::mutex> lock(mutex);
            while (countO==1)
                condition.wait(lock);

            // releaseOxygen() outputs "O". Do not change or remove this line.
            releaseOxygen();
            ++countO;

            if (countH==2&&countO==1)
            {
                countH=0;
                countO=0;
            }
            condition.notify_all();
        }
    }

    void Test()
    {
        std::thread t1([this]
        {
            for (int i = 0; i < 20; ++i)
                hydrogen([](){std::cout << "H" << std::endl;});
        });
        std::thread t2([this]
        {
            for (int i = 0; i < 10; ++i)
                oxygen([](){std::cout << "O" << std::endl;});
        });
        t1.join();
        t2.join();
    }
};
#endif
