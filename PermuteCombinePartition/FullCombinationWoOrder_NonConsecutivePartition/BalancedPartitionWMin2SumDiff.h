#ifndef BALANCED_PARTITION_W_MIN_2_SUM_DIFF_H
#define BALANCED_PARTITION_W_MIN_2_SUM_DIFF_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, DynamicProgramming: Divide the spoils fairly
http://www.careercup.com/question?id=10244832
http://people.cs.clemson.edu/~bcdean/dp_practice/
http://stackoverflow.com/questions/4212050/minimum-difference-between-sum-of-two-subsets
http://stackoverflow.com/questions/6454598/stuck-with-an-interview-question-partitioning-of-an-array
http://chinmaylokesh.wordpress.com/2011/02/10/balanced-partition-problem-finding-the-minimized-sum-between-two-partitions-of-a-set-of-positive-integers/
http://chinmaylokesh.wordpress.com/2011/01/24/algorithm-to-implement-equal-sum-partition-problem-for-a-sequence-of-numbers-find-a-subsetssame-order-as-original-sequence-in-which-each-subset-has-the-same-smallest-sum/
https://sites.google.com/site/mybravocode/algorithms-r/balanced-partition-problem
http://forums.codeguru.com/showthread.php?535049-Balanced-Partitioning-Dynamic-Programming-Problem

Given an array of N integers.
Divide the numbers into two subsets such that the difference between the sums of the 2 subsets is minimal.
NP-complete
(This problem is a special case of CombinationSum where the targetSum is totalSum/2.)
DP1D: pseudo-polynomial time, O(n * sum) time, O(sum) space

Variant: Solve the same problem with the additional constraint that the two subsets should have the same size.
http://www.geeksforgeeks.org/tug-of-war/
See also CombinationSum.h, Combinations.h, MinSumOf2IntFromADigitArr.h, MaxDiff2SubArraySum.h
*/
class BalancedPartitionWMin2SumDiff
{
public:
	BalancedPartitionWMin2SumDiff(){}
	~BalancedPartitionWMin2SumDiff(){}

	int DP1D(const std::vector<int> & v)
	{
		int N = v.size();
		int totalSum = 0;
		for (int i = 0; i < N; ++i)
			totalSum += v[i];
		std::vector<int> dp(totalSum + 1, 0);
		dp[0] = 1;//a sum of 0 is a combination sum of 0 element
		/*
		dp[i] == 1: i is a valid combination sum of any element(s) in the array
		dp[i] == 0: i is NOT a combination sum of any element(s) in the array
		*/

		int minHalfSumDiff = INT_MAX;
		int res;
		for (int i = 0; i < N; ++i)
		{
			for (int sum = totalSum; sum >= v[i]; --sum)//decrementing
			{
				/*
				if "sum-v[i]" is a valid combination sum,
				then "sum" must be another valid combination sum,
				because sum = v[i] + (sum-v[i]).
				*/
				dp[sum] = dp[sum] | dp[sum - v[i]];
				if (dp[sum] == 1)
				{
					/*compare if current combination sum is closest to totalSum/2*/
					if (minHalfSumDiff > std::abs(totalSum / 2 - sum))
					{
						minHalfSumDiff = std::abs(totalSum / 2 - sum);
						res = sum;
					}
				}
			}
		}
		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "BalancedPartitionWMin2SumDiff DP1D for \"" << Debug::ToStr1D<int>()(v) << "\": abs(" << res << "-" << totalSum - res << ")=" << std::abs(res - (totalSum - res)) << std::endl;
		return std::min(res, totalSum - res);
	}

	//Enumerate all combinations of subsets with half size of v. See also Combinations.h
	int EqualSized_Recur(const std::vector<int> & v)
	{
		int N = v.size();
		std::vector<int> path;
		std::vector<int> res;
		int totalSum = std::accumulate(v.cbegin(), v.cend(), 0);
		int minSumDiff = INT_MAX;
		this->recur(v, N / 2, 0, totalSum, 0, minSumDiff, path, res);
		std::cout << "BalancedPartitionWMin2SumDiff EqualSized_Recur for \"" << Debug::ToStr1D<int>()(v) << "\": " << minSumDiff << ", one subset: " << Debug::ToStr1D<int>()(res) << std::endl;
		return minSumDiff;
	}
private:
	void recur(const std::vector<int> & v, int count, int begin, const int & totalSum, int runningSum, int & minSumDiff, std::vector<int> & path, std::vector<int> & res)
	{
		if (count == 0)
		{
			int sum2 = totalSum - runningSum;
			if (std::abs(sum2 - runningSum) < minSumDiff)
			{
				minSumDiff = std::abs(sum2 - runningSum);
				res = path;
			}
			return;
		}

		int N = v.size();
		int end = N - 1 - count + 1;
		for (int i = begin; i <= end; ++i)
		{
			runningSum += v[i];
			path.push_back(v[i]);
			this->recur(v, count - 1, i + 1, totalSum, runningSum, minSumDiff, path, res);
			runningSum -= v[i];
			path.pop_back();
		}
	}
};
/*
1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1
BalancedPartitionWMin2SumDiff DP1D for "9, 16, 1, 4": abs(16-14)=2
1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1
BalancedPartitionWMin2SumDiff DP1D for "1, 5, 9, 3, 8": abs(13-13)=0
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
BalancedPartitionWMin2SumDiff DP1D for "1, 2, 3, 5, 10": abs(10-11)=1
1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1
BalancedPartitionWMin2SumDiff DP1D for "2, 10, 3, 8, 5, 7, 9, 5, 3, 2": abs(27-27)=0
BalancedPartitionWMin2SumDiff EqualSized_Recur for "9, 16, 1, 4": 4, one subset: 9, 4
BalancedPartitionWMin2SumDiff EqualSized_Recur for "1, 5, 9, 3, 8": 0, one subset: 5, 8
BalancedPartitionWMin2SumDiff EqualSized_Recur for "1, 2, 3, 5, 10": 1, one subset: 1, 10
BalancedPartitionWMin2SumDiff EqualSized_Recur for "2, 10, 3, 8, 5, 7, 9, 5, 3, 2": 0, one subset: 2, 10, 3, 5, 7
BalancedPartitionWMin2SumDiff EqualSized_Recur for "425, 180, 120, 110, 5, 4, 2, 1": 17, one subset: 425, 4, 2, 1
BalancedPartitionWMin2SumDiff EqualSized_Recur for "3": 3, one subset:
*/
#endif