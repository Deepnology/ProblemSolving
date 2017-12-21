#ifndef STABLE_PARTITION_H
#define STABLE_PARTITION_H
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Google
http://www.careercup.com/question?id=5201559730257920
http://slientcode.blogspot.tw/2012/05/partition-of-array.html
http://stones333.blogspot.tw/2013/10/algorithms-to-put-negatives-in-front-of.html
http://stackoverflow.com/questions/4897280/given-an-array-of-positive-and-negative-integers-re-arrange-it-so-that-you-have
Given an array with positive and negative numbers.
Rearrange the array so that all the negative numbers are in the front and all the positive numbers are in the back.
The relative order of each group should be preserved.

1. modification on merge sort: O(nlogn) linearithmic time, O(1) space
2. linear time with extra space: O(n) time, O(n) space
3. quadratic time: O(n^2) time, O(1) space
4. std::stable_partition: O(n) time, O(n) space; OR O(nlongn) time, O(1) space

*/
class StablePartition
{
public:
	StablePartition(){}
	~StablePartition(){}

	void ModifyMergeSort(std::vector<int> & A)
	{
		std::string before = Debug::ToStr1D<int>()(A);
		int N = A.size();
		this->modifyMergeSortRecur(A, 0, N - 1);
		std::cout << "StablePartition ModifyMergeSort for \"" << before << "\": " << Debug::ToStr1D<int>()(A) << std::endl;
	}
private:
	void modifyMergeSortRecur(std::vector<int> & A, int first, int last)
	{
		if (first >= last)//keep 2 entries in between [first,last] inclusive
			return;

		int middle = first + (last - first) / 2;
		this->modifyMergeSortRecur(A, first, middle);//since middle points to the left of central pair when there are even entries in total, middle should be included in the front group
		this->modifyMergeSortRecur(A, middle + 1, last);

		//now post order merge front and back groups, where both front and back groups are "negatives followed by positives"
		int posBegin = first;
		int negEnd = middle + 1;
		while (posBegin < middle + 1 && A[posBegin] < 0)
			++posBegin;
		//now posBegin points to the first positive element in the front group

		while (negEnd <= last && A[negEnd] < 0)
			++negEnd;
		--negEnd;
		//now negEnd points to the last negative element in the back group

		if (posBegin < middle + 1 && negEnd > middle)//if there are positives in front group and negatives in back group
		{
			int backNegCount = negEnd - (middle + 1) + 1;
			//before: A1A2B1B2 (A1: front negative, A2: front positive, B1: back negative, B2: back positive)
			this->reverse(A, posBegin, negEnd);//reverse A2B1. now: A1B1'A2'B2 (B1': reverse of B1, A2': reverse of A2)
			this->reverse(A, posBegin, posBegin + backNegCount - 1);//reverse B1. now: A1B1A2'B2
			this->reverse(A, posBegin + backNegCount, negEnd);//reverse A2. now: A1B1A2B2
		}
	}
	void reverse(std::vector<int> & A, int first, int last)
	{
		int N = A.size();
		if (first < 0 || last >= N)
			return;
		while (first < last)
			std::swap(A[first++], A[last--]);
	}

public:
	void QuadraticTime(std::vector<int> & A)
	{
		std::string before = Debug::ToStr1D<int>()(A);
		int N = A.size();
		int negCount = 0;//points to the next positive of negatives
		int posCount = 0;//points to the next negative of positives
		while (true)
		{
			while (negCount < N && A[negCount] < 0)
				++negCount;
			if (negCount == N)
				break;
			posCount = negCount;
			while (posCount < N && A[posCount] >= 0)
				++posCount;
			if (posCount == N)
				break;
			for (int i = posCount; i > negCount; --i)//move A[posCount], which is a negative, to negCount, and shift all positives to right (similar to InsertionSort)
				std::swap(A[i - 1], A[i]);
		}
		std::cout << "StablePartition QuadraticTime for \"" << before << "\": " << Debug::ToStr1D<int>()(A) << std::endl;
	}

	void LinearTimeLinearSpace(std::vector<int> & A)
	{
		std::string before = Debug::ToStr1D<int>()(A);
		std::vector<int> tempPositives;
		int N = A.size();

		/*save all positive numbers*/
		for (int i = 0; i < N; ++i)
			if (A[i] >= 0)
				tempPositives.push_back(A[i]);

		/*shift all negative numbers to the front side (similar to partition)*/
		int curFrontCount = 0;
		for (int i = 0; i < N; ++i)
		{
			if (A[i] < 0)
			{
				//copy this negative to the next of front consecutive negatives
				A[curFrontCount++] = A[i];
			}
		}

		/*copy all positive numbers back to A*/
		for (int i = curFrontCount; i < N; ++i)
		{
			A[i] = tempPositives[i - curFrontCount];
		}

		std::cout << "StablePartition LinearTimeLinearSpace for \"" << before << "\": " << Debug::ToStr1D<int>()(A) << std::endl;
	}

	void STL(std::vector<int> & A)
	{
		std::string before = Debug::ToStr1D<int>()(A);
		std::stable_partition(A.begin(), A.end(),
			[](const int & i)->bool{return i < 0; });
		std::cout << "StablePartition STL for \"" << before << "\": " << Debug::ToStr1D<int>()(A) << std::endl;
	}
};
/*
StablePartition ModifyMergeSort for "1, -1, 2, 3, -5, -2, 9, 3, -4": -1, -5, -2, -4, 1, 2, 3, 9, 3
StablePartition ModifyMergeSort for "-1, 1, 3, -2, 2": -1, -2, 1, 3, 2
StablePartition QuadraticTime for "1, -1, 2, 3, -5, -2, 9, 3, -4": -1, -5, -2, -4, 1, 2, 3, 9, 3
StablePartition LinearTimeLinearSpace for "1, -1, 2, 3, -5, -2, 9, 3, -4": -1, -5, -2, -4, 1, 2, 3, 9, 3
StablePartition STL for "1, -1, 2, 3, -5, -2, 9, 3, -4": -1, -5, -2, -4, 1, 2, 3, 9, 3
*/
#endif