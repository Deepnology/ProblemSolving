#ifndef _KTH_SMALLEST_ELEMENT_H
#define _KTH_SMALLEST_ELEMENT_H
#include <iostream>
#include <random>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
#include "Partition.h"
#include "MedianOfMedians.h"
/*
Leetcode: Kth Largest Element In An Array
Elements of programming interview, Searching: Find the k-th largest element
Design an algorithm for computing the k-th largest element in an array A that runs in O(n) expected time.
variant:
Design an algorithm for finding the k-th largest element of A in the presence of duplicates.
The k-th largest element is defined to be A[k-1] after A has been sorted in a stable manner, i.e., if A[i] = A[j] and i < j then A[i] must appear before A[j] after stable sorting.
See also StablePartition.h
http://www.ardendertat.com/2011/10/27/programming-interview-questions-10-kth-largest-element-in-array/
http://www.quora.com/Algorithms/What-is-the-most-efficient-algorithm-to-find-the-kth-smallest-element-in-an-array-having-n-elements#
http://www.careercup.com/question?id=4356905
(input array is NOT sorted)
K-th: index starting from 1
1. Sort in non-descending order and count first K elements: O(nlogn) time, O(1) space
2. Using a max heap to keep track of K smallest elements: O(nlogK) time, O(K) space
3. Quick Select: O(n + n/2 + n/4 + ...) time, Average O(n) time, Worst case O(n^2) time
(Quick Sort recurses into both sides with O(nlogn) time, but Quick Select recurses into only one side with O(n) time)
4. Quick Select with Median Of Medians: Worst case O(n) time

Once the K-th smallest element can be found with O(n) time, all those elements that are smaller than the K-th smallest element can be found with one scan, which yields overall O(n) time.
*/
class KthSmallestElement
{
public:
	KthSmallestElement(){}
	~KthSmallestElement(){}
	//1.1. Quick Select Iterate
	int QuickSelectIterate(int A[], int n, int K)//K: 1-based
	{
		if (K < 1 || K > n)
			throw (std::runtime_error("KthSmallestElement QuickSelectIterate K out of bound"));
		std::string before = Debug::ToStr1D<int>()(A, n);
		int Kbefore = K;

		int lo = 0;
		int hi = n - 1;
		int res = INT_MIN;
		while (lo <= hi)
		{
			int mid = (lo + hi) / 2;

			/*
			partition the array in the range [lo, hi] to rearrange elements smaller than A[mid] on left side of elements equal to or greater than A[mid]
			also make sure the first element of the second group is the smallest element of the second group
			*/

			/*
			method 1. use my implementation of partition which guarantees the first element of the second group is the smallest element of the second group
			*/
			//int pivot = Partition().SmallerThanPivot(A, lo, hi, mid);

			/*
			method 2. use std::partition, which returns an iterator to the first element of the second group
			since std::partition doesn't guarantee the first element of the second group is the smallest,
			we need to scan the second group and swap the smallest element with the first element, which is the pivot
			*/
			int pivotVal = A[mid];
			int pivot = std::partition(A + lo, A + hi + 1, [&](const int & a)->bool
			{
				return a < pivotVal;
			}) - A;
			for (int i = pivot; i <= hi; ++i)
			{
				if (!(A[pivot] < A[i]))
					std::swap(A[pivot], A[i]);
			}

			/*
			method 3. use std::nth_element, which guarantees our pivot is in the correct position of sorting the entire array,
			and none of the elements preceding nth are greater than it, and none of the elements following it are less
			*/
			//std::nth_element(A + lo, A + mid, A + hi + 1, [](const int & a, const int & b)
			//{
			//	return a < b;
			//});
			//int pivot = mid;


			if (K < pivot - lo + 1)
				hi = pivot - 1;
			else if (K > pivot - lo + 1)
			{
				K -= (pivot - lo + 1);
				lo = pivot + 1;
			}
			else
			{
				res = A[pivot];
				break;
			}
		}
		std::cout << "KthSmallestElement QuickSelectIterate for \"" << Kbefore << "\"-th in \"" << before << "\": " << res << " (" << Debug::ToStr1D<int>()(A, n) << ")" << std::endl;
		return res;
	}

	//1.2. Quick Select Recur
	int QuickSelectRecur(int A[], int n, int K)//K: 1-based
	{
		if (K < 1 || K > n)
			throw (std::runtime_error("KthSmallestElement QuickSelectRecur K out of bound"));
		std::string before = Debug::ToStr1D<int>()(A, n);
		int res = this->quickSelectRecur(A, 0, n - 1, K);
		std::cout << "KthSmallestElement QuickSelectRecur for \"" << K << "\"-th in \"" << before << "\": " << res << " (" << Debug::ToStr1D<int>()(A, n) << ")" << std::endl;
		return res;
	}
	int quickSelectRecur(int A[], int first, int last, int K)//K can be viewed as the length of A at the target element
	{
		int pivot = (first + last) / 2;
		pivot = Partition().SmallerThanPivot(A, first, last, pivot);//O(last - first + 1) time

		//K < length of [ A[first],A[pivot] ]
		if (K < pivot - first + 1)
			return this->quickSelectRecur(A, first, pivot - 1, K);

		//K > length of [ A[first],A[pivot] ]
		else if (K > pivot - first + 1)
			return this->quickSelectRecur(A, pivot + 1, last, K - (pivot - first + 1));

		//K == length of [ A[first],A[pivot] ]
		else
			return A[pivot];
	}

public:
	//2.1. Median Of Medians Select Iterate
	int MedianOfMediansSelectIterate(int A[], int n, int K)//K: 1-based
	{
		if (K < 1 || K > n)
			throw (std::runtime_error("KthSmallestElement MedianOfMediansSelectIterate K out of bound"));

		std::string before = Debug::ToStr1D<int>()(A, n);
		int Kbefore = K;

		int lo = 0;
		int hi = n - 1;
		int res = INT_MIN;
		while (lo <= hi)
		{
			int pivotVal = MedianOfMedians().GetValue_Recur(A, lo, hi);
			int pivot = Partition().SmallerThanPivotVal2(A, lo, hi, pivotVal);
			if (K < pivot - lo + 1)
				hi = pivot - 1;
			else if (K > pivot - lo + 1)
			{
				K -= (pivot - lo + 1);
				lo = pivot + 1;
			}
			else
			{
				res = A[pivot];
				break;
			}
		}
		std::cout << "KthSmallestElement MedianOfMediansSelectIterate for \"" << Kbefore << "\"-th in \"" << before << "\": " << res << " (" << Debug::ToStr1D<int>()(A, n) << ")" << std::endl;
		return res;
	}

	//2.2. Median Of Medians Select Recur
	int MedianOfMediansSelectRecur(int A[], int n, int K)//K: 1-based
	{
		if (K < 1 || K > n)
			throw (std::runtime_error("KthSmallestElement MedianOfMediansSelectRecur K out of bound"));
		std::string before = Debug::ToStr1D<int>()(A, n);
		int res = this->medianOfMediansSelectRecur(A, 0, n - 1, K);
		std::cout << "KthSmallestElement MedianOfMediansSelectRecur for \"" << K << "\"-th in \"" << before << "\": " << res << " (" << Debug::ToStr1D<int>()(A, n) << ")" << std::endl;
		return res;
	}
	int medianOfMediansSelectRecur(int A[], int first, int last, int K)//K can be viewed as the length of A at the target element
	{
		int pivotVal = MedianOfMedians().GetValue_Recur(A, first, last);
		int pivot = Partition().SmallerThanPivotVal2(A, first, last, pivotVal);

		//K < length of [ A[first],A[pivot] ]
		if (K < pivot - first + 1)
			return this->medianOfMediansSelectRecur(A, first, pivot - 1, K);

		//K > length of [ A[first],A[pivot] ]
		else if (K > pivot - first + 1)
			return this->medianOfMediansSelectRecur(A, pivot + 1, last, K - (pivot - first + 1));

		//K == length of [ A[first],A[pivot] ]
		else
			return A[pivot];
	}

	//3. STL Nth Element
	int STL_Nth_Element(std::vector<int> && A, int K)//K: 1-based
	{
		int n = A.size();
		if (K < 1 || K > n)
			throw (std::runtime_error("KthSmallestElement STL_Nth_Element K out of bound"));
		std::string before = Debug::ToStr1D<int>()(A);

		std::nth_element(A.begin(), A.begin() + (K - 1), A.end(), std::less<int>());

		std::cout << "KthSmallestElement STL_Nth_Element for \"" << K << "\"-th in " << before << "\": " << A[K - 1] << " (" << Debug::ToStr1D<int>()(A) << ")" << std::endl;
		return A[K - 1];
	}
};



//older
class KthSmallestElement2
{
public:
	KthSmallestElement2(){}
	~KthSmallestElement2(){}

	int GO_MedianOfMedians(int A[], int n, int K)
	{
		if (K < 1 || K > n)//K-th: starting from 1 to n
			throw (std::runtime_error("KthSmallestElement2 K out of bound"));
		std::string before = Debug::ToStr1D<int>()(A, n);
		int res = this->findKthRecur2(A, 0, n - 1, K);
		std::cout << "KthSmallestElement2 MedianOfMedians for \"" << K << "\"-th in \"" << before << "\": " << res << std::endl;
		return res;
	}

	int findKthRecur2(int A[], int left, int right, int K)
	{
		int length = right - left + 1;

		//1. if length <= 5, make a separate copy of the array and sort it, return the median of the elements
		if (length <= 5)
		{
			std::vector<int> tmp(A + left, A + right + 1);//begin, end
			std::sort(tmp.begin(), tmp.end(), std::less<int>());
			return tmp[K - 1];
		}

		//2. if length > 5, find the medians array of the elements
		int numMedians = length / 5;
		int remainings = length % 5;//0-4
		std::vector<int> medians;
		for (int i = 0; i <= numMedians; ++i)
		{
			int next_left;
			int next_right;
			int next_k;
			if (i < numMedians)
			{
				next_left = left + 5 * i;
				next_right = left + 5 * (i+1) - 1;
				next_k = 3;
				
				int median = this->findKthRecur2(A, next_left, next_right, next_k);
				medians.push_back(median);
			}
			else if (i == numMedians)
			{
				if (remainings == 0)
				{
					//should skip this
				}
				else//1-4
				{
					next_left = left + 5 * i;
					next_right = next_left + remainings - 1;//next_right should be next_left + 0-3
					next_k = remainings / 2 + 1;
					
					int median = this->findKthRecur2(A, next_left, next_right, next_k);
					medians.push_back(median);
				}
			}
		}

		//3. find median of medians array recursively
		int medians_k = medians.size() / 2 + 1;
		int pivotVal = this->findKthRecur2(&medians[0], 0, medians.size() - 1, medians_k);

		//4. use median of medians array as the pivot to partition (move elements based on the pivot)
		int pivotIndex = this->partition(A, left, right, pivotVal);
		//int pivotIndex = Partition().SmallerThanPivotVal(A, left, right, pivot);

		//5. continue to find Kth smallest element with pivot's left or right array recursively
		int rank = pivotIndex - left + 1;
		if (K <= rank)
		{
			return this->findKthRecur2(A, left, pivotIndex, K);
		}
		else
		{
			return this->findKthRecur2(A, pivotIndex + 1, right, K - rank);
		}
	}
private:
	int partition(int A[], int left, int right, int pivot)
	{
		int swapIndex = left;
		for (int i = left; i <= right; ++i)
		{
			if (A[i] < pivot)
			{
				std::swap(A[swapIndex], A[i]);
				++swapIndex;
			}
		}
		return swapIndex - 1;
	}
};
/*
QuickSort for "3, 9, 8, 7, 6, -5, -5, 13, -2, -1, -7, -9, 5, 4, 4, 11, 2, 12, 1, 14, 20, 19, 17, 16, 18, -3, -4, -6, 21, 11, 13, 15, 16, 24" is: -9, -7, -6, -5, -5, -4, -3, -2, -1, 1, 2, 3, 4, 4, 5, 6, 7, 8, 9, 11, 11, 12, 13, 13, 14, 15, 16, 16, 17, 18, 19, 20, 21, 24
KthSmallestElement QuickSelectRecur for "18"-th in "3, 9, 8, 7, 6, -5, -5, 13, -2, -1, -7, -9, 5, 4, 4, 11, 2, 12, 1, 14, 20, 19, 17, 16, 18, -3, -4, -6, 21, 11, 13, 15, 16, 24": 8 (-6, -4, -3, 1, -9, -5, -5, -7, -2, -1, 2, 3, 4, 4, 7, 5, 6, 8, 9, 11, 11, 12, 13, 13, 14, 15, 16, 16, 17, 18, 19, 20, 24, 21)
KthSmallestElement QuickSelectRecur for "11"-th in "10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0": 10 (1, 2, 3, 4, 0, 5, 7, 8, 6, 9, 10)
KthSmallestElement QuickSelectRecur for "1"-th in "7": 7 (7)
KthSmallestElement QuickSelectIterate for "18"-th in "3, 9, 8, 7, 6, -5, -5, 13, -2, -1, -7, -9, 5, 4, 4, 11, 2, 12, 1, 14, 20, 19, 17, 16, 18, -3, -4, -6, 21, 11, 13, 15, 16, 24": 8 (-6, -4, -3, 1, -9, -5, -5, -7, -2, -1, 2, 3, 4, 6, 5, 4, 7, 8, 9, 11, 11, 12, 13, 13, 14, 16, 16, 15, 17, 21, 18, 19, 20, 24)
KthSmallestElement QuickSelectIterate for "11"-th in "10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0": 10 (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
KthSmallestElement QuickSelectIterate for "1"-th in "7": 7 (7)
KthSmallestElement STL_Nth_Element for "18"-th in 3, 9, 8, 7, 6, -5, -5, 13, -2, -1, -7, -9, 5, 4, 4, 11, 2, 12, 1, 14, 20, 19, 17, 16, 18, -3, -4, -6, 21, 11, 13, 15, 16, 24": 8 (-9, -7, -6, -5, -5, -4, -3, -2, -1, 1, 2, 3, 4, 4, 5, 6, 7, 8, 9, 11, 11, 12, 17, 16, 18, 13, 14, 20, 21, 19, 13, 15, 16, 24)
KthSmallestElement STL_Nth_Element for "11"-th in 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0": 10 (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
KthSmallestElement STL_Nth_Element for "1"-th in 7": 7 (7)
KthSmallestElement MedianOfMediansSelectRecur for "18"-th in "3, 9, 8, 7, 6, -5, -5, 13, -2, -1, -7, -9, 5, 4, 4, 11, 2, 12, 1, 14, 20, 19, 17, 16, 18, -3, -4, -6, 21, 11, 13, 15, 16, 24": 8 (3, -5, -5, -2, -1, -7, -9, 2, 1, -3, -4, -6, 4, 4, 5, 6, 7, 8, 13, 14, 12, 11, 9, 11, 13, 15, 16, 19, 21, 17, 18, 20, 16, 24)
KthSmallestElement MedianOfMediansSelectIterate for "18"-th in "3, 9, 8, 7, 6, -5, -5, 13, -2, -1, -7, -9, 5, 4, 4, 11, 2, 12, 1, 14, 20, 19, 17, 16, 18, -3, -4, -6, 21, 11, 13, 15, 16, 24": 8 (3, -5, -5, -2, -1, -7, -9, 2, 1, -3, -4, -6, 4, 4, 5, 6, 7, 8, 13, 14, 12, 11, 9, 11, 13, 15, 16, 19, 21, 17, 18, 20, 16, 24)
KthSmallestElement2 MedianOfMedians for "18"-th in "3, 9, 8, 7, 6, -5, -5, 13, -2, -1, -7, -9, 5, 4, 4, 11, 2, 12, 1, 14, 20, 19, 17, 16, 18, -3, -4, -6, 21, 11, 13, 15, 16, 24": 8
KthSmallestElement QuickSelectRecur for "37"-th in "40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1": 37 (2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1, 21, 23, 24, 25, 26, 27, 28, 29, 30, 31, 22, 32, 34, 35, 36, 33, 37, 39, 40, 38)
KthSmallestElement QuickSelectIterate for "37"-th in "40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1": 37 (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40)
KthSmallestElement MedianOfMediansSelectRecur for "37"-th in "40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1": 37 (27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40)
KthSmallestElement MedianOfMediansSelectIterate for "37"-th in "40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1": 37 (27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40)
KthSmallestElement2 MedianOfMedians for "37"-th in "40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1": 37
*/
#endif

