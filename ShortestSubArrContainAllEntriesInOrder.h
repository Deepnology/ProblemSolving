/*HashTable*/
#ifndef SHORTEST_SUB_ARR_CONTAIN_ALL_ENTRIES_IN_ORDER_H
#define SHORTEST_SUB_ARR_CONTAIN_ALL_ENTRIES_IN_ORDER_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include "Debug.h"
/*
Elements of programming interview, HashTable: Find the smallest subarray that sequentially covering all values
Write a function that takes two integer-valued arrays A and Q and computes a minimum length subarray A[i:j] that sequentially covers Q.
Assume all elements in Q are distinct.

DistinceEntries: O(n) time, O(m) space, where n is the size of A, and m the size of Q

See also ShortestSubArrContainAllEntries.h, ShortestSubstrContainAllChars.h
*/
class ShortestSubArrContainAllEntriesInOrder
{
public:
	ShortestSubArrContainAllEntriesInOrder(){}
	~ShortestSubArrContainAllEntriesInOrder(){}

	std::pair<int, int> DistinctEntries(const std::vector<std::string> & v, const std::vector<std::string> & entries)
	{
		int N = v.size();
		int M = entries.size();
		std::unordered_map<std::string, int> wordMap;//first: entry, second: index in entries
		for (int i = 0; i < M; ++i)
		{
			wordMap[entries[i]] = i;
		}
		std::vector<int> latestIdx(M, -1);
		std::vector<int> curLenTill(M, INT_MAX);
		int minLen = INT_MAX;
		int minBegin = 0;
		int minEnd = 0;

		for (int i = 0; i < N; ++i)
		{
			auto itr = wordMap.find(v[i]);
			if (itr != wordMap.end())
			{
				int curWordIdx = itr->second;
				if (curWordIdx == 0)
				{
					curLenTill[0] = 1;
				}
				else if (curLenTill[curWordIdx - 1] != INT_MAX)//update curLenTill[curWordIdx] only when its preceding entry have been met
				{
					curLenTill[curWordIdx] = (i - latestIdx[curWordIdx - 1]) + curLenTill[curWordIdx - 1];
				}
				latestIdx[curWordIdx] = i;

				if (curWordIdx == M - 1 && curLenTill[M - 1] < minLen)//update minLen only when current word is the last entry in entries
				{
					minLen = curLenTill[M - 1];
					minBegin = i - curLenTill[M - 1] + 1;
					minEnd = i;
				}
			}
		}

		std::cout << Debug::ToStr1D<std::string, int>()(wordMap) << std::endl;
		std::string resStr = minLen == INT_MAX ? "N" : Debug::ToStr1D<std::string>()(v, minBegin, minEnd);
		std::cout << "ShortestSubArrContainAllEntriesInOrder DistinctEntries for \"" << Debug::ToStr1D<std::string>()(entries) << "\" in \"" << Debug::ToStr1D<std::string>()(v) << "\": " << minLen << " (" << resStr << ")" << std::endl;
		return{ minBegin, minEnd };
	}
};
/*
[B,0], [D,1]
ShortestSubArrContainAllEntriesInOrder DistinctEntries for "B, D" in "A, C, B, B, B, A, C, D, D, A, D, C, A, C, B": 4 (B, A, C, D)
*/

/*
Leetcode: Minimum Window Subsequence
Given strings S and T, find the minimum (contiguous) substring W of S, so that T is a subsequence of W.
If there is no such window in S that covers all characters in T, return the empty string "".
If there are multiple such minimum-length windows, return the one with the left-most starting index.
Example 1:
Input:
S = "abcdebdde", T = "bde"
Output: "bcde"
Explanation:
"bcde" is the answer because it occurs before "bdde" which has the same length.
"deb" is not a smaller window because the elements of T in the window must occur in order.
 */
class ShortestSubstrContainAllCharsInOrder
{
public:
    ShortestSubstrContainAllCharsInOrder(){}

    std::string DP1D(const std::string & S, const std::string & T)
    {
        //O(N) time, O(M) space
        std::unordered_map<char, std::vector<int>> toIdx;
        int M = T.size();
        for (int i = 0; i < M; ++i)
            toIdx[T[i]].push_back(i);


        std::vector<int> dp(M, -1);//dp[i]: idx in S of nearest T[0] till T[i]
        int N = S.size();
        int minLen = N+1;
        int begin = -1;
        for (int i = 0; i < N; ++i)
        {
            if (toIdx.count(S[i]))
            {
                //replace the nearest begin of cur char with the nearest begin of its prev char
                //from back to front such that for duplicated chars in T, it's just a right shift
                for (int j = toIdx[S[i]].size()-1; j >= 0; --j)
                {
                    int idx = toIdx[S[i]][j];
                    dp[idx] = (idx==0) ? i : dp[idx-1]; //if cur char is begin of T, record cur idx; otherwise, right shift (can be either -1 or non -1)
                    if (idx == M-1 && dp[idx] != -1 && i-dp[idx]+1 < minLen)
                    {
                        minLen = i-dp[idx]+1;
                        begin = dp[idx];
                    }
                }
            }
        }
        std::string res = (begin==-1) ? "" : S.substr(begin, minLen);

        std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
        std::cout << "ShortestSubstrContainAllCharsInOrder DP1D for \"" << S << "\", \"" << T << "\": " << res << std::endl;
        return res;
    }

    std::string DP2D(const std::string & S, const std::string & T)
    {
        //O(N*M) time, O(N*M) space
        int N = S.size();
        int M = T.size();
        std::vector<std::vector<int>> dp(N+1, std::vector<int>(M+1, 0));//dp[i][j]: min len for S[0:i-1] and T[0:j-1]

        for (int i = 0; i <= N; ++i)
            for (int j = 1; j <= M; ++j)
            {
                dp[i][j] = N+1;
                if (i)
                {
                    dp[i][j] = std::min(dp[i][j], 1 + dp[i-1][j]);
                    if (S[i-1] == T[j-1])
                        dp[i][j] = std::min(dp[i][j], 1 + dp[i-1][j-1]);
                }
            }

        int minLen = N+1;
        int minEnd = -1;
        for (int i = 0; i <= N; ++i)
        {
            //std::cout << dp[i][M] << std::endl;
            if (dp[i][M] < minLen)
            {
                minLen = dp[i][M];
                minEnd = i;//exclusive end index
            }
        }
        std::string res = (minEnd==-1) ? "" : S.substr(minEnd-minLen, minLen);

        Debug::Print2D<int>()(dp, false);
        std::cout << "ShortestSubstrContainAllCharsInOrder DP2D for \"" << S << "\", \"" << T << "\": " << res << std::endl;
        return res;
    }
};
/*
14, 4, 4
ShortestSubstrContainAllCharsInOrder DP1D for "acbbbacddadcacb", "bdd": bacdd
[rY][cX]
Row#0	= 0, 16, 16, 16
Row#1	= 0, 16, 16, 16
Row#2	= 0, 16, 16, 16
Row#3	= 0, 1, 16, 16
Row#4	= 0, 1, 16, 16
Row#5	= 0, 1, 16, 16
Row#6	= 0, 2, 16, 16
Row#7	= 0, 3, 16, 16
Row#8	= 0, 4, 4, 16
Row#9	= 0, 5, 5, 5
Row#10	= 0, 6, 6, 6
Row#11	= 0, 7, 7, 7
Row#12	= 0, 8, 8, 8
Row#13	= 0, 9, 9, 9
Row#14	= 0, 10, 10, 10
Row#15	= 0, 1, 11, 11

ShortestSubstrContainAllCharsInOrder DP2D for "acbbbacddadcacb", "bdd": bacdd
 */
#endif