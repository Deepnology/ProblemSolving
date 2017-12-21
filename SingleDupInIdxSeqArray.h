#ifndef SINGLE_DUP_IN_IDX_SEQ_ARRAY_H
#define SINGLE_DUP_IN_IDX_SEQ_ARRAY_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include "Debug.h"
/*
http://www.keithschwarz.com/interesting/code/?dir=find-duplicate
Leetcode: Find the Duplicate Number
Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist.
Assume that there is only one duplicate number, find the duplicate one.

Note:
You must not modify the array (assume the array is read only).
You must use only constant, O(1) extra space.
Your runtime complexity should be less than O(n^2).
There is only one duplicate number in the array, but it could be repeated more than once.

Prove:
each element ranges from 1 to n, inclusive
it means there are totally n different values
if we have an array of n+1 elements, one must necessarily be duplicated
(1 extra duplicate without missing element in the range of 1~n)

1. LinkedListCycleBegin: O(n) time, O(1) space
see also LinkedListCycle.h

2. Use XOR: O(n) time, O(1) space (for the case of single duplicate only)
see also OddOccurNum.h

3. Make 2 equations: O(n) time, O(1) space
this method might cause addition and multiplication overflow problems

(the following methods also work for multiple duplicates)

4. MarkNegative: O(n) time, O(1) space
see also MultiDupInIdxSeqArray.h

5. BruteForce: O(n^2) time, O(1) space
enumerate all possible pairs in the array
std::vector<int> res;
for (i = 0; i < N; ++i)
	for (j = i; j < N; ++j)
		if (A[i] == A[j])
			res.push_back(A[i]);

6. CountArray: O(n) time, O(n) space
(similar to counting sort)
std::vector<int> countArray(N-1, 0);
for (i = 0; i < N; ++i)
if (countArray[A[i]] == 1)
	return A[i];
else
	++countArray[A[i]];
*/
class SingleDupInIdxSeqArray
{
public:
	SingleDupInIdxSeqArray(){}
	~SingleDupInIdxSeqArray(){}

	int Find_CycleBegin(const std::vector<int> & v)//v contains only 1 duplicate number that may repeat more than once
	{
		int N = v.size();
		if (N == 0)
			throw std::exception("");

		//1. advance slow ptr 1 node, fast ptr 2 nodes
		//they will meet at some node in the middle of the cycle
		int slow = 0;
		int fast = 0;
		while (true)
		{
			slow = v[slow];
			fast = v[v[fast]];
			std::cout << slow << ", " << fast << std::endl;
			if (slow == fast)
				break;
		}
		std::cout << "slow, fast: " << slow << ", " << fast << std::endl;

		//2. let finder ptr start from head, slow ptr start from its current node, advance both ptrs 1 node
		//they will meet at the cycle begin node
		int finder = 0;
		while (true)
		{
			slow = v[slow];
			finder = v[finder];
			std::cout << slow << ", " << finder << std::endl;
			if (slow == finder)
				break;
		}
		std::cout << "slow, finder: " << slow << ", " << finder << std::endl;

		std::cout << "SingleDupInIdxSeqArray Find_CycleBegin for \"" << Debug::ToStr1D<int>()(v) << "\": " << slow << std::endl;
		return slow;
	}

	int Find_XOR(const std::vector<int> & A)//for the case of single duplicate only
	{
		int N = A.size();
		int res = 0;
		for (int i = 0; i < N; ++i)
		{
			res ^= A[i];
		}
		for (int i = 1; i < N; ++i)//A[i] is in the range [1...N-1]
		{
			res ^= i;
		}
		std::cout << "SingleDupInIdxSeqArray Find_XOR for \"" << Debug::ToStr1D<int>()(A) << "\": " << res << std::endl;
		return res;
	}
};
/*
9, 10
10, 13
7, 14
13, 1
8, 11
14, 4
6, 7
1, 8
5, 6
11, 5
12, 12
slow, fast: 12, 12
4, 9
3, 10
7, 7
slow, finder: 7, 7
SingleDupInIdxSeqArray Find_CycleBegin for "9, 5, 2, 7, 3, 11, 1, 13, 14, 10, 7, 12, 4, 8, 6": 7
SingleDupInIdxSeqArray Find_XOR for "9, 5, 2, 7, 3, 11, 1, 13, 14, 10, 7, 12, 4, 8, 6": 7
9, 10
10, 13
7, 14
13, 1
8, 11
14, 4
6, 14
1, 1
slow, fast: 1, 1
5, 9
11, 10
12, 7
4, 13
3, 8
14, 14
slow, finder: 14, 14
SingleDupInIdxSeqArray Find_CycleBegin for "9, 5, 2, 14, 3, 11, 1, 13, 14, 10, 7, 12, 4, 8, 6": 14
SingleDupInIdxSeqArray Find_XOR for "9, 5, 2, 14, 3, 11, 1, 13, 14, 10, 7, 12, 4, 8, 6": 14
*/
#endif