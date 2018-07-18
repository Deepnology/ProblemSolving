#ifndef RANDOM_FROM_PROB_DIST_H
#define RANDOM_FROM_PROB_DIST_H
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "Debug.h"
/*
Random from probability distribution
Elements of programming interview, Array: Generate nonuniform random numbers
http://www.geeksforgeeks.org/random-number-generator-in-arbitrary-probability-distribution-fashion/
http://www.careercup.com/question?id=17433662
Given n numbers, each with some frequency of occurrence.
Return a random number with probability proportional to its frequency of occurrence.

Preprocessing: O(n) time
Generate: O(logn) time, bounded by binary search in cumulative probability array

see also AliasMethod.h
*/
class RandomFromProbDist
{
	std::vector<int> m_cumulative;
public:
	explicit RandomFromProbDist(const std::vector<int> & probabilityDistribution) : m_cumulative(probabilityDistribution.size())
	{
		int N = probabilityDistribution.size();
		m_cumulative[0] = probabilityDistribution[0];
		for (int i = 1; i < N; ++i)
			m_cumulative[i] = m_cumulative[i - 1] + probabilityDistribution[i];

		srand((unsigned int)time(NULL));
	}
	~RandomFromProbDist(){}

	int NextIndex()
	{
		int r = (rand() % m_cumulative.back()) + 1;

		//binary search m_cumulative to find lower bound of r: O(logn)
		int left = -1;
		int right = m_cumulative.size() ;
		while (right - left > 1)
		{
			int mid = left + (right - left) / 2;
			if (m_cumulative[mid] >= r)
				right = mid;
			else
				left = mid;
		}
		//now right is the lower bound
		if (right == m_cumulative.size())
			return -1;
		return right;
	}

	int NextIndex2()
	{
		int r = (rand() % m_cumulative.back()) + 1;

		//binary search m_cumulative to find ceil of r: O(logn)
		int low = 0;
		int high = m_cumulative.size() - 1;
		while (low < high)
		{
			int mid = low + (high - low) / 2;
			if (r <= m_cumulative[mid])//left side
				high = mid;
			else//right side
				low = mid + 1;
		}

		//now m_cumulative[low] should be the the ceil of r
		if (m_cumulative[low] >= r)
			return low;
		else
			return -1;
	}

	int NextIndex3()
	{
		int r = (rand() % m_cumulative.back()) + 1;
		int low = 0;
		int high = m_cumulative.size() - 1;
		while (low <= high)
		{
			int mid = low + (high - low) / 2;
			if (r <= m_cumulative[mid])//left side
				high = mid - 1;
			else//right side
				low = mid + 1;
		}

		//now m_cumulative[low] should be the the lower bound of r
		if (m_cumulative[low] >= r)
			return low;
		else
			return -1;//won't happen
	}



	void Roll(const std::vector<int> & v, int times)
	{
		if (v.size() != m_cumulative.size())
			throw std::runtime_error("");
		int N = v.size();
		std::vector<std::pair<int,int>> res;
		for (int i = 0; i < N; ++i)
			res.push_back(std::make_pair(v[i], 0));
		for (int i = 0; i < times; ++i)
			++res[this->NextIndex3()].second;

		std::cout << "RandomFromProbDist for \"" << Debug::ToStr1D<int>()(v) << "\" with CumulativeProbability \"" << Debug::ToStr1D<int>()(m_cumulative) << "\":" << std::endl 
			<< ", Roll for \"" << times << "\"-times: " << Debug::ToStr1D<int>()(res) << std::endl;
	}
};
/*
RandomFromProbDist for "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14" with CumulativeProbability "1, 2, 4, 6, 9, 12, 16, 22, 28, 35, 44, 55, 68, 83, 100":
, Roll for "1000"-times: [0,11], [1,11], [2,18], [3,19], [4,31], [5,32], [6,32], [7,52], [8,60], [9,70], [10,101], [11,98], [12,145], [13,168], [14,152]

RandomFromProbDist for "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14" with CumulativeProbability "1, 2, 4, 6, 9, 12, 16, 22, 28, 35, 44, 55, 68, 83, 100":
, Roll for "1000"-times: [0,10], [1,11], [2,23], [3,17], [4,31], [5,26], [6,31], [7,69], [8,67], [9,56], [10,90], [11,128], [12,133], [13,144], [14,164]
*/
#endif