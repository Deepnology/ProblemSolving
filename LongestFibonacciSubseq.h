#ifndef _LONGEST_FIBONACCI_SUBSEQ_H
#define _LONGEST_FIBONACCI_SUBSEQ_H
#include "Debug.h"
/*
Leetcode: Length of longest Fibonacci Subsequence
A sequence X_1, X_2, ..., X_n is fibonacci-like if:
n >= 3
X_i + X_{i+1} = X_{i+2} for all i + 2 <= n
Given a strictly increasing array A of positive integers forming a sequence, find the length of the longest fibonacci-like subsequence of A.
If one does not exist, return 0.
(Recall that a subsequence is derived from another sequence A by deleting any number of elements (including none) from A, without changing the order of the remaining elements.
For example, [3, 5, 8] is a subsequence of [3, 4, 5, 6, 7, 8].)
Example 1:
Input: [1,2,3,4,5,6,7,8]
Output: 5
Explanation:
The longest subsequence that is fibonacci-like: [1,2,3,5,8].
Example 2:
Input: [1,3,7,11,12,14,18]
Output: 3
Explanation:
The longest subsequence that is fibonacci-like:
[1,11,12], [3,11,14] or [7,11,18].

see also PartitionIntoFibonacciSeq.h
 */
class LongestFibonacciSubseq
{
public:
    LongestFibonacciSubseq(){}
    ~LongestFibonacciSubseq(){}

    int BruteForce(std::vector<int> && A)
    {
        //brute force: O(N^2logM) time, where M=max(A)
        int N = A.size();
        std::unordered_set<int> nums(A.begin(), A.end());
        int res = 0;
        //enumerate all initial pairs
        for (int i = 0; i < N-1; ++i)
            for (int j = i + 1; j < N; ++j)
            {
                int num1 = A[i];
                int num2 = A[j];
                int len = 2;
                while (nums.count(num1+num2))
                {
                    ++len;
                    int tmp = num1;
                    num1 = num2;
                    num2 += tmp;
                }
                res = std::max(res, len);
            }

        res = res > 2 ? res : 0;

        std::cout << "LongestFibonacciSubseq BruteForce for [" << Debug::ToStr1D<int>()(A) << "]: " << res << std::endl;
        return res;
    }

    int DP(std::vector<int> && A)
    {
        //DP: O(N^2) time
        int N = A.size();
        std::unordered_map<int,int> numToIdx;
        for (int i = 0; i < N; ++i)
            numToIdx[A[i]] = i;
        std::vector<std::vector<int>> dp(N, std::vector<int>(N, 2));
        //dp[i][j]: len of longest F subseq ending at A[i] and A[j]
        //similar to LIS
        std::vector<int> preIdx(N,0);
        int maxIdx = 0;
        int res = 0;
        for (int end = 1; end < N; ++end)
        {
            for (int start = 0; start < end; ++start)
            {
                int preNum = A[end] - A[start];
                if (numToIdx.count(preNum) && numToIdx[preNum] < start)
                {
                    dp[start][end] = std::max(dp[start][end], dp[numToIdx[preNum]][start]+1);
                    if (res < dp[start][end])
                    {
                        res = dp[start][end];
                        maxIdx = end;
                        preIdx[end] = start;
                    }
                }
            }
        }

        std::vector<int> resSubseq(res);
        int len = res;
        while (len-- > 0)
        {
            resSubseq[len] = A[maxIdx];
            maxIdx = preIdx[maxIdx];
        }
        std::ostringstream oss;
        for (auto & n : resSubseq)
            oss << n << ",";
        std::cout << oss.str() << std::endl;

        std::cout << "LongestFibonacciSubseq DP for [" << Debug::ToStr1D<int>()(A) << "]: " << res << std::endl;
        return res;

    }
};
/*
LongestFibonacciSubseq BruteForce for [1, 2, 3, 4, 5, 6, 7, 8]: 5
1,2,3,5,8,
LongestFibonacciSubseq DP for [1, 2, 3, 4, 5, 6, 7, 8]: 5
 */
#endif
