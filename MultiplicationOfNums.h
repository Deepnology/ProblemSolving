#ifndef MULTIPLICATION_OF_NUMS_H
#define MULTIPLICATION_OF_NUMS_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Product of Array Except Self
Elements of programming interview, Array: Compute the maximum product of all but one entries
Facebook
http://www.careercup.com/question?id=5179916190482432
http://www.careercup.com/question?id=21024669
http://leetcode.com/2010/04/multiplication-of-numbers.html
There is an array A[N] of N numbers. 
You have to compose an array Output[N] such that Output[i] will be equal to multiplication of all the elements of A[N] except A[i]. 
Solve it without division operator and in O(n).

For example Output[0] will be multiplication of A[1] to A[N-1] and Output[1] will be multiplication of A[0] and from A[2] to A[N-1].

Example:
A: {4, 3, 2, 1, 2}
OUTPUT: {12, 16, 24, 48, 24}

Use Left and Right accumulated products: O(n) time, O(n) space
DP1D: O(n) time, O(n) space
FindMaxProduct: O(n) time, O(1) space

See also MaxProductOf3.h, MaxSubArrayProduct.h
*/
class MultiplicationOfNums
{
public:
	MultiplicationOfNums(){}
	~MultiplicationOfNums(){}

	std::vector<int> Solve(const std::vector<int> & A)
	{
		int N = A.size();
		std::vector<int> res(N, 1);
		int left = 1;
		int right = 1;
		for (int i = 0; i < N; ++i)
		{
			res[i] *= left;
			res[N - 1 - i] *= right;
			left *= A[i];
			right *= A[N - 1 - i];
		}
		std::cout << "MultiplicationOfNums for \"" << Debug::ToStr1D<int>()(A) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
	std::vector<int> Solve_2Scans(const std::vector<int> & A)
	{
		int N = A.size();
		std::vector<int> res(N, 1);
		int left = 1;
		for (int i = 0; i < N; ++i)
		{
			res[i] *= left;
			left *= A[i];
		}
		std::cout << Debug::ToStr1D<int>()(res) << std::endl;
		int right = 1;
		for (int i = 0; i < N; ++i)
		{
			res[N - 1 - i] *= right;
			right *= A[N - 1 - i];
		}
		std::cout << "MultiplicationOfNums 2Scans for \"" << Debug::ToStr1D<int>()(A) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> DP1D(const std::vector<int> & v)
	{
		int N = v.size();
		std::vector<int> leftProduct(N);//leftProduct[i]: the accumulative product of v[0]~v[i-1]
		std::vector<int> rightProduct(N);//rightProduct[i]: the accumulative product of v[i+1]~v[N-1]
		for (int i = 0; i < N; ++i)
		{
			leftProduct[i] = (i == 0 ? 1 : v[i - 1] * leftProduct[i - 1]);
		}
		for (int i = N - 1; i >= 0; --i)
		{
			rightProduct[i] = (i == N - 1 ? 1 : v[i + 1] * rightProduct[i + 1]);
		}

		std::vector<int> product(N);
		for (int i = 0; i < N; ++i)
		{
			product[i] = leftProduct[i] * rightProduct[i];
		}

		std::cout << "MultiplicationOfNums DP1D for \"" << Debug::ToStr1D<int>()(v) << "\": " << Debug::ToStr1D<int>()(product) << std::endl;
		return product;
	}

	//find the max product of n-1 nums: O(n) time, O(1) space
	int FindMaxProduct(const std::vector<int> & v)
	{
		int N = v.size();
		int zeroCount = 0;
		int posCount = 0;
		int negCount = 0;
		int zeroIdx = -1;
		int maxNegIdx = -1;
		int minNegIdx = -1;
		int minPosIdx = -1;

		for (int i = 0; i < N; ++i)
		{
			if (v[i] < 0)
			{
				++negCount;
				if (minNegIdx == -1 || v[i] < v[minNegIdx])
					minNegIdx = i;
				if (maxNegIdx == -1 || v[i] > v[maxNegIdx])
					maxNegIdx = i;
			}
			else if (v[i] == 0)
			{
				++zeroCount;
				zeroIdx = i;
			}
			else//v[i] > 0
			{
				++posCount;
				if (minPosIdx == -1 || v[i] < v[minPosIdx])
					minPosIdx = i;
			}
		}

		int excludeIdx;
		if (zeroCount >= 2)
		{
			std::cout << "MultiplicationOfNums FindMaxProduct for \"" << Debug::ToStr1D<int>()(v) << "\": " << 0 << std::endl;
			return 0;
		}
		else if (zeroCount == 1)
		{
			if (negCount & 1)//odd number negative
			{
				std::cout << "MultiplicationOfNums FindMaxProduct for \"" << Debug::ToStr1D<int>()(v) << "\": " << 0 << std::endl;
				return 0;
			}
			else//even number negative
				excludeIdx = zeroIdx;
		}
		else//no zero
		{
			if (negCount & 1)//odd number negative => exclude the max negative number
				excludeIdx = maxNegIdx;
			else//even number negative: non-all-negative => exclude the min positive number; all-negative => exclude the min negative number
			{
				if (posCount > 0)
					excludeIdx = minPosIdx;
				else
					excludeIdx = minNegIdx;
			}
		}

		int maxProduct = 1;
		for (int i = 0; i < N; ++i)
			if (i != excludeIdx)
				maxProduct *= v[i];

		std::cout << "MultiplicationOfNums FindMaxProduct for \"" << Debug::ToStr1D<int>()(v) << "\": " << maxProduct << std::endl;
		return maxProduct;
	}
};
/*
MultiplicationOfNums for "4, 3, 2, 1, 2": 12, 16, 24, 48, 24
1, 4, 12, 24, 24
MultiplicationOfNums 2Scans for "4, 3, 2, 1, 2": 12, 16, 24, 48, 24
MultiplicationOfNums DP1D for "4, 3, 2, 1, 2": 12, 16, 24, 48, 24
MultiplicationOfNums FindMaxProduct for "4, 3, 2, 1, 2": 48
*/
#endif