#ifndef _MONOTONIC_ARRAY_H
#define _MONOTONIC_ARRAY_H
#include "Debug.h"
/*
Leetcode: Monotonic Array
An array is monotonic if it is either monotone increasing or monotone decreasing.
An array A is monotone increasing if for all i <= j, A[i] <= A[j].
An array A is monotone decreasing if for all i <= j, A[i] >= A[j].
Return true if and only if the given array A is monotonic.
Example 1:
Input: [1,2,2,3]
Output: true
Example 2:
Input: [6,5,4,4]
Output: true
Example 3:
Input: [1,3,2]
Output: false
Example 4:
Input: [1,2,4,5]
Output: true
Example 5:
Input: [1,1,1]
Output: true
 */
class MonotonicArray
{
public:
    MonotonicArray(){}
    ~MonotonicArray(){}

    bool Valid(std::vector<int> && A)
    {
        int N = A.size();
        bool incr = true;
        bool decr = true;
        for (int i = 0; i < N-1; ++i)
        {
            incr &= (A[i] <= A[i+1]);
            decr &= (A[i] >= A[i+1]);
        }
        int res = incr || decr;
        std::cout << "MonotonicArray Valid for [" << Debug::ToStr1D<int>()(A) << "]: " << res << std::endl;
        return res;
    }
};
/*
MonotonicArray Valid for [1, 2, 2, 3]: 1
 */
#endif
