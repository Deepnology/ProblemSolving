#ifndef MOVE_ZEROS_TO_END_OF_ARRAY_H
#define MOVE_ZEROS_TO_END_OF_ARRAY_H
#include "Debug.h"
/*
Leetcode: Move zeros
Given an integer array, move all zeros to end of array and keep original order.
see also RemoveSomeElementFromArray.h, AltPosNegNumArray.h
*/
class MoveZerosToEndOfArray
{
public:
	MoveZerosToEndOfArray() {}

	void InPlace(std::vector<int> && v)
	{
		std::string before = Debug::ToStr1D<int>()(v);

		int N = v.size();
		int left = 0;//0
		int right = 0;//non-0
		while (true)
		{
			while (left < N && v[left] != 0)
				++left;
			if (left == N) break;
			right = std::max(left + 1, right + 1);
			while (right < N && v[right] == 0)
				++right;
			if (right == N) break;
			std::swap(v[left], v[right]);
			++left;
		}
		
		std::cout << "MoveZerosToEndOfArray InPlace for \"" << before << "\": " << Debug::ToStr1D<int>()(v) << std::endl;
	}

	void InPlace2(std::vector<int> && nums)
	{
		std::string before = Debug::ToStr1D<int>()(nums);

		int N = nums.size();
		int newEnd = 0;
		for (int i = 0; i < N; ++i)
		{
			if (nums[i] != 0)
				nums[newEnd++] = nums[i];
		}
		for (; newEnd < N; ++newEnd)
			nums[newEnd] = 0;

		std::cout << "MoveZerosToEndOfArray InPlace2 for \"" << before << "\": " << Debug::ToStr1D<int>()(nums) << std::endl;
	}
};
/*
MoveZerosToEndOfArray InPlace for "1, 2, 0, 4, 3, 0, 5, 0": 1, 2, 4, 3, 5, 0, 0, 0
MoveZerosToEndOfArray InPlace for "1, 2, 0, 0, 0, 3, 6": 1, 2, 3, 6, 0, 0, 0
MoveZerosToEndOfArray InPlace for "0, 9, 0, 4, 0, 0, 2, 7, 0, 6, 0": 9, 4, 2, 7, 6, 0, 0, 0, 0, 0, 0
MoveZerosToEndOfArray InPlace for "0, 9, 0, 0, 0, 0, 0, 7, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1": 9, 7, 4, 6, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
*/
#endif
