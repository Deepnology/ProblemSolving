#ifndef _SHORTEST_COMMON_SUPER_SEQ_H
#define _SHORTEST_COMMON_SUPER_SEQ_H
#include "Debug.h"
/*
Leetcode: Shortest Common Supersequence
Given two strings str1 and str2, return the shortest string that has both str1 and str2 as subsequences.
If multiple answers exist, you may return any of them.
(A string S is a subsequence of string T if deleting some number of characters from T (possibly 0, and the characters are chosen anywhere from T) results in the string S.)
Example 1:
Input: str1 = "abac", str2 = "cab"
Output: "cabac"
Explanation:
str1 = "abac" is a subsequence of "cabac" because we can delete the first "c".
str2 = "cab" is a subsequence of "cabac" because we can delete the last "ac".
The answer provided is the shortest such string that satisfies these properties.
Note:
1 <= str1.length, str2.length <= 1000
str1 and str2 consist of lowercase English letters.
 */
class ShortestCommonSuperSeq
{
public:
    std::string UseLCS(std::string X, std::string Y)
    {
        int N = X.size();
        int M = Y.size();
        std::vector<std::vector<std::string> > dp(N + 1, std::vector<std::string>(M + 1, ""));
        //dp[i][j]: LCS from X[0]~X[i-1] and Y[0]~[j-1]

        for (int i = 0; i <= N; ++i)
        {
            for (int j = 0; j <= M; ++j)
            {
                if (i == 0 || j == 0)//first row || first column
                    dp[i][j] = "";

                else if (X[i - 1] == Y[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + X[i - 1];
                } else
                    dp[i][j] = dp[i - 1][j].size() > dp[i][j - 1].size() ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
        std::cout << dp[N][M] << std::endl;
        std::string res;
        int i = 0;
        int j = 0;
        for (auto &c : dp[N][M])
        {
            while (i < N && X[i] != c)
                res += X[i++];
            while (j < M && Y[j] != c)
                res += Y[j++];
            res += c;
            ++i;
            ++j;
        }
        res = res + X.substr(i) + Y.substr(j);

        std::cout << "ShortestCommonSuperSeq UseLCS for " << X << ", " << Y << ": " << res << std::endl;
        return res;
    }
};
/*
befhi
ShortestCommonSuperSeq UseLCS for abcedfghi, bxefhki: abcxedfghki
 */
#endif
