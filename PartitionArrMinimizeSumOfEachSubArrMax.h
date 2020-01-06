#ifndef _PARTITION_ARR_MINIMIZE_SUM_OF_EACH_SUB_ARR_MAX_H
#define _PARTITION_ARR_MINIMIZE_SUM_OF_EACH_SUB_ARR_MAX_H
#include "Debug.h"
/*
AIG hackerrank online coding
Given an integer array, partition the array into k subarrays such that the sum of each subarray's max integer is minimized.
ex:
 [30, 10, 40, 20, 50], k=2: 80 ([30],[10,40,20,50] where sum=30+50=80)
 [74303, 20452, 66120, 44483, 5370, 68585], k=5: 234830 ([74303],[20452],[66120,44483],[5370],[68585] where sum=74303+20452+66120+5370+68585)

see also PaintersPartitionFairWorkload.h
 */
class PartitionArrMinimizeSumOfEachSubArrMax
{
public:

    int Recur(std::vector<int> && v, int k)
    {
        int res = recur(v, v.size(), k);
        std::cout << "PartitionArrMinimizeSumOfEachSubArrMax Recur for [" << Debug::ToStr1D<int>()(v) << "], k=" << k << ": " << res << std::endl;
        return res;
    }
private:
    int recur(std::vector<int> & v, int curSize, int k)
    {
        if (k == 1)
            return Max(v, 0, curSize-1);
        if (curSize == 1)
            return v[0];

        int minMaxSum = INT_MAX;
        for (int leftSize = 1; leftSize < curSize; ++leftSize)
        {
            if (k-1 > leftSize) continue; //condition to make sure left array size >= k-1  !!!
            minMaxSum = std::min(minMaxSum, recur(v, leftSize, k-1) + Max(v, leftSize, curSize-1));
        }

        return minMaxSum;
    }

    int Max(std::vector<int> & v, int begin, int end)
    {
        int res = v[begin];
        for (int i = begin; i <= end; ++i)
            res = std::max(res, v[i]);
        return res;
    }
};
/*
PartitionArrMinimizeSumOfEachSubArrMax Recur for [30, 10, 40, 20, 50], k=2: 80
PartitionArrMinimizeSumOfEachSubArrMax Recur for [74303, 20452, 66120, 44483, 5370, 68585], k=5: 234830
 */
#endif
