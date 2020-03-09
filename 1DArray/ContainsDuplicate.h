#ifndef CONTAINS_DUPLICATE_H
#define CONTAINS_DUPLICATE_H
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Contains Duplicate
Given an array of integers, find if the array contains any duplicates.
Your function should return true if any value appears at least twice in the array, and it should return false if every element is distinct.

Leetcode: Contains Duplicate II
Given an array of integers and an integer k, find out whether there there are two distinct indices i and j in the array 
such that nums[i] = nums[j] and the difference between i and j is at most k.

Leetcode: Contains Duplicate III
Given an array of integers, find out whether there are two distinct indices i and j in the array 
such that the difference between nums[i] and nums[j] is at most t and the difference between i and j is at most k.
*/
class ContainsDuplicate
{
public:
	ContainsDuplicate(){}
	~ContainsDuplicate(){}

	void Solve(const std::vector<int> & v, int k, int t)
	{
		bool res1 = this->containsDuplicate(v);
		bool res2 = this->containsNearbyDuplicate(v, k);
		bool res3 = this->containsNearbyAlmostDuplicate(v, k, t);

		std::cout << "ContainsDuplicate for \"" << Debug::ToStr1D<int>()(v) << "\": " << res1 << std::endl;
		std::cout << "ContainsDuplicate for AtMost \"" << k << "-Indicies from " << Debug::ToStr1D<int>()(v) << "\": " << res2 << std::endl;
		std::cout << "ContainsDuplicate for AtMost \"" << k << "-Indicies, AtMost " << t << "-Diff from " << Debug::ToStr1D<int>()(v) << "\": " << res3 << std::endl;
	}

	bool containsDuplicate(const std::vector<int> & v)
	{
		int N = v.size();
		std::unordered_set<int> s;
		for (int i = 0; i < N; ++i)
		{
			auto itr = s.find(v[i]);
			if (itr != s.end())
				return true;
			s.insert(v[i]);
		}
		return false;
	}

	bool containsNearbyDuplicate(const std::vector<int> & nums, int k)
	{
		int N = nums.size();
		std::unordered_map<long, int> toIdx;//first: entry, second: last occurrence index
		for (int i = 0; i < N; ++i)
		{
			auto itr = toIdx.find(nums[i]);
			if (itr == toIdx.end())
			{
				toIdx.insert({ nums[i], i });
			}
			else
			{
				if (std::abs(itr->second - i) <= k)
					return true;
				itr->second = i;
			}
		}
		return false;
	}

	bool containsNearbyAlmostDuplicate(const std::vector<int> & nums, int k, int t)
	{
		int N = nums.size();
		std::map<long, int> toIdx;//first: entry, second: last occurrence index
		for (int i = 0; i < N; ++i)
		{
			auto itr = toIdx.lower_bound(nums[i]);
			if (itr == toIdx.end())
			{
				if (toIdx.size() > 0)
				{
					--itr;
					if (std::abs(itr->first - nums[i]) <= t && std::abs(itr->second - i) <= k)
						return true;
				}
			}
			else if (itr->first == nums[i])
			{
				if (std::abs(itr->first - nums[i]) <= t && std::abs(itr->second - i) <= k)
					return true;
				itr->second = i;
				continue;
			}
			else
			{
				if (std::abs(itr->first - nums[i]) <= t && std::abs(itr->second - i) <= k)
					return true;
				if (itr != toIdx.begin())
				{
					--itr;
					if (std::abs(itr->first - nums[i]) <= t && std::abs(itr->second - i) <= k)
						return true;
				}
			}
			toIdx.insert({ nums[i], i });
		}
		return false;
	}
};
/*
ContainsDuplicate for "10, 62, 61, 59, 31, 70, 49, 27, 36, 64, 59, 19, 61, 59, 3, 94, 58, 37, 1, 79, 87, 48, 54, 13, 91": 1
ContainsDuplicate for AtMost "8-Indicies from 10, 62, 61, 59, 31, 70, 49, 27, 36, 64, 59, 19, 61, 59, 3, 94, 58, 37, 1, 79, 87, 48, 54, 13, 91": 1
ContainsDuplicate for AtMost "8-Indicies, AtMost 42-Diff from 10, 62, 61, 59, 31, 70, 49, 27, 36, 64, 59, 19, 61, 59, 3, 94, 58, 37, 1, 79, 87, 48, 54, 13, 91": 1
*/
#endif