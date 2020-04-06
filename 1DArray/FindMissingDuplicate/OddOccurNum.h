#ifndef ODD_OCCUR_NUM_H
#define ODD_OCCUR_NUM_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "Debug.h"
#include "KeyGenAux.hpp"
/*
XOR of 0 and any number will result in that number.
XOR of all occurrences of a number which occur even number of times will result in 0.

1. Leetcode: Single Number
http://www.geeksforgeeks.org/find-the-number-occurring-odd-number-of-times/
Given an array of integers, every element appears twice (even times) except for one (odd times).
Find the number in linear time and constant space.

2.
http://www.geeksforgeeks.org/find-the-two-numbers-with-odd-occurences-in-an-unsorted-array/
http://www.geeksforgeeks.org/find-two-non-repeating-elements-in-an-array-of-repeating-elements/
Given an array of integers, evey number appears even times except two numbers (odd times).
Find the two numbers in linear time and constant space.

3. Leetcode: Single Number II
Elements of programming interview, Searching: Find an element that appears only once
http://www.geeksforgeeks.org/find-the-element-that-appears-once/
http://www.careercup.com/question?id=7902674 Google
Given an array of integers, every number appears three times except for one element which appears only once.
Find the number in linear time and constant space.

*/
class OddOccurNum
{
public:
	OddOccurNum(){}
	~OddOccurNum(){}

	int FindOneOddOccur_FromEvenOccurArray(const std::vector<int> & A)
	{
		int N = A.size();
		int res = 0;
		for (int i = 0; i < N; ++i)
			res ^= A[i];
		std::cout << "OddOccurNum FindOneOddOccur_FromEvenOccurArray for \"" << Debug::ToStr1D<int>()(A) << "\": " << res << std::endl;
		return res;
	}

	std::pair<int, int> FindTwoOddOccur_FromEvenOccurArray(const std::vector<int> & A)
	{
		int N = A.size();
		
		//1. XOR all "A[0]~A[N-1]" nums to get x^y
		int xorOf2OddOccur = A[0];
		for (int i = 1; i < N; ++i)
			xorOf2OddOccur ^= A[i];

		int oneSetBit = xorOf2OddOccur & ~(xorOf2OddOccur - 1);
		//oneSetBit is the rightmost set bit of xorOf2OddOccur bc it is easy to get (isolate rightmost set bit)

		//2. divide all "A[0]~A[N-1]" nums into 2 sets
		//XOR all nums in each set separately, and the 2 odd occurring nums will be in diff sets
		int x = 0;
		int y = 0;
		for (int i = 0; i < N; ++i)
		{
			if (A[i] & oneSetBit)//A[i]'s corresponding bit is "1"
				x ^= A[i];
			else//A[i]'s corresponding bit is "0"
				y ^= A[i];
		}

		std::cout << "OddOccurNum FindTwoOddOccur_FromEvenOccurArray for \"" << Debug::ToStr1D<int>()(A) << "\": " << x << ", " << y << std::endl;
		return std::make_pair(x, y);
	}

	int FindOneOccur_FromThreeOccurArray(const std::vector<int> & A)//better
	{
		int N = A.size();
		int curOneOccurBits = 0;
		int curTwoOccurBits = 0;
		
		for (int i = 0; i < N; ++i)
		{
			//std::ostringstream oss;
			//oss << i << ". " << KeyGenAux().UIntToBinStrTrunc(A[i]) << ": ";

			/*1. compute oneOccurBits, twoOccurBits, threeOccurBits*/
			curTwoOccurBits = curTwoOccurBits | (curOneOccurBits & A[i]);//(curOneOccurBits & A[i]) means prev one occur bits & A[i]
			curOneOccurBits ^= A[i];
			int curThreeOccurBits = curOneOccurBits & curTwoOccurBits;

			//oss << "[oneOccur,twoOccur,threeOccur] = [" << KeyGenAux().UIntToBinStrTrunc(curOneOccurBits) << "," << KeyGenAux().UIntToBinStrTrunc(curTwoOccurBits) << "," << KeyGenAux().UIntToBinStrTrunc(curThreeOccurBits) << "] => Remove Three Occur Bits";

			/*2. remove threeOccurBits from oneOccurBits and twoOccurBits*/
			int nonThreeOccurBitsFilter = ~curThreeOccurBits;
			curOneOccurBits &= nonThreeOccurBitsFilter;
			curTwoOccurBits &= nonThreeOccurBitsFilter;

			//oss << " => [" << KeyGenAux().UIntToBinStrTrunc(curOneOccurBits) << "," << KeyGenAux().UIntToBinStrTrunc(curTwoOccurBits) << "," << KeyGenAux().UIntToBinStrTrunc(curThreeOccurBits) << "]";
			//std::cout << oss.str() << std::endl;
		}
		std::cout << "OddOccurNum FindOneOccur_FromThreeOccurArray for \"" << Debug::ToStr1D<int>()(A) << "\": " << curOneOccurBits << std::endl;
		return curOneOccurBits;
	}
	int FindOneOccur_FromThreeOccurArray2(const std::vector<int> & A)//from elements of programming interview
	{
		int N = A.size();
		int ones = 0;//the set bits in this number represent those bits that have been visited for only once after modulo 3
		int twos = 0;//the set bits in this number represent those bits that have been visited for twice after modulo 3
		for (int i = 0; i < N; ++i)//perform modulo 3 for each bit of each num
		{
			int nextOnes = (~A[i] & ones) | (A[i] & ~ones & ~twos);//the bit of A[i] is 0 and the bit's accumulated modulo 3 is 1, OR, the bit of A[i] is 1 and the bit's accumulated modulo 3 is 0
			int nextTwos = (~A[i] & twos) | (A[i] & ones);//the bit of A[i] is 0 and the bit's accumulated modulo 3 is 2, OR, the bit of A[i] is 1 and the bit's accumulated modulo 3 is 1
			ones = nextOnes;
			twos = nextTwos;
		}

		std::cout << "OddOccurNum FindOneOccur_FromThreeOccurArray2 for\"" << Debug::ToStr1D<int>()(A) << "\": " << ones << std::endl;
		return ones;
	}
	int FindOneOccur_FromThreeOccurArray3(const std::vector<int> & A)
	{
		int N = A.size();
		int res = 0;

		/*
		1. count the occurrence of each bit from 0~31 among all the numbers in A
		O(32 * n) = O(n) time
		*/
		for (int i = 0; i < 32; ++i)
		{
			int curBitMask = 1 << i;
			int count = 0;
			for (int j = 0; j < N; ++j)
			{
				if (A[j] & curBitMask)
					++count;
			}

			/*2. if the occurrence of current bit is not a mulitple of 3, we insert this bit to the result*/
			if (count % 3)
				res |= curBitMask;
		}

		std::cout << "OddOccurNum FindOneOccur_FromThreeOccurArray3 for\"" << Debug::ToStr1D<int>()(A) << "\": " << res << std::endl;
		return res;
	}
};
/*
OddOccurNum FindOneOddOccur_FromEvenOccurArray for "2, 3, 5, 4, 5, 2, 4, 3, 5, 2, 4, 4, 2": 5
OddOccurNum FindTwoOddOccur_FromEvenOccurArray for "2, 3, 5, 4, 5, 2, 4, 3, 5, 2, 4, 2": 5, 4
OddOccurNum FindOneOccur_FromThreeOccurArray for "2, 1, 4, 5, 1, 4, 2, 2, 4, 1": 5
OddOccurNum FindOneOccur_FromThreeOccurArray2 for"2, 1, 4, 5, 1, 4, 2, 2, 4, 1": 5
OddOccurNum FindOneOccur_FromThreeOccurArray3 for"2, 1, 4, 5, 1, 4, 2, 2, 4, 1": 5
OddOccurNum FindOneOccur_FromThreeOccurArray for "3, 3, 2, 3": 2
OddOccurNum FindOneOccur_FromThreeOccurArray2 for"3, 3, 2, 3": 2
OddOccurNum FindOneOccur_FromThreeOccurArray3 for"3, 3, 2, 3": 2
*/
#endif