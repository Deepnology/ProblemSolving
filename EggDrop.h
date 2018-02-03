#ifndef _EGG_DROP_H_
#define _EGG_DROP_H_
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/dynamic-programming-set-11-egg-dropping-puzzle/
http://www.cnblogs.com/AlgoWing/p/3491677.html
Cracking the coding interview

Given a building with 100 floors and 2 eggs. 
Assume the egg breaks if dropped at only floor X and higher floors.
Design a strategy to calculate the minimum trials required to find out floor X in the worst case.
(We want to guarantee the result minimum trials can find the floor X even in the worst case)

The perfect "load balance in the worst case" strategy is the sum of trails of egg1 and trails of egg2 should be always the same.

Suppose we drop 1st egg at floor X. If it breaks, then drop 2nd egg from floor 1 to at most floor X-1. This requires at most X-1 trials for 2nd egg.
If it doesn't break, then jump up another X-1 floors. If it breaks, then drop 2nd egg from floor X+1, X+2, ..., to at most floor X-1-1. This requires at most X-2 trials for 2nd egg.
If it doesn't break, then jump up another X-2 floors. If it breaks, then it requires at most X-3 trials for 2nd egg.
...
If it doesn't break, then jump up another 1 floor. Now we already have made (X-1)+(X-2)+...+1 trials, and it must reach or exceed 100 floors. If it breaks, then it requires at most 0 trials for 2nd egg. (This would be the worst case)

X + (X-1) + (X-2) + (X-3) + (X-4) + ... + 1  >=  100

X * (X+1) / 2  >=  100

X * (X+1) >= 100*2

X >= 13.651

So the first drop should be from floor 14, if egg survives we jump up 13 floors to floor 27, then jump up 12 floors to 39 ...
The minimum number of trials in the worst case would be 14.

DP2D: O(n*k^2) time, O(n*k) space


Elements of programming interview, DynamicProgramming: Determine the critical height
Given N eggs and a limit of D drops, we want to find out the maximum number of floors that you can test in the worst case.
Assume there exists a floor x such that the egg will break if it is dropped from any floor x or heigher but will remain intact if dropped from a floor below x.

O((N+1)*(D+1)) time, O((N+1)*(D+1)) space
*/
class EggDrop
{
public:
	EggDrop(){}
	~EggDrop(){}

	int MinTrialsWorstCase_Formula_2Eggs(int K)//K: floor number
	{
		int n = 1;
		while (n * (n+1) < K*2)
		{
			++n;
		}

		std::cout << "EggDrop MinTrialsWorstCase_Formula_2Eggs for \"" << K << "\" floors: " << n << std::endl;
		return n;
	}

public:
	int MinTrialsWorstCase_Recur(int N, int K)
	{
		int res = this->minTrialsRecur(N, K);
		std::cout << "EggDrop MinTrialsWorstCase_Recur for \"" << N << "\" eggs, \"" << K << "\" floors: " << res << std::endl;
		return res;
	}
private:
	int minTrialsRecur(int N, int K)//N: egg number, K: floor number
	{
		if (K == 1 || K == 0)
			return K;

		if (N == 1)
			return K;

		int min = INT_MAX;
		for (int flr = 1; flr <= K; ++flr)
		{
			int broken = this->minTrialsRecur(N - 1, flr - 1);
			int nonBroken = this->minTrialsRecur(N, K - flr);
			int count = std::max(broken, nonBroken);//choose the worst case
			if (count < min)
				min = count;
		}
		return min + 1;
	}
public:
	int MinTrialsWorstCase_DP2D_Recur(int N, int K)
	{
		std::vector<std::vector<int> > dp(N + 1, std::vector<int>(K + 1, -1));
		int res = this->minTrials_DP2D_Recur(N, K, dp);
		Debug::Print2D<int>()(dp, false);
		std::cout << "EggDrop MinTrialsWorstCase_DP2D_Recur for \"" << N << "\" eggs, \"" << K << "\" floors: " << res << std::endl;
		return res;
	}
private:
	int minTrials_DP2D_Recur(int N, int K, std::vector<std::vector<int> > & dp)//N: egg number, K: floor number
	{
		if (K == 1 || K == 0)
			return K;

		if (N == 1)
			return K;

		int min = INT_MAX;
		for (int flr = 1; flr <= K; ++flr)
		{
			int broken = dp[N - 1][flr - 1] == -1 ? dp[N - 1][flr - 1] = this->minTrialsRecur(N - 1, flr - 1) : dp[N - 1][flr - 1];
			int nonBroken = dp[N][K - flr] == -1 ? dp[N][K - flr] = this->minTrialsRecur(N, K - flr) : dp[N][K - flr];
			int count = std::max(broken, nonBroken);
			if (count < min)
				min = count;
		}
		return min + 1;
	}

public:
	int MinTrialsWorstCase_DP2D_Iterate(int N, int K)
	{
		std::vector<std::vector<int> > dp(N + 1, std::vector<int>(K + 1));//row is egg number, column is floor number	
		
		// We need one trial for one floor and 0 trials for 0 floors
		for (int egg = 1; egg <= N; ++egg)
		{
			dp[egg][1] = 1;
			dp[egg][0] = 0;
		}

		// We always need flr trials for one egg and flr floors
		for (int flr = 1; flr <= K; ++flr)
		{
			dp[1][flr] = flr;
		}

		// Fill rest of the entries in table using optimal substructure property
		for (int egg = 2; egg <= N; ++egg)
		{
			for (int flr = 2; flr <= K; ++flr)
			{
				dp[egg][flr] = INT_MAX;
				for (int x = 1; x <= flr; ++x)
				{
					int broken = dp[egg - 1][x - 1];
					int nonBroken = dp[egg][flr - x];
					int count = 1 + std::max(broken, nonBroken);
					if (count < dp[egg][flr])
						dp[egg][flr] = count;
				}
			}
		}

		Debug::Print2D<int>()(dp, false);
		std::cout << "EggDrop MinTrialsWorstCase_DP2D_Iterate for \"" << N << "\" eggs, \"" << K << "\" floors: " << dp[N][K] << std::endl;
		return dp[N][K];
	}


	int MaxFloorsWorstCase_DP2D_Recur(int N, int D)//N: egg number, D: number of drops
	{
		std::vector<std::vector<int> > dp(N + 1, std::vector<int>(D + 1, -1));
		int res = this->maxFloorsWorstCase_DP2D_Recur(N, D, dp);

		Debug::Print2D<int>()(dp, false);
		std::cout << "EggDrop MaxFloorsWorstCase_DP2D_Recur for \"" << N << "\" eggs, \"" << D << "\" drops: " << res << std::endl;
		return res;
	}
private:
	int maxFloorsWorstCase_DP2D_Recur(int N, int D, std::vector<std::vector<int> > & dp)
	{
		if (N == 0 || D == 0)
			return 0;
		if (N == 1)//one egg and D drops left, we can still test D floors in the worst case
			return D;

		if (dp[N][D] == -1)
		{
			dp[N][D] = this->maxFloorsWorstCase_DP2D_Recur(N, D - 1, dp) +
				this->maxFloorsWorstCase_DP2D_Recur(N - 1, D - 1, dp) + 1;
		}
		return dp[N][D];
	}
};
/*
EggDrop MinTrialsWorstCase_Formula_2Eggs for "100" floors: 14
EggDrop MinTrialsWorstCase_Recur for "2" eggs, "10" floors: 4
[rY][cX]
Row#0	= -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
Row#1	= 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1
Row#2	= 0, 1, 2, 2, 3, 3, 3, 4, 4, 4, -1

EggDrop MinTrialsWorstCase_DP2D_Recur for "2" eggs, "10" floors: 4
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#1	= 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
Row#2	= 0, 1, 2, 2, 3, 3, 3, 4, 4, 4, 4

EggDrop MinTrialsWorstCase_DP2D_Iterate for "2" eggs, "10" floors: 4
[rY][cX]
Row#0	= -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
Row#1	= -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
Row#2	= -1, 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 66, 78, 91, 105

EggDrop MaxFloorsWorstCase_DP2D_Recur for "2" eggs, "14" drops: 105
 */

#endif