#ifndef REMOVE_SOME_ELEMENT_FROM_ARRAY_H
#define REMOVE_SOME_ELEMENT_FROM_ARRAY_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Move Zeros
Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.
For example, given nums = [0, 1, 0, 3, 12], after calling your function, nums should be [1, 3, 12, 0, 0].
Note:
You must do this in-place without making a copy of the array.
Minimize the total number of operations.

Elements of programming interview, Array: Delete a key from an array
Leetcode: Remove Element
// Given an array and a value, remove all instances of that value in place
// and return the new length.
//
// The order of elements can be changed. It doesn't matter what you leave
// beyond the new length.
//
// Complexity
// O(n) time

Google
http://www.careercup.com/question?id=18460667
Given a string, remove all 'b' and 'ac' in place.
Expected O(n) time one scan.

See also RemoveReplaceElementFromArr.h
*/
class RemoveSomeElementFromArray
{
public:
	RemoveSomeElementFromArray(){}
	~RemoveSomeElementFromArray(){}

	int InPlace(int A[], int n, int val)
	{
		std::string before = Debug::ToStr1D<int>()(A, n);
		/*walk thru A and construct a new array with elements not equal to val from begin*/
		int newEnd = 0;
		for (int oldCur = 0; oldCur < n; ++oldCur)
		{
			if (A[oldCur] != val)
				A[newEnd++] = A[oldCur];
		}

		std::string after = Debug::ToStr1D<int>()(A, newEnd);
		std::cout << "RemoveSomeElementFromArray InPlace \"" << val << "\" in \"" << before << "\": " << after << std::endl;
		return newEnd;
	}
	int InPlace(std::vector<int> & A, int val)
	{
		int n = A.size();
		std::string before = Debug::ToStr1D<int>()(A);
		/*walk thru A and construct a new array with elements not equal to val from begin*/
		int newEnd = 0;
		for (int oldCur = 0; oldCur < n; ++oldCur)
		{
			if (A[oldCur] != val)
				A[newEnd++] = A[oldCur];
		}

		std::string after = Debug::ToStr1D<int>()(A);
		std::cout << "RemoveSomeElementFromArray InPlace \"" << val << "\" in \"" << before << "\": " << after << std::endl;
		return newEnd;
	}

	void InPlace_b_and_ac(char * A, int n)
	{
		std::string before(A, n);

		int oldCur = 0;
		int newEnd = 0;

		while (oldCur < n)
		{
			if (A[oldCur] == 'b')
				++oldCur;
			else if (A[oldCur] == 'a' && oldCur + 1 < n && A[oldCur + 1] == 'c')
				oldCur += 2;
			else
				A[newEnd++] = A[oldCur++];
		}
		A[newEnd] = '\0';

		std::cout << "RemoveSomeElementFromArray InPlace_b_and_ac in \"" << before << "\": " << A << std::endl;
	}
};
/*
RemoveSomeElementFromArray InPlace "7" in "6, 8, 7, 4, 2, 1, 7, 8, 9, 5": 6, 8, 4, 2, 1, 8, 9, 5
RemoveSomeElementFromArray InPlace_b_and_ac in "xbyzacdafcbmacnij": xyzdafcmnij
*/
#endif