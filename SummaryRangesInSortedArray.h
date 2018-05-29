#ifndef SUMMARY_RANGES_IN_SORTED_ARRAY_H
#define SUMMARY_RANGES_IN_SORTED_ARRAY_H
#include <vector>
#include <string>
#include <iostream>
#include "Debug.h"
/*
Leetcode: Summary Ranges In Sorted Array
Given a sorted integer array without duplicates, return the summary of its ranges.
For example, given [0,1,2,4,5,7], return ["0->2","4->5","7"].

*/
class SummaryRangesInSortedArray
{
public:
	SummaryRangesInSortedArray(){}
	~SummaryRangesInSortedArray(){}

	std::vector<std::string> Solve(const std::vector<int> & nums)
	{
		int N = nums.size();
		if (N == 0)
			return std::vector<std::string>();
		if (N == 1)
			return std::vector<std::string>(1, std::to_string(nums[0]));

		std::vector<std::string> res;
		int begin = 0;
		for (int i = 1; i < N; ++i)
		{
			if (nums[i] != nums[i - 1] + 1)//summary range [begin:i-1]
			{
				std::string r;
				r.append(std::to_string(nums[begin]));
				if (begin != i - 1)
				{
					r.append("->");
					r.append(std::to_string(nums[i - 1]));
				}
				res.push_back(r);
				begin = i;
			}
		}

		std::string r;//summary range [begin:N-1]
		r.append(std::to_string(nums[begin]));
		if (begin != N - 1)
		{
			r.append("->");
			r.append(std::to_string(nums[N - 1]));
		}
		res.push_back(r);

		std::cout << "SummaryRangesInSortedArray for \"" << Debug::ToStr1D<int>()(nums) << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}

	std::vector<std::string> Better(const std::vector<int> & nums)
	{
		int N = nums.size();
		std::vector<std::string> res;
		int begin = 0;
		while (begin < N)
		{
			int end = begin + 1;
			while (end < N && nums[end] == nums[end-1]+1)
				++end;
			//now summary [begin,end-1]
			if (begin == end-1)
				res.push_back(std::to_string(nums[begin]));
			else
				res.push_back(std::to_string(nums[begin])+std::string("->")+std::to_string(nums[end-1]));
			begin = end;
		}

		std::cout << "SummaryRangesInSortedArray Better for \"" << Debug::ToStr1D<int>()(nums) << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
};
/*
SummaryRangesInSortedArray for "2, 3, 3, 4, 5, 7, 7, 9, 10, 13": 2->3, 3->5, 7, 7, 9->10, 13
SummaryRangesInSortedArray Better for "1, 2, 2, 2, 3, 4, 5, 6, 10, 13": 1->2, 2, 2->6, 10, 13
*/
#endif