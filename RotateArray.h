#ifndef ROTATE_ARRAY_H
#define ROTATE_ARRAY_H
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
https://leetcode.com/problems/rotate-array/
Elements of programming interview, Array: Rotate an array
http://www.geeksforgeeks.org/array-rotation/
Rotate an array of size N by D elements to the left.
1. temp array: O(n) time, O(d) space
2. rotate one by one: O(n*d) time, O(1) space
3. a juggling algorithm (move sets): O(n) time, O(1) space
4. swap and reverse 2 subarr: O(n) time, O(1) space

Move sets
When GCD == 1
Left rotate 5 for the following array with size 8:
index:		0 1 2 3 4 | 5 6 7 8 9 | 10 11 12
array:		1 2 3 4 5 | 6 7 8 _ _ | __ __ __
nxt right5:	0 5 2 7 4 | 1 6 3
			8
res:		6 7 8 1 2 | 3 4 5


When GCD >= 2
Left rotate 2 for the following array with size 8:
index:		0 1 | 2 3 | 4 5 | 6 7 | 8 9 |
array:		1 2 | 3 4 | 5 6 | 7 8 | _ _ |
nxt right2:	0     1     2     3
			4
			  0     1     2     3
			  4
res:		3 4 | 5 6 | 7 8 | 1 2


see also RotatedStr.h, MinLexicographicStrRotation.h, CircularQueueByArray.h
*/
class RotateArray
{
public:
	RotateArray(){}
	~RotateArray(){}

	//2. rotate one by one
public:
	void ToLeft_OneByOne(std::vector<int> & A, int D)
	{
		std::string before = Debug::ToStr1D<int>()(A);
		int N = A.size();
		D %= N;
		for (int i = 0; i < D; ++i)
			this->LeftRotateByOne(A);
		std::cout << "RotateArray ToLeft_OneByOne for \"" << D << "\" in \"" << before << "\": " << Debug::ToStr1D<int>()(A) << std::endl;
	}
private:
	void LeftRotateByOne(std::vector<int> & A)
	{
		int N = A.size();
		int tmp = A[0];
		for (int i = 0; i < N - 1; ++i)
			A[i] = A[i + 1];
		A[N - 1] = tmp;
	}

	//3. a juggling algorithm
public:
	void ToLeft_MoveSets(std::vector<int> & A, int D)
	{
		std::string before = Debug::ToStr1D<int>()(A);
		int N = A.size();
		D %= N;
		int GCD = this->GCD_Recur(D, N);
		
		//2 cases: there will be at lest 2 sets without remainings when GCD >= 2, otherwise, there will be only one set with all elements are remainings when GCD == 1
		//for each element in the first set
		for (int i = 0; i < GCD; ++i)
		{
			int tmp = A[i];//save the i-th element in first set
			int curSetIdx = i;//the i-th element index in curSet
			while (true)
			{
				int nxtSetIdx = curSetIdx + D;//right shifted D of curSetIdx: the i-th element index in nxtSet
				if (nxtSetIdx >= N)
					nxtSetIdx = nxtSetIdx - N;//the extra index after N: the rotated right shifted D positions of curSetIdx in the first set
				//must be the i-th element in the first set when GCD >= 2,
				//otherwise, may or may not be the 0-th element in the first set when GCD == 1

				if (nxtSetIdx == i)
					break;

				A[curSetIdx] = A[nxtSetIdx];//move element: to left when GCD >= 2, otherwise, to left or to right when GCD == 1
				curSetIdx = nxtSetIdx;//advance curSetIdx: to right when GCD >= 2, otherwise, left or to right when GCD == 1
			}
			A[curSetIdx] = tmp;//move the i-th element in first set: to right to the last set when GCD >= 2, otherwise, move the 0-th element to right in the first set
		}
		std::cout << "RotateArray ToLeft_MoveSets for \"" << D << "\" in \"" << before << "\": " << Debug::ToStr1D<int>()(A) << std::endl;
	}
private:
	int GCD_Recur(int a, int b)//Greatest Common Divisor 最大公因數
	{
		if (b == 0)
			return a;
		else
			return this->GCD_Recur(b, a%b);
	}

	//4. swap and reverse 2 subarrays
public:
	void ToLeft_SwapReverse2Subarr(std::vector<int> & A, int D)
	{
		std::string before = Debug::ToStr1D<int>()(A);
		int N = A.size();
		D %= N;
		int len2ndPart = N - D;
		std::reverse(A.begin(), A.end());//reverse all: the 2nd part is now on left side, and the 1st part is now on right side
		std::reverse(A.begin(), A.begin() + len2ndPart);//reverse the 2nd part
		std::reverse(A.begin() + len2ndPart, A.end());//reverse the 1st part

		std::cout << "RotateArray ToLeft_SwapReverse2Subarr for \"" << D << "\" in \"" << before << "\": " << Debug::ToStr1D<int>()(A) << std::endl;
	}



	//Rotate To Right...
	void ToRight_MoveSets(std::vector<int> & A, int D)
	{
		std::string before = Debug::ToStr1D<int>()(A);
		int N = A.size();
		D %= N;
		int GCD = this->GCD_Recur(D, N);

		for (int i = 0; i < GCD; ++i)
		{
			int tmp = A[i];
			int curSetIdx = i;
			while (true)
			{
				int nxtSetIdx = curSetIdx - D;
				if (nxtSetIdx < 0)
					nxtSetIdx = nxtSetIdx + N;

				if (nxtSetIdx == i)
					break;

				A[curSetIdx] = A[nxtSetIdx];
				curSetIdx = nxtSetIdx;
			}
			A[curSetIdx] = tmp;
		}
		std::cout << "RotateArray ToRight_MoveSets for \"" << D << "\" in \"" << before << "\": " << Debug::ToStr1D<int>()(A) << std::endl;
	}
	void ToRight_SwapReverse2Subarr(std::vector<int> & A, int D)
	{
		std::string before = Debug::ToStr1D<int>()(A);
		int N = A.size();
		D %= N;
		int len2ndPart = D;
		std::reverse(A.begin(), A.end());//reverse all: the 2nd part is now on left side, and the 1st part is now on right side
		std::reverse(A.begin(), A.begin() + len2ndPart);//reverse the 2nd part
		std::reverse(A.begin() + len2ndPart, A.end());//reverse the 1st part

		std::cout << "RotateArray ToRight_SwapReverse2Subarr for \"" << D << "\" in \"" << before << "\": " << Debug::ToStr1D<int>()(A) << std::endl;
	}
};
/*
RotateArray ToLeft_OneByOne for "5" in "1, 2, 3, 4, 5, 6, 7": 6, 7, 1, 2, 3, 4, 5
RotateArray ToLeft_OneByOne for "6" in "1, 2, 3, 4, 5, 6, 7": 7, 1, 2, 3, 4, 5, 6
RotateArray ToLeft_MoveSets for "5" in "1, 2, 3, 4, 5, 6, 7": 6, 7, 1, 2, 3, 4, 5
RotateArray ToLeft_MoveSets for "6" in "1, 2, 3, 4, 5, 6, 7": 7, 1, 2, 3, 4, 5, 6
RotateArray ToLeft_MoveSets for "5" in "1, 2, 3, 4, 5, 6, 7, 8": 6, 7, 8, 1, 2, 3, 4, 5
RotateArray ToLeft_MoveSets for "2" in "1, 2, 3, 4, 5, 6, 7, 8": 3, 4, 5, 6, 7, 8, 1, 2
RotateArray ToLeft_SwapReverse2Subarr for "5" in "1, 2, 3, 4, 5, 6, 7": 6, 7, 1, 2, 3, 4, 5
RotateArray ToLeft_SwapReverse2Subarr for "6" in "1, 2, 3, 4, 5, 6, 7": 7, 1, 2, 3, 4, 5, 6
RotateArray ToLeft_SwapReverse2Subarr for "5" in "1, 2, 3, 4, 5, 6, 7, 8": 6, 7, 8, 1, 2, 3, 4, 5
RotateArray ToLeft_SwapReverse2Subarr for "2" in "1, 2, 3, 4, 5, 6, 7, 8": 3, 4, 5, 6, 7, 8, 1, 2
RotateArray ToRight_MoveSets for "5" in "1, 2, 3, 4, 5, 6, 7": 3, 4, 5, 6, 7, 1, 2
RotateArray ToRight_MoveSets for "6" in "1, 2, 3, 4, 5, 6, 7": 2, 3, 4, 5, 6, 7, 1
RotateArray ToRight_MoveSets for "5" in "1, 2, 3, 4, 5, 6, 7, 8": 4, 5, 6, 7, 8, 1, 2, 3
RotateArray ToRight_MoveSets for "2" in "1, 2, 3, 4, 5, 6, 7, 8": 7, 8, 1, 2, 3, 4, 5, 6
RotateArray ToRight_SwapReverse2Subarr for "5" in "1, 2, 3, 4, 5, 6, 7": 3, 4, 5, 6, 7, 1, 2
RotateArray ToRight_SwapReverse2Subarr for "6" in "1, 2, 3, 4, 5, 6, 7": 2, 3, 4, 5, 6, 7, 1
RotateArray ToRight_SwapReverse2Subarr for "5" in "1, 2, 3, 4, 5, 6, 7, 8": 4, 5, 6, 7, 8, 1, 2, 3
RotateArray ToRight_SwapReverse2Subarr for "2" in "1, 2, 3, 4, 5, 6, 7, 8": 7, 8, 1, 2, 3, 4, 5, 6
*/
#endif