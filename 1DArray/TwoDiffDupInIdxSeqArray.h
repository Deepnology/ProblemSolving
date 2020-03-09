#ifndef TWO_DIFF_DUP_IN_IDX_SEQ_ARRAY_H
#define TWO_DIFF_DUP_IN_IDX_SEQ_ARRAY_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include "Debug.h"
/*
Leetcode: Single Number III
Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice.
Find the two elements that appear only once.
For example: Given nums = [1, 2, 1, 3, 2, 5], return [3, 5].
(XOR all nums[i] to get xorOfThe2Nums. Isolate the rightmost set bit of xorOfThe2Nums. Divide all nums[i] into 2 groups. XOR all nums[i] in each group to get the 2 nums, respectively.)

http://www.geeksforgeeks.org/find-the-two-repeating-elements-in-a-given-array/
Given an array of n elements.
All elements in the array are in the range of 1~(n-2).
All elements occur once except two elements which occur twice.
(2 extra duplicates without missing elements in the range of 1~(n-2))
Find the two duplicates.

1. Use XOR: O(n) time, O(1) space
(XOR all v[i] and i to get xorOfTwoDups. Isolate the rightmost set bit. Dividt all v[i] and i into 2 groups. XOR all v[i] and i in each group to get the 2 dups.)
see also OddOccurNum.h, SingleDupInIdxSeqArray.h

2. Make 2 equations: O(n) time, O(1) space
this method might cause addition and multiplication overflow problems

(the following methods also work for multiple duplicates)

3. MarkNegative: O(n) time, O(1) space
see also MultiDupInIdxSeqArray.h

4. BruteForce: O(n^2) time, O(1) space
std::vector<int> res;
for (i = 0; i < N; ++i)
	for (j = i; j < N; ++j)
		if (A[i] == A[j])
			res.push_back(A[i]);

5. CountArray: O(n) time, O(n) space
std::vector<int> countArray(N-1, 0);
for (i = 0; i < N; ++i)
if (countArray[A[i]] == 1)
	return A[i];
else
	++countArray[A[i]];
*/
class TwoDiffDupInIdxSeqArray
{
public:
	TwoDiffDupInIdxSeqArray(){}
	~TwoDiffDupInIdxSeqArray(){}

	std::pair<int, int> Find_XOR(const std::vector<int> & A)
	{
		int N = A.size();

		//1. XOR all "A[0]~A[N-1] and 1~N-2" nums to get dup1^dup2
		int xorOfNonDups = 0;
		for (int i = 0; i < N; ++i)
			xorOfNonDups ^= A[i];

		int xorOfTwoDups = xorOfNonDups;
		for (int i = 1; i <= N - 2; ++i)
			xorOfTwoDups ^= i;

		int rightmostDiffBitOfTwoDups = xorOfTwoDups & ~(xorOfTwoDups - 1);//get the rightmost bit of xorOfTwoDups (isolate rightmost set bit)

		//2. divide all "A[0]~A[N-1] and 1~N-2" nums into 2 sets
		//XOR all nums in each set separately, and the dup1 and dup2 will be in diff sets
		int xorOfNonDups_set1 = 0;
		int xorOfNonDups_set2 = 0;
		for (int i = 0; i < N; ++i)
		{
			if (rightmostDiffBitOfTwoDups & A[i])
				xorOfNonDups_set1 ^= A[i];
			else
				xorOfNonDups_set2 ^= A[i];
		}

		int dup1 = xorOfNonDups_set1;
		int dup2 = xorOfNonDups_set2;
		for (int i = 1; i <= N - 2; ++i)
		{
			if (rightmostDiffBitOfTwoDups & i)
				dup1 ^= i;
			else
				dup2 ^= i;
		}

		std::cout << "TwoDiffDupInIdxSeqArray XOR for \"" << Debug::ToStr1D<int>()(A) << "\": " << dup1 << ", " << dup2 << std::endl;
		return std::make_pair(dup1, dup2);
	}
};
/*
TwoDiffDupInIdxSeqArray XOR for "4, 2, 4, 5, 2, 3, 1": 2, 4
*/
#endif