/*Facebook*/
#ifndef _MAX_SUB_ARR_SUM_SIZE_K_H
#define _MAX_SUB_ARR_SUM_SIZE_K_H
#include "Debug.h"
/*
Given an integer array, find max subarray sum with size K.
 */
class MaxSubArrSumSizeK
{
public:
    MaxSubArrSumSizeK(){}

    int PrefixSumArr_SlideWindow(const std::vector<int> & v)
    {
        return 0;
    }
    int ConstSpace_SlideWindow(const std::vector<int> & v, int k)
    {
        int N = v.size();
        int begin = 0;
        int end = 0;
        int res = INT_MIN;
        int sum = 0;
        while (end < N)
        {
            sum += v[end];
            if (end - begin + 1 == k)
            {
                res = std::max(res, sum);
                sum -= v[begin++];
            }
            ++end;
        }

        return res;
    }
};
#endif
