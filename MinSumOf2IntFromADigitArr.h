#ifndef MIN_SUM_OF_2_INT_FROM_A_DIGIT_ARR_H
#define MIN_SUM_OF_2_INT_FROM_A_DIGIT_ARR_H
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
Google
http://www.careercup.com/question?id=5678435150069760
Given an array of integers in the range of [0,9] inclusive.
Partition and rearrange the integers into 2 groups such that the sum of the 2 numbers represented by each group is minimum.
Return the minimum sum.

See also BalancedPartitionWMin2SumDiff.h
*/
class MinSumOf2IntFromADigitArr
{
public:
	MinSumOf2IntFromADigitArr(){}
	~MinSumOf2IntFromADigitArr(){}

	int Sort_And_Alternate(std::vector<int> && v)
	{
		std::string before = Debug::ToStr1D<int>()(v);
		int N = v.size();
		std::sort(v.begin(), v.end(), [](const int & a, const int & b)
		{
			return a < b;//ascending order
		});
		int num1 = 0;
		int num2 = 0;
		for (int i = 0; i < N; ++i)
		{
			if (i % 2)
				num1 = 10 * num1 + v[i];
			else
				num2 = 10 * num2 + v[i];
		}

		std::cout << "MinSumOf2IntFromADigitArr for \"" << before << "\": " << num1 << " + " << num2 << " = " << num1 + num2 << std::endl;
		return num1 + num2;
	}
};
/*
MinSumOf2IntFromADigitArr for "1, 2, 7, 8, 9": 28 + 179 = 207
MinSumOf2IntFromADigitArr for "6, 4, 6, 0, 1, 4, 8, 7, 3": 1467 + 3468 = 4935
*/
#endif