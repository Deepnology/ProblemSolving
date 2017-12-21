#ifndef H_INDEX_H
#define H_INDEX_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: H-Index
Given an array of citations (each citation is a non-negative integer) of a researcher, write a function to compute the researcher's h-index.
According to the definition of h-index on Wikipedia: "A scientist has index h if h of his/her N papers have at least h citations each, and the other N-h papers have no more than h citations each."
For example, given citations = [3, 0, 6, 1, 5], which means the researcher has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations respectively.
Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, his h-index is 3.
Note: If there are several possible values for h, the maximum one is taken as the h-index.
Hint:
An easy approach is to sort the array first.
What are the possible values of h-index?
A faster approach is to use extra space.

See also MaxNumWLeastGreaterEqualCount.h

Leetcode: H-Index II
Follow up for H-Index: What if the citations array is sorted in ascending order? Could you optimize your algorithm?
Hint:
Expected runtime complexity is in O(log n) and the input is sorted.
*/
class HIndex
{
public:
	HIndex() {}
	~HIndex() {}

	//I. O(nlogn) time
	int Sort_LinearScan(std::vector<int> & citations)
	{
		int N = citations.size();
		std::sort(citations.begin(), citations.end());//sort in ascending order
		int h = 0;//default is 0 if not found
		for (int i = 0; i < N; ++i)//find the max count of papers whose citations are >= paper count
		{
			if (citations[i] >= N - i)//(N-i) is the count of papers whose citations are >= (N-i)
			{
				h = N - i;
				break;
			}
		}

		std::cout << "H-Index Sort_LinearScan for \"" << Debug::ToStr1D<int>()(citations) << "\": " << h << std::endl;
		return h;
	}
	//O(n) time
	int LinearTimeExtraSpace(std::vector<int> & citations)
	{
		int N = citations.size();
		std::vector<int> cnt(N + 1, 0);//index: citation number, value: number of papers
		for (int i = 0; i < N; ++i)
			++cnt[citations[i] > N ? N : citations[i]];//for citation number greater than N: count in at cnt[N]

		int h = 0;
		int numPapers = 0;//accumulated number of papers from highest citation
		for (int i = 0; i < N; ++i)
		{
			numPapers += cnt[N - i];
			if (numPapers >= N - i)//(N-i) is the count of papers whose citations are >= (N-i)
			{
				h = N - i;
				break;
			}
		}

		std::cout << "H-Index LinearTimeExtraSpace (UseBuckets) for \"" << Debug::ToStr1D<int>()(citations) << "\": " << h << std::endl;
		return h;
	}
	//QuickSelect: O(n) time const space
	//partition the nums that are greater than pivotVal to left side
	//we want to maximize the count of nums in left side where each num is >= count of nums in left side
	int QuickSelect(std::vector<int> & citations)
	{
		int N = citations.size();
		if (N == 0) return 0;
		int h = 0;
		int left = 0;
		int right = N - 1;
		while (left <= right)
		{
			int mid = left + (right - left) / 2;
			std::nth_element(citations.begin() + left, citations.begin() + mid, citations.begin() + right + 1, [&](const int & a, const int & b) { return a > b; });
			int pivot = mid;//now pivot points to the greatest num in 2nd group, and all nums in 1st group are greater than pivotVal
			if (pivot + 1 <= citations[pivot])
			{
				h = std::max(h, pivot + 1);
				left = pivot + 1;
			}
			else
			{
				right = pivot - 1;
			}
		}

		std::cout << "H-Index QuickSelect for \"" << Debug::ToStr1D<int>()(citations) << "\": " << h << std::endl;
		return h;
	}

	//II.
	int BinarySearch(const std::vector<int> & sortedCitations)//citations is already sorted in ascending order
	{
		int N = sortedCitations.size();
		if (N == 0) return 0;

		//we want to find the first i such that "sortedCitations[i] >= N-i" from left: find the lower bound

		int lo = 0;
		int hi = N - 1;
		while (lo <= hi)
		{
			int mid = lo + (hi - lo) / 2;
			if (sortedCitations[mid] >= N - mid)
				hi = mid - 1;
			else
				lo = mid + 1;
		}
		//now lo is the lower bound

		int h = 0;//default is 0 if not found
		if (sortedCitations[lo] >= N - lo)
			h = N - lo;

		std::cout << "H-Index BinarySearch for \"" << Debug::ToStr1D<int>()(sortedCitations) << "\": " << h << std::endl;
		return h;
	}
	int BinarySearch2(const std::vector<int> & sortedCitations)//citations is already sorted in ascending order
	{
		int N = sortedCitations.size();
		if (N == 0) return 0;

		//we want to find the first i such that "sortedCitations[i] >= N-i" from left: find the lower bound

		int lo = -1;
		int hi = N;
		while (hi - lo > 1)//keep 3 entries
		{
			int mid = lo + (hi - lo) / 2;
			if (sortedCitations[mid] >= N - mid)
				hi = mid;
			else
				lo = mid;
		}
		//now hi is the lower bound

		int h = 0;//default is 0 if not found
		if (sortedCitations[hi] >= N - hi)
			h = N - hi;
		
		std::cout << "H-Index BinarySearch2 for \"" << Debug::ToStr1D<int>()(sortedCitations) << "\": " << h << std::endl;
		return h;
	}
};
/*
H-Index Sort_LinearScan for "0, 1, 3, 5, 6": 3
H-Index LinearTimeExtraSpace (UseBuckets) for "3, 0, 6, 1, 5": 3
H-Index QuickSelect for "6, 5, 3, 1, 0": 3
H-Index BinarySearch for "0, 1, 3, 5, 6": 3
H-Index BinarySearch2 for "0, 1, 3, 5, 6": 3
*/
#endif
