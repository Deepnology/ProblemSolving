#ifndef MAX_SUB_ARRAY_SUM_CIRCULAR_H
#define MAX_SUB_ARRAY_SUM_CIRCULAR_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "Debug.h"
/*
Elements of programming interview, DynamicProgramming: Compute the maximum subarray sum in a circular array
Given a circular array A, compute its maximum subarray sum in O(n) time, where n is the length of A.
Can you devise an algorithm that takes O(n) time and O(1) space?

DP1D: O(n) time, O(n) space
Math: O(n) time, O(1) space
*/
class MaxSubArraySumCircular
{
public:
	MaxSubArraySumCircular(){}
	~MaxSubArraySumCircular(){}

	int DP1D(const std::vector<int> & A)
	{
		int maxNonCircular = this->maxSubArrSum(A);
		int maxCircular = this->circularMaxSubArrSum_DP1D(A);
		int res = maxNonCircular > 0 ? std::max(maxNonCircular, maxCircular) : maxNonCircular;
		//note: when all nums in A are negative, maxSubArrSum = max(A), minSubArrSum = sum(A)
		std::cout << "MaxSubArraySumCircular DP1D for \"" << Debug::ToStr1D<int>()(A) << "\": " << res << " (nonCircular: " << maxNonCircular << ", circular: " << maxCircular << ")" << std::endl;
		return res;
	}

	int Math(const std::vector<int> & A)
	{
		int maxNonCircular = this->maxSubArrSum(A);
		int maxCircular = std::accumulate(A.cbegin(), A.cend(), 0) - this->minSubArrSum(A);//the total sum subtract the min subarray sum
		int res = maxNonCircular > 0 ? std::max(maxNonCircular, maxCircular) : maxNonCircular;
		//note: when all nums in A are negative, maxSubArrSum = max(A), minSubArrSum = sum(A)
		std::cout << "MaxSubArraySumCircular Math for \"" << Debug::ToStr1D<int>()(A) << "\": " << res << " (nonCircular: " << maxNonCircular << ", circular: " << maxCircular << ")" << std::endl;
		return res;
	}

private:
	int circularMaxSubArrSum_DP1D(const std::vector<int> & A)
	{
		int N = A.size();
		int sum = A.front();
		std::vector<int> maxPrefixSumLeft;
		maxPrefixSumLeft.push_back(sum);
		for (int i = 1; i < N; ++i)
		{
			sum += A[i];
			maxPrefixSumLeft.push_back(std::max(maxPrefixSumLeft.back(), sum));
		}
		std::cout << "max accumulated sum from left (inclusive): " << Debug::ToStr1D<int>()(maxPrefixSumLeft) << std::endl;

		std::vector<int> maxPrefixSumRight(N);
		maxPrefixSumRight[N - 1] = A.back();
		sum = A.back();
		for (int i = N - 2; i >= 0; --i)
		{
			sum += A[i];
			maxPrefixSumRight[i] = std::max(maxPrefixSumRight[i + 1], sum);
		}
		std::cout << "max accumulated sum from right (inclusive): " << Debug::ToStr1D<int>()(maxPrefixSumRight) << std::endl;

		int maxCircular = 0;
		for (int i = 0; i < N; ++i)
		{
			if (i == 0)
				maxCircular = std::max(maxCircular, maxPrefixSumRight[0]);
			else if (i == N - 1)
				maxCircular = std::max(maxCircular, maxPrefixSumLeft[N - 1]);
			else
				maxCircular = std::max(maxCircular, 
				std::max(maxPrefixSumLeft[i - 1] + maxPrefixSumRight[i], maxPrefixSumLeft[i] + maxPrefixSumRight[i + 1]));
			/*
			max circular subarr sum at a particular position =
			max prefix sum from left + max prefix sum from right,
			which means a subarr from left end (at most to the particular position) concatenate with another subarr from right end (at most to the particular position)
			
			2 cases at idx 3:
			maxPrefixSumLeft[2] + maxPrefixSumRight[3]
			0  1  2   3  4  5  6
			_______/ \__________

			maxPrefixSumLeft[3] + maxPrefixSumRight[4]
			0  1  2  3   4  5  6
			__________/ \_______
			*/
		}

		return maxCircular;
	}
	int maxSubArrSum(const std::vector<int> & A)
	{
		int N = A.size();
		int curSubarrMax = 0;
		int dpMax = INT_MIN;
		for (int i = 0; i < N; ++i)
		{
			curSubarrMax = std::max(curSubarrMax + A[i], A[i]);
			dpMax = std::max(dpMax, curSubarrMax);
		}
		return dpMax;
	}
	int minSubArrSum(const std::vector<int> & A)
	{
		int N = A.size();
		int curSubarrMin = 0;
		int dpMin = INT_MAX;
		for (int i = 0; i < N; ++i)
		{
			curSubarrMin = std::min(curSubarrMin + A[i], A[i]);
			dpMin = std::min(dpMin, curSubarrMin);
		}
		return dpMin;
	}
};
/*
max accumulated sum from left (inclusive): 904, 944, 1467, 1479, 1479, 1479, 1479, 1479, 1479
max accumulated sum from right (inclusive): 1085, 450, 450, 450, 450, 450, 450, 450, -31
MaxSubArraySumCircular DP1D for "904, 40, 523, 12, -335, -385, -124, 481, -31": 1929 (nonCircular: 1479, circular: 1929)
MaxSubArraySumCircular Math for "904, 40, 523, 12, -335, -385, -124, 481, -31": 1929 (nonCircular: 1479, circular: 1929)
max accumulated sum from left (inclusive): 10, 10, 11, 11, 17
max accumulated sum from right (inclusive): 17, 11, 11, 10, 10
MaxSubArraySumCircular DP1D for "10, -4, 5, -4, 10": 21 (nonCircular: 17, circular: 21)
MaxSubArraySumCircular Math for "10, -4, 5, -4, 10": 21 (nonCircular: 17, circular: 21)
max accumulated sum from left (inclusive): -2, 1, 6, 8, 8, 8
max accumulated sum from right (inclusive): 5, 5, 2, -1, -1, -1
MaxSubArraySumCircular DP1D for "-2, 3, 5, 2, -4, -1": 10 (nonCircular: 10, circular: 8)
MaxSubArraySumCircular Math for "-2, 3, 5, 2, -4, -1": 10 (nonCircular: 10, circular: 8)
max accumulated sum from left (inclusive): -4, -4, -4, -3, -1, -1
max accumulated sum from right (inclusive): 7, 7, 7, 7, -2, -4
MaxSubArraySumCircular DP1D for "-4, -8, 0, 9, 2, -4": 11 (nonCircular: 11, circular: 7)
MaxSubArraySumCircular Math for "-4, -8, 0, 9, 2, -4": 11 (nonCircular: 11, circular: 7)
max accumulated sum from left (inclusive): -10, -10, -10, 0, 9, 9
max accumulated sum from right (inclusive): 24, 24, 24, 19, 9, 0
MaxSubArraySumCircular DP1D for "-10, -5, 5, 10, 9, 0": 24 (nonCircular: 24, circular: 24)
MaxSubArraySumCircular Math for "-10, -5, 5, 10, 9, 0": 24 (nonCircular: 24, circular: 24)
max accumulated sum from left (inclusive): 7, 14, 17, 20, 25, 30
max accumulated sum from right (inclusive): 30, 23, 16, 13, 10, 5
MaxSubArraySumCircular DP1D for "7, 7, 3, 3, 5, 5": 30 (nonCircular: 30, circular: 30)
MaxSubArraySumCircular Math for "7, 7, 3, 3, 5, 5": 30 (nonCircular: 30, circular: 27)
*/
#endif