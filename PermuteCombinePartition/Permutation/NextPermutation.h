#ifndef NEXT_PERMUTATION_H
#define NEXT_PERMUTATION_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include "Debug.h"
/*
Elements of programming interview, Array: Compute the next permutation
https://github.com/anson627/leetcode/blob/master/NextPermutation/NextPermutation.cpp
http://stackoverflow.com/questions/1622532/algorithm-to-find-next-greater-permutation-of-a-given-string
// Implement next permutation, which rearranges numbers into the
// lexicographically next greater permutation of numbers.
//
// If such arrangement is not possible, it must rearrange it as the lowest
// possible order (ie, sorted in ascending order).
//
// The replacement must be in-place, do not allocate extra memory.
//
// Here are some examples. Inputs are in the left-hand column and its
// corresponding outputs are in the right-hand column.
// 1,2,3 -> 1,3,2
// 3,2,1 -> 1,2,3
// 1,1,5 -> 1,5,1
// 6,2,1,5,4,3,0 -> 6,2,3,0,1,4,5
//
// Complexity
// O(n) time

Check also NextPrevNumWSameDigits.h, PreviousPermutation.h
*/
class NextPermutation
{
public:
	NextPermutation(){}
	~NextPermutation(){}

	void Next(std::vector<int> && num)
	{
		std::string before = Debug::ToStr1D<int>()(num);
		
		int N = num.size();
		if (N < 2)
			return;

		//1. find the highest index such that num[i-1]<num[i] (skip all num[i-1]>=num[i])
		//equivalent to find the last element that is in ascending order from right
		int ascendingEnd = N - 1;
		while (ascendingEnd > 0 && !(num[ascendingEnd - 1] < num[ascendingEnd]))
			--ascendingEnd;
		//now num[ascendingEnd]~num[N-1] is sorted in ascending order from right to left
		//num[ascendingEnd-1] is the highest index that is smaller than its right

		//2. reverse [ num[ascendingEnd],num[N-1] ]
		std::reverse(std::begin(num) + ascendingEnd, std::end(num));
		//now num[ascendingEnd]~num[N-1] are sorted in ascending order from left to right

		//if ascendingEnd == 0 (no such index exists), then the current array must be the last permutation (of a sorted array in ascending order from left to right)
		//the reversed array [num[0],num[N-1]] must be the first permutation (of a sorted array in ascending order from left to right)
		//which is also the next permutation
		
		if (ascendingEnd > 0)
		{
			int pivot = ascendingEnd - 1;

			//3. if ascendingEnd != 0
			//find the lowest index j in sorted num[ascendingEnd]~num[N-1] such that num[j]>num[pivot]
			//since the ascending order upper bound is the first element that compares greater than pivot: O(logn)
			//so we want to find the upper bound element
			int ascendingUpperBound = std::upper_bound(num.begin() + ascendingEnd, num.end(), num[pivot], std::less<int>()) - num.begin();
			//ascendingUpperBound will never be N because it should always find the first element that compares greater than pivot (at least the num[ascendingEnd] element meets the requirement)

			//4. swap num[pivot] with num[ascendingUpperBound]
			std::swap(num[pivot], num[ascendingUpperBound]);
		}

		std::cout << "NextPermutation for \"" << before << "\": " << Debug::ToStr1D<int>()(num) << std::endl;
	}

};
class NextPermutationOneSwap
{
public:
	void Next(std::vector<int> && num)
	{
		std::string before = Debug::ToStr1D<int>()(num);

		int N = num.size();
		if (N < 2)
			return;

		int ascendingEnd = N - 1;
		while (ascendingEnd > 0 && !(num[ascendingEnd - 1] < num[ascendingEnd]))
			--ascendingEnd;

		if (ascendingEnd > 0)
		{
			int pivot = ascendingEnd - 1;

			//we want to find the 1st num of prev num of lower bound of pivot in an descending order sorted range, then swap it with pivot
			int LB = std::lower_bound(num.begin() + ascendingEnd, num.end(), num[pivot], std::greater<int>()) - num.begin();
			int prevOfLB = std::lower_bound(num.begin() + ascendingEnd, num.end(), num[LB-1], std::greater<int>()) - num.begin();

			std::swap(num[pivot], num[prevOfLB]);
		}

		std::cout << "NextPermutationOneSwap for \"" << before << "\": " << Debug::ToStr1D<int>()(num) << std::endl;
	}
};
/*
NextPermutation for "1, 2, 3": 1, 3, 2
NextPermutation for "3, 2, 1": 1, 2, 3
NextPermutation for "1, 1, 3": 1, 3, 1
NextPermutation for "6, 2, 1, 5, 4, 3, 0": 6, 2, 3, 0, 1, 4, 5
*/
#endif