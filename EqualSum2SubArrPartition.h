#ifndef EUQAL_SUM_2_SUB_ARR_PARTITION_H
#define EUQAL_SUM_2_SUB_ARR_PARTITION_H
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include "Debug.h"
/*
Google
http://www.careercup.com/question?id=5449136090382336
Given an integer array.
Find all break points such that the sum of elements from index 0 to index (break point - 1) is equal to the sum of index break point to index N-1.

FindBreakPoints: O(n) time, O(1) space
FindBreakPoints_PrefixSums: O(n) time, O(n) space

Equivalent to EquilibriumIndexOfArray.h
*/
class EqualSum2SubArrPartition
{
public:
	EqualSum2SubArrPartition(){}
	~EqualSum2SubArrPartition(){}

	std::vector<int> FindBreakPoints(const std::vector<int> & v)
	{
		int N = v.size();
		int sumLeftToRight = 0;
		int sumRightToLeft = 0;
		for (int i = 0; i < N; ++i)
			sumRightToLeft += v[i];

		std::vector<int> res;
		for (int i = 0; i < N; ++i)
		{
			if (sumLeftToRight == sumRightToLeft)
				res.push_back(i);

			sumLeftToRight += v[i];
			sumRightToLeft -= v[i];
		}

		std::cout << "EqualSum2SubArrPartition FindBreakPoints for \"" << Debug::ToStr1D<int>()(v) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> FindBreakPoints_PrefixSums(const std::vector<int> & v)
	{
		int N = v.size();

		std::vector<int> prefixSumLeft(N);
		prefixSumLeft[0] = v[0];
		for (int i = 1; i < N; ++i)
			prefixSumLeft[i] = prefixSumLeft[i - 1] + v[i];

		std::vector<int> prefixSumRight(N);
		prefixSumRight[N - 1] = v[N - 1];
		for (int i = N - 2; i >= 0; --i)
			prefixSumRight[i] = prefixSumRight[i + 1] + v[i];

		std::vector<int> res;
		for (int i = 0; i <= N; ++i)
		{
			if ((i == 0 && prefixSumRight[i] == 0) ||
				(i == N && prefixSumLeft[i - 1] == 0) ||
				(i != 0 && i != N && prefixSumLeft[i - 1] == prefixSumRight[i]))//subarray sum in [0,i-1] == subarray sum in [i,N-1]
				res.push_back(i);
		}

		std::cout << Debug::ToStr1D<int>()(prefixSumLeft) << std::endl;
		std::cout << Debug::ToStr1D<int>()(prefixSumRight) << std::endl;
		std::cout << "EqualSum2SubArrPartition FindBreakPoints_PrefixSums for \"" << Debug::ToStr1D<int>()(v) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
EqualSum2SubArrPartition FindBreakPoints for "1, -1, 0, 1, 1": 1, 4
1, 0, 0, 1, 2
2, 1, 2, 2, 1
EqualSum2SubArrPartition FindBreakPoints_PrefixSums for "1, -1, 0, 1, 1": 1, 4
EqualSum2SubArrPartition FindBreakPoints for "1, 1, -1, 1, 0": 1, 3
1, 2, 1, 2, 2
2, 1, 0, 1, 0
EqualSum2SubArrPartition FindBreakPoints_PrefixSums for "1, 1, -1, 1, 0": 1, 3
*/
#endif