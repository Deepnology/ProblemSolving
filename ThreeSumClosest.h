#ifndef THREE_SUM_CLOSEST_H
#define THREE_SUM_CLOSEST_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Greedy: The 3-sum problem, variant
Write a function that takes as input an array of integers A and an integer T
, and return a 3-tuple (A[p],A[q],A[r]) where p,q,r are all distinct
, minimizing |T-(A[p]+A[q]+A[r])|, and A[p] <= A[q] <= A[r].
Leetcode: 3Sum Closest
// Given an array S of n integers, find three integers in S such that the sum
// is closest to a given number, target. Return the sum of the three integers.
// You may assume that each input would have exactly one solution.
//
// For example, given array S = {-1 2 1 -4}, and target = 1.
//
// The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
//
// Complexity: O(n^2) time, O(1) space

Leetcode: 3Sum Smaller
Given an array of n integers nums and a target, find the number of index triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target.
For example, given nums = [-2, 0, 1, 3], and target = 2. Return 2.
Because there are two triplets which sums are less than 2:
[-2, 0, 1]
[-2, 0, 3]
Follow up:
Could you solve it in O(n^2) runtime?
*/
class ThreeSumClosest
{
public:
	ThreeSumClosest(){}
	~ThreeSumClosest(){}

	int Sort_Greedy(std::vector<int> && num, int target)
	{
		int N = num.size();
		std::sort(std::begin(num), std::end(num));
		int res = num[0] + num[1] + num[2];
		for (int i = 0; i < N - 2; ++i)
		{
			int start = i + 1;
			int end = N - 1;
			while (start < end)
			{
				int sum = num[i] + num[start] + num[end];

				if (std::abs(sum - target) < std::abs(res - target))
					res = sum;

				if (sum < target)
					++start;
				else if (sum > target)
					--end;
				else//found a sum equal to target!
					break;
			}
		}

		std::cout << "ThreeSumClosest Sort_Greedy for \"" << target << "\" in \"" << Debug::ToStr1D<int>()(num) << "\": " << res << std::endl;
		return res;
	}
};
class ThreeSumSmaller
{
public:
	ThreeSumSmaller() {}
	~ThreeSumSmaller() {}
	int Sort_Greedy(std::vector<int> && num, int target)
	{
		int N = num.size();
		std::sort(std::begin(num), std::end(num));
		int count = 0;
		for (int i = 0; i < N - 2; ++i)
		{
			int start = i + 1;
			int end = N - 1;
			while (start < end)
			{
				int sum = num[i] + num[start] + num[end];

				if (sum < target)
				{
					//fix both "i" and "end"
					//count in [i, start, end], [i, start+1, end], ..., [i, end-1, end]
					count += (end - start);
					++start;
				}
				else
					--end;
			}
		}

		std::cout << "ThreeSumSmaller Sort_Greedy for \"" << target << "\" in \"" << Debug::ToStr1D<int>()(num) << "\": " << count << std::endl;
		return count;
	}
};
/*
ThreeSumClosest Sort_Greedy for "-1" in "-5, -4, -3, -2, 3": -2
ThreeSumSmaller Sort_Greedy for "2" in "-2, 0, 1, 3": 2
*/
#endif