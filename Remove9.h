#ifndef REMOVE_9_H
#define REMOVE_9_H
#include "Debug.h"
/*
Leetcode: Remove 9
Start from integer 1, remove any integer that contains 9 such as 9, 19, 29...
So now, you will have a new integer sequence: 1, 2, 3, 4, 5, 6, 7, 8, 10, 11, ...
Given a positive integer n, you need to return the n-th integer after removing.
Note that 1 will be the first integer.
Example 1:
Input: 9
Output: 10
Hint: n will not exceed 9 x 10^8.
*/
class Remove9
{
public:
	Remove9() {}

	int newInteger(int n)
	{
		//equivalent to convert decimal to binary (base of 2) (with decimal format)
		//now convert decimal to a base of 9 (with decimal format)
		//when it hits a '9', advance to next number
		//return a decimal number where all '9'nums were removed
		int res = 0;
		int base = 1;
		while (n)
		{
			res += (n % 9) * base;
			n /= 9;
			base *= 10;
		}
		return res;
	}
};
#endif
