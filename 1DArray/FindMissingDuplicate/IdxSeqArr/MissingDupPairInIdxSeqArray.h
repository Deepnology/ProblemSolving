#ifndef MISSING_DUP_PAIR_IN_IDX_SEQ_ARRAY_H
#define MISSING_DUP_PAIR_IN_IDX_SEQ_ARRAY_H
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include "Debug.h"
/*
Leetcode: Set Mismatch
http://www.geeksforgeeks.org/find-a-repeating-and-a-missing-number/
Elements of programming interview, Searching: Find the duplicate and missing elements
Let A be an array containing n-1 integers, each in the set Zn = {0,1,...,n-1}.
Suppose exactly one element m in Zn is missing in A.
We can determine m in O(n) time and O(1) space by computing Sum(A), the sum of the elements in A.
The sum of all the elements in Zn is Sum(Zn) = n*(n-1)/2.
Hence, Sum(Zn) - Sum(A) equals the missing element m.
Similarly, if A contains n+1 elements drawn from the set Zn, whith exactly one element t appearing twice in A
, the element t will be equal to Sum(A)-Sum(Zn).

Now, the problem is:
Let A be an array of n integers in Zn, with exactly one element t appearing twice.
This implies exactly one element m in Zn is missing from A.
How would you compute t and m in O(n) time and O(1) space?

1. By Math
SumDiff = Sum(Zn) - Sum(A) = m - t ....................................(1)
SquareSumDiff = SquareSum(Zn) - SquareSum(A) = m^2 - t^2 ..............(2)

from (2)
m^2 - t^2 = (m+t) * (m-t)
m + t = (m^2-t^2) / (m-t) = SquareSumDiff/SumDiff .....................(3)

add (1) and (3)
m = (SquareSumDiff/SumDiff + SumDiff) / 2

subtract (1) to (3)
t = (SquareSumDiff/SumDiff - SumDiff) / 2

2. By XOR
*/
class MissingDupPairInIdxSeqArray
{
public:
	MissingDupPairInIdxSeqArray(){}
	~MissingDupPairInIdxSeqArray(){}

	std::pair<int, int> BySumNSquareSum(const std::vector<int> & v)
	{
		int N = v.size();
		int sumDiff = 0;
		int squareSumDiff = 0;
		for (int i = 0; i < N; ++i)
		{
			sumDiff += i - v[i];
			squareSumDiff += i * i - v[i] * v[i];
		}
		int dup = (squareSumDiff / sumDiff - sumDiff) / 2;
		int miss = (squareSumDiff / sumDiff + sumDiff) / 2;

		std::cout << "MissingDupPairInIdxSeqArray BySumNSquareSum for \"" << Debug::ToStr1D<int>()(v) << "\": " << miss << ", " << dup << std::endl;
		return{ dup, miss };
	}

	std::pair<int, int> ByXOR(const std::vector<int> & v)
	{
		int N = v.size();

		//1. XOR all "A[0]~A[N-1] and 0~N-1" nums to get miss^dup
		int xorOfMissAndDup = 0;
		for (int i = 0; i < N; ++i)
			xorOfMissAndDup ^= i ^ v[i];

		int rightmostDiffBitOfMissAndDup = xorOfMissAndDup & ~(xorOfMissAndDup - 1);//get the rightmost bit of xorOfMissAndDup (isolate rightmost set bit)

		//2. divide all "A[0]~A[N-1] and 0~N-1" nums into 2 sets
		//XOR all nums in each set separately, and the miss and dup will be in diff sets
		int missOrDup = 0;
		for (int i = 0; i < N; ++i)
		{
			if (i & rightmostDiffBitOfMissAndDup)
				missOrDup ^= i;

			if (v[i] & rightmostDiffBitOfMissAndDup)
				missOrDup ^= v[i];
		}

		bool isDup = false;
		for (int n : v)
		{
			if (n == missOrDup)
			{
				isDup = true;
				break;
			}
		}

		int dup = isDup ? missOrDup : missOrDup ^ xorOfMissAndDup;
		int miss = isDup ? missOrDup ^ xorOfMissAndDup : missOrDup;
		std::cout << "MissingDupPairInIdxSeqArray ByXOR for \"" << Debug::ToStr1D<int>()(v) << "\": " << miss << ", " << dup << std::endl;
		return{ dup, miss };
	}
};
/*
MissingDupPairInIdxSeqArray BySumNSquareSum for "9, 5, 2, 7, 3, 11, 1, 13, 14, 10, 7, 12, 4, 0, 6": 8, 7
MissingDupPairInIdxSeqArray ByXOR for "9, 5, 2, 7, 3, 11, 1, 13, 14, 10, 7, 12, 4, 0, 6": 8, 7
MissingDupPairInIdxSeqArray BySumNSquareSum for "9, 5, 2, 8, 3, 11, 1, 13, 14, 10, 0, 12, 4, 0, 6": 7, 0
MissingDupPairInIdxSeqArray ByXOR for "9, 5, 2, 8, 3, 11, 1, 13, 14, 10, 0, 12, 4, 0, 6": 7, 0
MissingDupPairInIdxSeqArray BySumNSquareSum for "9, 5, 2, 7, 3, 11, 1, 13, 14, 10, 8, 12, 4, 7, 6": 0, 7
MissingDupPairInIdxSeqArray ByXOR for "9, 5, 2, 7, 3, 11, 1, 13, 14, 10, 8, 12, 4, 7, 6": 0, 7
*/
#endif