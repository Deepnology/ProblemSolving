#ifndef MAX_DIFF_2_SUB_ARRAY_SUM_H
#define MAX_DIFF_2_SUB_ARRAY_SUM_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Google:
Max Distance Between 2 Disjoint Subarray Sum
http://www.careercup.com/question?id=19286747
Given an array of integers.
Find two disjoint contiguous sub-arrays such that the absolute difference between the sum of two sub-arrays is maximum.
The sub-arrays should not overlap.

dp: O(n) time, O(n) space

see also BalancedPartitionWMin2SumDiff.h, BalancedPartitionWEqual2Sum.h
*/
class MaxDiff2SubArraySum
{
public:
	MaxDiff2SubArraySum() {}
	~MaxDiff2SubArraySum() {}

public:
	int DP1D(const std::vector<int> & A)
	{
		int N = A.size();
		std::vector<std::pair<int, int>> leftInclusiveCur(N);//key: max, value: min (max and min subarray sum on cur's left including cur)
		std::vector<std::pair<int, int>> rightExclusiveCur(N);//key: max, value: min (max and min subarray sum on cur's right excluding cur)
		int curSubarrMax;
		int curSubarrMin;
		for (int i = 0; i < N; ++i)
		{
			if (i == 0)
			{
				curSubarrMax = A[0];
				curSubarrMin = A[0];
				leftInclusiveCur[i].first = A[0];
				leftInclusiveCur[i].second = A[0];
				continue;
			}
			curSubarrMax = std::max(A[i], curSubarrMax + A[i]);
			leftInclusiveCur[i].first = std::max(leftInclusiveCur[i - 1].first, curSubarrMax);
			curSubarrMin = std::min(A[i], curSubarrMin + A[i]);
			leftInclusiveCur[i].second = std::min(leftInclusiveCur[i - 1].second, curSubarrMin);
		}
		//now leftInclusiveCur[i].first is the max contiguous subarr sum in A[0]~A[i]
		//leftInclusiveCur[i].second is the min contiguous subarr sum in A[0]~A[i]

		for (int i = N - 1; i >= 0; --i)
		{
			if (i == N - 1)
			{
				rightExclusiveCur[i].first = INT_MIN;
				rightExclusiveCur[i].second = INT_MAX;
				continue;
			}
			else if (i == N - 2)
			{
				curSubarrMax = A[i + 1];
				curSubarrMin = A[i + 1];
				rightExclusiveCur[i].first = A[i + 1];
				rightExclusiveCur[i].second = A[i + 1];
				continue;
			}
			curSubarrMax = std::max(A[i + 1], curSubarrMax + A[i + 1]);
			rightExclusiveCur[i].first = std::max(rightExclusiveCur[i + 1].first, curSubarrMax);
			curSubarrMin = std::min(A[i + 1], curSubarrMin + A[i + 1]);
			rightExclusiveCur[i].second = std::min(rightExclusiveCur[i + 1].second, curSubarrMin);
		}
		//now rightExclusiveCur[i].first is the max contiguous subarr sum in A[i+1]~A[N-1]
		//rightExclusiveCur[i].second is the min contiguous subarr sum in A[i+1]~A[N-1]

		int res = INT_MIN;
		for (int i = 0; i < N; ++i)
		{
			int diff1;
			int diff2;
			if (i == N - 1)
			{
				diff1 = std::abs(leftInclusiveCur[i].first - 0);
				diff2 = std::abs(0 - leftInclusiveCur[i].second);
			}
			else
			{
				diff1 = std::abs(leftInclusiveCur[i].first - rightExclusiveCur[i].second);
				diff2 = std::abs(rightExclusiveCur[i].first - leftInclusiveCur[i].second);
			}
			int max = std::max(diff1, diff2);
			res = std::max(max, res);
		}
		std::cout << Debug::ToStr1D<int>()(leftInclusiveCur) << std::endl;
		std::cout << Debug::ToStr1D<int>()(rightExclusiveCur) << std::endl;
		std::cout << "MaxDiff2SubArraySum DP1D for \"" << Debug::ToStr1D<int>()(A) << "\": " << res << std::endl;
		return res;
	}
};
/*
[4,4], [4,-1], [10,-1]
[7,-1], [7,7], [-2147483648,2147483647]
MaxDiff2SubArraySum DP1D for "4, -1, 7": 10
[-1,-1], [-1,-3], [-1,-6]
[-2,-5], [-3,-3], [-2147483648,2147483647]
MaxDiff2SubArraySum DP1D for "-1, -2, -3": 6
[-10,-10], [7,-10], [7,-10], [7,-10], [8,-10], [8,-22], [8,-22]
[8,-20], [4,-20], [4,-20], [2,-20], [1,-20], [1,1], [-2147483648,2147483647]
MaxDiff2SubArraySum DP1D for "-10, 7, -3, 2, 2, -20, 1": 28
[2,2], [2,-1], [2,-3], [2,-3], [2,-6], [2,-6], [10,-6]
[10,-6], [10,-5], [10,-4], [10,-4], [10,2], [8,8], [-2147483648,2147483647]
MaxDiff2SubArraySum DP1D for "2, -1, -2, 1, -4, 2, 8": 16
*/
#endif
