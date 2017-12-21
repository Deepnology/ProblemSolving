/*MUST*/
#ifndef ALL_PAIRS_W_SMALLER_EQUAL_SUM_H
#define ALL_PAIRS_W_SMALLER_EQUAL_SUM_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
Google
http://www.careercup.com/question?id=5858156613730304
http://www.careercup.com/question?id=5908384326877184
Given an integer array and a target threshold.
Find all distinct pairs in the array whose sum is smaller equal than the target threshold.

Algorithm
Sort: O(nlon) time
1. sort the array in incr order
2. for each element from the smallest, binary search the lower bound of (target-v[i]) in v[i+1:N-1], and record pairs of v[i] and nums in v[i+1:lb]

QuickSelect: O(n) time in avg, O(n^2) time in worst case
1. find min in current range [0,N-1]
2. move "elements that plus min are smaller equal to target" to the left side of min, update pivot to min's idx after rearrange (partition)
3. collect all elements on pivot's left side together with pivot to form pairs
4. update next range as [0,pivot-1] and repeat until pivot <= 0
Recursively partitioning until end: O(n) + O(n/2) + O(n/4) + O(n/8) +.... = O(n) time
*/
class AllPairsWSmallerEqualSum
{
public:
	AllPairsWSmallerEqualSum(){}
	~AllPairsWSmallerEqualSum(){}

	std::vector<std::pair<int, int> > FindAll(std::vector<int> & v, int t)
	{
		int N = v.size();
		std::vector<std::pair<int, int> > res;
		int preMin_Pivot = N;
		do
		{
			/*
			1. find min in range v[0]~v[preMin_Pivot-1] as the pivot for partition
			*/
			int curMin = INT_MAX;
			int curMin_Pivot;
			for (int i = 0; i < preMin_Pivot; ++i)
				if (v[i] < curMin)
				{
					curMin = v[i];
					curMin_Pivot = i;
				}
			/*
			2. partition the range v[0]~v[preMin_Pivot-1] to move "the elements whose value plus pivot are smaller equal than target" on the left side of pivot, as the 1st group
			   pivot should be the 1st element of the 2nd group
			   return the index of the 1st element of the 2nd group, which is the current pivot, as the next boundary
			*/
			int nxtMin_Pivot = this->partition(v, 0, preMin_Pivot - 1, curMin_Pivot, t);

			/*record all pairs on pivot's left side*/
			for (int i = 0; i < nxtMin_Pivot; ++i)
				res.push_back(std::make_pair(v[nxtMin_Pivot], v[i]));

			/*
			3. update preMin_Pivot
			*/
			preMin_Pivot = nxtMin_Pivot;

		} while (preMin_Pivot > 0);

		std::cout << "AllPairsWSmallerEqualSum for \"" << t << "\", \"" << Debug::ToStr1D<int>()(v) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

private:
	int partition(std::vector<int> & v, int first, int last, int pivot, int sum)
	{
		int pivotVal = v[pivot];
		std::swap(v[pivot], v[last]);
		int left = first;
		int right = last - 1;
		while (left <= right)
		{
			if (v[left] + pivotVal <= sum)
				++left;
			else if (v[right] + pivotVal > sum)
				--right;
			else
				std::swap(v[left++], v[right--]);
		}
		std::swap(v[left], v[last]);
		return left;
	}
};
/*
AllPairsWSmallerEqualSum for "13", "7, 6, 8, 5, 9, 4, 10, 3, 11, 2, 12, 12, 1, 15, 16, 14, 17, 13": [1,10], [1,3], [1,7], [1,2], [1,4], [1,6], [1,9], [1,12], [1,8], [1,12], [1,5], [1,11], [2,10], [2,3], [2,7], [2,11], [2,4], [2,6], [2,9], [2,5], [2,8], [3,10], [3,8], [3,7], [3,5], [3,4], [3,6], [3,9], [4,6], [4,8], [4,7], [4,5], [4,9], [5,6], [5,8], [5,7], [6,7]
AllPairsWSmallerEqualSum for "7", "4, 3, 5, 2, 6, 1, 9, 12, 15, 12, 13, 11, 17, 8, 7, 14, 10, 16": [1,5], [1,3], [1,6], [1,2], [1,4], [2,5], [2,3], [2,4], [3,4]
*/
#endif