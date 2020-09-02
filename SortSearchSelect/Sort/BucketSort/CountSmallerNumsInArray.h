#ifndef _COUNT_SMALLER_NUMS_IN_ARRAY_H
#define _COUNT_SMALLER_NUMS_IN_ARRAY_H
#include "Debug.h"
/*
Leetcode: How Many Numbers Are Smaller Than the Current Number
Given the array nums, for each nums[i] find out how many numbers in the array are smaller than it.
That is, for each nums[i] you have to count the number of valid j's such that j != i and nums[j] < nums[i].
Return the answer in an array.
Example 1:
Input: nums = [8,1,2,2,3]
Output: [4,0,1,1,3]
Explanation:
For nums[0]=8 there exist four smaller numbers than it (1, 2, 2 and 3).
For nums[1]=1 does not exist any smaller number than it.
For nums[2]=2 there exist one smaller number than it (1).
For nums[3]=2 there exist one smaller number than it (1).
For nums[4]=3 there exist three smaller numbers than it (1, 2 and 2).
Example 2:
Input: nums = [6,5,4,8]
Output: [2,1,0,3]
Example 3:
Input: nums = [7,7,7,7]
Output: [0,0,0,0]
Constraints:
2 <= nums.length <= 500
0 <= nums[i] <= 100
 */
class CountSmallerNumsInArray
{
public:
    std::vector<int> UseMap(const std::vector<int> & nums)
    {
        //O(nlogn + N) time, where n is count of distinct values in nums, N is size of nums
        std::map<int, int> sortedCount;
        for (auto & n : nums)
            ++sortedCount[n];
        //calculate prefix sum (excluding self)
        int prefixSum = 0;
        for (auto itr = sortedCount.begin(); itr != sortedCount.end(); ++itr)
        {
            int tmp = itr->second;
            itr->second = prefixSum;
            prefixSum += tmp;
        }
        std::vector<int> res(nums.size());
        for (auto i = 0; i < nums.size(); ++i)
            res[i] = sortedCount[nums[i]];
        return res;
    }

    std::vector<int> UseBucketSort(const std::vector<int> & nums)
    {
        //bucket sort: O(n + N) time, where n is the range size of values in nums, N is size of nums
        std::vector<int> count(101, 0);
        for (auto & n : nums)
            ++count[n];
        int prefixSum = 0; //excluding self
        for (auto i = 0; i < 101; ++i)
        {
            int tmp = count[i];
            count[i] = prefixSum;
            prefixSum += tmp;
        }
        std::vector<int> res(nums.size());
        for (auto i = 0; i < nums.size(); ++i)
            res[i] = count[nums[i]];
        return res;
    }
};
#endif
