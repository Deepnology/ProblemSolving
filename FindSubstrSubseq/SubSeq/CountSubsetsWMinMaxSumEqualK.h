#ifndef _COUNT_SUBSETS_W_MIN_MAX_SUM_EQUAL_K_H
#define _COUNT_SUBSETS_W_MIN_MAX_SUM_EQUAL_K_H
#include "Debug.h"
/*
https://leetcode.com/discuss/interview-experience/275785/Facebook-Phone-Interview
Input:

Given an array A of
-positive
-sorted
-no duplicate
-integer

A positive integer k

Output:

Count of all such subsets of A,
Such that for any such subset S,
Min(S) + Max(S) = k
subset should contain at least two elements

input: {1,2,3,4,5}, k = 5
=>
count = 5
{1,4},{2,3},{1,2,4},{1,2,3,4},{1,3,4}

Leetcode: Number of Subsequences That Satisfy the Given Sum Condition
Given an array of integers nums and an integer target.
Return the number of non-empty subsequences of nums such that the sum of the minimum and maximum element on it is less or equal to target.
Since the answer may be too large, return it modulo 10^9 + 7.
Example 1:
Input: nums = [3,5,6,7], target = 9
Output: 4
Explanation: There are 4 subsequences that satisfy the condition.
[3] -> Min value + max value <= target (3 + 3 <= 9)
[3,5] -> (3 + 5 <= 9)
[3,5,6] -> (3 + 6 <= 9)
[3,6] -> (3 + 6 <= 9)
*/
class CountSubsetsWMinMaxSumEqualK
{
public:
    CountSubsetsWMinMaxSumEqualK(){}

    int TwoPtrsFromSortedArr(std::vector<int> && sorted, int k) //sorted contains all distinct integers
    {
        int N = sorted.size();
        int i = 0;
        int j = N-1;
        int count = 0;
        while (i < j)
        {
            if (sorted[i] + sorted[j] == k)
            {
                count += (1 << (j-i-1));
                std::cout << "NumOfSubsetsIn [" << sorted[i] << "," << sorted[j] << "]: " << (1<<(j-i-1)) << std::endl;
                //num of subsets of a window that include at least both ends = 2^(windowLen-2)
                //ex: [1,2,3,4,5]: [1,2,3,4,5],[1,2,3,5],[1,2,4,5],[1,3,4,5],[1,2,5],[1,3,5],[1,4,5],[1,5], 2^3=8
                ++i;
                --j;
            }
            else if (sorted[i] + sorted[j] < k)
                ++i;
            else
                --j;
        }

        std::cout << "CountSubsetsWMinMaxSumEqualK TwoPtrsFromSortedArr for k=" << k << " from [" << Debug::ToStr1D<int>()(sorted) << "]: " << count << std::endl;
        return count;
    }
};
class CountSubsetsWMinMaxSumLessEqualK
{
public:
    int TwoPtrs(std::vector<int> & nums, int target)
    {
        int MOD = 1000000007;
        std::sort(nums.begin(), nums.end());
        int N = nums.size();
        std::vector<int> pows(N, 1);
        for (int i = 1; i < N; ++i)
            pows[i] = pows[i-1]*2%MOD;
        int i = 0;
        int j = N-1;
        int res = 0;
        while (i <= j)
        {
            if (nums[i]+nums[j] > target)
                --j;
            else
            {
                res = (res+pows[j-i])%MOD; //2^(j-i)
                ++i;
            }
        }
        return res;
    }
};
/*
NumOfSubsetsIn [1,5]: 8
NumOfSubsetsIn [2,4]: 2
CountSubsetsWMinMaxSumEqualK TwoPtrsFromSortedArr for k=6 from [1, 2, 3, 4, 5]: 10
 */
#endif
