#ifndef _MIN_NUM_OF_SUBARR_INCR_TO_FORM_TGT_ARR_H
#define _MIN_NUM_OF_SUBARR_INCR_TO_FORM_TGT_ARR_H
#include "Debug.h"
/*
Leetcode: Minimum Number of Increments on Subarrays to Form a Target Array
Given an array of positive integers target and an array initial of same size with all zeros.
Return the minimum number of operations to form a target array from initial if you are allowed to do the following operation:
Choose any subarray from initial and increment each value by one.
The answer is guaranteed to fit within the range of a 32-bit signed integer.
Example 1:
Input: target = [1,2,3,2,1]
Output: 3
Explanation: We need at least 3 operations to form the target array from the initial array.
[0,0,0,0,0] increment 1 from index 0 to 4 (inclusive).
[1,1,1,1,1] increment 1 from index 1 to 3 (inclusive).
[1,2,2,2,1] increment 1 at index 2.
[1,2,3,2,1] target array is formed.
 */
class MinNumOfSubarrIncrToFormTgtArr
{
public:
    int Count(std::vector<int> & target)
    {
        int res = target[0];
        for (int i = 1; i < target.size(); ++i)
            if (target[i] > target[i-1]) //need more target[i]-target[i-1] increments for target[i]
                res += target[i]-target[i-1];
        //else if (target[i] < target[i-1]): use target[i] for both, and target[i-1]-target[i] for target[i-1]
        //else: same increments

        return res;
    }
};
#endif
