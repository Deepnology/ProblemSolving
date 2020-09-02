#ifndef PREVIOUS_PERMUTATION_H
#define PREVIOUS_PERMUTATION_H
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

For example:
input:  6,2,3,0,1,4,5
output: 6,2,1,5,4,3,0

See also NextPermutation.h

Leetcode: Previous Permutation With One Swap
Given an array A of positive integers (not necessarily distinct),
 return the lexicographically largest permutation that is smaller than A, that can be made with one swap
 (A swap exchanges the positions of two numbers A[i] and A[j]).
If it cannot be done, then return the same array.
Example 1:
Input: [3,2,1]
Output: [3,1,2]
Explanation: Swapping 2 and 1.
Example 2:
Input: [1,1,5]
Output: [1,1,5]
Explanation: This is already the smallest permutation.
Example 3:
Input: [1,9,4,6,7]
Output: [1,7,4,6,9]
Explanation: Swapping 9 and 7.
Example 4:
Input: [3,1,1,3]
Output: [1,3,1,3]
Explanation: Swapping 1 and 3.
*/
class PreviousPermutation
{
public:
	PreviousPermutation(){}
	~PreviousPermutation(){}

	void InPlace(std::vector<int> && v)
	{
		std::string before = Debug::ToStr1D<int>()(v);
		int N = v.size();
		if (N < 2)
			return;

		int descendingEnd = N - 1;
		while (descendingEnd > 0 && !(v[descendingEnd - 1] > v[descendingEnd]))
			--descendingEnd;

		std::reverse(std::begin(v) + descendingEnd, std::end(v));

		if (descendingEnd > 0)
		{
			int pivot = descendingEnd - 1;

			//we want to find the upper bound in an descending order sorted array, the comparator should be "greater than" now
			int descendingUpperBound = std::upper_bound(v.begin() + descendingEnd, v.end(), v[pivot], std::greater<int>()) - v.begin();
			
			std::swap(v[pivot], v[descendingUpperBound]);
		}

		std::cout << "PreviousPermutation for \"" << before << "\": " << Debug::ToStr1D<int>()(v) << std::endl;
	}
};
class PreviousPermutationOneSwap
{
public:
    std::vector<int> Solve(std::vector<int> && v)
    {
        std::string before = Debug::ToStr1D<int>()(v);
        int N = v.size();
        if (N < 2)
            return v;

        int descendingEnd = N - 1;
        while (descendingEnd > 0 && !(v[descendingEnd - 1] > v[descendingEnd]))
            --descendingEnd;

        if (descendingEnd > 0)
        {
            int pivot = descendingEnd - 1;

            //we want to find the 1st num of prev num of lower bound of pivot in an ascending order sorted range, then swap it with pivot
            int LB = std::lower_bound(v.begin() + descendingEnd, v.end(), v[pivot], std::less<int>()) - v.begin();
            int prevOfLB = std::lower_bound(v.begin() + descendingEnd, v.end(), v[LB-1], std::less<int>()) - v.begin();

            std::swap(v[pivot], v[prevOfLB]);
        }

        std::cout << "PreviousPermutationOneSwap for \"" << before << "\": " << Debug::ToStr1D<int>()(v) << std::endl;
        return v;
    }
};
/*
PreviousPermutation for "6, 2, 3, 0, 1, 4, 5": 6, 2, 1, 5, 4, 3, 0
PreviousPermutation for "1, 3, 1": 1, 1, 3
PreviousPermutation for "1, 2, 3": 3, 2, 1
PreviousPermutation for "1, 3, 2": 1, 2, 3

PreviousPermutationOneSwap for "1, 3, 1, 3": 1, 1, 3, 3
*/
#endif