#ifndef MATCHSTICKS_TO_SQUARE_H
#define MATCHSTICKS_TO_SQUARE_H
#include "Debug.h"
/*
Leetcode: Matchsticks to square
Remember the story of Little Match Girl? By now, you know exactly what matchsticks the little match girl has, please find out a way you can make one square by using up all those matchsticks.
You should not break any stick, but you can link them up, and each matchstick must be used exactly one time.
Your input will be several matchsticks the girl has, represented with their stick length.
Your output will either be true or false, to represent whether you could make one square using all the matchsticks the little match girl has.
Example 1:
Input: [1,1,2,2,2]
Output: true
Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.
Example 2:
Input: [3,3,3,3,4]
Output: false
Explanation: You cannot find a way to form a square with all the matchsticks.
Note:
The length sum of the given matchsticks is in the range of 0 to 10^9.
The length of the given matchstick array will not exceed 15.
*/
class MatchsticksToSquare
{
public:
	MatchsticksToSquare() {}

	bool CanMakeSquare(std::vector<int> && nums)
	{
		bool res = Recur(nums);
		std::cout << "MatchsticksToSquare CanMakeSquareRecur for \"" << Debug::ToStr1D<int>()(nums) << "\": " << res << std::endl;
		return res;
	}

	bool Recur(std::vector<int> & nums)
	{
		//a special case of partition an array into 2 equal sums
		if (nums.size() < 4) return false;
		int sum = std::accumulate(nums.begin(), nums.end(), 0);
		if (sum % 4 != 0) return false;
		int width = sum / 4;
		std::sort(nums.begin(), nums.end(), std::greater<int>());//sort in decr order accelerates the computation time !!!
		std::vector<int> sides(4, 0);
		return recur(nums, 0, sides, width);
	}
private:
	bool recur(const std::vector<int> & nums, int cur, std::vector<int> sides, int width)
	{
		int N = nums.size();
		if (cur == N)
		{
			for (int i = 0; i < 4; ++i)
			{
				if (sides[i] != width)
					return false;
			}
			return true;
		}

		//try add nums[cur] to 1 of 4 sides
		std::unordered_set<int> dupSides;
		for (int i = 0; i < 4; ++i)
		{
			if (nums[cur] + sides[i] <= width && dupSides.count(sides[i]) == 0)
			{
				sides[i] += nums[cur];
				if (recur(nums, cur + 1, sides, width)) return true;
				sides[i] -= nums[cur];
				dupSides.insert(sides[i]);//skip duplicated sides that were computed before and was invalid
			}
		}
		return false;
	}
};
/*
MatchsticksToSquare CanMakeSquareRecur for "2, 2, 2, 1, 1": 1
MatchsticksToSquare CanMakeSquareRecur for "4, 3, 3, 3, 3": 0
*/
#endif
