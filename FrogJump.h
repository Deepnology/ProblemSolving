#ifndef FROG_JUMP_H
#define FROG_JUMP_H
#include "Debug.h"
/*
Leetcode: Frog Jump
A frog is crossing a river.
The river is divided into x units and at each unit there may or may not exist a stone.
The frog can jump on a stone, but it must not jump into the water.
Given a list of stones' positions (in units) in sorted ascending order, determine if the frog is able to cross the river by landing on the last stone.
Initially, the frog is on the first stone and assume the first jump must be 1 unit.
If the frog's last jump was k units, then its next jump must be either k - 1, k, or k + 1 units.
Note that the frog can only jump in the forward direction.

Note:
The number of stones is >= 2 and is < 1,100.
Each stone's position will be a non-negative integer < 2^31.
The first stone's position is always 0.

Example 1:
[0,1,3,5,6,8,12,17]
There are a total of 8 stones.
The first stone at the 0th unit, second stone at the 1st unit,
third stone at the 3rd unit, and so on...
The last stone at the 17th unit.
Return true. The frog can jump to the last stone by jumping
1 unit to the 2nd stone, then 2 units to the 3rd stone, then
2 units to the 4th stone, then 3 units to the 6th stone,
4 units to the 7th stone, and 5 units to the 8th stone.
Example 2:
[0,1,2,3,4,8,9,11]
Return false. There is no way to jump to the last stone as
the gap between the 5th and 6th stone is too large.
*/
class FrogJump
{
public:
	FrogJump() {}

	bool DP(std::vector<int> & stones)
	{
		int N = stones.size();
		std::vector<std::unordered_set<int>> dp(N, std::unordered_set<int>());
		dp[0].insert(1);//first jump dist must be 1
		for (int i = 1; i < N; ++i)
		{
			//an less efficient approach to check all the values in [0:begin]
			for (int j = 0; j < i; ++j)
			{
				int diff = stones[i] - stones[j];
				if (dp[j].count(diff))
				{
					dp[i].insert(diff);
					if (diff - 1 > 0)
						dp[i].insert(diff - 1);
					if (diff + 1 <= stones[N - 1] - stones[i])
						dp[i].insert(diff + 1);
				}
			}
		}
		std::cout << "FrogJump DP for \"" << Debug::ToStr1D<int>()(stones) << "\": " << (dp[N-1].size() > 0) << std::endl;
		return dp[N - 1].size() > 0;
	}

	bool Recur(std::vector<int> & stones)
	{
		int N = stones.size();
		std::vector<std::unordered_map<int, bool>> dp(N, std::unordered_map<int, bool>());
		bool res = recur(stones, 0, 0, dp);
		std::cout << "FrogJump Recur for \"" << Debug::ToStr1D<int>()(stones) << "\": " << res << std::endl;
		return res;
	}
private:
	bool recur(std::vector<int> & stones, int begin, int diff, std::vector<std::unordered_map<int, bool>> & dp)
	{

		int N = stones.size();
		if (begin == N - 1) return true;
		if (dp[begin].count(diff)) return dp[begin][diff];

		//only need to check the range: stones[begin]+diff-1 <= vales <= stones[begin]+diff+1
		auto lb1 = std::lower_bound(stones.begin() + begin + 1, stones.end(), (stones[begin] + diff - 1));
		auto lb2 = std::lower_bound(stones.begin() + begin + 1, stones.end(), (stones[begin] + diff + 2));
		for (auto itr = lb1; itr != lb2; ++itr)
		{
			int nxtDiff = *itr - stones[begin];
			if (recur(stones, itr - stones.begin(), nxtDiff, dp)) return dp[begin][diff] = true;
		}
		/*
		//an less enfficient approach to check all the range after begin
		for (int i = begin + 1; i < N; ++i)
		{
			int nxtDiff = stones[i] - stones[begin];
			if (nxtDiff > diff + 1) return false;//remember stones is sorted, the remaining nxtDiff will always be greater than diff+1
			if (nxtDiff < diff - 1) continue;//skip this smaller one
			if (recur(stones, i, nxtDiff, dp)) return dp[begin][diff] = true;
		}
		*/
		return dp[begin][diff] = false;
	}
};
/*
FrogJump DP for "0, 1, 3, 5, 6, 8, 12, 17": 1
FrogJump Recur for "0, 1, 3, 5, 6, 8, 12, 17": 1
FrogJump DP for "0, 1, 2, 3, 4, 8, 9, 11": 0
FrogJump Recur for "0, 1, 2, 3, 4, 8, 9, 11": 0
*/
#endif
