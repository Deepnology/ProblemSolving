#ifndef _THREE_SUM_H
#define _THREE_SUM_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Greedy: The 3-sum problem
Leetcode: 3Sum
// Given an array S of n integers, are there elements a, b, c in S such that
// a + b + c = 0?
// Find all unique triplets in the array which gives the sum of zero.
//
// Note:
// Elements in a triplet (a,b,c) must be in non-descending order. (ie, a <= b <= c)
// The solution set must not contain duplicate triplets.
// For example, given array S = {-1 0 1 2 -1 -4},
//
// A solution set is:
// (-1, 0, 1)
// (-1, -1, 2)
//
// Complexity:
// O(n^2) time, O(1) space
*/
class ThreeSum
{
public:
	ThreeSum(){}
	~ThreeSum(){}

	std::vector<std::vector<int> > FindAll_Sort_Greedy(std::vector<int> && num, int target)
	{
		int N = num.size();
		std::sort(std::begin(num), std::end(num));
		std::vector<std::vector<int>> res;

		for (int i = 0; i < N - 2; ++i)
		{
			if (i > 0 && num[i - 1] == num[i])
				continue;//skip repeats

			//start, end are on the right side of index
			int start = i + 1;
			int end = N - 1;
			while (start < end)
			{
				int sum = num[i] + num[start] + num[end];
				if (sum < target)
					++start;
				else if (sum > target)
					--end;
				else
				{
					res.push_back(std::vector<int>({num[i], num[start], num[end]}));
					do
					{
						++start;
					} while (start < end && num[start - 1] == num[start]);//skip repeats
					do
					{
						--end;
					} while (start < end && num[end] == num[end + 1]);//skip repeats
				}
			}
		}

		std::cout << "ThreeSum FindAll_Sort_Greedy for " << target << " in \"" << Debug::ToStr1D<int>()(num) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

};
/*
ThreeSum FindAll_Sort_Greedy for 15 in "1, 2, 3, 4, 5, 6, 7, 8, 9, 10": [1,4,10], [1,5,9], [1,6,8], [2,3,10], [2,4,9], [2,5,8], [2,6,7], [3,4,8], [3,5,7], [4,5,6]
*/

#endif