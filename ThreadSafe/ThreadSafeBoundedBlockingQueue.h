#ifndef _THREAD_SAFE_BOUNDED_BLOCKING_QUEUE_H
#define _THREAD_SAFE_BOUNDED_BLOCKING_QUEUE_H
#include "Debug.h"
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <future>
#include <thread>
/*
Leetcode: Design Bounded Blocking Queue
Implement a thread safe bounded blocking queue that has the following methods:
BoundedBlockingQueue(int capacity) The constructor initializes the queue with a maximum capacity.
void enqueue(int element) Adds an element to the front of the queue. If the queue is full, the calling thread is blocked until the queue is no longer full.
int dequeue() Returns the element at the rear of the queue and removes it. If the queue is empty, the calling thread is blocked until the queue is no longer empty.
int size() Returns the number of elements currently in the queue.
Your implementation will be tested using multiple threads at the same time. Each thread will either be a producer thread that only makes calls to the enqueue method or a consumer thread that only makes calls to the dequeue method. The size method will be called after every test case.
 */
class ThreadSafeBoundedBlockingQueue
{
    std::mutex mutex;
    std::deque<int> que;
    int capacity;
    std::condition_variable condition;
public:
    ThreadSafeBoundedBlockingQueue(int capacity) : capacity(capacity)
    {

    }

    void enqueue(int element)
    {
        std::unique_lock<std::mutex> lock(mutex);
        while (que.size() == capacity)
            condition.wait(lock);
        que.push_back(element);
        condition.notify_all();
    }

    int dequeue()
    {
        std::unique_lock<std::mutex> lock(mutex);
        while (que.empty())
            condition.wait(lock);
        int res = que.front();
        que.pop_front();
        condition.notify_all();
        return res;
    }

    int size()
    {
        std::unique_lock<std::mutex> lock(mutex);
        return que.size();
    }
};
#endif
