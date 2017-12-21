#ifndef CANDY_H
#define CANDY_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include "Debug.h"
/*
Leetcode: Candy
// There are N children standing in a line. Each child is assigned a rating
// value.
//
// You are giving candies to these children subjected to the following
// requirements:
//
// Each child must have at least one candy.
// Children with a higher rating get more candies than their neighbors.
// What is the minimum candies you must give?

Elements of programming interview, Heaps: Compute fair bonuses
Given an array of ratings of developers, you want to give bonus to each developer based on their ratings.
You also want to minimize the sum of all bonuses.
Each developer can only compare his/her rating with his/her left and right neighbors, as well as his/her bonus.
Design an algorithm to compute an array of minimum bonuses that you need to give to each developer.

Given an array A of nonnegative integers, compute an array T whoses sum is minimum subject to for every i, if A[i]>A[i-1] then T[i]>T[i-1]
, and if A[i]>A[i+1] then T[i]>T[i+1].

Iterate_2Pass: O(n) time, O(n) space
Iterate_2Psss_DP1D: O(n) time, O(n) space
BruteForce_MinHeap: O(nlogn) time, O(n) space
*/
class Candy
{
public:
	Candy(){}
	~Candy(){}

	int Iterate_2Pass(const std::vector<int> & ratings)
	{
		int N = ratings.size();
		std::vector<int> candies(N, 1);

		for (int i = 1; i < N; ++i)//from left to right
			if (ratings[i] > ratings[i - 1])
				candies[i] = candies[i - 1] + 1;

		for (int i = N - 2; i >= 0; --i)//from right to left
			if (ratings[i] > ratings[i + 1] && candies[i] <= candies[i + 1])
				candies[i] = candies[i + 1] + 1;

		int res = 0;
		for (int i = 0; i < N; i++)
			res += candies[i];

		std::cout << "Candy Iterate_2Pass for \"" << Debug::ToStr1D<int>()(ratings) << "\": " << res << ". (" << Debug::ToStr1D<int>()(candies) << ")" << std::endl;
		return res;
	}

	int Iterate_2Pass_DP1D(const std::vector<int> & ratings)
	{
		int N = ratings.size();
		if (N == 0)
			return 0;
		if (N == 1)
			return 1;
		std::vector<int> left(N, 1);
		std::vector<int> right(N, 1);
		int res = 0;

		for (int i = 1; i < N; ++i)//from left to right
			if (ratings[i] > ratings[i - 1])
				left[i] = 1 + left[i - 1];

		for (int i = N - 2; i >= 0; --i)//from right to left
			if (ratings[i] > ratings[i + 1])
				right[i] = 1 + right[i + 1];

		for (int i = 0; i < N; ++i)
			res += std::max(left[i], right[i]);

		std::cout << "Candy Iterate_2Pass_DP1D for \"" << Debug::ToStr1D<int>()(ratings) << "\": " << res << std::endl;
		return res;
	}

	struct GreaterThanComp
	{
		bool operator()(const std::pair<int, int> & a, const std::pair<int, int> & b)
		{
			return a.first > b.first;
		}
	};
	int BruteForce_MinHeap(const std::vector<int> & v)
	{
		int N = v.size();
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >, GreaterThanComp> minHeap;//first: val, second: idx
		for (int i = 0; i < N; ++i)
		{
			minHeap.push(std::make_pair(v[i], i));
		}

		std::vector<int> res(N, 1);
		while (!minHeap.empty())
		{
			auto & p = minHeap.top();
			if (p.second > 0)//compare with left neighbor
			{
				if (v[p.second] > v[p.second - 1])
					res[p.second] = res[p.second - 1] + 1;//first visit the developer when comparing with his left neighbor
			}
			if (p.second + 1 < N)//compare with right neighbor
			{
				if (v[p.second] > v[p.second + 1])
					res[p.second] = std::max(res[p.second], res[p.second + 1] + 1);//second visit the developer when comparing with his right neighbor
			}
			minHeap.pop();
		}

		int sum = 0;
		for (int i = 0; i < N; i++)
			sum += res[i];

		std::cout << "Candy BruteForce_MinHeap for \"" << Debug::ToStr1D<int>()(v) << "\": " << sum << ". (" << Debug::ToStr1D<int>()(res) << ")" << std::endl;
		return sum;
	}
};
/*
Candy Iterate_2Pass for "3, 8, 9, 1, 2, 4, 5, 7, 6, 5, 4, 3": 31. (1, 2, 3, 1, 2, 3, 4, 5, 4, 3, 2, 1)
Candy Iterate_2Pass_DP1D for "3, 8, 9, 1, 2, 4, 5, 7, 6, 5, 4, 3": 31
Candy BruteForce_MinHeap for "3, 8, 9, 1, 2, 4, 5, 7, 6, 5, 4, 3": 31. (1, 2, 3, 1, 2, 3, 4, 5, 4, 3, 2, 1)
*/
#endif