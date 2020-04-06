#ifndef PATTERN_132_H
#define PATTERN_132_H
#include "Debug.h"
/*
Leetcode: 132 Pattern
Given a sequence of n integers a1, a2, ..., an, a 132 pattern is a subsequence ai, aj, ak such that i < j < k and ai < ak < aj.
Design an algorithm that takes a list of n numbers as input and checks whether there is a 132 pattern in the list.
Note: n will be less than 15,000.
Example 1:
Input: [1, 2, 3, 4]
Output: False
Explanation: There is no 132 pattern in the sequence.
Example 2:
Input: [3, 1, 4, 2]
Output: True
Explanation: There is a 132 pattern in the sequence: [1, 4, 2].
Example 3:
Input: [-1, 3, 2, 0]
Output: True
Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1, 3, 0] and [-1, 2, 0].
*/
class Pattern132
{
public:
	Pattern132() {}

	void SolveStack(const std::vector<int> & nums)
	{
		bool res1 = ForwardStack(nums);
		bool res2 = BackwardStack(nums);
		std::cout << "Pattern132 ForwardStack and BackwardStack for \"" << Debug::ToStr1D<int>()(nums) << "\": " << res1 << ", " << res2 << std::endl;
	}

	bool ForwardStack(const std::vector<int> & nums)
	{
		std::stack<std::pair<int, int>> stk;//prev [curNum,curMin] pairs where curMin sorted in decr order, exclude the current curMin
		//curNum1>curMin1,curMin1>=curNum2,curNum2>curMin2
		int curMin = INT_MAX;//keep tracks of cur min (will be updated in decr order)
		for (auto & i : nums)
		{
			if (i <= curMin)
			{
				curMin = i;
			}
			else//i is not a min number: look for prev [curNum,curMin] pair & see if curMin < i < curNum
			{
				while (!stk.empty() && stk.top().second < i)
				{
					if (stk.top().first > i) return true;
					stk.pop();
				}
				//now stk contains prev [curNum,curMin] pairs whose curMin are >= i sorted in decr order, and we have a even smaller curMin
				//push [curNum,curMin] pair as [prevNum,prevMin] pair for next i
				stk.push({ i,curMin });
			}
		}
		return false;
	}

	bool BackwardStack(const std::vector<int> & nums)
	{
		std::stack<int> stk;//sorted in decr order from right to left (bottom to top) that keeps track of [cur:curMax]
		int max2 = INT_MIN;//keeps track of curMax's (if available, which means there must at least 1 smaller num on the right of curMax) next smaller num on its right
		int N = nums.size();
		for (int i = N - 1; i >= 0; --i)
		{
			if (nums[i] < max2) return true;
			while (!stk.empty() && stk.top() < nums[i])
			{
				max2 = stk.top();//update max2 as curMax's next smaller num on its right (nums[i] might be the new curMax or not)
				stk.pop();
			}
			stk.push(nums[i]);
		}
		return false;
	}
};
/*
Pattern132 ForwardStack and BackwardStack for "8, 6, 5, 7, 3, 4, 2, 1, 0, 1, 3, 4, 5": 0, 0
*/
#endif
