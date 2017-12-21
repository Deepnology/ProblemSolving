#ifndef COUNT_THE_REPETITIONS_H
#define COUNT_THE_REPETITIONS_H
#include "Debug.h"
/*
Leetcode: Count the repetitions
Define S = [s,n] as the string S which consists of n connected strings s.
For example, ["abc", 3] ="abcabcabc".
On the other hand, we define that string s1 can be obtained from string s2 if we can remove some characters from s2 such that it becomes s1.
For example, ¡§abc¡¨ can be obtained from ¡§abdbec¡¨ based on our definition, but it can not be obtained from ¡§acbbe¡¨.
You are given two non-empty strings s1 and s2 (each at most 100 characters long) and two integers 0 <= n1 <= 106 and 1 <= n2 <= 106.
Now consider the strings S1 and S2, where S1=[s1,n1] and S2=[s2,n2].
Find the maximum integer M such that [S2,M] can be obtained from S1.
Example:
Input:
s1="acb", n1=4
s2="ab", n2=2
Return:
2

see also SentenceScreenFitting.h
*/
class CountTheRepetitions
{
public:
	CountTheRepetitions() {}

	int DP(std::string s1, int n1, std::string s2, int n2)
	{
		int N = s1.size();
		int M = s2.size();
		int i = 0;
		int j = 0;
		int count1 = 0;
		int count2 = 0;
		std::unordered_map<int, std::pair<int, int>> dp;//<begin idx in s2, <count of s2, end idx in s2>>
		while (count1 < n1)
		{
			if (dp.count(j) == 0)
			{
				int curBegin = j;
				int curCount = 0;
				while (i < N)
				{
					if (s1[i] == s2[j])
					{
						++j;
						if (j == M)
						{
							j = 0;
							++curCount;
						}
					}
					++i;
				}
				dp[curBegin] = { curCount, j };
				count2 += curCount;
				i = 0;
			}
			else
			{
				count2 += dp[j].first;
				j = dp[j].second;
				i = 0;
			}
			++count1;
		}

		std::cout << "CountTheRepetitions DP for \"[" << s1 << ", " << n1 << "]\", \"[" << s2 << ", " << n2 << "]\": " << (count2 / n2) << std::endl;
		return count2 / n2;
	}
};
/*
CountTheRepetitions DP for "[acb, 4]", "[ab, 2]": 2
*/
#endif
