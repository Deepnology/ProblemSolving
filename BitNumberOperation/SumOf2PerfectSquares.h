#ifndef SUM_OF_2_PERFECT_SQUARES_H
#define SUM_OF_2_PERFECT_SQUARES_H
#include "Debug.h"
/*
Leetcode: Sum Of Square Numbers
Given a non-negative integer c, your task is to decide whether there're two integers a and b such that a^2 + b^2 = c.
Example 1:
Input: 5
Output: True
Explanation: 1 * 1 + 2 * 2 = 5
Example 2:
Input: 3
Output: False
*/
class SumOf2PerfectSquares
{
public:
	SumOf2PerfectSquares() {}

	bool UseSqrt(int c)
	{
		for (long i = 0; i * i <= c; ++i)
		{
			double j = sqrt((long)c - i*i);
			if (j == (int)j)
				return true;
		}
		return false;
	}
	bool BinarySearch(int c)
	{
		int left = 0;
		int right = (int)sqrt(c);
		while (left <= right)
		{
			int sum = left*left + right*right;
			if (sum == c)
				return true;
			if (sum < c)
				++left;
			else
				--right;
		}
		return false;
	}
	/*
	Any positive number n is expressible as a sum of two squares if and only if
	the prime factorization of n, every prime of the form (4k+3) occurs an even number of times
	*/
	bool FermatTheory(int c)
	{
		for (int i = 2; i*i <= c; ++i)
		{
			if (c % i == 0)
			{
				int count = 0;
				while (c % i == 0)
				{
					c /= i;
					++count;
				}
				if (i % 4 == 3 && count % 2 != 0)
					return false;
			}
		}
		return c % 4 != 3;
	}
};
#endif
