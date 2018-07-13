#ifndef EQUILIBRIUM_INDEX_OF_ARRAY_H
#define EQUILIBRIUM_INDEX_OF_ARRAY_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include "Debug.h"
/*
Leetcode: Find Pivot Index
http://www.geeksforgeeks.org/equilibrium-index-of-an-array/
Equilibrium index of an array is an index such that the sum of elements at lower indices (EXCLUDE itself) is equal to the sum of elements at higher indices (EXCLUDE itself).
-7, 1, 5, 2, -4, 3, 0
 0  1  2  3   4  5  6
3 (-7+1+5 = -4+3+0) and 6 (-7+1+5+2-4+3 = 0) are equilibrium indices.

O(n) time, O(1) space

Equivalent to EqualSum2SubArrPartition.h
*/
class EquilibriumIndexOfArray
{
public:
	EquilibriumIndexOfArray(){}
	~EquilibriumIndexOfArray(){}

	std::vector<int> FindAll_2Scan(const std::vector<int> & A)
	{
		int N = A.size();
		int rightSum = 0;
		int leftSum = 0;
		std::vector<int> res;

		for (int i = 0; i < N; ++i)
			rightSum += A[i];

		for (int i = 0; i < N; ++i)
		{
			rightSum -= A[i];

			if (leftSum == rightSum)
				res.push_back(i);

			leftSum += A[i];
		}

		std::cout << "EquilibriumIndexOfArray 2Scan for \"" << Debug::ToStr1D<int>()(A) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
EquilibriumIndexOfArray 2Scan for "-7, 1, 5, 2, -4, 3, 0": 3, 6
*/
#endif