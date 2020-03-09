#ifndef _COUNT_ALL_PALINDROME_SUBSEQ_H
#define _COUNT_ALL_PALINDROME_SUBSEQ_H
#include "Debug.h"
/*
Leetcode: Count Different Palindrome Subsequences
Given a string S, find the number of different non-empty palindromic subsequences in S, and return that number modulo 10^9 + 7.
A subsequence of a string S is obtained by deleting 0 or more characters from S.
A sequence is palindromic if it is equal to the sequence reversed.
Two sequences A_1, A_2, ... and B_1, B_2, ... are different if there is some i for which A_i != B_i.
Example 1:
Input:
S = 'bccb'
Output: 6
Explanation:
The 6 different non-empty palindromic subsequences are 'b', 'c', 'bb', 'cc', 'bcb', 'bccb'.
Note that 'bcb' is counted only once, even though it occurs twice.
Example 2:
Input:
S = 'abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba'
Output: 104860361
Explanation:
There are 3104860382 different non-empty palindromic subsequences, which is 104860361 modulo 10^9 + 7.
Note:
The length of S will be in the range [1, 1000].
Each character S[i] will be in the set {'a', 'b', 'c', 'd'}.
 */
class CountAllPalindromeSubseq
{
public:
    CountAllPalindromeSubseq(){}

    int DP2D(const std::string & S)
    {
        int N = S.size();
        std::vector<std::vector<int>> dp(N, std::vector<int>(N, 0));

        for (int len = 1; len <= N; ++len)
        {
            for (int begin = 0; begin < N-len+1; ++begin)
            {
                int end = begin+len-1;
                if (len == 1)
                {
                    dp[begin][end] = 1;
                }
                    //note: len==2 are included in the following cases
                else if (S[begin] == S[end])
                {
                    int left = begin+1;
                    int right = end-1;
                    while (left <= right && S[left] != S[begin])
                        ++left;
                    while (left <= right && S[right] != S[end])
                        --right;
                    //now S[left] == S[begin] == S[right] == S[end]
                    if (left < right)
                    {
                        //ex: aacaa, dp[0][4]=dp[1][3]*2-dp[2][2]
                        //dp[1][3]: a, c, aa, aca
                        //dp[1][3]*2: a, c, aa, aca, aaa, aca, aaaa, aacaa
                        //dp[2][2]: c
                        dp[begin][end] = dp[begin+1][end-1] * 2 - dp[left+1][right-1];
                    }
                    else if (left == right)
                    {
                        //ex: aaa, dp[0][2]=dp[1][1]*2+1
                        //dp[1][1]: a
                        //dp[1][1]*2: a, aaa
                        //1: aa
                        dp[begin][end] = dp[begin+1][end-1] * 2 + 1;
                    }
                    else//left > right
                    {
                        //ex: aba, dp[0][2]=dp[1][1]*2+2
                        //dp[1][1]: b
                        //dp[1][1]*2: b, aba
                        //2: a, aa
                        dp[begin][end] = dp[begin+1][end-1] * 2 + 2;
                    }
                }
                else//S[begin] != S[end]
                    dp[begin][end] = dp[begin+1][end] + dp[begin][end-1] - dp[begin+1][end-1];

                dp[begin][end] = dp[begin][end] < 0 ? dp[begin][end] + 1000000007 : dp[begin][end] % 1000000007;
            }
        }

        Debug::Print2D<int>()(dp, false);
        std::cout << "CountAllPalindromeSubseq DP2D for \"" << S << "\": " << dp[0][N-1] << std::endl;
        return dp[0][N-1];
    }
};
/*
[rY][cX]
Row#0	= 1, 2, 3, 6
Row#1	= 0, 1, 2, 3
Row#2	= 0, 0, 1, 2
Row#3	= 0, 0, 0, 1

CountAllPalindromeSubseq DP2D for "bccb": 6
[rY][cX]
Row#0	= 1, 2, 4, 5, 8
Row#1	= 0, 1, 2, 3, 6
Row#2	= 0, 0, 1, 2, 3
Row#3	= 0, 0, 0, 1, 2
Row#4	= 0, 0, 0, 0, 1

CountAllPalindromeSubseq DP2D for "abaab": 8
[rY][cX]
Row#0	= 1, 2, 4, 5, 8, 12
Row#1	= 0, 1, 2, 3, 6, 8
Row#2	= 0, 0, 1, 2, 3, 5
Row#3	= 0, 0, 0, 1, 2, 4
Row#4	= 0, 0, 0, 0, 1, 2
Row#5	= 0, 0, 0, 0, 0, 1

CountAllPalindromeSubseq DP2D for "abaaba": 12
[rY][cX]
Row#0	= 1, 2, 3, 6, 7, 9, 11
Row#1	= 0, 1, 2, 3, 4, 6, 8
Row#2	= 0, 0, 1, 2, 3, 5, 7
Row#3	= 0, 0, 0, 1, 2, 4, 6
Row#4	= 0, 0, 0, 0, 1, 2, 4
Row#5	= 0, 0, 0, 0, 0, 1, 2
Row#6	= 0, 0, 0, 0, 0, 0, 1

CountAllPalindromeSubseq DP2D for "abbaeae": 11
 */
#endif
