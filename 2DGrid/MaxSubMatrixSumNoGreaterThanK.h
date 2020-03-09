#ifndef MAX_SUBMATRIX_SUM_NO_GREATER_THAN_K_H
#define MAX_SUBMATRIX_SUM_NO_GREATER_THAN_K_H
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "Debug.h"
/*
http://bookshadow.com/weblog/2016/06/22/leetcode-max-sum-of-sub-matrix-no-larger-than-k/
Leetcode: Max Sum of Rectangle No Larger Than K
Given a non-empty 2D matrix matrix and an integer k, find the max sum of a rectangle in the matrix such that its sum is no larger than k.
Example:
Given matrix =
[[1,  0, 1],
 [0, -2, 3]]
k = 2
The answer is 2. Because the sum of rectangle [[0, 1], [-2, 3]] is 2 and 2 is the max number no larger than k (k = 2).
Note:
The rectangle inside the matrix must have an area > 0.
What if the number of rows is much larger than the number of columns?
BruteForce w/ prefixSums: O(n^4) time
Use set to keep track of sorted prefixSums: O(n^2*m*logm) time

1D problem: find max subarray sum that is no greater than K
https://www.quora.com/Given-an-array-of-integers-A-and-an-integer-k-find-a-subarray-that-contains-the-largest-sum-subject-to-a-constraint-that-the-sum-is-less-than-k
BruteForce w/ prefixSums: O(n^2) time
Use set to keep track of sorted prefixSums: O(nlogn) time

see also RangeSumQueryWPrefixSums.h, RangeSumCount.h, ClosestSubArraySum.h
*/
class MaxSubMatrixSumNoGreaterThanK
{
public:
	MaxSubMatrixSumNoGreaterThanK() {}
	~MaxSubMatrixSumNoGreaterThanK() {}

	int OneD_BruteForcePrefixSums(const std::vector<int> & v, int K)
	{
		int N = v.size();
		std::vector<int> prefixSums(N, 0);
		for (int i = 0; i < N; ++i)
			prefixSums[i] = v[i] + (i == 0 ? 0 : prefixSums[i - 1]);

		//enumerate all possible subarray sums: O(n^2) time
		int res = INT_MIN;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j <= i; ++j)
			{
				int subArrSum = (j == 0 ? prefixSums[i] : prefixSums[i] - prefixSums[j - 1]);
				if (subArrSum <= K)
					res = std::max(res, subArrSum);
			}
		}

		std::cout << "MaxSubMatrixSumNoGreaterThanK OneD_BruteForcePrefixSums for \"" << Debug::ToStr1D<int>()(v) << "\", K=\"" << K << "\": " << res << std::endl;
		return res;
	}

	int TwoD_BruteForcePrefixSums(const std::vector<std::vector<int>> & v, int K)
	{
		int N = v.size();
		int M = v[0].size();

		std::vector<std::vector<int>> prefixSums(N, std::vector<int>(M, 0));
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				//prefixSums[i][j] = v[i][j] + prefixSums[i-1][j] + prefixSums[i][j-1] - prefixSums[i-1][j-1]
				prefixSums[i][j] = v[i][j] + (i == 0 ? 0 : prefixSums[i - 1][j]) + (j == 0 ? 0 : prefixSums[i][j - 1]) - (i == 0 || j == 0 ? 0 : prefixSums[i - 1][j - 1]);
			}
		}

		//enumerate all possible submatrix sums: O(n^4) time
		int res = INT_MIN;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				for (int ii = 0; ii <= i; ++ii)
				{
					for (int jj = 0; jj <= j; ++jj)
					{
						//subMatrixSum between [ii,jj] and [i,j] includsive is
						//prefixSums[i][j] - prefixSums[ii-1][j] - prefixSums[i][jj-1] + prefixSums[ii-1][jj-1]
						int subMatrixSum = prefixSums[i][j] - (ii == 0 ? 0 : prefixSums[ii - 1][j]) - (jj == 0 ? 0 : prefixSums[i][jj - 1]) + (ii == 0 || jj == 0 ? 0 : prefixSums[ii - 1][jj - 1]);
						if (subMatrixSum <= K)
							res = std::max(res, subMatrixSum);
					}
				}
			}
		}

		Debug::Print2D<int>()(v, false);
		Debug::Print2D<int>()(prefixSums, false);
		std::cout << "MaxSubMatrixSumNoGreaterThanK TwoD_BruteForcePrefixSums for the above matrix, K=\"" << K << "\": " << res << std::endl;
		return res;
	}



	int OneD_SortedPrefixSums(const std::vector<int> & v, int K)
	{
		int N = v.size();
		std::set<int> prefixSums;
		prefixSums.insert(0);
		int res = INT_MIN;
		int prefixSum = 0;
		for (int i = 0; i < N; ++i)//O(nlogn) time
		{
			prefixSum += v[i];
			auto itr = prefixSums.lower_bound(prefixSum - K);//see if there is a leftPrefixSum such that (prefixSum-leftPrefixSum) <= K
			if (itr != prefixSums.end())
				res = std::max(res, prefixSum - *itr);//(prefixSum-*itr) is the subarray sum
			prefixSums.insert(prefixSum);
		}

		std::cout << "MaxSubMatrixSumNoGraterThankK OneD_SortedPrefixSums for \"" << Debug::ToStr1D<int>()(v) << "\", K=\"" << K << "\": " << res << std::endl;
		return res;
	}

	int TwoD_SortedPrefixSums(const std::vector<std::vector<int>> & v, int K)//Similar to Kadane, see MaxSubMatrixSum.h
	{
		int N = v.size();
		int M = v[0].size();
		int res = INT_MIN;
		for (int topRowY = 0; topRowY < N; ++topRowY)//O(n^2*m*logm) time
		{
			std::vector<int> subMatrixSum(M, 0);
			for (int bottomRowY = topRowY; bottomRowY < N; ++bottomRowY)
			{
				for (int col = 0; col < M; ++col)
				{
					subMatrixSum[col] += v[bottomRowY][col];
				}

				std::set<int> prefixSums;
				int prefixSum = 0;
				prefixSums.insert(0);//in case prefixSum==K, so we can return 0 such that prefixSum-0 = prefixSum
				for (const auto & sum : subMatrixSum)
				{
					prefixSum += sum;
					auto itr = prefixSums.lower_bound(prefixSum - K);//see if there is a leftPrefixSum such that (prefixSum-leftPrefixSum) <= K
					if (itr != prefixSums.end())
						res = std::max(res, prefixSum - *itr);//(prefixSum-*itr) is the submatrix sum
					prefixSums.insert(prefixSum);
				}
			}
		}

		Debug::Print2D<int>()(v, false);
		std::cout << "MaxSubMatrixSumNoGreaterThanK TwoD_SortedPrefixSums for the above matrix, K=\"" << K << "\": " << res << std::endl;
		return res;
	}

	int TwoD_SortedPrefixSums_2(const std::vector<std::vector<int>> & v, int K)//same thing, switch row with col, this passes online judge
	{
		int N = v.size();
		int M = v[0].size();
		int res = INT_MIN;
		for (int leftColX = 0; leftColX < M; ++leftColX)
		{
			std::vector<int> subMatrixSum(N, 0);
			for (int rightColX = leftColX; rightColX < M; ++rightColX)
			{
				for (int row = 0; row < N; ++row)
				{
					subMatrixSum[row] += v[row][rightColX];
				}

				std::set<int> prefixSums;
				int prefixSum = 0;
				prefixSums.insert(0);
				for (const auto & sum : subMatrixSum)
				{
					prefixSum += sum;
					auto itr = prefixSums.lower_bound(prefixSum - K);
					if (itr != prefixSums.end())
						res = std::max(res, prefixSum - *itr);
					prefixSums.insert(prefixSum);
				}
			}
		}

		return res;
	}
};
/*
[rY][cX]
Row#0	= 1, 0, 1
Row#1	= 0, -2, 3

[rY][cX]
Row#0	= 1, 1, 2
Row#1	= 1, -1, 3

MaxSubMatrixSumNoGreaterThanK TwoD_BruteForcePrefixSums for the above matrix, K="2": 2
[rY][cX]
Row#0	= 1, 0, 1
Row#1	= 0, -2, 3

MaxSubMatrixSumNoGreaterThanK TwoD_SortedPrefixSums for the above matrix, K="2": 2
*/
#endif
