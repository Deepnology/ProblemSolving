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

    void ReceiveAndPrint(int idx)
    {
        std::cout << idx << ": ";
        if (nxtIdxToPrint == idx)
        {
            std::cout << idx << ",";
            ++nxtIdxToPrint;
            while (!minHeap.empty() && minHeap.top() == nxtIdxToPrint)
            {
                std::cout << minHeap.top() << ",";
                minHeap.pop();
                ++nxtIdxToPrint;
            }
        }
        else
            minHeap.push(idx);
        std::cout << std::endl;
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
 */
#endif
