#ifndef MAX_SUM_PARENTHESIZE_ARITHMETIC_EXPR_H
#define MAX_SUM_PARENTHESIZE_ARITHMETIC_EXPR_H
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
http://stackoverflow.com/questions/3781962/building-an-expression-with-maximum-value
Given an array of N integers, and an array of (N-1) operations in set (+,-,*).
The two arrays form a mathematical expression of arithmetics.
Use parentheses to find the maximum sum of the mathematical expression.

DP2D: O(n^3) time, O(n^2) space

See also MatrixChainMultiplication.h, MaxVerticesSumOfPolygon.h
*/
class MaxSumParenthesizeArithmeticExpr
{
public:
	MaxSumParenthesizeArithmeticExpr(){}
	~MaxSumParenthesizeArithmeticExpr(){}

	int DP2D(const std::vector<int> & v, const std::vector<int> & op)
	{
		int N = v.size();
		std::vector<std::vector<std::pair<int, int> > > dp(N, std::vector<std::pair<int, int> >(N, std::make_pair(0, 0)));
		/*
		dp[i][j].first: max in the range v[i]~v[j] inclusive
		dp[i][j].second: min in the range v[i]~v[j] inclusive
		*/

		/*init with number itself when start/end is the same*/
		for (int i = 0; i < N; ++i)
		{
			dp[i][i].first = v[i];
			dp[i][i].second = v[i];
		}

		for (int len = 2; len <= N; ++len)
		{
			for (int first = 0; first < N - len + 1; ++first)
			{
				int last = first + len - 1;
				dp[first][last].first = INT_MIN;
				dp[first][last].second = INT_MAX;
				for (int mid = first; mid < last; ++mid)
				{
					/*T: *, P: +, S: -*/
					int maxTmax = dp[first][mid].first * dp[mid + 1][last].first;
					int maxTmin = dp[first][mid].first * dp[mid + 1][last].second;
					int minTmax = dp[first][mid].second * dp[mid + 1][last].first;
					int minTmin = dp[first][mid].second * dp[mid + 1][last].second;

					int maxPmax = dp[first][mid].first + dp[mid + 1][last].first;
					int maxSmin1 = dp[first][mid].first - dp[mid + 1][last].second;
					int maxSmin2 = 0 - dp[first][mid].second + dp[mid + 1][last].first;
					
					int minPmin = dp[first][mid].second + dp[mid + 1][last].second;
					int minSmax1 = dp[first][mid].second - dp[mid + 1][last].first;
					int minSmax2 = 0 - dp[first][mid].first + dp[mid + 1][last].second;

					int max = INT_MIN;
					int min = INT_MAX;
					if (op[mid] == 0)//+
					{
						max = maxPmax;
						min = minPmin;
					}
					else if (op[mid] == 1)//*
					{
						max = this->max(maxTmax, maxTmin, minTmax, minTmin);
						min = this->min(maxTmax, maxTmin, minTmax, minTmin);
					}
					else if (op[mid] == 2)//-
					{
						max = std::max(maxSmin1, maxSmin2);
						min = std::min(minSmax1, minSmax2);
					}

					if (max > dp[first][last].first)
						dp[first][last].first = max;
					if (min < dp[first][last].second)
						dp[first][last].second = min;
				}
			}
		}
		Debug::Print2D<int>()(dp, false);
		std::cout << "MaxSumParenthesizeArithmeticExpr DP2D for [" << Debug::ToStr1D<int>()(v) << "], [" << Debug::ToStr1D<int>()(op) << "]: " << dp[0][N - 1].first << ", MinSum: " << dp[0][N - 1].second << std::endl;
		return dp[0][N - 1].first;
	}

private:
	int min(int a, int b, int c, int d)
	{
		return std::min(a,
			std::min(b,
			std::min(c, d)));
	}
	int max(int a, int b, int c, int d)
	{
		return std::max(a,
			std::max(b,
			std::max(c, d)));
	}
};
/*
[rY][cX]
Row#0	= [-8,-8], [-32,-32], [-64,-64], [-61,-160], [320,-70], [1600,-350]
Row#1	= [0,0], [4,4], [8,8], [20,11], [2,-40], [10,-200]
Row#2	= [0,0], [0,0], [2,2], [5,5], [-4,-10], [-20,-50]
Row#3	= [0,0], [0,0], [0,0], [3,3], [-6,-6], [-30,-30]
Row#4	= [0,0], [0,0], [0,0], [0,0], [-2,-2], [-10,-10]
Row#5	= [0,0], [0,0], [0,0], [0,0], [0,0], [5,5]

MaxSumParenthesizeArithmeticExpr DP2D for "-8, 4, 2, 3, -2, 5", "1, 1, 0, 1, 1": 1600, MinSum: -350
[rY][cX]
Row#0	= [-8,-8], [-16,-16], [8,-19], [104,-95]
Row#1	= [0,0], [2,2], [-1,-1], [-5,-13]
Row#2	= [0,0], [0,0], [-3,-3], [-15,-15]
Row#3	= [0,0], [0,0], [0,0], [5,5]

MaxSumParenthesizeArithmeticExpr DP2D for "-8, 2, -3, 5", "1, 0, 1": 104, MinSum: -95
*/
#endif