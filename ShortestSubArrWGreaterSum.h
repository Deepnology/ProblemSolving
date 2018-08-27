#ifndef SHORTEST_SUB_ARR_W_GREATER_SUM_H
#define SHORTEST_SUB_ARR_W_GREATER_SUM_H
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Minimum Size Subarray Sum
Given an array of n positive integers and a positive integer s, find the minimal length of a subarray of which the sum >= s.
If there isn't one, return 0 instead.
For example, given the array [2,3,1,2,4,3] and s = 7,
the subarray [4,3] has the minimal length under the problem constraint.

http://www.careercup.com/question?id=5653018213089280
http://www.geeksforgeeks.org/minimum-length-subarray-sum-greater-given-value/
Find the shortest consecutive sequences (subarray) from an input array whose sum is greater than a given value.

SlideWindow(Stormage): O(n) time, O(1) space, O(n^2) time in worst case
BruteForce_PrefixSums: O(n^2) time, O(n) space
BruteForce: O(n^3) time, O(1) space

see also ShortestSubstrContainAllChars.h, SubArrayWGivenSum.h

Leetcode: Shortest Subarray with Sum at least K (array might contain negative numbers)
Return the length of the shortest, non-empty, contiguous subarray of A with sum at least K.
If there is no non-empty subarray with sum at least K, return -1.
Example 1:
Input: A = [1], K = 1
Output: 1
Example 2:
Input: A = [1,2], K = 4
Output: -1
Example 3:
Input: A = [2,-1,2], K = 3
Output: 3
*/
class ShortestSubArrWGreaterSum
{
public:
	ShortestSubArrWGreaterSum(){}
	~ShortestSubArrWGreaterSum(){}

	int SlideWindow_GreaterEqual(const std::vector<int> & v, int val)
	{
		int N = v.size();
		int sum = 0;
		int left = 0;
		int right = 0;
		int winNegCount = 0;//num of negative entries in window
		int minLen = INT_MAX;
		int minLeft = 0;
		int minRight = 0;

		for (; right < N; ++right)
		{
			if (v[right] >= val)
			{
				//found best answer
				minLen = 1;
				minLeft = right;
				minRight = right;
				break;
			}

			sum += v[right];
			if (v[right] < 0)
				++winNegCount;

			//when sum<=0 which means we must have just added a non-positive int, it can no longer be >=val bc the non-positive int wasn't >=val. so reset it.
			if (sum <= 0)
			{
				left = right + 1;
				sum = 0;
				winNegCount = 0;
				continue;
			}

			//shrink window left when running sum >= val
			if (sum >= val)
			{
				if (winNegCount > 0)//use the more expensive approach when negative entries present in the window, O(n^2) time in worst case
				{
					//a. accumulate running sum from right to left until greater equal than val to find tgtLeft
					int sum2 = 0;
					int tgtLeft = right;
					while (sum2 + v[tgtLeft] < val && tgtLeft > left)
					{
						sum2 += v[tgtLeft];
						--tgtLeft;
					}
					sum2 += v[tgtLeft];

					//b. subtract num of negative entries from left to tgtLeft
					for (int i = left; i < tgtLeft; ++i)
						if (v[i] < 0)
							--winNegCount;

					//c. update running sum and window left
					sum = sum2;
					left = tgtLeft;
				}
				else//use the less expensive approach when no negative entries present in the window, O(n) time
				{
					//shrink window left by excluding running sum until smaller than val
					while (sum - v[left] >= val && left < right)
					{
						sum -= v[left];
						++left;
					}
				}

				if (right - left + 1 < minLen)
				{
					minLen = right - left + 1;
					minLeft = left;
					minRight = right;
				}
			}
		}

		if (minLen == INT_MAX)//not found
			minLen = 0;

		if (minLen == 0)
			std::cout << "ShortestSubArrWGreaterEqualSum for \"" << val << "\" from \"" << Debug::ToStr1D<int>()(v) << "\": doesn't exist" << std::endl;
		else
			std::cout << "ShortestSubArrWGreaterEqualSum for \"" << val << "\" from \"" << Debug::ToStr1D<int>()(v) << "\": [" << minLeft << "," << minRight << "] = " << Debug::ToStr1D<int>()(v, minLeft, minRight) << std::endl;
		return minLen;
	}

	int SlideWindow_Greater(const std::vector<int> & v, int val)
	{
		int N = v.size();
		int sum = 0;
		int left = 0;
		int right = 0;
		int winNegCount = 0;//num of negative entries in window
		int minLen = INT_MAX;
		int minLeft = 0;
		int minRight = 0;

		for (; right < N; ++right)
		{
			if (v[right] > val)
			{
				//found best answer
				minLen = 1;
				minLeft = right;
				minRight = right;
				break;
			}

			sum += v[right];
			if (v[right] < 0)
				++winNegCount;

			//when sum<=0 which means we must have just added a non-positive int, it can no longer be >val bc the non-positive int wasn't >val. so reset it.
			if (sum <= 0)
			{
				left = right + 1;
				sum = 0;
				winNegCount = 0;
				continue;
			}

			//shrink window left when running sum > val
			if (sum > val)
			{
				if (winNegCount > 0)//use the more expensive approach when negative entries present in the window, O(n^2) time in worst case
				{
					//a. accumulate running sum from right to left until greater than val to find tgtLeft
					int sum2 = 0;
					int tgtLeft = right;
					while (sum2 + v[tgtLeft] <= val && tgtLeft > left)
					{
						sum2 += v[tgtLeft];
						--tgtLeft;
					}
					sum2 += v[tgtLeft];

					//b. subtract num of negative entries from left to tgtLeft
					for (int i = left; i < tgtLeft; ++i)
						if (v[i] < 0)
							--winNegCount;

					//c. update running sum and window left
					sum = sum2;
					left = tgtLeft;
				}
				else//use the less expensive approach when no negative entries present in the window, O(n) time
				{
					//shrink window left by excluding running sum until smaller equal than val
					while (sum - v[left] > val && left < right)
					{
						sum -= v[left];
						++left;
					}
				}

				if (right - left + 1 < minLen)
				{
					minLen = right - left + 1;
					minLeft = left;
					minRight = right;
				}
			}
		}

		if (minLen == INT_MAX)//not found
			minLen = 0;

		if (minLen == 0)
			std::cout << "ShortestSubArrWGreaterSum for \"" << val << "\" from \"" << Debug::ToStr1D<int>()(v) << "\": doesn't exist" << std::endl;
		else
			std::cout << "ShortestSubArrWGreaterSum for \"" << val << "\" from \"" << Debug::ToStr1D<int>()(v) << "\": [" << minLeft << "," << minRight << "] = " << Debug::ToStr1D<int>()(v, minLeft, minRight) << std::endl;
		return minLen;
	}

    //leetcode: shortest subarray with sum at least k (array might contain negative nums)
    int SortedQueue_GreaterEqual(const std::vector<int> & v, int val)
    {
        int N = v.size();
        std::vector<int> prefixSum(N, 0);
        for (int i = 0; i < N; ++i)
            prefixSum[i] = v[i] + (i==0 ? 0 : prefixSum[i-1]);
        prefixSum.insert(prefixSum.begin(), 0);

        std::deque<int> sortedQue;//in incr order
        sortedQue.push_back(0);
        int res = INT_MAX;
        for (int i = 1; i <= N; ++i)
        {
            while (!sortedQue.empty() && prefixSum[i] <= prefixSum[sortedQue.back()])
                sortedQue.pop_back();
            sortedQue.push_back(i);
            while (!sortedQue.empty() && prefixSum[i] - prefixSum[sortedQue.front()] >= val)
            {
                res = std::min(res, i-sortedQue.front());
                sortedQue.pop_front();
            }
        }
        res = (res==INT_MAX ? -1 : res);

        std::cout << "ShortestSubArrWGreaterSum SortedQueue GreaterEqual for \"" << val << "\" from [" << Debug::ToStr1D<int>()(v) << "]: " << res << std::endl;
        return res;
    }

	//leetcode: minimum size subarray sum (v contains positive nums only)
	int SlideWindow_GreaterEqual_PositiveNums(const std::vector<int> & v, int val)
	{
		int N = v.size();
		int left = 0;
		int right = 0;
		int sum = 0;
		int minLen = INT_MAX;
		for (; right < N; ++right)
		{
			sum += v[right];
			while (sum - v[left] >= val && left < right)
			{
				sum -= v[left];
				++left;
			}
			if (sum >= val && right - left + 1 < minLen)
			{
				minLen = right - left + 1;
				//record minLeft and minRight if required
			}
		}
		if (minLen == INT_MAX) minLen = 0;

		std::cout << "ShortestSubArrWGreaterSum SlideWindow_GreaterEqual_PositiveNums for \"" << val << "\" from \"" << Debug::ToStr1D<int>()(v) << "\": " << minLen << std::endl;
		return minLen;
	}
	int SortedPrefixSums_GreaterEqual_PositiveNums(const std::vector<int> & v, int val)
	{
		int N = v.size();
		std::vector<long long> prefixSums;//sorted prefixSums
		prefixSums.push_back(0);//add an extra 0 in case of searching for a negative value or a value equal to val will return a lb or ub pointing to it
		long long prefixSum = 0;
		int minLen = INT_MAX;
		for (int i = 0; i < N; ++i)//O(nlogn) time
		{
			prefixSum += v[i];
			//prefixSum2 - prefixSum1 >= val
			//prefixSum2 - val >= prefixSum1
			//since we want to find min len between prefixSum2 and prefixSum1
			//we want to find the rightmost equal element of lower bound, which is equivalent to upper bound - 1
			//otherwise (no equal element) we want to find lower bound - 1, which is also equivalent to upper bound - 1
			auto lb = std::lower_bound(prefixSums.begin(), prefixSums.end(), prefixSum - val);
			auto ub = std::upper_bound(prefixSums.begin(), prefixSums.end(), prefixSum - val);
			
			std::cout << Debug::ToStr1D<long long>()(prefixSums) << std::endl;
			std::cout << "PrefixSum=" << prefixSum << ", lb=" << (lb - prefixSums.begin()) << ", ub=" << (ub - prefixSums.begin()) << ", len=";
			
			if (lb != prefixSums.end() && *lb == (long long)(prefixSum - val))
			{
				int len = (i - (ub - prefixSums.begin() - 1) + 1);
				minLen = std::min(minLen, len);

				std::cout << len << std::endl;
			}
			else if (lb == prefixSums.begin())//(prefixSum-val) is negative
			{
				//skip
				std::cout << "skip (prefixSum-" << val << " is negative)" << std::endl;
			}
			else
			{
				int len = (i - (lb - prefixSums.begin() - 1) + 1);
				minLen = std::min(minLen, len);

				std::cout << len << std::endl;
			}

			prefixSums.push_back(prefixSum);
		}
		if (minLen == INT_MAX) minLen = 0;

		std::cout << "ShortestSubArrWGreaterSum SortedPrefixSums_GreaterEqual_PositiveNums for \"" << val << "\" from \"" << Debug::ToStr1D<int>()(v) << "\": " << minLen << std::endl;
		return minLen;
	}


};
/*
ShortestSubArrWGreaterSum for "-5" from "-6, -4, -7": [1,1] = -4
ShortestSubArrWGreaterSum for "3" from "2, -1, 0, 2, 1, -7, 1, 2, -1, 2, -5, 3, 0, 1, -4, 1, 3, -3, 4": [18,18] = 4
ShortestSubArrWGreaterSum for "3" from "2, -1, 0, 2, 1, -7, 1, 2, -1, 2, -5, 3, 0, 1, -4, 1, 3": [15,16] = 1, 3
ShortestSubArrWGreaterSum for "3" from "-1, 2, -1, 0, 2, -1, 2, 0, 1": [4,8] = 2, -1, 2, 0, 1
ShortestSubArrWGreaterSum for "10" from "1, 2, 3, 4, -10, -2, 22": [6,6] = 22
ShortestSubArrWGreaterSum for "-3" from "-3, -7, -5, -4, -2, -6, -8": [4,4] = -2
ShortestSubArrWGreaterSum for "0" from "-3, -7, -5, -4, -2, -6, -8": doesn't exist
ShortestSubArrWGreaterSum for "15" from "7, -3, 8, 4, 13, -5": [3,4] = 4, 13
ShortestSubArrWGreaterSum for "8" from "2, 1, 1, 4, 3, 6, 1": [4,5] = 3, 6
ShortestSubArrWGreaterSum for "57" from "1, 1, 1, 1, 1, 1, 1, 1, 50": [0,8] = 1, 1, 1, 1, 1, 1, 1, 1, 50
ShortestSubArrWGreaterSum for "51" from "1, 4, 45, 6, 10, 19": [1,3] = 4, 45, 6
ShortestSubArrWGreaterSum for "9" from "1, 10, 5, 2, 7": [1,1] = 10
ShortestSubArrWGreaterSum for "280" from "1, 11, 100, 1, 0, 200, 3, 2, 1, 250": [2,5] = 100, 1, 0, 200
ShortestSubArrWGreaterEqualSum for "7" from "2, 3, 1, 2, 4, 3": [4,5] = 4, 3
ShortestSubArrWGreaterSum SlideWindow_GreaterEqual_PositiveNums for "7" from "2, 3, 1, 1": 4
ShortestSubArrWGreaterSum SlideWindow_GreaterEqual_PositiveNums for "7" from "2, 3, 1, 2, 4, 3": 2
ShortestSubArrWGreaterSum SlideWindow_GreaterEqual_PositiveNums for "4" from "1, 4, 4": 1
ShortestSubArrWGreaterSum SlideWindow_GreaterEqual_PositiveNums for "7" from "10, 3, 1": 1
0
PrefixSum=2, lb=0, ub=0, len=skip (prefixSum-7 is negative)
0, 2
PrefixSum=5, lb=0, ub=0, len=skip (prefixSum-7 is negative)
0, 2, 5
PrefixSum=6, lb=0, ub=0, len=skip (prefixSum-7 is negative)
0, 2, 5, 6
PrefixSum=7, lb=0, ub=1, len=4
ShortestSubArrWGreaterSum SortedPrefixSums_GreaterEqual_PositiveNums for "7" from "2, 3, 1, 1": 4
0
PrefixSum=2, lb=0, ub=0, len=skip (prefixSum-7 is negative)
0, 2
PrefixSum=5, lb=0, ub=0, len=skip (prefixSum-7 is negative)
0, 2, 5
PrefixSum=6, lb=0, ub=0, len=skip (prefixSum-7 is negative)
0, 2, 5, 6
PrefixSum=8, lb=1, ub=1, len=4
0, 2, 5, 6, 8
PrefixSum=12, lb=2, ub=3, len=3
0, 2, 5, 6, 8, 12
PrefixSum=15, lb=4, ub=5, len=2
ShortestSubArrWGreaterSum SortedPrefixSums_GreaterEqual_PositiveNums for "7" from "2, 3, 1, 2, 4, 3": 2
0
PrefixSum=1, lb=0, ub=0, len=skip (prefixSum-4 is negative)
0, 1
PrefixSum=5, lb=1, ub=2, len=1
0, 1, 5
PrefixSum=9, lb=2, ub=3, len=1
ShortestSubArrWGreaterSum SortedPrefixSums_GreaterEqual_PositiveNums for "4" from "1, 4, 4": 1
0
PrefixSum=10, lb=1, ub=1, len=1
0, 10
PrefixSum=13, lb=1, ub=1, len=2
0, 10, 13
PrefixSum=14, lb=1, ub=1, len=3
ShortestSubArrWGreaterSum SortedPrefixSums_GreaterEqual_PositiveNums for "7" from "10, 3, 1": 1

ShortestSubArrWGreaterSum SortedQueue GreaterEqual for "3" from [2, -1, 2]: 3
ShortestSubArrWGreaterSum SortedQueue GreaterEqual for "3" from [-2, 2, -1, 2]: 3
*/
#endif