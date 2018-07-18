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
    std::vector<int> m_prob;
	std::vector<int> m_cumulative;
public:
	explicit RandomFromProbDist(const std::vector<int> & probabilityDistribution) : m_prob(probabilityDistribution), m_cumulative(probabilityDistribution.size())
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

    int NextIndex_ConstSpace(const std::vector<int> & prob)
    {
        int sum = std::accumulate(prob.begin(), prob.end(), 0);
        int r = (rand() % sum) + 1;
        int N = prob.size();
        int i = 0;
        int prefixSum = 0;
        while (i < N && prefixSum + prob[i] < r)
            prefixSum += prob[i++];
        //now prefixSum + prob[i] >= r
        return i;
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

		std::cout << "RandomFromProbDist BinarySearch for \"" << Debug::ToStr1D<int>()(v) << "\" with CumulativeProbability \"" << Debug::ToStr1D<int>()(m_cumulative) << "\":" << std::endl
			<< ", Roll for \"" << times << "\"-times: " << Debug::ToStr1D<int>()(res) << std::endl;

        for (int i = 0; i < N; ++i)
            res[i].second = 0;
        for (int i = 0; i < times; ++i)
            ++res[this->NextIndex_ConstSpace(m_prob)].second;

		std::cout << "RandomFromProbDist ConstSpace for \"" << Debug::ToStr1D<int>()(v) << "\" with CumulativeProbability \"" << Debug::ToStr1D<int>()(m_cumulative) << "\":" << std::endl
				  << ", Roll for \"" << times << "\"-times: " << Debug::ToStr1D<int>()(res) << std::endl;
	}
};
/*
RandomFromProbDist BinarySearch for "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14" with CumulativeProbability "1, 2, 4, 6, 9, 12, 16, 22, 28, 35, 44, 55, 68, 83, 100":
, Roll for "1000"-times: [0,7], [1,7], [2,21], [3,18], [4,24], [5,24], [6,38], [7,68], [8,55], [9,72], [10,98], [11,110], [12,136], [13,147], [14,175]
RandomFromProbDist ConstSpace for "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14" with CumulativeProbability "1, 2, 4, 6, 9, 12, 16, 22, 28, 35, 44, 55, 68, 83, 100":
, Roll for "1000"-times: [0,13], [1,10], [2,20], [3,19], [4,34], [5,30], [6,51], [7,62], [8,58], [9,67], [10,81], [11,98], [12,132], [13,161], [14,164]
*/
#endif