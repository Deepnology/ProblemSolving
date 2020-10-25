#ifndef _EQUAL_SUM_3_SUB_ARR_PARTITION_H
#define _EQUAL_SUM_3_SUB_ARR_PARTITION_H
#include "Debug.h"
/*
Leetcode: Partition Array Into Three Parts With Equal Sum
Given an array A of integers, return true if and only if we can partition the array into three non-empty parts with equal sums.
Formally, we can partition the array if we can find indexes i+1 < j with (A[0] + A[1] + ... + A[i] == A[i+1] + A[i+2] + ... + A[j-1] == A[j] + A[j-1] + ... + A[A.length - 1])
Example 1:
Input: A = [0,2,1,-6,6,-7,9,1,2,0,1]
Output: true
Explanation: 0 + 2 + 1 = -6 + 6 - 7 + 9 + 1 = 2 + 0 + 1
Example 2:
Input: A = [0,2,1,-6,6,7,9,-1,2,0,1]
Output: false
Example 3:
Input: A = [3,3,6,5,-2,2,5,1,-9,4]
Output: true
Explanation: 3 + 3 = 6 = 5 - 2 + 2 + 5 + 1 - 9 + 4
 */
class EqualSum3SubArrPartition
{
public:
    //BruteForce: O(N^2) time

    bool Solve(std::vector<int> & A)//O(N) time
    {
        int sum = std::accumulate(A.begin(), A.end(), 0);
        if (sum % 3 != 0) return false;
        int curSum = 0;
        int count = 0;
        int N = A.size();
        for (int i = 0; i < N; ++i)
        {
            curSum += A[i];
            if (curSum == sum/3)
            {
                curSum = 0;
                ++count;
            }
        }
        return curSum == 0 && count >= 3;

        /*
        note: count >= 3
        ex: [10,-10,10,-10,10,-10,10,-10]
        if sum is 0, we can reach it for more than 3 times
        */
    }
};
#endif
