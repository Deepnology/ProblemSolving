#ifndef _LBSUBARR_H
#define _LBSUBARR_H
#include "Debug.h"
/*
Leetcode: Longest Mountain in Array
Let's call any (contiguous) subarray B (of A) a mountain if the following properties hold:
B.length >= 3
There exists some 0 < i < B.length - 1 such that B[0] < B[1] < ... B[i-1] < B[i] > B[i+1] > ... > B[B.length - 1]
(Note that B could be any subarray of A, including the entire array A.)
Given an array A of integers, return the length of the longest mountain.
Return 0 if there is no mountain.
Example 1:
Input: [2,1,4,7,3,2,5]
Output: 5
Explanation: The largest mountain is [1,4,7,3,2] which has length 5.
Example 2:
Input: [2,2,2]
Output: 0
Explanation: There is no mountain.

Leetcode: Valid Mountain Array
Given an array A of integers, return true if and only if it is a valid mountain array.
Recall that A is a mountain array if and only if:
A.length >= 3
There exists some i with 0 < i < A.length - 1 such that:
A[0] < A[1] < ... A[i-1] < A[i]
A[i] > A[i+1] > ... > A[B.length - 1]
Example 1:
Input: [2,1]
Output: false
Example 2:
Input: [3,5,5]
Output: false
Example 3:
Input: [0,3,2,1]
Output: true
 */
class LBSubArr
{
public:
    LBSubArr(){}
    ~LBSubArr(){}

    int BruteForce(std::vector<int> && A)
    {
        int N = A.size();
        if (N < 3) return 0;
        int res = 0;
        for (int i = 1; i < N-1; ++i)
        {
            if (A[i-1] < A[i] && A[i] > A[i+1])
            {
                int left = i-1;
                while (left >= 0 && A[left] < A[left+1])
                    --left;
                int right = i+1;
                while (right < N && A[right-1] > A[right])
                    ++right;
                res = std::max(res, right-left-1);//exclude both left and right
            }
        }
        std::cout << "LBSubArr BruteForce for [" << Debug::ToStr1D<int>()(A) << "]: " << res << std::endl;
        return res;
    }

    int DP(std::vector<int> && A)
    {
        int N = A.size();
        if (N < 3) return 0;
        int res = 0;
        std::vector<int> incr(N, 0);//incr[i]: len of incr subarr from left ending at i
        std::vector<int> decr(N, 0);//decr[i]: len of decr subarr from right ending at i
        for (int i = 0; i < N; ++i)
            if (i > 0 && A[i-1] < A[i])
                incr[i] = incr[i-1] + 1;
        for (int i = N-1; i >= 0; --i)
            if (i < N-1 && A[i] > A[i+1])
                decr[i] = decr[i+1] + 1;
        for (int i = 0; i < N; ++i)
            if (incr[i] > 0 && decr[i] > 0)
                res = std::max(res, incr[i]+decr[i]+1);

        std::cout << "LBSubArr DP for [" << Debug::ToStr1D<int>()(A) << "]: " << res << std::endl;
        return res;
    }

    int OnePass(std::vector<int> && A)
    {
        int N = A.size();
        if (N < 3) return 0;
        int res = 0;
        int incr = 0;
        int decr = 0;
        for (int i = 1; i < N; ++i)
        {
            if (decr && A[i-1] < A[i] || A[i-1] == A[i])//reset at end of mountain
                incr = decr = 0;
            incr += A[i-1] < A[i];
            decr += A[i-1] > A[i];
            if (incr && decr)
                res = std::max(res, incr + decr + 1);
        }

        std::cout << "LBSubArr OnePass for [" << Debug::ToStr1D<int>()(A) << "]: " << res << std::endl;
        return res;
    }

    bool ValidBitonicArray(std::vector<int> && A)
    {
        int incr = 0;
        int decr = 0;
        int N = A.size();
        if (N < 3) return false;
        int i = 1;
        while (i < N && A[i-1] < A[i])
        {
            ++incr;
            ++i;
        }
        if (incr == 0) return false;
        while (i < N && A[i-1] > A[i])
        {
            ++decr;
            ++i;
        }
        if (decr == 0) return false;
        return i == N;
    }
};
/*
LBSubArr BruteForce for [2, 1, 4, 7, 3, 2, 5]: 5
LBSubArr DP for [2, 1, 4, 7, 3, 2, 5]: 5
LBSubArr OnePass for [2, 1, 4, 7, 3, 2, 5]: 5
 */
#endif
