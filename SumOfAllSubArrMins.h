#ifndef _SUM_OF_ALL_SUB_ARR_MINS_H
#define _SUM_OF_ALL_SUB_ARR_MINS_H
#include "Debug.h"
/*
Leetcode: Sum Of Subarray minimums
Given an array of integers A, find the sum of min(B), where B ranges over every (contiguous) subarray of A.
Since the answer may be large, return the answer modulo 10^9 + 7.
Example 1:
Input: [3,1,2,4]
Output: 17
Explanation: Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4].
Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.  Sum is 17.
 */
class SumOfAllSubArrMins
{
public:
    SumOfAllSubArrMins(){}
    ~SumOfAllSubArrMins(){}

    int UseMonotoneIncrStk(std::vector<int> && A)
    {
        int N = A.size();
        std::stack<int> stk;//sorted in incr order
        long res = 0;
        for (int i = 0; i <= N; ++i)
        {
            while (!stk.empty() && A[stk.top()] > (i==N ? 0 : A[i]))
            {
                int cur = stk.top();
                stk.pop();
                int pre = stk.empty() ? -1 : stk.top();
                res += A[cur] * (cur-pre) * (i-cur);
                res %= 1000000007;
            }
            stk.push(i);
        }
        std::cout << "SumOfAllSubArrMins UseMonotoneIncrStk for [" << Debug::ToStr1D<int>()(A) << "]: " << res << std::endl;
        return res;
    }
};
/*
SumOfAllSubArrMins UseMonotoneIncrStk for [3, 1, 2, 4]: 17
 */
#endif
