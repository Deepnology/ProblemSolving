#ifndef FACTOR_COMBINATIONS_H
#define FACTOR_COMBINATIONS_H
#include <iostream>
#include <string>
#include <vector>
#include "Debug.h"
/*
Leetcode: Factor Combinations
Numbers can be regarded as product of its factors. For example,
8 = 2 x 2 x 2;
= 2 x 4.
Write a function that takes an integer n and return all possible combinations of its factors.
Note:
Each combination's factors must be sorted ascending, for example: The factors of 2 and 6 is [2, 6], not [6, 2].
You may assume that n is always positive.
Factors should be greater than 1 and less than n.
Examples:
input: 1
output:
[]
input: 37
output:
[]
input: 12
output:
[
[2, 6],
[2, 2, 3],
[3, 4]
]
input: 32
output:
[
[2, 16],
[2, 2, 8],
[2, 2, 2, 4],
[2, 2, 2, 2, 2],
[2, 4, 4],
[4, 8]
]
*/
class FactorCombinations
{
public:
	FactorCombinations() {}
	~FactorCombinations() {}

	std::vector<std::vector<int>> Recur(int n)
	{
		std::vector<std::vector<int>> res;
		if (n == 1) return res;
		std::vector<int> path;
		this->recur2(2, 1, n, path, res);

		std::cout << "FactorCombinations Recur for \"" << n << "\": " << std::endl;
		Debug::Print2D<int>()(res, false);
		return res;
	}

private:
	void recur(int begin, int curProduct, int n, std::vector<int> & path, std::vector<std::vector<int>> & res)//time limit exceeded
	{
		if (curProduct > n) return;
		if (curProduct == n)
		{
			res.emplace_back(path);
			return;
		}
		for (int i = begin; i < n; ++i)
		{
			if (n % (i * curProduct) == 0)
			{
				path.push_back(i);
				this->recur(i, i*curProduct, n, path, res);
				path.pop_back();
			}
		}
	}
	void recur2(int begin, int curProduct, int n, std::vector<int> & path, std::vector<std::vector<int>> & res)//accepted
	{
		if (curProduct > n) return;
		if (curProduct == n)
		{
			res.emplace_back(path);
			return;
		}
		for (int i = begin; i <= sqrt(n); ++i)
		{
			if (n % (i * curProduct) == 0)
			{
				path.push_back(i);
				this->recur2(i, i*curProduct, n, path, res);
				path.pop_back();
			}
			if (n / i > sqrt(n) && n % ((n / i) * curProduct) == 0)
			{
				path.push_back(n / i);
				this->recur2(n / i, (n / i)*curProduct, n, path, res);
				path.pop_back();
			}
		}
	}
};
/*
FactorCombinations Recur for "1":
FactorCombinations Recur for "37":
FactorCombinations Recur for "12":
[rY][cX]
Row#0	= 2, 2, 3
Row#1	= 2, 6,
Row#2	= 3, 4,

FactorCombinations Recur for "32":
[rY][cX]
Row#0	= 2, 2, 2, 2, 2
Row#1	= 2, 2, 2, 4,
Row#2	= 2, 2, 8,  ,
Row#3	= 2, 4, 4,  ,
Row#4	= 2, 16,  ,  ,
Row#5	= 4, 8,  ,  ,

*/
#endif
