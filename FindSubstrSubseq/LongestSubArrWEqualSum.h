#ifndef LONGEST_SUBARR_W_EQUAL_SUM_H
#define LONGEST_SUBARR_W_EQUAL_SUM_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include "Debug.h"
/*
Leetcode: Maximum Size Subarray Sum Equals K
Given an array nums and a target value k, find the maximum length of a subarray that sums to k.
If there isn't one, return 0 instead.

Example 1:
Given nums = [1, -1, 5, -2, 3], k = 3,
return 4. (because the subarray [1, -1, 5, -2] sums to 3 and is the longest)

Example 2:
Given nums = [-2, -1, 2, 1], k = 1,
return 2. (because the subarray [-1, 2] sums to 1 and is the longest)

HashMap: O(n) time, O(n) space
see also LongestSubArrWLessEqualSum.h

Leetcode: Contiguous Array
Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.
Example 1:
Input: [0,1]
Output: 2
Explanation: [0, 1] is the longest contiguous subarray with equal number of 0 and 1.
Example 2:
Input: [0,1,0]
Output: 2
Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.
=> special case of LongestSubArrWEqualSum after transforming the input array w/ 0s to -1s and find longest subarray whose sum=0.
*/
class LongestSubArrWEqualSum
{
public:
	LongestSubArrWEqualSum() {}
	~LongestSubArrWEqualSum() {}

	int HashMap(const std::vector<int> & v, int k)
	{
		std::unordered_map<int, int> prefixSumMap;//first: a prefix sum, second: the running sum's first occurrence index
		int maxLen = 0;
		int prefixSum = 0;
		int N = v.size();
		for (int i = 0; i < N; ++i)
		{
			prefixSum += v[i];
			if (prefixSum == k)
			{
				maxLen = std::max(maxLen, i + 1);//from 0 to i
			}
			//check if a prefix sum of (current prefix sum - k) exists
			//if exists, then the subarray from that index to current index i must sum to k
			else if (prefixSumMap.find(prefixSum - k) != prefixSumMap.end())
			{
				maxLen = std::max(maxLen, i - prefixSumMap[prefixSum - k]);
			}

			if (prefixSumMap.find(prefixSum) == prefixSumMap.end())
			{
				prefixSumMap.insert({ prefixSum, i });//only keep prefix sum's smallest index
			}
		}

		std::cout << "LongestSubArrWEqualSum HashMap for \"" << k << "\" from \"" << Debug::ToStr1D<int>()(v) << "\": " << maxLen << std::endl;
		return maxLen;
	}
};
/*
LongestSubArrWEqualSum HashMap for "3" from "1, -1, 5, -2, 3": 4
LongestSubArrWEqualSum HashMap for "1" from "-2, -1, 2, 1": 2
*/
/*
Leetcode: Longest Well-Performing Interval
We are given hours, a list of the number of hours worked per day for a given employee.
A day is considered to be a tiring day if and only if the number of hours worked is (strictly) greater than 8.
A well-performing interval is an interval of days for which the number of tiring days is strictly larger than the number of non-tiring days.
Return the length of the longest well-performing interval.
Example 1:
Input: hours = [9,9,6,0,6,6,9]
Output: 3
Explanation: The longest well-performing interval is [9,9,6].
 */
class LongestSubArrWMoreGreaterThan8NumCount
{
public:
	int LongestOneAndMinusOneSubArrWPositiveSum(std::vector<int> && hours)
	{
		std::unordered_map<int,int> prefixSumMap;//<prefixSum, first occur index>
		int N = hours.size();
		int prefixSum = 0;
		int maxLen = 0;
		for (int i = 0; i < N; ++i)
		{
			prefixSum += hours[i] > 8 ? 1 : -1;
			if (prefixSum > 0)
				maxLen = std::max(maxLen, i+1);//from 0 to i
			else if (prefixSumMap.count(prefixSum-1))
				maxLen = std::max(maxLen, i-prefixSumMap[prefixSum-1]);
			//ex: if prefixSum=0, find the first index w/ prefixSum=-1, such that subarr sum in [index+1:i] = 0-(-1) = 1, where the subarr len is i-index
			//ex: if prefixSum=-1, find the first index w/ prefixSum=-2, such that subarr sum in [index+1:i] = -1-(-2) = 1, where the subarr len is i-index
			if (!prefixSumMap.count(prefixSum))//record i if first seen prefixSum
				prefixSumMap[prefixSum] = i;
		}

		std::cout << "LongestSubArrWMoreGreaterThan8NumCount LongestOneAndMinusOneSubArrWPositiveSum for [" << Debug::ToStr1D<int>()(hours) << "]: " << maxLen << std::endl;
		return maxLen;
	}
};
/*
LongestSubArrWMoreGreaterThan8NumCount LongestOneAndMinusOneSubArrWPositiveSum for [9, 9, 6, 0, 6, 6, 9]: 3
 */
#endif
