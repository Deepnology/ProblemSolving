#ifndef	DISTINCT_SUBSEQUENCES_2_H
#define DISTINCT_SUBSEQUENCES_2_H
#include "Debug.h"
/*
http://www.geeksforgeeks.org/count-distinct-subsequences/
Count number of distinct subsequences of a given string.

len==1: non,a
len==2: non,a,b,ab
len==3: non,a,b,c,ab,ac,bc,abc
len==4: non,a,b,c,d,ab,ac,ad,bc,bd,cd,abc,abd,acd,bcd,abcd

non a b c d
1   2 4 8 16

dp[i]=2*dp[i-1]-repetition
*/
class DistinctSubsequences2
{
public:
	DistinctSubsequences2() {}
	~DistinctSubsequences2() {}

	int CountDP1D(const std::string & s)
	{
		int N = s.size();
		std::vector<int> dp(N + 1, 0);
		dp[0] = 1;
		std::vector<int> lastIdx(256, -1);
		for (int i = 1; i <= N; ++i)
		{
			dp[i] = 2 * dp[i - 1];
			if (lastIdx[s[i - 1]] != -1)
				dp[i] -= dp[lastIdx[s[i - 1]]];
			lastIdx[s[i - 1]] = i - 1;
		}

		std::cout << "DistinctSubsequences2 DP1D for \"" << s << "\": " << dp[N] << std::endl;
		return dp[N];
	}
};
/*
DistinctSubsequences2 DP1D for "abc": 8
DistinctSubsequences2 DP1D for "abcd": 16
DistinctSubsequences2 DP1D for "abad": 14
DistinctSubsequences2 DP1D for "gfg": 7
DistinctSubsequences2 DP1D for "ggg": 4
*/
#endif
