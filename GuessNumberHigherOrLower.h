#ifndef GUESS_NUMBER_HIGHER_OR_LOWER_H
#define GUESS_NUMBER_HIGHER_OR_LOWER_H
#include <iostream>
#include <string>
#include "Debug.h"
/*
Leetcode: Guess Number Higher or Lower
We are playing the Guess Game. The game is as follows:
I pick a number from 1 to n. You have to guess which number I picked.
Every time you guess wrong, I'll tell you whether the number is higher or lower.
You call a pre-defined API guess(int num) which returns 3 possible results (-1, 1, or 0):
-1 : My number is lower
1 : My number is higher
0 : Congrats! You got it!
Example:
n = 10, I pick 6.
Return 6.

Leetcode: Guess Number Higher or Lower II
We are playing the Guess Game. The game is as follows:
I pick a number from 1 to n. You have to guess which number I picked.
Every time you guess wrong, I'll tell you whether the number I picked is higher or lower.
However, when you guess a particular number x, and you guess wrong, you pay $x. You win the game when you guess the number I picked.
Example:
n = 10, I pick 8.
First round:  You guess 5, I tell you that it's higher. You pay $5.
Second round: You guess 7, I tell you that it's higher. You pay $7.
Third round:  You guess 9, I tell you that it's lower. You pay $9.
Game over. 8 is the number I picked.
You end up paying $5 + $7 + $9 = $21.
Given a particular n >= 1, find out how much money you need to have to guarantee a win.
Hint:
1. The best strategy to play the game is to minimize the maximum loss you could possibly face.
Another strategy is to minimize the expected loss. Here, we are interested in the first scenario.
2. Take a small example (n = 3). What do you end up paying in the worst case?
3. Check out this article if you're still stuck.
4. The purely recursive implementation of minimax would be worthless for even a small n. You MUST use dynamic programming.
As a follow-up, how would you modify your code to solve the problem of minimizing the expected loss, instead of the worst-case loss?
*/
class GuessNumberHigherOrLower
{
public:
	GuessNumberHigherOrLower() {}
	~GuessNumberHigherOrLower() {}

	//I.
	int BinarySearch(int N)
	{
		int left = 1;
		int right = N;
		while (left <= right)
		{
			int mid = left + (right - left) / 2;
			if (guess(mid) <= 0)//too big or equal: go left
				right = mid - 1;
			else
				left = mid + 1;
		}
		//now left is lower bound

		std::cout << "GuessNumberHigherOrLower BinarySearch for \"" << N << "\": " << left << std::endl;
		return left;
	}

	int guess(int n)
	{
		if (n < 1)
			return 1;
		if (n > 1000)
			return -1;
		if (n == 777)
			return 0;
		else if (n < 777)
			return 1;
		else
			return -1;
	}

	//II. minmax
	int DP2D(int n)
	{
		std::vector<std::vector<int>> dp(n + 2, std::vector<int>(n + 1, 0));
		for (int len = 2; len <= n; ++len)//min cost for 1 entry in between [left,right] inclusive is 0, so len starts from 2
		{
			for (int left = 1; left + len - 1 <= n; ++left)
			{
				int right = left + len - 1;
				int minCost = INT_MAX;
				for (int mid = left; mid <= right; ++mid)
				{
					int cost = mid + std::max(dp[left][mid - 1], dp[mid + 1][right]);
					minCost = std::min(cost, minCost);
				}
				dp[left][right] = minCost;
			}
		}

		Debug::Print2D<int>()(dp, false);
		std::cout << "GuessNumberHigherOrLower MinCost DP2D for \"" << n << "\": " << dp[1][n] << std::endl;
		return dp[1][n];
	}

	int Recur(int n)
	{
		int res = recur(1, n);
		std::cout << "GuessNumberHigherOrLower MinCost Recur for \"" << n << "\": " << res << std::endl;
		return res;
	}
private:
	int recur(int left, int right)
	{
		if (left >= right) return 0;//min cost for 1 entry in between [left,right] inclusive is 0
		int minCost = INT_MAX;
		for (int mid = left; mid <= right; ++mid)
		{
			int cost = mid + std::max(recur(left, mid - 1), recur(mid + 1, right));
			minCost = std::min(minCost, cost);
		}
		return minCost;
	}
};
/*
GuessNumberHigherOrLower BinarySearch for "1000": 777
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 1, 2, 4, 6, 8, 10, 12, 14, 16
Row#2	= 0, 0, 0, 2, 3, 6, 8, 10, 12, 14, 16
Row#3	= 0, 0, 0, 0, 3, 4, 8, 10, 12, 14, 16
Row#4	= 0, 0, 0, 0, 0, 4, 5, 10, 12, 14, 16
Row#5	= 0, 0, 0, 0, 0, 0, 5, 6, 12, 14, 16
Row#6	= 0, 0, 0, 0, 0, 0, 0, 6, 7, 14, 16
Row#7	= 0, 0, 0, 0, 0, 0, 0, 0, 7, 8, 16
Row#8	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 9
Row#9	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9
Row#10	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#11	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

GuessNumberHigherOrLower MinCost DP2D for "10": 16
GuessNumberHigherOrLower MinCost Recur for "10": 16
[rY][cX]
Row#0	= 0, 0, 0, 0
Row#1	= 0, 0, 1, 2
Row#2	= 0, 0, 0, 2
Row#3	= 0, 0, 0, 0
Row#4	= 0, 0, 0, 0

GuessNumberHigherOrLower MinCost DP2D for "3": 2
GuessNumberHigherOrLower MinCost Recur for "3": 2
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 1, 2, 4, 6, 8, 10, 12, 14, 16, 18, 21, 24, 27, 30
Row#2	= 0, 0, 0, 2, 3, 6, 8, 10, 12, 14, 16, 18, 21, 24, 27, 30
Row#3	= 0, 0, 0, 0, 3, 4, 8, 10, 12, 14, 16, 18, 21, 24, 27, 30
Row#4	= 0, 0, 0, 0, 0, 4, 5, 10, 12, 14, 16, 18, 21, 24, 27, 30
Row#5	= 0, 0, 0, 0, 0, 0, 5, 6, 12, 14, 16, 18, 21, 24, 27, 30
Row#6	= 0, 0, 0, 0, 0, 0, 0, 6, 7, 14, 16, 18, 20, 24, 27, 30
Row#7	= 0, 0, 0, 0, 0, 0, 0, 0, 7, 8, 16, 18, 20, 22, 27, 30
Row#8	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 9, 18, 20, 22, 24, 30
Row#9	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 10, 20, 22, 24, 26
Row#10	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 11, 22, 24, 26
Row#11	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 12, 24, 26
Row#12	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 13, 26
Row#13	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 14
Row#14	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14
Row#15	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#16	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

GuessNumberHigherOrLower MinCost DP2D for "15": 30
GuessNumberHigherOrLower MinCost Recur for "15": 30
*/
#endif
