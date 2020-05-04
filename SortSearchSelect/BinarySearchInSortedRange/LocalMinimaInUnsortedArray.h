#ifndef LOCAL_MINIMA_IN_UNSORTED_ARRAY_H
#define LOCAL_MINIMA_IN_UNSORTED_ARRAY_H
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include "Debug.h"
/*
Elements of programming interview, Searching: Search a sorted array for first occurrence of k, variant
http://www.dsalgo.com/2013/03/find-local-minima-in-array.html
http://www.careercup.com/question?id=8223978
Given an unsorted integer array A, with A[0] >= A[1] and A[N-2] <= A[N-1].
Call an index i a local minimum if A[i] is less than or equal to its neighbors.
How would you efficiently find a local minimum, if one exists?

If in an array of non-duplicate-adjacent integers first two numbers are decreasing and last two numbers are increasing, there ought to be a local minima.
We can do binary search to find out the local minima.
We will first check the mid index of the array.
If it is smaller than its left and right, then it is the answer.
If it is bigger than the left number then from start to left we have a subproblem
, and as we proved already that starting with decreasing and ending with increasing sequence array will have to have a local minima
, we can safely go to the left subarray.
Otherwise, if mid is bigger than its right, then we go to the right subarray.

For our implementation, we assume adjacent integers might have duplicates.

NonStrickly local minima: A[i] >= A[i-1] && A[i] >= A[i+1]
Strickly local minima: A[i] > A[i-1] && A[i] > A[i+1]

BinarySearch: O(logn) time
*/
class LocalMinimaInUnsortedArray
{
public:
	LocalMinimaInUnsortedArray(){}
	~LocalMinimaInUnsortedArray(){}

	int Index_NonStrickly_Iterate(const std::vector<int> & v)
	{
		int N = v.size();
		int left = 0;
		int right = N - 1;
		int res = -1;
		while (right - left > 1)//keep 3 entries between [left,right] inclusive
		{
			int mid = (left + right) / 2;
			std::cout << left << "," << right << " => " << mid << std::endl;
			if (mid < 1 || mid > N - 2)
				break;
			else if (v[mid] <= v[mid - 1] && v[mid] <= v[mid + 1])
			{
				res = mid;
				break;
			}
			else if (v[mid] < v[mid - 1])//since we want to find local min, abandon left side which contain a larger element
				left = mid;
			else
				right = mid;
		}
		
		std::cout << "LocalMinimaInUnsortedArray Index_NonStrickly_Iterate for \"" << Debug::ToStr1D<int>()(v) << "\" idx: " << res << ", [left,right]=[" << left << "," << right << "]" << std::endl;
		return res;
	}

	

	int Index_Strickly_AllowDup(const std::vector<int> & v)
	{
		int res = this->index_Strickly_AllowDup_Iterate(v);
		int res1 = this->index_Strickly_Recur(v, 0, v.size() - 1);
		int res2 = this->index_Strickly_Recur2(v, 0, v.size() - 1);
		int res3 = this->index_Strickly_Recur3(v, 0, v.size() - 1);
		int res4 = this->index_Strickly_Recur4(v, 0, v.size() - 1);
		std::cout << "LocalMinimaInUnsortedArray Index_Strickly_AllowDup for \"" << Debug::ToStr1D<int>()(v) << "\" idx: " << res << ". approach1: " << res1 << ". approach2: " << res2 << ". apporach3: " << res3 << ". approach4: " << res4 << std::endl;
		return res;
	}
private:
	int index_Strickly_AllowDup_Iterate(const std::vector<int> & v)
	{
		int N = v.size();
		int left = 0;
		int right = N - 1;
		int res = -1;
		while (right - left > 1)//keep 3 entries between [left,right] inclusive
		{
			int mid = (left + right) / 2;
			//std::cout << left << "," << right << " => " << mid << std::endl;
			if (mid < 1 || mid > N - 2)
				break;
			else if (v[mid] < v[mid - 1] && v[mid] < v[mid + 1])
			{
				res = mid;
				break;
			}
			else if (v[mid] < v[mid - 1])//since we want to find local min, abandon left side which contain a larger element
				left = mid;
			else
				right = mid;
		}
		return res;
	}
	int index_Strickly_Recur(const std::vector<int> & v, int left, int right)
	{
		if (right - left <= 1)//less than 3 entries between [left,right] inclusive
			return -1;
		int N = v.size();
		int mid = (left + right) / 2;
		if (mid < 1 || mid > N - 2)
			return -1;

		if (v[mid] < v[mid - 1] && v[mid] < v[mid + 1])
			return mid;

		if (v[mid] < v[mid - 1])//since we want to find local min, abandon left side which contain a larger element
			return this->index_Strickly_Recur(v, mid, right);
		else
			return this->index_Strickly_Recur(v, left, mid);
	}

	int index_Strickly_Recur2(const std::vector<int> & v, int left, int right)
	{
		if (right - left <= 1)//less than 3 entries between [left,right] inclusive
			return -1;
		int N = v.size();
		int mid = (left + right) / 2;
		if (mid < 1 || mid > N - 2)
			return -1;

		if (v[mid] < v[mid - 1] && v[mid] < v[mid + 1])
			return mid;

		if (v[mid] < v[mid - 1])//since we want to find local min, abandon left side which contain a larger element
			return this->index_Strickly_Recur(v, mid, right);
		else if (v[mid] < v[mid + 1])//since we want to find local min, abandon right side which contain a larger element
			return this->index_Strickly_Recur(v, left, mid);
		else//v[mid]>=v[mid-1] && v[mid]>=v[mid+1]
		{
			std::cout << "search both2 at v[" << mid << "] = " << v[mid] << std::endl;
			int lres = this->index_Strickly_Recur(v, left, mid);
			if (lres != -1)
				return lres;
			return this->index_Strickly_Recur(v, mid, right);
		}
	}

	int index_Strickly_Recur3(const std::vector<int> & v, int left, int right)
	{
		if (right - left <= 1)//less than 3 entries between [left,right] inclusive
			return -1;
		int N = v.size();
		int mid = (left + right) / 2;
		if (mid < 1 || mid > N - 2)
			return -1;

		if (v[mid] < v[mid - 1] && v[mid] < v[mid + 1])
			return mid;

		if (v[mid] > v[mid - 1])//since we want to find local min, branch to left side which contain a smaller element
			return this->index_Strickly_Recur(v, left, mid);
		else
			return this->index_Strickly_Recur(v, mid, right);
	}

	int index_Strickly_Recur4(const std::vector<int> & v, int left, int right)
	{
		if (right - left <= 1)//less than 3 entries between [left,right] inclusive
			return -1;
		int N = v.size();
		int mid = (left + right) / 2;
		if (mid < 1 || mid > N - 2)
			return -1;

		if (v[mid] < v[mid - 1] && v[mid] < v[mid + 1])
			return mid;

		if (v[mid] > v[mid - 1])//since we want to find local min, branch to left side which contain a smaller element
			return this->index_Strickly_Recur(v, left, mid);
		else if (v[mid] > v[mid + 1])//since we want to find local min, branch to right side which contain a smaller element
			return this->index_Strickly_Recur(v, mid, right);
		else//v[mid]<=v[mid-1] && v[mid]<=v[mid+1], but !(v[mid]<v[mid-1] && v[mid]<v[mid+1])
		{
			std::cout << "search both4 at v[" << mid << "] = " << v[mid] << std::endl;
			int lres = this->index_Strickly_Recur(v, left, mid - 1);
			if (lres != -1)
				return lres;
			return this->index_Strickly_Recur(v, mid + 1, right);
		}
	}
};
/*
0,15 => 7
7,15 => 11
LocalMinimaInUnsortedArray Index_NonStrickly_Iterate for "9, 7, 7, 2, 1, 3, 7, 5, 4, 7, 3, 3, 4, 8, 6, 9" idx: 11, [left,right]=[7,15]
0,15 => 7
7,15 => 11
11,15 => 13
LocalMinimaInUnsortedArray Index_NonStrickly_Iterate for "19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 7, 8" idx: 13, [left,right]=[11,15]
0,23 => 11
LocalMinimaInUnsortedArray Index_NonStrickly_Iterate for "19, 18, 17, 17, 16, 15, 14, 13, 13, 12, 12, 11, 11, 10, 10, 9, 8, 7, 7, 6, 6, 7, 7, 8" idx: 11, [left,right]=[0,23]
0,13 => 6
6,13 => 9
LocalMinimaInUnsortedArray Index_NonStrickly_Iterate for "9, 7, 2, 1, 3, 7, 5, 4, 7, 3, 4, 8, 6, 9" idx: 9, [left,right]=[6,13]
0,15 => 7
7,15 => 11
11,15 => 13
LocalMinimaInUnsortedArray Index_NonStrickly_Iterate for "19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 7, 8" idx: 13, [left,right]=[11,15]
0,17 => 8
8,17 => 12
12,17 => 14
12,14 => 13
LocalMinimaInUnsortedArray Index_NonStrickly_Iterate for "19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 7, 8, 17, 19" idx: 13, [left,right]=[12,14]
0,3 => 1
LocalMinimaInUnsortedArray Index_NonStrickly_Iterate for "8, 7, 7, 8" idx: 1, [left,right]=[0,3]
0,4 => 2
0,2 => 1
LocalMinimaInUnsortedArray Index_NonStrickly_Iterate for "8, 6, 9, 7, 8" idx: 1, [left,right]=[0,2]
0,4 => 2
LocalMinimaInUnsortedArray Index_NonStrickly_Iterate for "8, 6, 6, 6, 8" idx: 2, [left,right]=[0,4]
LocalMinimaInUnsortedArray Index_Strickly_AllowDup for "9, 7, 7, 2, 1, 3, 7, 5, 4, 7, 3, 3, 4, 8, 6, 9" idx: 8. approach1: 8. approach2: 8. apporach3: 8. approach4: 8
LocalMinimaInUnsortedArray Index_Strickly_AllowDup for "19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 7, 8" idx: 13. approach1: 13. approach2: 13. apporach3: 13. approach4: 13
search both4 at v[11] = 11
LocalMinimaInUnsortedArray Index_Strickly_AllowDup for "19, 18, 17, 17, 16, 15, 14, 13, 13, 12, 12, 11, 11, 10, 10, 9, 8, 7, 7, 6, 6, 7, 7, 8" idx: -1. approach1: -1. approach2: -1. apporach3: -1. approach4: -1
LocalMinimaInUnsortedArray Index_Strickly_AllowDup for "9, 7, 2, 1, 3, 7, 5, 4, 7, 3, 4, 8, 6, 9" idx: 9. approach1: 9. approach2: 9. apporach3: 9. approach4: 9
LocalMinimaInUnsortedArray Index_Strickly_AllowDup for "19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 7, 8" idx: 13. approach1: 13. approach2: 13. apporach3: 13. approach4: 13
LocalMinimaInUnsortedArray Index_Strickly_AllowDup for "19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 7, 8, 17, 19" idx: 13. approach1: 13. approach2: 13. apporach3: 13. approach4: 13
search both4 at v[1] = 7
LocalMinimaInUnsortedArray Index_Strickly_AllowDup for "8, 7, 7, 8" idx: -1. approach1: -1. approach2: -1. apporach3: -1. approach4: -1
search both2 at v[2] = 9
LocalMinimaInUnsortedArray Index_Strickly_AllowDup for "8, 6, 9, 7, 8" idx: 1. approach1: 1. approach2: 1. apporach3: 1. approach4: 1
search both2 at v[2] = 6
search both4 at v[2] = 6
LocalMinimaInUnsortedArray Index_Strickly_AllowDup for "8, 6, 6, 6, 8" idx: -1. approach1: -1. approach2: -1. apporach3: -1. approach4: -1
LocalMinimaInUnsortedArray Index_Strickly_AllowDup for "10, 9, 1, 5, 4, 8, 8, 2, 2, 3, 4, 2, 10, 7, 6, 3, 2, 9, 2, 5" idx: 4. approach1: 4. approach2: 4. apporach3: 4. approach4: 4
*/
#endif