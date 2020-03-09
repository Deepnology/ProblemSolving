#ifndef ALT_POS_NEG_NUM_ARRAY_H
#define ALT_POS_NEG_NUM_ARRAY_H
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "Debug.h"
#include "../SortSearchSelect/StablePartition.h"
/*
1.
http://www.geeksforgeeks.org/rearrange-array-alternating-positive-negative-items-o1-extra-space/
http://www.careercup.com/question?id=4748947486670848
Given an array, with positive and negative integers, arrange it in such a way that, positive numbers occupy even positions and negative numbers occupy odd position. 
All the remaining extra positive or negative integers should be stored at the end of the array. 
Remember, the elements of the array should remain in the same order.
O(n) time, O(1) space
2.
http://www.geeksforgeeks.org/rearrange-positive-and-negative-numbers-publish/
http://www.careercup.com/question?id=7892661
An array contains both positive and negative numbers in random order. 
Rearrange the array elements so that positive and negative numbers are placed alternatively. 
Number of positive and negative numbers need not be equal. 
If there are more positive numbers they appear at the end of the array. 
If there are more negative numbers, they too appear in the end of the array.
O(n) time, O(1) space
*/
class AltPosNegNumArray
{
public:
	AltPosNegNumArray(){}
	~AltPosNegNumArray(){}

	void Stable(std::vector<int> && A)//O(n) time
	{
		std::string before = Debug::ToStr1D<int>()(A);
		int N = A.size();

		int cur = 0;
		int curPos = 0;
		int curPosVal = 0;
		int nxtPos = 0;
		int nxtPosVal = 0;
		int curNeg = 0;
		int curNegVal = 0;
		int nxtNeg = 0;
		int nxtNegVal = 0;

		//1. init curPos, curPosVal, nxtPos, nxtPosVal, curNeg, curNegVal, nxtNeg, nxtNegVal with their first available values
		while (curPos < N && A[curPos] < 0) { ++curPos; }
		if (curPos < N)
			curPosVal = A[curPos];
		nxtPos = curPos + 1;
		while (nxtPos < N && A[nxtPos] < 0) { ++nxtPos; }
		if (nxtPos < N)
			nxtPosVal = A[nxtPos];

		while (curNeg < N && A[curNeg] > 0) { ++curNeg; }
		if (curNeg < N)
			curNegVal = A[curNeg];
		nxtNeg = curNeg + 1;
		while (nxtNeg < N && A[nxtNeg] > 0) { ++nxtNeg; }
		if (nxtNeg < N)
			nxtNegVal = A[nxtNeg];

		//2. alternatively assign pos and neg vals until cur/curPos/curNeg reaches end
		while (true)
		{
			//2.1 assign pos val
			if (cur < N && curPos < N)
				A[cur++] = curPosVal;
			else
				break;
			curPos = nxtPos;
			curPosVal = nxtPosVal;
			++nxtPos;
			while (nxtPos < N && A[nxtPos] < 0) { ++nxtPos; }
			if (nxtPos < N)
				nxtPosVal = A[nxtPos];
			
			//2.2 assign neg val
			if (cur < N && curNeg < N)
				A[cur++] = curNegVal;
			else
				break;
			curNeg = nxtNeg;
			curNegVal = nxtNegVal;
			++nxtNeg;
			while (nxtNeg < N && A[nxtNeg] > 0) { ++nxtNeg; }
			if (nxtNeg < N)
				nxtNegVal = A[nxtNeg];
		}
		std::cout << Debug::ToStr1D<int>()(A) << std::endl;
		std::cout << cur << std::endl;
		std::cout << curPos << "," << curPosVal << "," << nxtPos << "," << nxtPosVal << std::endl;
		std::cout << curNeg << "," << curNegVal << "," << nxtNeg << "," << nxtNegVal << std::endl;

		//3. assign the remaining pos or neg vals
		if (curPos == N)
		{
			while (cur < N && curNeg < N)
			{
				A[cur++] = curNegVal;
				curNeg = nxtNeg;
				curNegVal = nxtNegVal;
				++nxtNeg;
				while (nxtNeg < N && A[nxtNeg] > 0) { ++nxtNeg; }
				if (nxtNeg < N)
					nxtNegVal = A[nxtNeg];
			}
		}
		else if (curNeg == N)
		{
			while (cur < N && curPos < N)
			{
				A[cur++] = curPosVal;
				curPos = nxtPos;
				curPosVal = nxtPosVal;
				++nxtPos;
				while (nxtPos < N && A[nxtPos] < 0) { ++nxtPos; }
				if (nxtPos < N)
					nxtPosVal = A[nxtPos];
			}
		}

		std::cout << "AltPosNegNumArray Stable for \"" << before << "\": " << Debug::ToStr1D<int>()(A) << std::endl;
	}

	void StablePartition_ModifiedMergeSort(std::vector<int> && v)//O(nlogn) time
	{
		std::string before = Debug::ToStr1D<int>()(v);
		int N = v.size();
		StablePartition().ModifyMergeSort(v);

		int left = 0;
		int right = 0;
		while (right < N && v[right] < 0)
			++right;
		int rightBegin = right;

		std::vector<int> res(N);
		int i = 0;
		while (left < rightBegin || right < N)
			res[i++] = (right == N || (left < rightBegin && i % 2 == 1)) ? v[left++] : v[right++];

		res.swap(v);
		
		std::cout << "AltPosNegNumArray StablePartition_ModifiedMergeSort for \"" << before << "\": " << Debug::ToStr1D<int>()(v) << std::endl;
	}

	void UnStablePartition(std::vector<int> && A)
	{
		std::string before = Debug::ToStr1D<int>()(A);
		int N = A.size();

		/*partition with pivotVal = 0*/
		int curFrontCount = 0;
		for (int i = 0; i < N; ++i)
		{
			if (A[i] < 0)
				std::swap(A[i], A[curFrontCount++]);
		}
		//now all negative nubmers are in the front and positive numbers are in the back
		std::cout << Debug::ToStr1D<int>()(A) << std::endl;

		int left = 0;
		int right = curFrontCount;
		while (right < N && left < right && A[left] < 0)
		{
			std::swap(A[left], A[right]);
			left += 2;
			++right;
		}
		std::cout << "AltPosNegNumArray UnStablePartition for \"" << before << "\": " << Debug::ToStr1D<int>()(A) << std::endl;
	}

};
/*
2, -1, 4, -3, 5, -7, 6, -8, 9, 10, 11, 12
9
9,10,10,11
12,-8,13,-8
AltPosNegNumArray Stable for "-1, 2, -3, 4, 5, 6, -7, -8, 9, 10, 11, 12": 2, -1, 4, -3, 5, -7, 6, -8, 9, 10, 11, 12
StablePartition ModifyMergeSort for "-1, 2, -3, 4, 5, 6, -7, -8, 9, 10, 11, 12": -1, -3, -7, -8, 2, 4, 5, 6, 9, 10, 11, 12
AltPosNegNumArray StablePartition_ModifiedMergeSort for "-1, 2, -3, 4, 5, 6, -7, -8, 9, 10, 11, 12": 2, -1, 4, -3, 5, -7, 6, -8, 9, 10, 11, 12
-1, -3, -7, -8, 5, 6, 2, 4, 9, 10, 11, 12
AltPosNegNumArray UnStablePartition for "-1, 2, -3, 4, 5, 6, -7, -8, 9, 10, 11, 12": 5, -3, 6, -8, 2, -7, 4, -1, 9, 10, 11, 12
2, -1, 4, -3, 11, -5, -7, -8, -9, -10, 11, -12
6
12,11,13,11
5,-6,6,-7
AltPosNegNumArray Stable for "-1, 2, -3, 4, -5, -6, -7, -8, -9, -10, 11, -12": 2, -1, 4, -3, 11, -5, -6, -7, -8, -9, -10, -12
StablePartition ModifyMergeSort for "-1, 2, -3, 4, -5, -6, -7, -8, -9, -10, 11, -12": -1, -3, -5, -6, -7, -8, -9, -10, -12, 2, 4, 11
AltPosNegNumArray StablePartition_ModifiedMergeSort for "-1, 2, -3, 4, -5, -6, -7, -8, -9, -10, 11, -12": 2, -1, 4, -3, 11, -5, -6, -7, -8, -9, -10, -12
-1, -3, -5, -6, -7, -8, -9, -10, -12, 4, 11, 2
AltPosNegNumArray UnStablePartition for "-1, 2, -3, 4, -5, -6, -7, -8, -9, -10, 11, -12": 4, -3, 11, -6, 2, -8, -9, -10, -12, -1, -5, -7
1, -5, 7, -12, 9, -8, 15, 17, 18, 19, 20, -8
7
6,16,7,17
12,-8,13,-8
AltPosNegNumArray Stable for "1, 7, -5, 9, -12, 15, 16, 17, 18, 19, 20, -8": 1, -5, 7, -12, 9, -8, 15, 16, 17, 18, 19, 20
StablePartition ModifyMergeSort for "1, 7, -5, 9, -12, 15, 16, 17, 18, 19, 20, -8": -5, -12, -8, 1, 7, 9, 15, 16, 17, 18, 19, 20
AltPosNegNumArray StablePartition_ModifiedMergeSort for "1, 7, -5, 9, -12, 15, 16, 17, 18, 19, 20, -8": 1, -5, 7, -12, 9, -8, 15, 16, 17, 18, 19, 20
-5, -12, -8, 9, 7, 15, 16, 17, 18, 19, 20, 1
AltPosNegNumArray UnStablePartition for "1, 7, -5, 9, -12, 15, 16, 17, 18, 19, 20, -8": 9, -12, 7, -5, 15, -8, 16, 17, 18, 19, 20, 1
2, -1, 4, -3, 5, -7, 6, 8, 9
7
7,8,8,9
9,-7,10,-7
AltPosNegNumArray Stable for "-1, 2, -3, 4, 5, 6, -7, 8, 9": 2, -1, 4, -3, 5, -7, 6, 8, 9
StablePartition ModifyMergeSort for "-1, 2, -3, 4, 5, 6, -7, 8, 9": -1, -3, -7, 2, 4, 5, 6, 8, 9
AltPosNegNumArray StablePartition_ModifiedMergeSort for "-1, 2, -3, 4, 5, 6, -7, 8, 9": 2, -1, 4, -3, 5, -7, 6, 8, 9
-1, -3, -7, 4, 5, 6, 2, 8, 9
AltPosNegNumArray UnStablePartition for "-1, 2, -3, 4, 5, 6, -7, 8, 9": 4, -3, 5, -1, 6, -7, 2, 8, 9
*/
#endif