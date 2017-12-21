#ifndef	MIN_EQUAL_SUM_SUB_ARR_PARTITION_H
#define MIN_EQUAL_SUM_SUB_ARR_PARTITION_H
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include "Debug.h"
/*
http://chinmaylokesh.wordpress.com/2011/01/24/algorithm-to-implement-equal-sum-partition-problem-for-a-sequence-of-numbers-find-a-subsetssame-order-as-original-sequence-in-which-each-subset-has-the-same-smallest-sum/
Given an array of integers.
Partition the array such that each subarray has equal smallest sum.
Worst case: cannot be partitioned into equal sum subarrays, then the min subarray sum is the total sum of the array

BruteForce:
enumerate all possible consecutive partitions, test each consecutive partition has equal subarray sum, find the partition that has min equal subarray sum
see also AllSubArrayPartitions.h

Greedy: O(n^2) time
check if any prefix sum is divisible by the total sum and is a valid equal sum partition
*/
class MinEqualSumSubArrPartition
{
public:
	MinEqualSumSubArrPartition(){}
	~MinEqualSumSubArrPartition(){}

	int Greedy(const std::vector<int> & v)
	{
		int N = v.size();
		int totalSum = 0;
		for (int i = 0; i < N; ++i)
			totalSum += v[i];
		
		bool partitionable = false;
		int minSubarrSum = 0;

		//we want to partition into at least 2 subarrays with a minSubarrSum, so minSubarrSum is at most totalSum/2
		//start accumulate minSubarrSum from left with length 1, once found a first minSubarrSum that is valid from the rest entries, we are done
		for (int i = 0; i < N && minSubarrSum <= totalSum / 2; ++i)
		{
			minSubarrSum += v[i];
			if (totalSum % minSubarrSum == 0)//minSubarrSum is divisible for totalSum
			{
				/*now check if minSubarrSum is valid for the remaining elements of v*/
				bool validForRemainings = false;
				int minSubarrSum2 = 0;
				for (int j = i + 1; j < N; ++j)
				{
					minSubarrSum2 += v[j];
					if (minSubarrSum2 > minSubarrSum)
						break;//fail
					else if (minSubarrSum2 == minSubarrSum)
						minSubarrSum2 = 0;//reset
				}
				if (minSubarrSum2 == 0)
					validForRemainings = true;
				/**/

				if (validForRemainings)
				{
					partitionable = true;
					break;
				}
			}
		}
		if (!partitionable)
			minSubarrSum = totalSum;

		/*now collect subarrays*/
		std::vector<std::vector<int> > res;
		std::vector<int> subarr;
		int curSum = 0;
		for (int i = 0; i < N; ++i)
		{
			curSum += v[i];
			subarr.push_back(v[i]);
			if (curSum == minSubarrSum)
			{
				curSum = 0;
				res.push_back(subarr);
				subarr.clear();
			}
		}

		Debug::Print2D<int>()(res, false);
		std::cout << "MinEqualSumSubArrPartition Greedy for \"" << Debug::ToStr1D<int>()(v) << "\": " << minSubarrSum << std::endl;
		return minSubarrSum;
	}
};
/*
[rY][cX]
Row#0	= 3, 1, 3
Row#1	= 7,  ,
Row#2	= 5, 2,

MinEqualSumSubArrPartition Greedy for "3, 1, 3, 7, 5, 2": 7
[rY][cX]
Row#0	= 3, 1, 3, 6, 6, 2

MinEqualSumSubArrPartition Greedy for "3, 1, 3, 6, 6, 2": 21
[rY][cX]
Row#0	= 3, 2, 7, 1, 5, 3

MinEqualSumSubArrPartition Greedy for "3, 2, 7, 1, 5, 3": 21
*/
#endif