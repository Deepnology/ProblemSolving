#ifndef COUNT_SUBARR_W_SUM_EQUAL_K_H
#define COUNT_SUBARR_W_SUM_EQUAL_K_H
#include "Debug.h"
/*
Leetcode: Subarray Sum Equals K
Given an array of integers and an integer k, you need to find the total number of continuous subarrays whose sum equals to k.
Example 1:
Input:nums = [1,1,1], k = 2
Output: 2
Note:
The length of the array is in range [1, 20,000].
The range of numbers in the array is [-1000, 1000] and the range of the integer k is [-1e7, 1e7].


Use prefixSum array: O(N^2) time
Use prefixSumMap: O(N) time

Bloomberg:
Given an array of integers and an integer k, find the total number of continuous subarrays whose odd numbers count equals to k.
=> Transform the array to an 0/1 array where original even numbers transforming to 0s and original odd numbers transforming to 1s.
=> Then find number of subarrays whose sum equals to k.

see also RangeSumCount.h
*/
class CountSubArrWSumEqualK
{
public:
	CountSubArrWSumEqualK() {}

	int UsePrefixSumMap(std::vector<int> & nums, int k)
	{
		std::unordered_map<int, int> prefixSumCount;
		prefixSumCount[0] = 1;
		int N = nums.size();
		int prefixSum = 0;
		int res = 0;
		for (int i = 0; i < N; ++i)
		{
			prefixSum += nums[i];
			if (prefixSumCount.count(prefixSum - k))
				res += prefixSumCount[prefixSum - k];
			++prefixSumCount[prefixSum];
		}

		std::cout << "CountSubArrWSumEqualK UsePrefixSumMap for \"" << Debug::ToStr1D<int>()(nums) << "\", k=\"" << k << "\": " << res << std::endl;
		return res;
	}

	std::vector<std::pair<int, int>> FindAll_PrefixSumMap(std::vector<int> & nums, int k)
	{
		std::unordered_map<int, std::vector<int>> prefixSumIdxArr;//<prefixSum, arr of idxs>
		prefixSumIdxArr[0] = { -1 };
		int prefixSum = 0;
		std::vector<std::pair<int, int>> res;
		int N = nums.size();
		for (int i = 0; i < N; ++i)
		{
			prefixSum += nums[i];
			if (prefixSumIdxArr.count(prefixSum - k))
			{
				for (auto & idx : prefixSumIdxArr[prefixSum - k])
					res.push_back({ idx + 1, i });
			}
			prefixSumIdxArr[prefixSum].push_back(i);
		}

		std::cout << "CountSubArrWSumEqualK FindAll_PrefixSumMap for \"" << Debug::ToStr1D<int>()(nums) << "\", k=\"" << k << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
CountSubArrWSumEqualK UsePrefixSumMap for "1, 1, 1", k="2": 2
CountSubArrWSumEqualK FindAll_PrefixSumMap for "1, 1, 1", k="2": [0,1], [1,2]
CountSubArrWSumEqualK UsePrefixSumMap for "0, 1, 0, -2, 2, 1, 0, 0, -2", k="1": 16
CountSubArrWSumEqualK FindAll_PrefixSumMap for "0, 1, 0, -2, 2, 1, 0, 0, -2", k="1": [0,1], [1,1], [0,2], [1,2], [0,4], [1,4], [2,5], [3,5], [5,5], [2,6], [3,6], [5,6], [2,7], [3,7], [5,7], [4,8]
*/
#endif
