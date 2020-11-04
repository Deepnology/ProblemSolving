#ifndef _MIN_SUBARR_REMOVAL_TO_MAKE_REMAINING_DIVISIBLE_BY_K_H
#define _MIN_SUBARR_REMOVAL_TO_MAKE_REMAINING_DIVISIBLE_BY_K_H
#include "Debug.h"
/*
Leetcode: Make Sum Divisible by P
Given an array of positive integers nums, remove the smallest subarray (possibly empty) such that
 the sum of the remaining elements is divisible by p.
It is not allowed to remove the whole array.
Return the length of the smallest subarray that you need to remove, or -1 if it's impossible.
A subarray is defined as a contiguous block of elements in the array.
Example 1:
Input: nums = [3,1,4,2], p = 6
Output: 1
Explanation: The sum of the elements in nums is 10, which is not divisible by 6. We can remove the subarray [4], and the sum of the remaining elements is 6, which is divisible by 6.
Example 2:
Input: nums = [6,3,5,2], p = 9
Output: 2
Explanation: We cannot remove a single element to get a sum divisible by 9. The best way is to remove the subarray [5,2], leaving us with [6,3] with sum 9.
Example 3:
Input: nums = [1,2,3], p = 3
Output: 0
Explanation: Here the sum is 6. which is already divisible by 3. Thus we do not need to remove anything.
Example 4:
Input: nums = [1,2,3], p = 7
Output: -1
Explanation: There is no way to remove a subarray in order to get a sum divisible by 7.
Example 5:
Input: nums = [1000000000,1000000000,1000000000], p = 3
Output: 0
 */
class MinSubarrRemovalToMakeRemainingDivisibleByK
{
public:
    int UsePrefixSum(std::vector<int> & v, int k)
    {
        int N = v.size();
        int need = 0;//the subarray sum we need to remove
        for (auto & n : v)
            need = (need+n) % k;
        std::unordered_map<int,int> lastIdx;//map prefixSum to lastIdx
        lastIdx.insert({0,-1});
        int prefixSum = 0;
        int res = N;
        for (int i = 0; i < N; ++i)
        {
            prefixSum = (prefixSum+v[i])%k;
            lastIdx[prefixSum] = i;
            int want = (prefixSum-need+k)%k; //+k: to circulate in case of negative num
            if (lastIdx.count(want))
                res = std::min(res, i-lastIdx[want]);
        }
        return res < N ? res : -1;
    }
};
#endif
