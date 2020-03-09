#ifndef _PRINT_SEQ_IN_ORDER_FROM_UNORDERED_STREAM_H
#define _PRINT_SEQ_IN_ORDER_FROM_UNORDERED_STREAM_H
#include "Debug.h"
/*
Bloomberg, Uber
UDP packet classic problem, Apache Kafka similar question
Ex:
1. 4
2. 5
3. 3
4. 1 => print 1
5. 2 => print 2,3,4,5

Ex:
1. 4
2. 1 => print 1
3. 5
4. 2 => print 2
5. 3 => print 3,4,5
 */
class PrintSeqInOrderFromUnorderedStream
{
public:
    PrintSeqInOrderFromUnorderedStream(){}

    void Test(const std::vector<int> & streamIdx)
    {
        //reset:
        nxtIdxToPrint = 1;
        std::priority_queue<int, std::vector<int>, std::greater<int>>().swap(minHeap);

        std::cout << "PrintSeqInOrderFromUnorderedStream for [" << Debug::ToStr1D<int>()(streamIdx) << "]:" << std::endl;
        for (const auto & i : streamIdx)
            ReceiveAndPrint(i);
    }

    std::vector<int> ReceiveAndPrint(int idx)
    {
        std::cout << idx << ": ";
        std::vector<int> res;
        if (nxtIdxToPrint == idx)
        {
            std::cout << idx << ",";
            res.push_back(idx);
            ++nxtIdxToPrint;
            while (!minHeap.empty() && minHeap.top() == nxtIdxToPrint)
            {
                std::cout << minHeap.top() << ",";
                res.push_back(minHeap.top());
                minHeap.pop();
                ++nxtIdxToPrint;
            }
        }
        else
            minHeap.push(idx);
        std::cout << std::endl;
        return res;
    }
private:
    int nxtIdxToPrint;
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
};

class PrintSeqInOrderFromUnorderedStream_AllowRepeats
{
public:
    PrintSeqInOrderFromUnorderedStream_AllowRepeats(){}

    void Test(const std::vector<int> & streamIdx)
    {
        //reset:
        nxtIdxToPrint = 1;
        std::priority_queue<int, std::vector<int>, std::greater<int>>().swap(minHeap);

        std::cout << "PrintSeqInOrderFromUnorderedStream_AllowRepeats for [" << Debug::ToStr1D<int>()(streamIdx) << "]:" << std::endl;
        for (const auto & i : streamIdx)
            ReceiveAndPrint(i);
    }

    std::vector<int> ReceiveAndPrint(int idx)
    {
        std::cout << idx << ": ";
        std::vector<int> res;
        if (nxtIdxToPrint > idx)
        {
            std::cout << idx << ",";
            res.push_back(idx);
        }
        else if (nxtIdxToPrint == idx)
        {
            std::cout << idx << ",";
            res.push_back(idx);
            ++nxtIdxToPrint;

            while (!minHeap.empty() && minHeap.top() == nxtIdxToPrint)
            {
                while (!minHeap.empty() && minHeap.top() == nxtIdxToPrint)
                {
                    std::cout << minHeap.top() << ",";
                    res.push_back(minHeap.top());
                    minHeap.pop();
                }
                ++nxtIdxToPrint;
            }
        }
        else
            minHeap.push(idx);

        std::cout << std::endl;
        return res;
    }
private:
    int nxtIdxToPrint;
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
};
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>
class PrintSeqInOrderFromUnorderedStream_AllowRepeats_ThreadSafe
{
    std::queue<int> m_inputQue;
    std::mutex m_mutex1;
    std::condition_variable m_condition1;
    std::condition_variable m_condition2;//for join only
    bool m_interrupt;//for join only

    int nxtIdxToPrint;
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    std::mutex m_mutexTask;

public:
    PrintSeqInOrderFromUnorderedStream_AllowRepeats_ThreadSafe(): m_interrupt(false),
            nxtIdxToPrint(1)
    {

    }

    void Run()
    {
        std::vector<std::thread*> pool;//note: vector::ctor not working properly to create thread instances
        for (int i = 0; i < 2; ++i)
            pool.push_back(new std::thread(&PrintSeqInOrderFromUnorderedStream_AllowRepeats_ThreadSafe::InfiniteLoop, this));

        for (int i = 0; i < 30; ++i)
        {
            int idx = rand() % 5 + 1;
            std::unique_lock<std::mutex> lock1(m_mutex1);
            m_inputQue.push(idx);
            m_condition1.notify_one();
        }
        //std::this_thread::sleep_for(std::chrono::seconds(10));

        //wait until inputQue is empty
        {
            std::unique_lock<std::mutex> lock1(m_mutex1);

            while (!m_inputQue.empty())
            {
                m_condition1.notify_one();
                m_condition2.wait(lock1);
            }
            //equivalent to
            //m_condition2.wait(lock1, [this](){ return m_inputQue.empty(); });

            //now inputQue is empty
            //mark interrupt by main thread
            m_interrupt = true;
            m_condition1.notify_all();
        }

        //now join by main thread
        for (auto t : pool)
        {
            t->join();
            delete t;
        }
    }

    void InfiniteLoop()
    {
        while (true)
        {
            if (ReceiveAndPrint()) break;
        }
    }

    bool ReceiveAndPrint()
    {
        int idx;
        {
            std::unique_lock<std::mutex> lock1(m_mutex1);
            if (m_interrupt) return true;
            //equivalent to "while (m_inputQue.empty() && !m_interrupt) m_condition1.wait(lock1);"
            m_condition1.wait(lock1, [this]() { return !m_inputQue.empty() || m_interrupt; });//note: when calling m_condition1.notify() the lambda function will always be tested again !
            if (m_interrupt) return true;
            idx = m_inputQue.front(); m_inputQue.pop();
            m_condition2.notify_one();
        }

        std::cout << std::this_thread::get_id() << std::endl;

        std::ostringstream oss;
        oss << idx << ": ";

        {
            std::unique_lock<std::mutex> lock2(m_mutexTask);
            if (nxtIdxToPrint > idx)
            {
                oss << idx << ",";
            }
            else if (nxtIdxToPrint == idx)
            {
                oss << idx << ",";
                ++nxtIdxToPrint;

                while (!minHeap.empty() && minHeap.top() == nxtIdxToPrint)
                {
                    while (!minHeap.empty() && minHeap.top() == nxtIdxToPrint)
                    {
                        oss << minHeap.top() << ",";
                        minHeap.pop();
                    }
                    ++nxtIdxToPrint;
                }
            }
            else
                minHeap.push(idx);
        }

        std::cout << oss.str() << std::endl;
        return false;
    }
};
/*
PrintSeqInOrderFromUnorderedStream for [4, 5, 3, 1, 2]:
4:
5:
3:
1: 1,
2: 2,3,4,5,
PrintSeqInOrderFromUnorderedStream for [4, 1, 5, 2, 3]:
4:
1: 1,
5:
2: 2,
3: 3,4,5,
PrintSeqInOrderFromUnorderedStream for [3, 5, 1, 2, 4]:
3:
5:
1: 1,
2: 2,3,
4: 4,5,
PrintSeqInOrderFromUnorderedStream for [1, 3, 2, 4, 5]:
1: 1,
3:
2: 2,3,
4: 4,
5: 5,

PrintSeqInOrderFromUnorderedStream_AllowRepeats for [4, 5, 3, 4, 1, 5, 2, 1]:
4:
5:
3:
4:
1: 1,
5:
2: 2,3,4,4,5,5,
1: 1,
PrintSeqInOrderFromUnorderedStream_AllowRepeats for [4, 1, 4, 4, 5, 1, 2, 3]:
4:
1: 1,
4:
4:
5:
1: 1,
2: 2,
3: 3,4,4,4,5,
PrintSeqInOrderFromUnorderedStream_AllowRepeats for [3, 5, 1, 2, 5, 4, 1, 2]:
3:
5:
1: 1,
2: 2,3,
5:
4: 4,5,5,
1: 1,
2: 2,
PrintSeqInOrderFromUnorderedStream_AllowRepeats for [7, 8, 5, 3, 4, 4, 5, 2, 1, 2, 6, 3]:
7:
8:
5:
3:
4:
4:
5:
2:
1: 1,2,3,4,4,5,5,
2: 2,
6: 6,7,8,
3: 3,
 */
#endif
