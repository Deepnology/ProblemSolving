#ifndef REVERSE_INTEGER_H
#define REVERSE_INTEGER_H
#include <string>
#include <iostream>
#include <sstream>
/*
Elements of programming interview, PrimitiveTypes: Reverse digits
Leetcode: Reverse Integer
// Reverse digits of an integer.
//
// Example1: x = 123, return 321
// Example2: x = -123, return -321
//
// Have you thought about this?
// Here are some good questions to ask before coding. Bonus points for you if
// you have already thought through this!
//
// If the integer's last digit is 0, what should the output be? ie, cases such
// as 10, 100.
//
// Did you notice that the reversed integer might overflow? Assume the input
// is a 32-bit integer, then the reverse of 1000000003 overflows. How should
// you handle such cases?
//
// Throw an exception? Good, but what if throwing an exception is not an
// option? You would then have to re-design the function (ie, add an extra
// parameter).

O(n) time, where n is the number of digits in x

INT_MAX =  2147483647
INT_MIN = -2147483648
If abs(res) > 214748364, then abs(res*10) >= 2147483650 will overflow.
If abs(res) == 214748364, then original x must be 1463847412 (2463847412 > INT_MAX),
so the final res must be 2147483641, therefore 214748364 is valid.
*/
class ReverseInteger
{
public:
	ReverseInteger(){}
	~ReverseInteger(){}

	int GO(int x)
	{
		int before = x;
		
		int res = 0;
		while (x != 0)
		{
			if (std::abs(res) > 214748364)
			{
				res = 0;
				break;
			}
			res = res * 10 + x % 10;
			x /= 10;
		}

		std::cout << "ReverseInteger for \"" << before << "\" is: " << res << std::endl;
		return res;
	}
};
/*
ReverseInteger for "2147483647" is: 0
ReverseInteger for "-2147483648" is: 0
ReverseInteger for "2147483630" is: 363847412
ReverseInteger for "2147483640" is: 463847412
ReverseInteger for "2147483641" is: 1463847412
ReverseInteger for "2147483612" is: 0
ReverseInteger for "-2147483630" is: -363847412
ReverseInteger for "-2147483640" is: -463847412
ReverseInteger for "-2147483612" is: 0
*/
#endif