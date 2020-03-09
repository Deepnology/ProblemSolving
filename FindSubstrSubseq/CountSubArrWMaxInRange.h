#ifndef _COUNT_SUBARR_W_MAX_IN_RANGE_H
#define _COUNT_SUBARR_W_MAX_IN_RANGE_H
#include "Debug.h"
/*
Leetcode: Number of Subarrays with Bounded Maximum
We are given an array A of positive integers, and two positive integers L and R (L <= R).
Return the number of (contiguous, non-empty) subarrays such that the value of the maximum array element in that subarray is at least L and at most R.
Example :
Input:
A = [2, 1, 4, 3]
L = 2
R = 3
Output: 3
Explanation: There are three subarrays that meet the requirements: [2], [2, 1], [3].
 */
class CountSubArrWMaxInRange
{
public:
    int SlideWindow(const std::vector<int> & v, int L, int R)
    {
        int N = v.size();
        int left = 0;
        int right = 0;
        int res = 0;
        int count = 0;
        for (int i = 0; i < N; ++i)
        {
            if (v[i] >= L && v[i] <= R)//all subarrs ending at v[i] are valid
            {
                right = i;
                count = right-left+1;//record count of subarrs ending at v[right]
                res += count;
            }
            else if (v[i] < L)//all subarrs ending at v[right] are valid, can extend to v[i]
                res += count;
            else//v[i] > R: no subarrs ending at v[i] are valid
            {
                left = i+1;
                count = 0;
            }
        }
        std::cout << "CountSubArrWMaxInRange SlideWindow for [" << Debug::ToStr1D<int>()(v) << "], in [" << L << "," << R << "]: " << res << std::endl;
        return res;
    }
};
/*
CountSubArrWMaxInRange SlideWindow for [2, 1, 4, 3], in [2,3]: 3
 */
#endif
