#ifndef REVERSE_PAIRS_H
#define REVERSE_PAIRS_H
#include "Debug.h"
/*
Leetcode: Reverse Pairs
Given an array nums, we call (i, j) an important reverse pair if i < j and nums[i] > 2*nums[j].
You need to return the number of important reverse pairs in the given array.
Example1:
Input: [1,3,2,3,1]
Output: 2
Example2:
Input: [2,4,3,5,1]
Output: 3

MergeSort: O(nlogn) time
PrefixSums: O(n^2) time
BinaryIndexedTree: O(nlogn) time
SegmentTree: ?

see also InversionsInArray.h
*/
class ReversePairs
{
public:
	ReversePairs() {}

	int UseMergeSort(std::vector<int> & v)
	{
		int N = v.size();
		int res = 0;
		std::vector<int> tmp(N, 0);
		mergeSort(v, 0, N - 1, tmp, res);

		std::cout << "ReversePairs UseMergeSort for \"" << Debug::ToStr1D<int>()(v) << "\": " << res << std::endl;
		return res;
	}
private:
	void mergeSort(std::vector<int> & v, int left, int right, std::vector<int> & tmp, int & res)
	{
		if (left >= right) return;
		int mid = (left + right) / 2;
		mergeSort(v, left, mid, tmp, res);
		mergeSort(v, mid + 1, right, tmp, res);
		//now both left side and right side are sorted
		int i = left;
		int j = mid + 1;
		for (; i <= mid; ++i)//for each element i on left side
		{
			while (j <= right && v[i] / 2.0 > v[j])//advance satisfied elements j on right side
				++j;
			res += (j - 1) - (mid + 1) + 1;//accumulate distance [mid+1,j-1] on right side
		}
		//now merge
		i = left;
		j = mid + 1;
		int k = left;
		while (k <= right)
		{
			tmp[k++] = (j > right || (i <= mid && v[i] < v[j])) ? v[i++] : v[j++];
		}
		for (k = left; k <= right; ++k)
			v[k] = tmp[k];
	}
};
/*
ReversePairs UseMergeSort for "1, 1, 2, 3, 3": 2
ReversePairs UseMergeSort for "1, 2, 3, 4, 5": 3
*/
#endif
