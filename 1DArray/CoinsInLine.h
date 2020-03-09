#ifndef COINS_IN_LINE_H
#define COINS_IN_LINE_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Predict the Winner (determine if 1st player can win: return maxAmountOf1stPlayer >= (totalSum-maxAmountOf1stPlayer))
Elements of programming interview, DynamicProgramming: Pick up coins for maximum gain
Design an efficient algorithm for computing the maximum margin of victory for the starting player in the pick-up-coins game.
Google
http://www.careercup.com/question?id=15422849
http://leetcode.com/2011/02/coins-in-line.html
http://www.quora.com/Dynamic-Programming-DP/How-do-you-solve-the-pots-of-gold-game
http://www.geeksforgeeks.org/dynamic-programming-set-31-optimal-strategy-for-a-game/
There are n coins in a line. (Assume n is even). 
Two players, A and B, take turns to take a coin from one of the ends of the line until there are no more coins left. 
The player with the larger amount of money wins.

1. Would you rather go first or second? Does it matter?
2. Assume that you go first, describe an algorithm to compute the maximum amount of money you can win.

1.
Going first will guarantee that you will not lose. By following the strategy below, you will always win the game (or get a possible tie).

Count the sum of all coins that are odd-numbered. (Call this X)
Count the sum of all coins that are even-numbered. (Call this Y)
If X > Y, take the left-most coin first. Choose all odd-numbered coins in subsequent moves.
If X < Y, take the right-most coin first. Choose all even-numbered coins in subsequent moves.
If X == Y, you will guarantee to get a tie if you stick with taking only even-numbered/odd-numbered coins.

Hints:
One misconception is to think that the above non-losing strategy would generate the maximum amount of money as well. 
This is probably incorrect. Could you find a counter example? (You might need at least 6 coins to find a counter example).
{ 3, 2, 2, 3, 1, 2 }
Following our previous non-losing strategy, we would count the sum of odd-numbered coins, X = 3 + 2 + 1 = 6
, and the sum of even-numbered coins, Y = 2 + 3 + 2 = 7. As Y > X
, we would take the last coin first and end up winning with the total amount of 7 by taking only even-numbered coins.

However, let us try another way by taking the first coin (valued at 3, denote by (3)) instead. 
The opponent is left with two possible choices, the left coin (2) and the right coin (2), both valued at 2. 
No matter which coin the opponent chose, you can always take the other coin (2) next and the configuration of the coins becomes: { 2, 3, 1 }.
Now, the coin in the middle (3) would be yours to keep for sure. 
Therefore, you win the game by a total amount of 3 + 2 + 3 = 8, which proves that the previous non-losing strategy is not necessarily optimal.

2.
DFS Recur: O(n!) time
DFS RecurDP: O(2^n) time
DP2D: O(n^2) time, O(n^2) space

See also MinRemovalOfEndInArrayUntil.h
*/
class CoinsInLine
{
public:
	CoinsInLine(){}
	~CoinsInLine(){}

	int MaxVal_Recur(const std::vector<int> & coins)
	{
		int N = coins.size();
		int res = maxValRecur(coins, 0, N - 1);
		std::cout << "CoinsInLine Recur for \"" << Debug::ToStr1D<int>()(coins) << "\": " << res << std::endl;
		return res;
	}
private:
	int maxValRecur(const std::vector<int> & coins, int left, int right)
	{
		if (left > right)
			return 0;
		int maxValPickFront = coins[left] + 
			std::min(this->maxValRecur(coins, left + 2, right),//when B picks front
			this->maxValRecur(coins, left + 1, right - 1));//when B picks back

		int maxValPickBack = coins[right] +
			std::min(this->maxValRecur(coins, left + 1, right - 1),//when B picks front
			this->maxValRecur(coins, left, right - 2));//when B picks back

		return std::max(maxValPickFront, maxValPickBack);
	}

public:
	int MaxVal_DP2D_Recur(const std::vector<int> & coins)
	{
		int N = coins.size();
		std::vector<std::vector<int> > dp(N, std::vector<int>(N, -1));
		int res = maxValDP2DRecur(coins, 0, N - 1, dp);
		Debug::Print2D<int>()(dp, false);
		std::cout << "CoinsInLine DP2D Recur for \"" << Debug::ToStr1D<int>()(coins) << "\": " << res << std::endl;
		return res;
	}
private:
	int maxValDP2DRecur(const std::vector<int> & coins, int left, int right, std::vector<std::vector<int> > & dp)
	{
		if (left > right)
			return 0;
		
		if (dp[left][right] != -1)
			return dp[left][right];

		int maxValPickFront = coins[left] +
			std::min(this->maxValDP2DRecur(coins, left + 2, right, dp),//when B picks front
			this->maxValDP2DRecur(coins, left + 1, right - 1, dp));//when B picks back

		int maxValPickBack = coins[right] +
			std::min(this->maxValDP2DRecur(coins, left + 1, right - 1, dp),//when B picks front
			this->maxValDP2DRecur(coins, left, right - 2, dp));//when B picks back

		return dp[left][right] = std::max(maxValPickFront, maxValPickBack);
	}

public:
	int MaxVal_DP2D_Iterate(const std::vector<int> & coins)
	{
		int N = coins.size();
		std::vector<std::vector<int> > dp(N, std::vector<int>(N, 0));
		//dp[left][right]: max val to pick one from either front or back of coins[left]~coins[right]
		for (int len = 0; len < N; ++len)
		{
			for (int left = 0, right = len; right < N; ++left, ++right)//diagonal upper left to bottom right
			{
				//max val after A picks front and B picks front
				int maxValFrontFront = (left + 2 <= N - 1) ? dp[left + 2][right] : 0;//2 elements below
				//max val after A picks front and B picks back
				int maxValFrontBack = (left + 1 <= N - 1 && right - 1 >= 0) ? dp[left + 1][right - 1] : 0;//1 element below and 1 element left
				//max val after A picks back and B picks front
				int maxValBackFront = (left + 1 <= N - 1 && right - 1 >= 0) ? dp[left + 1][right - 1] : 0;//1 element below and 1 element left
				//max val after A picks back and B picks back
				int maxValBackBack = (right - 2 >= 0) ? dp[left][right - 2] : 0;//2 elements left

				dp[left][right] = std::max(
					coins[left] + std::min(maxValFrontFront, maxValFrontBack),
					coins[right] + std::min(maxValBackFront, maxValBackBack));
			}
		}
		Debug::Print2D<int>()(dp, false);
		//this->PrintMovesDP2D(dp, coins);
		int res = dp[0][N - 1];
		std::cout << "CoinsInLine DP2D Iterate for \"" << Debug::ToStr1D<int>()(coins) << "\": " << res << std::endl;
		return res;
	}

private:
	void PrintMovesDP2D(const std::vector<std::vector<int> > & dp, const std::vector<int> & coins)
	{
		int N = coins.size();
		bool myTurn = true;
		int left = 0;
		int right = N - 1;
		while (left <= right)
		{
			int p1 = dp[left + 1][right];
			int p2 = dp[left][right - 1];
			std::cout << (myTurn ? "I" : "You") << " take coin no. ";
			if (p1 <= p2)
			{
				std::cout << left + 1 << " (" << coins[left] << ")";
				++left;
			}
			else
			{
				std::cout << right + 1 << " (" << coins[right] << ")";
				--right;
			}
			std::cout << (myTurn ? ", " : ".\n");
			myTurn = !myTurn;
		}
		std::cout << std::endl << "The total amount of money (maximum) I get is " << dp[0][N - 1] << "." << std::endl;
	}
};
/*
CoinsInLine Recur for "3, 2, 2, 3, 1, 2": 8
[rY][cX]
Row#0	= -1, 3, -1, 5, -1, 8
Row#1	= -1, -1, 2, -1, 5, -1
Row#2	= -1, -1, -1, 3, -1, 5
Row#3	= -1, -1, -1, -1, 3, -1
Row#4	= -1, -1, -1, -1, -1, 2
Row#5	= -1, -1, -1, -1, -1, -1

CoinsInLine DP2D Recur for "3, 2, 2, 3, 1, 2": 8
[rY][cX]
Row#0	= 3, 3, 5, 5, 6, 8
Row#1	= 0, 2, 2, 5, 5, 5
Row#2	= 0, 0, 2, 3, 3, 5
Row#3	= 0, 0, 0, 3, 3, 4
Row#4	= 0, 0, 0, 0, 1, 2
Row#5	= 0, 0, 0, 0, 0, 2

CoinsInLine DP2D Iterate for "3, 2, 2, 3, 1, 2": 8
*/
/*
Leetcode: Stone Game
Alex and Lee play a game with piles of stones.
There are an even number of piles arranged in a row, and each pile has a positive integer number of stones piles[i].
The objective of the game is to end with the most stones.
The total number of stones is odd, so there are no ties.
Alex and Lee take turns, with Alex starting first.
Each turn, a player takes the entire pile of stones from either the beginning or the end of the row.
This continues until there are no more piles left, at which point the person with the most stones wins.
Assuming Alex and Lee play optimally, return True if and only if Alex wins the game.
Example 1:
Input: [5,3,4,5]
Output: true
Explanation:
Alex starts first, and can only take the first 5 or the last 5.
Say he takes the first 5, so that the row becomes [3, 4, 5].
If Lee takes 3, then the board is [4, 5], and Alex takes 5 to win with 10 points.
If Lee takes the last 5, then the board is [3, 4], and Alex takes 4 to win with 9 points.
This demonstrated that taking the first 5 was a winning move for Alex, so we return true.
 */
class StoneGame
{
public:
    StoneGame(){}

    bool Can1stHandWin_DP2DRecur(std::vector<int> && piles)
    {
        int N = piles.size();
        int sum = 0;
        for (auto & p : piles)
            sum += p;
        std::vector<std::vector<int>> dp(N, std::vector<int>(N, -1));
        int alex = maxValDP2DRecur(piles, 0, N-1, dp);
        int lee = sum - alex;
        return alex > lee;
    }
    int maxValDP2DRecur(const std::vector<int> & coins, int left, int right, std::vector<std::vector<int> > & dp)
    {
        if (left > right)
            return 0;

        if (dp[left][right] != -1)
            return dp[left][right];

        int maxValPickFront = coins[left] +
                              std::min(this->maxValDP2DRecur(coins, left + 2, right, dp),//when B picks front
                                       this->maxValDP2DRecur(coins, left + 1, right - 1, dp));//when B picks back

        int maxValPickBack = coins[right] +
                             std::min(this->maxValDP2DRecur(coins, left + 1, right - 1, dp),//when B picks front
                                      this->maxValDP2DRecur(coins, left, right - 2, dp));//when B picks back

        return dp[left][right] = std::max(maxValPickFront, maxValPickBack);
    }
};
#endif