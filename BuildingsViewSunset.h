#ifndef BUILDINGS_VIEW_SUNSET_H
#define BUILDINGS_VIEW_SUNSET_H
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include <string>
#include "Debug.h"
/*
Elements of programming interivew, StacksAndQueues: Compute buildings with a sunset view
You are given with a series of buildings that have windows facing west.
The buildings are in a straight line, and any building which is to the east of a building of equal or greater height cannot view the sunset.
Design an algorithm that processes buildings in east-to-west order and returns the set of buildings which view the sunset.
Each building is specified by its height.

input: building heights in an array from east to west (from left to right)
output: a set of buildings that are able to view sunset

BruteForce: O(n) time, O(n) space (this is because we need to scan reversely which needs the info of the entire array before hand)
Stack: O(n) time, O(n) space, O(1) space in best case
*/
class BuildingsViewSunset
{
public:
	BuildingsViewSunset(){}
	~BuildingsViewSunset(){}

	std::vector<int> BruteForce(const std::vector<int> & v)
	{
		int N = v.size();
		int runningMax = v.back();//keep a running max from right to left
		std::vector<int> res;
		res.push_back(v.back());
		for (int i = N - 2; i >= 0; --i)
		{
			if (v[i] > runningMax)
				res.push_back(v[i]);
			runningMax = std::max(runningMax, v[i]);
		}

		std::cout << "BuildingsViewSunset BruteForce for \"" << Debug::ToStr1D<int>()(v) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> SortedStack(const std::vector<int> & v)
	{
		int N = v.size();
		std::stack<std::pair<int, int>> sortedStk;//first: index, second: height (sorted in strckly decreasing order from left to right)
		for (int i = 0; i < N; ++i)
		{
			while (!sortedStk.empty() && sortedStk.top().second <= v[i])
			{
				sortedStk.pop();
			}
			sortedStk.push(std::make_pair(i, v[i]));
		}

		std::vector<int> res;
		while (!sortedStk.empty())
		{
			res.push_back(sortedStk.top().second);
			sortedStk.pop();
		}

		std::cout << "BuildingsViewSunset SortedStack for \"" << Debug::ToStr1D<int>()(v) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
BuildingsViewSunset BruteForce for "8, 17, 3, 7, 14, 13, 15, 9, 12, 5, 2": 2, 5, 12, 15, 17
BuildingsViewSunset SortedStack for "8, 17, 3, 7, 14, 13, 15, 9, 12, 5, 2": 2, 5, 12, 15, 17
*/
#endif