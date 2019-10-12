#ifndef _COUNT_SUB_ARR_W_LEFTMOST_NUM_LESS_EQUAL_TO_ALL_H
#define _COUNT_SUB_ARR_W_LEFTMOST_NUM_LESS_EQUAL_TO_ALL_H
#include "Debug.h"
/*
Leetcode: Number of Valid Subarrays
Given an array A of integers, return the number of non-empty continuous subarrays that satisfy the following condition:
The leftmost element of the subarray is not larger than other elements in the subarray.
Example 1:
Input: [1,4,2,5,3]
Output: 11
Explanation: There are 11 valid subarrays: [1],[4],[2],[5],[3],[1,4],[2,5],[1,4,2],[2,5,3],[1,4,2,5],[1,4,2,5,3].
Example 2:
Input: [3,2,1]
Output: 3
Explanation: The 3 valid subarrays are: [3],[2],[1].
Example 3:
Input: [2,2,2]
Output: 6
Explanation: There are 6 valid subarrays: [2],[2],[2],[2,2],[2,2],[2,2,2].

see also SumOfAllSubArrMins.h
 */
class CountSubArrWLeftmostNumLessEqualToAll
{
public:

    int UseStack(std::vector<int> && nums)
    {
        int N = nums.size();
        std::stack<int> stk;//sorted in incr order
        int res = 0;
        for (int i = 0; i < N; ++i)
        {
            while (!stk.empty() && nums[i] < nums[stk.top()])
                stk.pop();
            stk.push(i);
            std::cout << stk.size() << std::endl;
            res += stk.size();
        }
        std::cout << "CountSubArrWLeftmostNumLessEqualToAll UseStack for [" << Debug::ToStr1D<int>()(nums) << "]: " << res << std::endl;
        return res;
    }
    /*
    ex: [1,4,2,5,3,1]
    [1]: [1]
    [1,4]: [4],[1,4]
    [1,2]: [2],[1,4,2]
    [1,2,5]: [5],[2,5],[1,4,2,5]
    [1,2,3]: [3],[2,5,3],[1,4,2,5,3]
    [1,1]: [1],[1,4,2,5,3,1]
    */
};
/*
1
2
2
3
3
2
CountSubArrWLeftmostNumLessEqualToAll UseStack for [1, 4, 2, 5, 3, 1]: 13
 */
#endif
