#ifndef _LONGEST_ALTERNATING_SUB_ARR_H
#define _LONGEST_ALTERNATING_SUB_ARR_H
#include "Debug.h"
/*
Leetcode: Longest turbulent subarray
A subarray A[i], A[i+1], ..., A[j] of A is said to be turbulent if and only if:
For i <= k < j, A[k] > A[k+1] when k is odd, and A[k] < A[k+1] when k is even;
OR, for i <= k < j, A[k] > A[k+1] when k is even, and A[k] < A[k+1] when k is odd.
That is, the subarray is turbulent if the comparison sign flips between each adjacent pair of elements in the subarray.
Return the length of a maximum size turbulent subarray of A.
Example 1:
Input: [9,4,2,10,7,8,8,1,9]
Output: 5
Explanation: (A[1] > A[2] < A[3] > A[4] < A[5])
Example 2:
Input: [4,8,12,16]
Output: 2
Example 3:
Input: [100]
Output: 1
 */
class LongestAlternatingSubArr
{
public:
    LongestAlternatingSubArr(){}
    ~LongestAlternatingSubArr(){}

    int Find(std::vector<int> && A)
    {
        int N = A.size();
        std::vector<int> incr;//alternating subarray ending with a incr(A[i-1]<A[i])
        std::vector<int> decr;//alternating subarray ending with a decr(A[i-1]>A[i])
        std::vector<int> res;
        incr.push_back(A[0]);
        decr.push_back(A[0]);
        res.push_back(A[0]);
        for (int i = 1; i < N; ++i)
        {
            if (A[i-1] > A[i])
            {
                decr = incr;
                decr.push_back(A[i]);
                incr.clear();
                incr.push_back(A[i]);
            }
            else if (A[i-1] < A[i])
            {
                incr = decr;
                incr.push_back(A[i]);
                decr.clear();
                decr.push_back(A[i]);
            }
            else
            {
                incr.clear(); incr.push_back(A[i]);
                decr.clear(); decr.push_back(A[i]);
            }
            if (incr.size() > res.size() || decr.size() > res.size())
                res = incr.size() > decr.size() ? incr : decr;
        }

        std::cout << "LongestAlternatingSubArr for [" << Debug::ToStr1D<int>()(A) << "]: " << Debug::ToStr1D<int>()(res) << std::endl;
        return res.size();
    }

    int Solve(std::vector<int> && A)
    {
        int N = A.size();
        int incr = 1;//len of alternating subarray ending with a incr(A[i-1]<A[i])
        int decr = 1;//len of alternating subarray ending with a decr(A[i-1]>A[i])
        int res = 1;
        for (int i = 1; i < N; ++i)
        {
            if (A[i-1] > A[i])
            {
                decr = incr + 1;
                incr = 1;
            }
            else if (A[i-1] < A[i])
            {
                incr = decr + 1;
                decr = 1;
            }
            else
            {
                incr = 1;
                decr = 1;
            }
            res = std::max(res, std::max(incr, decr));
        }

        std::cout << "LongestAlternatingSubArr for [" << Debug::ToStr1D<int>()(A) << "]: " << res << std::endl;
        return res;
    }
};
/*
LongestAlternatingSubArr for [9, 4, 2, 10, 7, 8, 8, 1, 9]: 4, 2, 10, 7, 8
LongestAlternatingSubArr for [9, 4, 2, 10, 7, 8, 8, 1, 9]: 5
 */
#endif
