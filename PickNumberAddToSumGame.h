#ifndef PICK_NUMBER_ADD_TO_SUM_GAME_H
#define PICK_NUMBER_ADD_TO_SUM_GAME_H
#include "Debug.h"
/*
Leetcode: Can I Win
In the "100 game," two players take turns adding, to a running total, any integer from 1..10.
The player who first causes the running total to reach or exceed 100 wins.
What if we change the game so that players cannot re-use integers?
For example, two players might take turns drawing from a common pool of numbers of 1..15 without replacement until they reach a total >= 100.
Given an integer maxChoosableInteger and another integer desiredTotal, determine if the first player to move can force a win, assuming both players play optimally.
You can always assume that maxChoosableInteger will not be larger than 20 and desiredTotal will not be larger than 300.
Example
Input:
maxChoosableInteger = 10
desiredTotal = 11
Output:
false
Explanation:
No matter which integer the first player choose, the first player will lose.
The first player can choose an integer from 1 up to 10.
If the first player choose 1, the second player can only choose integers from 2 up to 10.
The second player will win by choosing 10 and get a total = 11, which is >= desiredTotal.
Same with other integers chosen by the first player, the second player will always win.
*/
class PickNumberAddToSumGame
{
public:
	PickNumberAddToSumGame() {}

	bool Recur(int maxChoosableInteger, int desiredTotal)
	{
		if (desiredTotal == 0) return true;
		int sum = maxChoosableInteger*(maxChoosableInteger + 1) / 2;
		if (sum < desiredTotal) return false;//check if sum of all integers >= desiredTotal
		if (sum == desiredTotal) return maxChoosableInteger & 1;//when all integer must be used, odd nums will guarantee first player win
		int state = 0;
		bool res = recur(state, maxChoosableInteger, 0, desiredTotal);
		std::cout << "PickNumberAddToSumGame Can1stPlayerWin Recur for pick from \"1..." << maxChoosableInteger << "\", sum to \"" << desiredTotal << "\": " << res << std::endl;
		return res;
	}
private:
	bool recur(int state, int maxInt, int curSum, int total)//O(n!)
	{
		if (curSum >= total) return false;//cur player loose
		for (int i = 0; i < maxInt; ++i)
		{
			int mask = (1 << i);
			if (state & mask)//cur num (i+1) was used
				continue;
			state |= mask;
			if (!recur(state, maxInt, curSum + (i + 1), total)) return true;//if next player loose, I win
			state ^= mask;
		}
		return false;//I loose
	}
public:
	bool RecurDP(int maxChoosableInteger, int desiredTotal)
	{
		if (desiredTotal == 0) return true;
		int sum = maxChoosableInteger*(maxChoosableInteger + 1) / 2;
		if (sum < desiredTotal) return false;//check if sum of all integers >= desiredTotal
		if (sum == desiredTotal) return maxChoosableInteger & 1;//when all integer must be used, odd nums will guarantee first player win
		int state = 0;
		std::unordered_map<int, bool> dp;
		bool res = recurDP(state, maxChoosableInteger, 0, desiredTotal, dp);
		std::cout << "PickNumberAddToSumGame Can1stPlayerWin RecurDP for pick from \"1..." << maxChoosableInteger << "\", sum to \"" << desiredTotal << "\": " << res << std::endl;
		return res;
	}
private:
	bool recurDP(int state, int maxInt, int curSum, int total, std::unordered_map<int, bool> & dp)//O(2^n)
	{
		if (dp.count(state)) return dp[state];
		if (curSum >= total) return false;
		for (int i = 0; i < maxInt; ++i)
		{
			int mask = (1 << i);
			if (state & mask)//cur num (i+1) was used
				continue;
			state |= mask;
			if (!recurDP(state, maxInt, curSum + (i + 1), total, dp)) return dp[state ^= mask] = true;
			state ^= mask;
		}
		return dp[state] = false;
	}
};
/*
PickNumberAddToSumGame Can1stPlayerWin Recur for pick from "1...10", sum to "11": 0
PickNumberAddToSumGame Can1stPlayerWin RecurDP for pick from "1...10", sum to "11": 0
*/
#endif
