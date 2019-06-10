#ifndef _MAX_SUM_2_NON_OVLP_SUBARRAYS_H
#define _MAX_SUM_2_NON_OVLP_SUBARRAYS_H
#include "Debug.h"
/*
Leetcode: Maximum Sum of Two Non-Overlapping Subarrays
Given an array A of non-negative integers, return the maximum sum of elements in two non-overlapping (contiguous) subarrays, which have lengths L and M.
For clarification, the L-length subarray could occur before or after the M-length subarray.)
Formally, return the largest V for which V = (A[i] + A[i+1] + ... + A[i+L-1]) + (A[j] + A[j+1] + ... + A[j+M-1]) and either:
0 <= i < i + L - 1 < j < j + M - 1 < A.length, or
0 <= j < j + M - 1 < i < i + L - 1 < A.length.
Example 1:
Input: A = [0,6,5,2,2,5,1,9,4], L = 1, M = 2
Output: 20
Explanation: One choice of subarrays is [9] with length 1, and [6,5] with length 2.
Example 2:
Input: A = [3,8,1,3,2,1,8,9,0], L = 3, M = 2
Output: 29
Explanation: One choice of subarrays is [3,8,1] with length 3, and [8,9] with length 2.
Example 3:
Input: A = [2,1,5,6,0,9,5,0,3,8], L = 4, M = 3
Output: 31
Explanation: One choice of subarrays is [5,6,0,9] with length 4, and [3,8] with length 3.
Note:
L >= 1
M >= 1
L + M <= A.length <= 1000
0 <= A[i] <= 1000
 */
class MaxSum2NonOvlpSubArrays
{
public:
    MaxSum2NonOvlpSubArrays(){}

    int DP_SlideWindow(std::vector<int> && A, int L, int M)
    {
        int res = std::max(MaxSumTwoDistinctSubArrSum(A, L, M), MaxSumTwoDistinctSubArrSum(A, M, L));
        std::cout << "MaxSum2NonOvlpSubArrays DP_SlideWindow for L=" << L << ", M=" << M << ", from [" << Debug::ToStr1D<int>()(A) << "]: " << res << std::endl;
        return res;
    }
private:
    int MaxSumTwoDistinctSubArrSum(std::vector<int> & v, int L, int M)
    {
        int N = v.size();
        std::vector<int> left(N, INT_MIN);//max subarr sum with size L from left
        int sum = 0;
        int maxSum = INT_MIN;
        for (int i = 0; i < N; ++i)
        {
            sum += v[i];
            int begin = i-L+1;
            if (begin>=0)
            {
                maxSum = std::max(maxSum, sum);
                left[i] = maxSum;
                sum -= v[begin];
            }
        }
        std::vector<int> right(N, INT_MIN);//max subarr sum with size M from right
        sum = 0;
        maxSum = INT_MIN;
        for (int i = N-1; i >= 0; --i)
        {
            sum += v[i];
            int begin = i+M-1;
            if (begin<N)
            {
                maxSum = std::max(maxSum, sum);
                right[i] = maxSum;
                sum -= v[begin];
            }
        }

        int res = INT_MIN;
        for (int i = L-1; i+M < N; ++i)
        {
            res = std::max(res, left[i]+right[i+1]);
        }
        return res;
    }
};
/*
MaxSum2NonOvlpSubArrays DP_SlideWindow for L=4, M=3, from [2, 1, 5, 6, 0, 9, 5, 0, 3, 8]: 31
 */
#endif
