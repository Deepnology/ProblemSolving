#ifndef _MIN_NUM_OF_FUNC_CALL_TO_FORM_TGT_ARR_H
#define _MIN_NUM_OF_FUNC_CALL_TO_FORM_TGT_ARR_H
#include "Debug.h"
/*
Leetcode:
Operation1: increment 1 for one num
Operation2: multiply all nums by 2
Your task is to form an integer array nums from an initial array of zeros arr that is the same size as nums.
Return the minimum number of function calls to make nums from arr.
The answer is guaranteed to fit in a 32-bit signed integer.
Example 1:
Input: nums = [1,5]
Output: 5
Explanation: Increment by 1 (second element): [0, 0] to get [0, 1] (1 operation).
Double all the elements: [0, 1] -> [0, 2] -> [0, 4] (2 operations).
Increment by 1 (both elements)  [0, 4] -> [1, 4] -> [1, 5] (2 operations).
Total of operations: 1 + 2 + 2 = 5.
Example 2:
Input: nums = [2,2]
Output: 3
Explanation: Increment by 1 (both elements) [0, 0] -> [0, 1] -> [1, 1] (2 operations).
Double all the elements: [1, 1] -> [2, 2] (1 operation).
Total of operations: 2 + 1 = 3.
 */
class MinNumOfFuncCallToFormTgtArr
{
public:
    int Count(std::vector<int> & nums)
    {
        int N = nums.size();
        int totalBitCount = 0;//for op1: increment 1 for one num
        int maxPow2 = 0;//for op2: multiply all nums by 2
        for (int i = 0; i < N; ++i)
        {
            int cur = nums[i];
            int bitCount = 0;
            int pow2 = 0;
            while (cur)
            {
                bitCount += cur & 1;
                ++pow2;
                cur >>= 1;
            }
            totalBitCount += bitCount;
            maxPow2 = std::max(maxPow2, pow2-1);
        }
        return totalBitCount + maxPow2;
    }
};
#endif
