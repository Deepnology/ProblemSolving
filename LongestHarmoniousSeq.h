#ifndef LONGEST_HARMONIOUS_SEQ_H
#define LONGEST_HARMONIOUS_SEQ_H
#include "Debug.h"
/*
Leetcode: Longest Harmonious Subsequence
We define a harmonious array is an array where the difference between its maximum value and its minimum value is exactly 1.
Now, given an integer array, you need to find the length of its longest harmonious subsequence among all its possible subsequences.
Example 1:
Input: [1,3,2,2,5,2,3,7]
Output: 5
Explanation: The longest harmonious subsequence is [3,2,2,2,3].
*/
class LongestHarmoniousSeq
{
public:
	LongestHarmoniousSeq() {}

	int FindLenOfLongestHarSeq(std::vector<int> & nums)
	{
		//since only need to find LENGTH of longest harmonious subseq, order doesn't matter
		std::map<int, int> count;//<key,count> where key is sorted
		for (auto & i : nums)
			++count[i];

		int prevNum = 0;//prev key in sorted order
		int prevCount = 0;//count of prev key
		int maxCount = 0;//max count of consecutive 2 keys whose diff is 1
		for (auto & p : count)
		{
			int curCount = 0;
			if (prevCount && prevNum + 1 == p.first)
				curCount = prevCount + p.second;
			maxCount = std::max(maxCount, curCount);
			prevNum = p.first;
			prevCount = p.second;
		}

		return maxCount;
	}
};
#endif
