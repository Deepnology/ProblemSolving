#ifndef COUNT_SET_BITS_FROM_1_TO_N_H
#define COUNT_SET_BITS_FROM_1_TO_N_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Debug.h"
/*
Leetcode: Counting Bits
Given a non-negative integer N. For every integer i in the range 0 <= i <= N, compute the number of 1s in their binary representation and return them as an array.
For N = 5, return [0,1,1,2,1,2].

It is very easy to come up with a solution with run time O(n*sizeof(integer)). But can you do it in linear time O(n) /possibly in a single pass?
Space complexity should be O(n).
Can you do it like a boss? Do it without using any builtin function like __builtin_popcount in c++ or in any other language.

You should make use of what you have produced already.
Divide the numbers in ranges like [2-3], [4-7], [8-15] and so on. And try to generate new range from previous.
Or does the odd/even status of the number help you in calculating the number of 1s?

DP: O(n) time, O(n) space
*/
class CountSetBitsFrom1toN
{
public:
	CountSetBitsFrom1toN() {}
	~CountSetBitsFrom1toN() {}

	std::vector<int> DP(int n)
	{
		std::vector<int> res;
		res.push_back(0);
		for (int i = 1; i <= n; ++i)
		{
			res.push_back((i & 1) + res[i >> 1]);//LSB digit + count of 1s excluding LSB
		}
		std::cout << "CountSetBitsFrom1toN DP for \"" << n << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
CountSetBitsFrom1toN DP for "56": 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3
*/
#endif
