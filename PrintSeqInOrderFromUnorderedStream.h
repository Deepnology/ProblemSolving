#ifndef _PRINT_SEQ_IN_ORDER_FROM_UNORDERED_STREAM_H
#define _PRINT_SEQ_IN_ORDER_FROM_UNORDERED_STREAM_H
#include "Debug.h"
/*
Bloomberg
UDP packet classic problem
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
