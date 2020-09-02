#ifndef PAINT_HOUSE_COMBINATIONS_H
#define PAINT_HOUSE_COMBINATIONS_H
#include <iostream>
#include <string>
#include <vector>
#include "Debug.h"
/*
Leetcode: Paint House
There are a row of n houses, each house can be painted with one of the three colors: red, blue or green.
The cost of painting each house with a certain color is different.
You have to paint all the houses such that no two adjacent houses have the same color.
The cost of painting each house with a certain color is represented by a n x 3 cost matrix.
For example, costs[0][0] is the cost of painting house 0 with color red; costs[1][2] is the cost of painting house 1 with color green, and so on...
Find the minimum cost to paint all houses.
Note:
All costs are positive integers.

Leetcode: Paint House II
There are a row of n houses, each house can be painted with one of the k colors.
The cost of painting each house with a certain color is different.
You have to paint all the houses such that no two adjacent houses have the same color.
The cost of painting each house with a certain color is represented by a n x k cost matrix.
For example, costs[0][0] is the cost of painting house 0 with color 0; costs[1][2] is the cost of painting house 1 with color 2, and so on...
Find the minimum cost to paint all houses.
Note:
All costs are positive integers.
Follow up:
Could you solve it in O(nk) runtime?
*/
class PaintHouseCombinations
{
public:
	PaintHouseCombinations() {}
	~PaintHouseCombinations() {}

	int DP2D_3Color(const std::vector<std::vector<int>> & cost)
	{
		int N = cost.size();
		if (N == 0) return 0;

		std::vector<std::vector<int>> dp(N, std::vector<int>(3, 0));
		dp[0][0] = cost[0][0];//R
		dp[0][1] = cost[0][1];//G
		dp[0][2] = cost[0][2];//B

		for (int i = 1; i < N; ++i)
		{
			dp[i][0] = cost[i][0] + std::min(dp[i - 1][1], dp[i - 1][2]);
			dp[i][1] = cost[i][1] + std::min(dp[i - 1][0], dp[i - 1][2]);
			dp[i][2] = cost[i][2] + std::min(dp[i - 1][0], dp[i - 1][1]);
		}

		int res = std::min(dp[N - 1][0], std::min(dp[N - 1][1], dp[N - 1][2]));

		Debug::Print2D<int>()(cost, false);
		std::cout << "PaintHouseCombinations DP2D_3Color for the above costs: " << res << std::endl;
		return res;
	}

	//O(n*k^2) time, O(n*k) space
	int DP2D_KColor(const std::vector<std::vector<int>> & cost)
	{
		int N = cost.size();
		if (N == 0) return 0;
		int K = cost[0].size();
		if (K == 0) return 0;

		std::vector<std::vector<int>> dp(N, std::vector<int>(K, 0));
		for (int j = 0; j < K; ++j)
			dp[0][j] = cost[0][j];

		for (int i = 1; i < N; ++i)
		{
			for (int j = 0; j < K; ++j)
			{
				dp[i][j] = INT_MAX;
				for (int jj = 0; jj < K; ++jj)
				{
					if (jj != j)//avoid same colors with prev house
						dp[i][j] = std::min(dp[i - 1][jj] + cost[i][j], dp[i][j]);
				}
			}
		}

		int res = INT_MAX;
		for (int j = 0; j < K; ++j)
			res = std::min(res, dp[N - 1][j]);

		Debug::Print2D<int>()(cost, false);
		std::cout << "PaintHouseCombinations DP2D_KColor for the above costs and \"K=" << K << "\": " << res << std::endl;
		return res;
	}

	//O(n*k^2) time, O(k) space
	int DP1D_KColor(const std::vector<std::vector<int>> & cost)
	{
		int N = cost.size();
		if (N == 0) return 0;
		int K = cost[0].size();
		if (K == 0) return 0;

		std::vector<int> dpPrev(K, 0);
		std::vector<int> dpCur(K, 0);
		for (int j = 0; j < K; ++j)
			dpPrev[j] = cost[0][j];

		for (int i = 1; i < N; ++i)
		{
			for (int j = 0; j < K; ++j)
			{
				dpCur[j] = INT_MAX;
				for (int jj = 0; jj < K; ++jj)
				{
					if (jj != j)
						dpCur[j] = std::min(dpPrev[jj] + cost[i][j], dpCur[j]);
				}
			}

			for (int j = 0; j < K; ++j)
				dpPrev[j] = dpCur[j];
		}

		int res = INT_MAX;
		for (int j = 0; j < K; ++j)
			res = std::min(res, dpPrev[j]);

		Debug::Print2D<int>()(cost, false);
		std::cout << "PaintHouseCombinations DP1D_KColor for the above costs and \"K=" << K << "\": " << res << std::endl;
		return res;
	}

	//O(n*k) time
	int BestTime_KColor(const std::vector<std::vector<int>> & cost)
	{
		int N = cost.size();
		if (N == 0) return 0;
		int K = cost[0].size();
		if (K == 0) return 0;

		int prevMin = 0;//min cost till prev house
		int prevSec = 0;//second min cost till prev house
		int prevMinIdx = -1;//the color used to paint prev house with min cost
		for (int i = 0; i < N; ++i)
		{
			int curMin = INT_MAX;
			int curSec = INT_MAX;
			int curMinIdx = -1;
			for (int j = 0; j < K; ++j)//compute cost of painting current house for using colors from 0 to K-1
			{
				int curCost = cost[i][j] + (prevMinIdx == j ? prevSec : prevMin);//for the case of same colors with prev house, use prevSec (prev second min)
				if (curCost < curMin)
				{
					curSec = curMin;
					curMin = curCost;
					curMinIdx = j;
				}
				else if (curCost < curSec)
					curSec = curCost;
			}
			prevMin = curMin;
			prevSec = curSec;
			prevMinIdx = curMinIdx;
		}

		Debug::Print2D<int>()(cost, false);
		std::cout << "PaintHouseCombinations BestTime_KColor for the above costs and \"K=" << K << "\": " << prevMin << std::endl;
		return prevMin;
	}
};
/*
[rY][cX]
Row#0	= 5, 8, 6
Row#1	= 19, 14, 13
Row#2	= 7, 5, 12
Row#3	= 14, 15, 17
Row#4	= 3, 20, 10

PaintHouseCombinations DP2D_3Color for the above costs: 43
[rY][cX]
Row#0	= 5, 8, 6
Row#1	= 19, 14, 13
Row#2	= 7, 5, 12
Row#3	= 14, 15, 17
Row#4	= 3, 20, 10

PaintHouseCombinations DP2D_KColor for the above costs and "K=3": 43
[rY][cX]
Row#0	= 5, 8, 6
Row#1	= 19, 14, 13
Row#2	= 7, 5, 12
Row#3	= 14, 15, 17
Row#4	= 3, 20, 10

PaintHouseCombinations DP1D_KColor for the above costs and "K=3": 43
[rY][cX]
Row#0	= 5, 8, 6
Row#1	= 19, 14, 13
Row#2	= 7, 5, 12
Row#3	= 14, 15, 17
Row#4	= 3, 20, 10

PaintHouseCombinations BestTime_KColor for the above costs and "K=3": 43
*/
#endif
