#ifndef SWAP_0_CONVERT_PERMUTATION_H
#define SWAP_0_CONVERT_PERMUTATION_H
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Debug.h"
/*
Google
http://www.careercup.com/question?id=5700226908160000
Given two arrays, src, tgt, containing two permutations of numbers 0...n-1.
Rearrange src so that it equals tgt.
The only allowed operation is "swap a number with 0".

Algorithm:
1. Find the element 0's idx in src array, and keep track of its idx
2. For each element in tgt array:
2.1 in src array, find corresponding element's idx
2.2 in src array, swap 0 to current element's idx of tgt array
2.3 in src array, swap the found element in step 2.1 to current element's idx of tgt array (which now contains 0 in src array)
2.4 in src array, update 0's idx

Practical application:
Imagine you have a parking place with n slots and n-1 cars numbered from 1...n-1.
The free slot is represented by 0 in the problem.
If you want to rearrange the cars, you can only move one car at a time into the empty slot,
which is equivalent to "swap a number with 0".
*/
class Swap0ConvertPermutation
{
public:
	Swap0ConvertPermutation(){}
	~Swap0ConvertPermutation(){}

	//O(n^2) time, O(1) space
	int Count_BruteForce(const std::vector<int> & tgt, std::vector<int> & src)
	{
		int N = tgt.size();
		if (N != (int)src.size())
			return -1;
		std::cout << "tgt: " << Debug::ToStr1D<int>()(tgt) << std::endl;
		std::cout << "src: " << Debug::ToStr1D<int>()(src) << std::endl;

		int count = 0;
		int srcZero = -1;
		for (int i = 0; i < N; ++i)
		{
			if (src[i] == 0)
			{
				srcZero = i;
				break;
			}
		}

		for (int i = 0; i < N; ++i)//for each num in tgt
		{
			//we want to find tgt[i] in src
			for (int j = 0; j < N; ++j)
			{
				if (tgt[i] == src[j])//found tgt[i] at src[j]
				{
					//move j to i in src through "swap 0 to i" and "swap 0 to j" in src
					if (i != j && j != srcZero)
					{
						if (i != srcZero)
						{
							std::swap(src[i], src[srcZero]);//1. swap 0 to i in src
							++count;
							srcZero = i;
						}
						if (j != srcZero)
						{
							std::swap(src[j], src[srcZero]);//2. swap 0 to j in src
							++count;
							srcZero = j;
						}
						break;
					}
				}
			}
			std::cout << "src: " << Debug::ToStr1D<int>()(src) << " = " << count << std::endl;
		}
		std::cout << "Swap0ConvertPermutation Count_BruteForce: " << count << std::endl;
		return count;
	}

	//O(n^2) time, O(1) space
	int Count_Better(const std::vector<int> & tgt, std::vector<int> & src)
	{
		int N = tgt.size();
		if (N != (int)src.size())
			return -1;
		std::cout << "tgt: " << Debug::ToStr1D<int>()(tgt) << std::endl;
		std::cout << "src: " << Debug::ToStr1D<int>()(src) << std::endl;

		int count = 0;
		int srcZero = -1;
		for (int i = 0; i < N; ++i)
		{
			if (src[i] == 0)
			{
				srcZero = i;
				break;
			}
		}

		while (true)
		{
			if (tgt[srcZero] != 0)
			{
				//we want to find the num in src that is equal to tgt[srcZero]
				//so that we can swap it with src[srcZero]
				for (int i = 0; i < N; ++i)
				{
					if (tgt[srcZero] == src[i])
					{
						std::swap(src[srcZero], src[i]);
						++count;
						srcZero = i;
						break;
					}
				}
			}
			else//tgt[srcZero] == 0
			{
				//we want to find next mismatch and swap it with src[srcZero]
				//if we cannot find any mismatch, we are done
				int i;
				for (i = 0; i < N; ++i)
				{
					if (tgt[i] != src[i])
					{
						std::swap(src[i], src[srcZero]);
						++count;
						srcZero = i;
						break;
					}
				}
				if (i == N)
					break;//break while
			}
			std::cout << "src: " << Debug::ToStr1D<int>()(src) << " = " << count << std::endl;
		}

		std::cout << "Swap0ConvertPermutation Count_Better: " << count << std::endl;
		return count;
	}

	//O(n) time, O(n) space
	int Count_BruteForce_HashMap(const std::vector<int> & tgt, std::vector<int> & src)
	{
		int N = tgt.size();
		if (N != (int)src.size())
			return -1;
		std::cout << "tgt: " << Debug::ToStr1D<int>()(tgt) << std::endl;
		std::cout << "src: " << Debug::ToStr1D<int>()(src) << std::endl;

		std::vector<int> srcIdxMap(N);
		for (int i = 0; i < N; ++i)
			srcIdxMap[src[i]] = i;

		int count = 0;

		for (int i = 0; i < N; ++i)//for each num idx i in tgt
		{
			//we want to find num idx j in src with same value of tgt[i]
			//move j to i in src through "swap 0 to i" and "swap 0 to j" in src
			int j = srcIdxMap[tgt[i]];
			if (i != j && j != srcIdxMap[0])
			{
				int srcZero = srcIdxMap[0];
				if (i != srcZero)
				{
					std::swap(src[i], src[srcZero]);//1. swap 0 to i in src
					++count;
					srcIdxMap[0] = i;//update 0's idx
					srcIdxMap[src[srcZero]] = srcZero;//update another element's idx
					srcZero = i;
				}
				if (j != srcZero)
				{
					std::swap(src[j], src[srcZero]);//2. swap 0 to j in src
					++count;
					srcIdxMap[0] = j;//update 0's idx
					srcIdxMap[src[srcZero]] = srcZero;//update another element's idx
				}
			}
			std::cout << "src: " << Debug::ToStr1D<int>()(src) << " = " << count << std::endl;
		}
		
		std::cout << "Swap0ConvertPermutation Count_BruteForce_HashMap: " << count << std::endl;
		return count;
	}
};
/*
tgt: 0, 2, 3, 1, 4, 5, 9, 8, 7, 6
src: 1, 0, 2, 3, 5, 4, 7, 9, 6, 8
src: 1, 0, 2, 3, 5, 4, 7, 9, 6, 8 = 0 (swap 0 to idx_0, swap 0 to idx_1 where 0 locates)
src: 1, 2, 0, 3, 5, 4, 7, 9, 6, 8 = 1 (swap 0 to idx_1, swap 0 to idx_2 where 2 locates)
src: 1, 2, 3, 0, 5, 4, 7, 9, 6, 8 = 2 (swap 0 to idx_2, swap 0 to idx_3 where 3 locates)
src: 0, 2, 3, 1, 5, 4, 7, 9, 6, 8 = 3 (swap 0 to idx_3, swap 0 to idx_0 where 1 locates)
src: 5, 2, 3, 1, 4, 0, 7, 9, 6, 8 = 5 (swap 0 to idx_4, swap 0 to idx_5 where 4 locates)
src: 0, 2, 3, 1, 4, 5, 7, 9, 6, 8 = 6 (swap 0 to idx_5, swap 0 to idx_0 where 5 locates)
src: 7, 2, 3, 1, 4, 5, 9, 0, 6, 8 = 8 (swap 0 to idx_6, swap 0 to idx_7 where 9 locates)
src: 7, 2, 3, 1, 4, 5, 9, 8, 6, 0 = 9 (swap 0 to idx_7, swap 0 to idx_9 where 8 locates)
src: 0, 2, 3, 1, 4, 5, 9, 8, 7, 6 = 11 (swap 0 to idx_8, swap 0 to idx_0 where 7 locates)
src: 0, 2, 3, 1, 4, 5, 9, 8, 7, 6 = 11 (no swap)
Swap0ConvertPermutation Count_BruteForce: 11
tgt: 0, 2, 3, 1, 4, 5, 9, 8, 7, 6
src: 1, 0, 2, 3, 5, 4, 7, 9, 6, 8
src: 1, 2, 0, 3, 5, 4, 7, 9, 6, 8 = 1 (swap 0 to idx_2 where 2 locates)
src: 1, 2, 3, 0, 5, 4, 7, 9, 6, 8 = 2 (swap 0 to idx_3 where 3 locates)
src: 0, 2, 3, 1, 5, 4, 7, 9, 6, 8 = 3 (swap 0 to idx_0 where 1 locates)
src: 5, 2, 3, 1, 0, 4, 7, 9, 6, 8 = 4 (swap 0 to idx_4 where next mismatch from left locates)
src: 5, 2, 3, 1, 4, 0, 7, 9, 6, 8 = 5 (swap 0 to idx_5 where 4 locates)
src: 0, 2, 3, 1, 4, 5, 7, 9, 6, 8 = 6 (swap 0 to idx_0 where 5 locates)
src: 7, 2, 3, 1, 4, 5, 0, 9, 6, 8 = 7 (swap 0 to idx_6 where next mismatch from left locates)
src: 7, 2, 3, 1, 4, 5, 9, 0, 6, 8 = 8 (swap 0 to idx_7 where 9 locates)
src: 7, 2, 3, 1, 4, 5, 9, 8, 6, 0 = 9 (swap 0 to idx_9 where 8 locates)
src: 7, 2, 3, 1, 4, 5, 9, 8, 0, 6 = 10 (swap 0 to idx_8 where 6 locates)
src: 0, 2, 3, 1, 4, 5, 9, 8, 7, 6 = 11 (swap 0 to idx_0 where 7 locates)
Swap0ConvertPermutation Count_Better: 11
tgt: 0, 2, 3, 1, 4, 5, 9, 8, 7, 6
src: 1, 0, 2, 3, 5, 4, 7, 9, 6, 8
src: 1, 0, 2, 3, 5, 4, 7, 9, 6, 8 = 0 (swap 0 to idx_0, swap 0 to idx_1 where 0 locates)
src: 1, 2, 0, 3, 5, 4, 7, 9, 6, 8 = 1 (swap 0 to idx_1, swap 0 to idx_2 where 2 locates)
src: 1, 2, 3, 0, 5, 4, 7, 9, 6, 8 = 2 (swap 0 to idx_2, swap 0 to idx_3 where 3 locates)
src: 0, 2, 3, 1, 5, 4, 7, 9, 6, 8 = 3 (swap 0 to idx_3, swap 0 to idx_0 where 1 locates)
src: 5, 2, 3, 1, 4, 0, 7, 9, 6, 8 = 5 (swap 0 to idx_4, swap 0 to idx_5 where 4 locates)
src: 0, 2, 3, 1, 4, 5, 7, 9, 6, 8 = 6 (swap 0 to idx_5, swap 0 to idx_0 where 5 locates)
src: 7, 2, 3, 1, 4, 5, 9, 0, 6, 8 = 8 (swap 0 to idx_6, swap 0 to idx_7 where 9 locates)
src: 7, 2, 3, 1, 4, 5, 9, 8, 6, 0 = 9 (swap 0 to idx_7, swap 0 to idx_9 where 8 locates)
src: 0, 2, 3, 1, 4, 5, 9, 8, 7, 6 = 11 (swap 0 to idx_8, swap 0 to idx_0 where 7 locates)
src: 0, 2, 3, 1, 4, 5, 9, 8, 7, 6 = 11 (no swap)
Swap0ConvertPermutation Count_BruteForce_HashMap: 11
*/
#endif