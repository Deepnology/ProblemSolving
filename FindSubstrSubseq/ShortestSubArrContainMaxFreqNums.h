#ifndef _SHORTEST_SUBARR_CONTAIN_MAX_FREQ_NUMS_H
#define _SHORTEST_SUBARR_CONTAIN_MAX_FREQ_NUMS_H
#include "Debug.h"
/*
Leetcode: Degree of an Array
Given a non-empty array of non-negative integers nums, the degree of this array is defined as the maximum frequency of any one of its elements.
Your task is to find the smallest possible length of a (contiguous) subarray of nums, that has the same degree as nums.
Example 1:
Input: [1, 2, 2, 3, 1]
Output: 2
Explanation:
The input array has a degree of 2 because both elements 1 and 2 appear twice.
Of the subarrays that have the same degree:
[1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
The shortest length is 2. So return 2.
Example 2:
Input: [1,2,2,3,1,4,2]
Output: 6
*/
class ShortestSubArrContainMaxFreqNums
{
public:
    ShortestSubArrContainMaxFreqNums(){}

    int GetLen_HashMap(const std::vector<int> & nums)
    {
        int N = nums.size();
        int len = N;
        int degree = 0;//max freq of a particular num
        std::unordered_map<int,int> startIdx;//<num,startIdx>
        std::unordered_map<int,int> count;//<num,count>
        for (int i = 0; i < N; ++i)
        {
            if (!startIdx.count(nums[i]))
                startIdx.insert({nums[i], i});
            ++count[nums[i]];
            if (count[nums[i]] == degree)
            {
                len = std::min(len,i-startIdx[nums[i]]+1);
            }
            else if (count[nums[i]] > degree)
            {
                degree = count[nums[i]];
                len = i-startIdx[nums[i]]+1;
            }
            //std::cout << nums[i] << ":" << degree << "," << len << std::endl;
        }

        std::cout << "ShortestSubArrContainMaxFreqNums GetLen_HashMap for \"" << Debug::ToStr1D<int>()(nums) << "\": " << len << std::endl;
        return len;
    }
};
/*
ShortestSubArrContainMaxFreqNums GetLen_HashMap for "1, 2, 2, 3, 1": 2
ShortestSubArrContainMaxFreqNums GetLen_HashMap for "1, 2, 2, 3, 1, 4, 2": 6
 */
#endif
