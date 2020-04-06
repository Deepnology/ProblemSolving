#ifndef BINARY_SEARCH_FIXED_POINT_H
#define BINARY_SEARCH_FIXED_POINT_H
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Searching: Search a sorted array for A[i] = i
variant: Solve the same problem when A is sorted but may contain duplicates.
Cracking the coding interview: Recursion
http://www.geeksforgeeks.org/find-a-fixed-point-in-a-given-array/
Given an array of n distinct integers sorted in ascending order, write a function that returns a Fixed Point in that array
, if there is any Fixed Point present in array, else, return -1.
Fixed Point in an array is an index i such that arr[i] is equal to i.

What if there are duplicates in the array?

Modification from normal binary search: just view the "target val" in binary search as the "middle index of left and right" when searching the fixed point

See also SearchInRotatedSortedArray.h
*/
class BinarySearchFixedPoint
{
public:
	BinarySearchFixedPoint(){}
	~BinarySearchFixedPoint(){}

	int Solve_NoDup_Iterate(const std::vector<int> & A)
	{
		int N = A.size();
		int left = 0;
		int right = N - 1;

		while (left <= right)//keep 1 entry between [left,right] inclusive
		{
			int middle = (left + right) / 2;
			if (A[middle] >= middle)
			{
				right = middle - 1;
			}
			else
			{
				left = middle + 1;
			}
		}
		//now left is the lower bound
		int resIdx = (left >= 0 && left <= N-1 && A[left] == left) ? left : -1;
		std::cout << "BinarySearchFixedPoint NoDup_Iterate for \"" << Debug::ToStr1D<int>()(A) << "\": " << resIdx << std::endl;
		return resIdx;
	}

	int Solve_AllowDup_Recur(const std::vector<int> & A)
	{
		int N = A.size();
		int res = this->recur(A, 0, N - 1);
		int res2 = this->recur2(A, 0, N - 1);
		std::cout << "BinarySearchFixedPoint AllowDup_Recur for \"" << Debug::ToStr1D<int>()(A) << "\": " << res << "(correct), " << res2 << "(might be incorrect)" << std::endl;
		return res;
	}
private:
	int recur(const std::vector<int> & A, int left, int right)
	{
		if (left > right || left < 0 || right > (int)A.size())//0 entries between [left,right] inclusive
			return -1;
		int mid = (left + right) / 2;
		int midVal = A[mid];
		if (midVal == mid)
			return mid;

		/*
		If not matched: we cannot tell "mid" is on the left side or on the right side of A[mid]
		so need to search both sides
		*/
		/*1. Search left side with skipping some elements*/
		int l = this->recur(A, left, std::min(mid - 1, midVal));
		if (l >= 0)
			return l;
		/*2. Search right side with skipping some elements*/
		int r = this->recur(A, std::max(mid + 1, midVal), right);
		return r;
	}

	int recur2(const std::vector<int> & A, int left, int right)//this approach might be incorrect
	{
		if (left > right || left < 0 || right >(int)A.size())//0 entries between [left,right] inclusive
			return -1;
		int mid = (left + right) / 2;
		int midVal = A[mid];
		if (midVal == mid)
			return mid;

		if (midVal > mid)//too big: go left
			return recur(A, left, std::min(mid - 1, midVal));
		else
			return recur(A, std::max(mid + 1, midVal), right);
	}
};
/*
BinarySearchFixedPoint NoDup_Iterate for "-40, -20, -1, 1, 2, 3, 5, 7, 9, 12, 13": 7
BinarySearchFixedPoint NoDup_Iterate for "-10, -5, 2, 2, 2, 3, 4, 8, 9, 12, 13": -1
BinarySearchFixedPoint NoDup_Iterate for "-10, -5, 1, 2, 5, 6, 7, 8, 8, 8, 12": -1
BinarySearchFixedPoint AllowDup_Recur for "-40, -20, -1, 1, 2, 3, 5, 7, 9, 12, 13": 7
BinarySearchFixedPoint AllowDup_Recur for "-10, -5, 2, 2, 2, 3, 4, 8, 9, 12, 13": 2
BinarySearchFixedPoint AllowDup_Recur for "-10, -5, 1, 2, 5, 6, 7, 8, 8, 8, 12": 8

BinarySearchFixedPoint NoDup_Iterate for "-2, -1, 2, 3, 5, 8, 9": 2
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, 4, 5, 6, 7, 9": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, 1, 5, 6, 8, 9": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, 0, 1, 2, 6, 8, 9": -1
BinarySearchFixedPoint NoDup_Iterate for "-2, 0, 2, 4, 5, 6, 9": 2
BinarySearchFixedPoint NoDup_Iterate for "0, 2, 3, 5, 6, 7, 9": 0
BinarySearchFixedPoint NoDup_Iterate for "-3, 1, 4, 5, 6, 8, 10": 1
BinarySearchFixedPoint NoDup_Iterate for "-3, -1, 2, 3, 4, 9, 10": 2
BinarySearchFixedPoint NoDup_Iterate for "-2, -1, 4, 5, 6, 8, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, 0, 3, 6, 7, 9": 3
BinarySearchFixedPoint NoDup_Iterate for "-2, -1, 0, 2, 5, 8, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "-2, -1, 0, 1, 5, 8, 9": -1
BinarySearchFixedPoint NoDup_Iterate for "-2, -1, 1, 2, 4, 7, 8": 4
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, 2, 4, 5, 6, 8": 2
BinarySearchFixedPoint NoDup_Iterate for "-2, 0, 2, 7, 8, 9, 10": 2
BinarySearchFixedPoint NoDup_Iterate for "-1, 0, 1, 3, 6, 9, 10": 3
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, -1, 4, 5, 7, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "-1, 0, 2, 6, 8, 9, 10": 2
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, 0, 2, 3, 5, 8": 5
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, -1, 0, 1, 3, 4": -1
BinarySearchFixedPoint NoDup_Iterate for "0, 1, 2, 4, 5, 7, 8": 0
BinarySearchFixedPoint NoDup_Iterate for "-2, 0, 1, 2, 4, 5, 9": 4
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, 3, 4, 6, 8, 9": -1
BinarySearchFixedPoint NoDup_Iterate for "-2, -1, 0, 6, 7, 8, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "3, 4, 5, 6, 7, 9, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "1, 2, 3, 4, 5, 6, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, -1, 5, 6, 7, 8, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "-1, 2, 3, 4, 5, 7, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "1, 2, 4, 7, 8, 9, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, 0, 2, 5, 6, 7": -1
BinarySearchFixedPoint NoDup_Iterate for "2, 3, 4, 6, 7, 8, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "-2, 0, 2, 4, 6, 8, 10": 2
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, 2, 6, 8, 9, 10": 2
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, -1, 0, 1, 6, 7": -1
BinarySearchFixedPoint NoDup_Iterate for "-2, 2, 3, 4, 5, 6, 8": -1
BinarySearchFixedPoint NoDup_Iterate for "-1, 2, 5, 6, 7, 8, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, 0, 2, 5, 7, 9, 10": 2
BinarySearchFixedPoint NoDup_Iterate for "0, 2, 3, 4, 5, 8, 10": 0
BinarySearchFixedPoint NoDup_Iterate for "-2, 3, 5, 6, 7, 8, 9": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, 1, 2, 6, 7, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, -1, 2, 4, 5, 6, 10": 2
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, -1, 0, 1, 3, 5": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, 0, 3, 4, 5, 6, 7": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, 0, 2, 5, 8, 9, 10": 2
BinarySearchFixedPoint NoDup_Iterate for "-2, -1, 0, 1, 4, 6, 7": 4
BinarySearchFixedPoint NoDup_Iterate for "-3, 0, 1, 2, 4, 9, 10": 4
BinarySearchFixedPoint NoDup_Iterate for "-2, -1, 1, 2, 3, 4, 6": 6
BinarySearchFixedPoint NoDup_Iterate for "-3, -1, 1, 2, 3, 8, 9": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, -1, 1, 4, 6, 8, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, 0, 4, 5, 8, 9, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "-1, 0, 2, 4, 5, 6, 8": 2
BinarySearchFixedPoint NoDup_Iterate for "-2, 0, 5, 6, 7, 8, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, 0, 1, 3, 4, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, -1, 1, 2, 4, 7": -1
BinarySearchFixedPoint NoDup_Iterate for "-2, 1, 2, 3, 6, 7, 8": 1
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, 4, 5, 8, 9, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, 0, 4, 5, 8, 9, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "-2, -1, 2, 4, 6, 8, 10": 2
BinarySearchFixedPoint NoDup_Iterate for "-2, 0, 1, 4, 6, 7, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, 2, 4, 5, 7, 8, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, -1, 3, 4, 5, 7, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "-2, 4, 5, 6, 7, 9, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, -1, 5, 6, 7, 9, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, 0, 3, 5, 6, 7, 9": -1
BinarySearchFixedPoint NoDup_Iterate for "-2, -1, 1, 3, 7, 9, 10": 3
BinarySearchFixedPoint NoDup_Iterate for "-2, 1, 2, 3, 5, 9, 10": 1
BinarySearchFixedPoint NoDup_Iterate for "-2, 1, 2, 7, 8, 9, 10": 1
BinarySearchFixedPoint NoDup_Iterate for "-2, -1, 0, 2, 3, 4, 9": -1
BinarySearchFixedPoint NoDup_Iterate for "-2, -1, 0, 3, 4, 7, 8": 3
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, -1, 2, 3, 6, 9": -1
BinarySearchFixedPoint NoDup_Iterate for "-2, 0, 1, 2, 3, 6, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "-2, -1, 0, 1, 2, 4, 9": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, 1, 3, 5, 7, 10": 3
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, -1, 3, 5, 8, 9": 3
BinarySearchFixedPoint NoDup_Iterate for "-1, 1, 2, 3, 5, 6, 9": 1
BinarySearchFixedPoint NoDup_Iterate for "-2, -1, 0, 2, 3, 4, 6": 6
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, -1, 3, 6, 9, 10": 3
BinarySearchFixedPoint NoDup_Iterate for "-2, 0, 2, 4, 7, 8, 10": 2
BinarySearchFixedPoint NoDup_Iterate for "-2, -1, 0, 2, 4, 5, 6": 4
BinarySearchFixedPoint NoDup_Iterate for "-2, -1, 1, 3, 7, 8, 9": 3
BinarySearchFixedPoint NoDup_Iterate for "-3, -1, 1, 3, 5, 7, 9": 3
BinarySearchFixedPoint NoDup_Iterate for "0, 1, 2, 5, 6, 8, 10": 0
BinarySearchFixedPoint NoDup_Iterate for "-3, -1, 2, 3, 5, 6, 7": 2
BinarySearchFixedPoint NoDup_Iterate for "-1, 1, 4, 7, 8, 9, 10": 1
BinarySearchFixedPoint NoDup_Iterate for "-1, 1, 2, 3, 6, 7, 10": 1
BinarySearchFixedPoint NoDup_Iterate for "-2, 0, 3, 6, 7, 9, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, -1, 0, 1, 5, 9": 5
BinarySearchFixedPoint NoDup_Iterate for "-2, -1, 0, 1, 3, 4, 7": -1
BinarySearchFixedPoint NoDup_Iterate for "-2, -1, 0, 2, 5, 6, 8": -1
BinarySearchFixedPoint NoDup_Iterate for "-1, 0, 1, 4, 5, 6, 8": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, 1, 5, 6, 8, 9": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, 2, 3, 5, 8, 10": 2
BinarySearchFixedPoint NoDup_Iterate for "2, 3, 4, 5, 6, 8, 9": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, 2, 3, 5, 7, 8, 10": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, 1, 2, 3, 4, 5, 6": 1
BinarySearchFixedPoint NoDup_Iterate for "-3, -1, 2, 3, 4, 5, 6": 2
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, 2, 4, 7, 8, 9": 2
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, -1, 2, 3, 6, 8": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, 0, 4, 5, 7, 8": -1
BinarySearchFixedPoint NoDup_Iterate for "-3, -2, -1, 2, 3, 7, 9": -1
BinarySearchFixedPoint AllowDup_Recur for "0, 0, 0, 3, 5, 6, 7": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "2, 3, 4, 4, 4, 4, 5": 4(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 3, 3, 5, 5, 6": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 0, 0, 2, 2, 4, 7": 0(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 1, 1, 2, 3, 7": 0(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 1, 1, 2, 3, 4": 0(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 1, 2, 3, 3, 6": 1(correct), 6(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 3, 3, 5, 5, 6, 7": 0(correct), 0(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 0, 2, 4, 6, 7, 7": 0(correct), 0(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "1, 1, 3, 3, 5, 6, 7": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 2, 2, 2, 4, 4": 1(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "1, 3, 3, 3, 3, 7, 7": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "2, 2, 2, 3, 4, 4, 6": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "3, 5, 6, 6, 6, 6, 6": 6(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 2, 2, 3, 6, 7": 1(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 0, 2, 4, 5, 5, 6": 0(correct), 0(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "2, 2, 3, 5, 7, 7, 7": -1(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 0, 0, 0, 2, 2, 5": 0(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 2, 3, 4, 5, 7": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "2, 2, 3, 4, 4, 5, 5": 5(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 0, 1, 2, 2, 4, 7": 0(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "1, 2, 3, 4, 7, 7, 7": -1(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "2, 5, 5, 5, 6, 7, 7": -1(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "2, 2, 2, 3, 4, 6, 6": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 0, 1, 5, 5, 7, 7": 0(correct), 0(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 1, 2, 4, 4, 5": 1(correct), 4(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 0, 0, 1, 1, 5, 6": 0(correct), 5(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 0, 0, 1, 2, 5, 6": 0(correct), 5(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 2, 2, 4, 6, 6": 1(correct), 4(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 1, 4, 4, 7, 7": 1(correct), 1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "1, 2, 4, 5, 7, 7, 7": -1(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "1, 1, 2, 2, 3, 7, 7": 1(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "2, 3, 3, 3, 3, 4, 5": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "2, 2, 3, 3, 6, 7, 7": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 1, 2, 4, 4, 6": 1(correct), 4(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 3, 5, 5, 6, 6": 1(correct), 1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "2, 2, 2, 3, 3, 3, 6": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 0, 2, 2, 3, 5, 7": 0(correct), 5(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "1, 1, 1, 3, 3, 4, 5": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "2, 3, 5, 6, 7, 7, 7": -1(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "1, 1, 2, 2, 3, 4, 5": 1(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 2, 2, 5, 5, 5, 7": 0(correct), 0(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "1, 2, 4, 4, 4, 5, 7": 5(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "1, 1, 3, 3, 5, 7, 7": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 2, 2, 5, 6, 7": 1(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "1, 3, 3, 3, 3, 7, 7": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "1, 1, 1, 3, 5, 5, 6": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 2, 2, 3, 4, 4, 7": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 0, 1, 2, 5, 6, 7": 0(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 2, 3, 3, 4, 6, 6": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 2, 3, 6, 7, 7": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 0, 2, 4, 6, 6, 7": 0(correct), 0(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 3, 6, 6, 6, 7": 1(correct), 1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "1, 1, 1, 3, 5, 6, 6": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 0, 4, 6, 6, 7, 7": 0(correct), 0(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "1, 1, 3, 3, 3, 5, 7": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 0, 1, 3, 3, 4, 7": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "1, 3, 4, 4, 4, 5, 6": 5(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 3, 4, 4, 5, 5, 7": 0(correct), 0(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 0, 1, 2, 2, 2, 2": 0(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "1, 1, 2, 4, 5, 6, 6": 1(correct), 1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 1, 3, 3, 4, 5": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 0, 0, 1, 2, 4, 7": 0(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 2, 2, 2, 4, 4": 1(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 1, 2, 2, 3, 6": 1(correct), 6(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 0, 1, 1, 1, 3, 4": 0(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "1, 3, 3, 5, 5, 7, 7": -1(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 2, 3, 4, 6, 6, 7": 0(correct), 0(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "1, 2, 3, 5, 6, 6, 6": 6(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "1, 2, 4, 5, 6, 6, 7": -1(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 2, 2, 3, 6, 7": 1(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 3, 4, 4, 6, 7, 7": 0(correct), 0(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 1, 2, 6, 7, 7": 1(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 2, 2, 5, 6, 6": 1(correct), 6(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "1, 2, 2, 4, 4, 6, 7": 2(correct), 2(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 0, 1, 2, 2, 4, 5": 0(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 2, 2, 5, 7, 7": 1(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "2, 2, 2, 5, 5, 7, 7": 2(correct), 2(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 2, 3, 4, 4, 6, 7": 0(correct), 0(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "2, 3, 3, 4, 4, 5, 6": 5(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 3, 3, 4, 4, 7": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 0, 3, 5, 5, 7, 7": 0(correct), 0(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 3, 3, 4, 6, 7": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "1, 1, 2, 2, 4, 5, 5": 1(correct), 5(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "2, 3, 4, 4, 6, 7, 7": -1(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 0, 2, 2, 4, 7, 7": 0(correct), 4(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 2, 2, 4, 5, 5, 7": 0(correct), 0(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "1, 2, 4, 4, 6, 6, 6": 6(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 2, 2, 2, 3, 6": 1(correct), 6(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "1, 4, 4, 5, 6, 7, 7": -1(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "3, 4, 5, 5, 6, 7, 7": -1(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "1, 2, 3, 3, 5, 6, 7": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 2, 2, 3, 3, 4, 6": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "1, 2, 2, 5, 5, 5, 5": 2(correct), 2(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 1, 3, 4, 5, 5, 5": 1(correct), 1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 0, 1, 2, 2, 4, 4": 0(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 2, 2, 2, 3, 4, 6": 0(correct), 6(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 2, 2, 3, 5, 5, 5": 3(correct), 3(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "1, 2, 5, 6, 6, 6, 7": -1(correct), -1(might be incorrect)
BinarySearchFixedPoint AllowDup_Recur for "0, 0, 2, 2, 4, 4, 4": 0(correct), 4(might be incorrect)
*/
#endif