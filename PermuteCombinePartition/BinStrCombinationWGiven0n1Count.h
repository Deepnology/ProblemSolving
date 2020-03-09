#ifndef BIN_STR_COMBINATION_W_GIVEN_0N1_COUNT_H
#define BIN_STR_COMBINATION_W_GIVEN_0N1_COUNT_H
#include "Debug.h"
/*
Leetcode: Ones and Zeros
In the computer world, use restricted resource you have to generate maximum benefit is what we always want to pursue.
For now, suppose you are a dominator of m 0s and n 1s respectively.
On the other hand, there is an array with strings consisting of only 0s and 1s.
Now your task is to find the maximum number of strings that you can form with given m 0s and n 1s.
Each 0 and 1 can be used at most once.
Note:
The given numbers of 0s and 1s will both not exceed 100
The size of given string array won't exceed 600.
Example 1:
Input: Array = {"10", "0001", "111001", "1", "0"}, m = 5, n = 3
Output: 4
Explanation: This are totally 4 strings can be formed by the using of 5 0s and 3 1s, which are ��10,��0001��,��1��,��0��
Example 2:
Input: Array = {"10", "0", "1"}, m = 1, n = 1
Output: 2
Explanation: You could form "10", but then you'd have nothing left. Better form "0" and "1".
*/
class BinStrCombinationWGiven0n1Count
{
public:
	BinStrCombinationWGiven0n1Count() {}

	int InExcludeRecur(const std::vector<std::string> & strs, int m, int n)
	{
		int maxCount = 0;
		recur(strs, 0, 0, m, n, maxCount);
		std::cout << "BinStrCombinationWGiven0n1Count InExcludeRecur for \"" << Debug::ToStr1D<std::string>()(strs) << "\", (0,1) count = (" << m << ", " << n << "): " << maxCount << std::endl;
		return maxCount;
	}
	void recur(const std::vector<std::string> & v, int begin, int count, int curM, int curN, int & maxCount)//DFS include/exclude
	{
		int N = v.size();
		if (curM < 0 || curN < 0) return;
		if (begin == N)
		{
			maxCount = std::max(maxCount, count);
			return;
		}

		//include v[begin]
		int numZero = 0;
		int numOne = 0;
		for (const auto c : v[begin])
			if (c == '0') ++numZero;
			else if (c == '1') ++numOne;
		recur(v, begin + 1, count + 1, curM - numZero, curN - numOne, maxCount);

		//exclude v[begin]
		recur(v, begin + 1, count, curM, curN, maxCount);
	}

	int DP3D(const std::vector<std::string> & strs, int m, int n)
	{
		int N = strs.size();
		std::vector<std::vector<std::vector<int>>> dp(N + 1, std::vector<std::vector<int>>(m + 1, std::vector<int>(n + 1, 0)));
		for (int i = 1; i <= N; ++i)
		{
			int numZero = 0;
			int numOne = 0;
			for (const auto c : strs[i - 1])
				if (c == '0') ++numZero;
				else if (c == '1') ++numOne;

			for (int j = 0; j <= m; ++j)
			{
				for (int k = 0; k <= n; ++k)
				{
					if (j >= numZero && k >= numOne)
						dp[i][j][k] = std::max(dp[i - 1][j][k], 1 + dp[i - 1][j - numZero][k - numOne]);
					else
						dp[i][j][k] = dp[i - 1][j][k];
				}
			}
		}
		Debug::Print3D<int>()(dp, false);
		std::cout << "BinStrCombinationWGiven0n1Count DP3D for \"" << Debug::ToStr1D<std::string>()(strs) << "\", (0,1) count = (" << m << ", " << n << "): " << dp[N][m][n] << std::endl;
		return dp[N][m][n];
	}

	int DP2D(const std::vector<std::string> & strs, int m, int n)
	{
		int N = strs.size();
		std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
		for (int i = 0; i < N; ++i)
		{
			int numZero = 0;
			int numOne = 0;
			for (const auto c : strs[i])
				if (c == '0') ++numZero;
				else if (c == '1') ++numOne;

			for (int j = m; j >= numZero; --j)//decrementing
			{
				for (int k = n; k >= numOne; --k)//decrementing
				{
					dp[j][k] = std::max(dp[j][k], 1 + dp[j - numZero][k - numOne]);
				}
			}
		}
		Debug::Print2D<int>()(dp, false);
		std::cout << "BinStrCombinationWGiven0n1Count DP2D for \"" << Debug::ToStr1D<std::string>()(strs) << "\", (0,1) count = (" << m << ", " << n << "): " << dp[m][n] << std::endl;
		return dp[m][n];
	}
};
/*
BinStrCombinationWGiven0n1Count InExcludeRecur for "10, 0001, 111001, 1, 0", (0,1) count = (5, 3): 4
[rY][cX][dZ]
Row#0	= 0,0,0,0.	0,0,0,0.	0,0,0,0.	0,0,0,0.	0,0,0,0.	0,0,0,0.
Row#1	= 0,0,0,0.	0,1,1,1.	0,1,1,1.	0,1,1,1.	0,1,1,1.	0,1,1,1.
Row#2	= 0,0,0,0.	0,1,1,1.	0,1,1,1.	0,1,1,1.	0,1,2,2.	0,1,2,2.
Row#3	= 0,0,0,0.	0,1,1,1.	0,1,1,1.	0,1,1,1.	0,1,2,2.	0,1,2,2.
Row#4	= 0,1,1,1.	0,1,2,2.	0,1,2,2.	0,1,2,2.	0,1,2,3.	0,1,2,3.
Row#5	= 0,1,1,1.	1,2,2,2.	1,2,3,3.	1,2,3,3.	1,2,3,3.	1,2,3,4.

BinStrCombinationWGiven0n1Count DP3D for "10, 0001, 111001, 1, 0", (0,1) count = (5, 3): 4
[rY][cX]
Row#0	= 0, 1, 1, 1
Row#1	= 1, 2, 2, 2
Row#2	= 1, 2, 3, 3
Row#3	= 1, 2, 3, 3
Row#4	= 1, 2, 3, 3
Row#5	= 1, 2, 3, 4

BinStrCombinationWGiven0n1Count DP2D for "10, 0001, 111001, 1, 0", (0,1) count = (5, 3): 4
BinStrCombinationWGiven0n1Count InExcludeRecur for "10, 0, 1", (0,1) count = (1, 1): 2
[rY][cX][dZ]
Row#0	= 0,0.	0,0.
Row#1	= 0,0.	0,1.
Row#2	= 0,0.	1,1.
Row#3	= 0,1.	1,2.

BinStrCombinationWGiven0n1Count DP3D for "10, 0, 1", (0,1) count = (1, 1): 2
[rY][cX]
Row#0	= 0, 1
Row#1	= 1, 2

BinStrCombinationWGiven0n1Count DP2D for "10, 0, 1", (0,1) count = (1, 1): 2
*/
#endif
