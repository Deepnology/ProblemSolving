#ifndef MAX_SUB_ARRAY_SUM_H
#define MAX_SUB_ARRAY_SUM_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/find-subarray-with-given-sum/
http://www.geeksforgeeks.org/largest-sum-contiguous-subarray/
Leetcode: Maximum Subarray
// Find the contiguous subarray within an array (containing at least one
// number) which has the largest sum.
//
// For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
// the contiguous subarray [4,-1,2,1] has the largest sum = 6.
//
// Complexity:
// dp (Kadane's Algorithm): O(n) time
// Divide and Conquer: O(nlog(n)) time
// PrefixSum Quadratic: O(n^2) time, O(n) space
// BruteForce (enumerate all subarrays and sum up all elements in each subarray): O(n^3) time, O(1) space

See also MaxSubMatrixSum.h
*/
class MaxSubArraySum
{
public:
	MaxSubArraySum(){}
	~MaxSubArraySum(){}

	int Kadane_2Pass(const std::vector<int> & v, int & begin, int & end)
	{
		int N = v.size();
		int sum = 0;
		int maxSum = INT_MIN;
		end = -1;
		int positiveBegin = 0;

		for (int i = 0; i < N; ++i)
		{
			sum += v[i];

			/*when sum is negative, we reset it and positiveBegin*/
			if (sum < 0)
			{
				sum = 0;
				positiveBegin = i + 1;
				continue;
			}

			/*we only update maxSum, begin, and end when sum is 0 or positive*/
			if (sum > maxSum)
			{
				maxSum = sum;
				begin = positiveBegin;
				end = i;
			}
		}

		/*
		special case when all elements are negative (sum never became positive or 0):
		just need find the max negative element
		*/
		if (end == -1)
		{
			maxSum = v[0];
			begin = end = 0;
			for (int i = 1; i < N; ++i)
			{
				if (v[i] > maxSum)
				{
					maxSum = v[i];
					begin = end = i;
				}
			}
		}

		std::cout << "MaxSubArraySum Kadane_2Pass for \"" << Debug::ToStr1D<int>()(v) << "\": " << maxSum << " (" << Debug::ToStr1D<int>()(v, begin, end) << ")" << std::endl;
		return maxSum;
	}

	int DP1D(int A[], int n)
	{
		//dp[i]: the max sub array sum of A[someBegin]~A[i] including A[i]
		//someBegin must be the index where A[i] > dp[i-1]+A[i]
		std::vector<int> dp(n, 0);
		dp[0] = A[0];
		for (int i = 1; i < n; ++i)
		{
			dp[i] = std::max(dp[i - 1] + A[i], A[i]);
		}
		int res = INT_MIN;
		for (int i = 0; i < n; ++i)
		{
			res = std::max(res, dp[i]);
		}
		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "MaxSubArraySum DP1D for \"" << Debug::ToStr1D<int>()(A, n) << "\": " << res << std::endl;
		return res;
	}

	int DP(int A[], int n)
	{
		int curSubarrMax = 0;
		int dpMax = INT_MIN;
		for (int i = 0; i < n; ++i)
		{
			curSubarrMax = std::max(curSubarrMax + A[i], A[i]);
			dpMax = std::max(dpMax, curSubarrMax);
		}
		std::cout << "MaxSubArraySum DP for \"" << Debug::ToStr1D<int>()(A, n) << "\": " << dpMax << std::endl;
		return dpMax;
	}

	int DivideConquerRecur(int A[], int n)
	{
		int res = this->maxSumRecur(A, 0, n - 1);
		std::cout << "MaxSubArraySum DivideConquerRecur for \"" << Debug::ToStr1D<int>()(A, n) << "\": " << res << std::endl;
		return res;
	}
private:
	int maxSumRecur(int A[], int start, int end)
	{
		if (start > end)
			return INT_MIN;
		int middle = start + (end - start) / 2;
		int sum = 0;
		int lmax = 0;
		int rmax = 0;
		for (int i = middle - 1; i >= start; --i)
		{
			sum += A[i];
			lmax = std::max(lmax, sum);
		}
		sum = 0;
		for (int i = middle + 1; i <= end; ++i)
		{
			sum += A[i];
			rmax = std::max(rmax, sum);
		}
		return std::max(
			A[middle] + lmax + rmax,//the subarray centered at A[middle]
			std::max(this->maxSumRecur(A, start, middle - 1), this->maxSumRecur(A, middle + 1, end))
			);
	}

public:
	int PrefixSum_Quadratic(const std::vector<int> & v)
	{
		int N = v.size();
		std::vector<int> prefixSum(N);
		prefixSum[0] = v[0];
		for (int i = 1; i < N; ++i)
			prefixSum[i] = prefixSum[i - 1] + v[i];

		int maxSum = INT_MIN;
		int maxBegin = 0;
		int maxEnd = 0;

		/*enumerate all possible subarrays whose sum = prefixSum[curEnd] - prefixSum[curBegin-1]*/
		for (int curEnd = 0; curEnd < N; ++curEnd)
		{
			for (int curBegin = 0; curBegin <= curEnd; ++curBegin)
			{
				if (curBegin == 0 && prefixSum[curEnd] > maxSum)
				{
					maxSum = prefixSum[curEnd];
					maxBegin = 0;
					maxEnd = curEnd;
				}
				else if (curBegin != 0 && prefixSum[curEnd] - prefixSum[curBegin - 1] > maxSum)
				{
					maxSum = prefixSum[curEnd] - prefixSum[curBegin - 1];
					maxBegin = curBegin;
					maxEnd = curEnd;
				}
			}
		}

		std::cout << "MaxSubArraySum PrefixSum_Quadratic for \"" << Debug::ToStr1D<int>()(v) << "\": " << maxSum << " (" << Debug::ToStr1D<int>()(v, maxBegin, maxEnd) << ")" << std::endl;
		return maxSum;
	}


};
/*
MaxSubArraySum Kadane_2Pass for "-2, 1, -3, 4, -1, 2, 1, -5, 4": 6 (4, -1, 2, 1)
MaxSubArraySum Kadane_2Pass for "-2, -10, -3, -4, -7, -9, -1, -8, -5": -1 (-1)
-2, 1, -2, 4, 3, 5, 6, 1, 5
MaxSubArraySum DP1D for "-2, 1, -3, 4, -1, 2, 1, -5, 4": 6
MaxSubArraySum DP for "-2, 1, -3, 4, -1, 2, 1, -5, 4": 6
MaxSubArraySum DivideConquerRecur for "-2, 1, -3, 4, -1, 2, 1, -5, 4": 6
MaxSubArraySum PrefixSum_Quadratic for "-2, 1, -3, 4, -1, 2, 1, -5, 4": 6 (4, -1, 2, 1)
*/
#endif