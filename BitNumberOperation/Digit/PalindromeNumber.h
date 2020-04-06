#ifndef PALINDROME_NUMBER_H
#define PALINDROME_NUMBER_H
#include <iostream>
#include <sstream>
/*
Elements of programming interview, PrimitiveTypes: Check if a decimal integer is a palindrome
Leetcode: Palindrome Number
// Determine whether an integer is a palindrome. Do this without extra space.
//
// Some hints:
// Could negative integers be palindromes? (ie, -1)
//
// If you are thinking of converting the integer to string, note the
// restriction of using extra space.
//
// You could also try reversing an integer. However, if you have solved the
// problem "Reverse Integer", you know that the reversed integer might
// overflow. How would you handle such case?
//
// There is a more generic way of solving this problem.

O(n) time, where n is the number of digits in x.
*/
class PalindromeNumber
{
public:
	PalindromeNumber(){}
	~PalindromeNumber(){}

	bool Valid(int x)
	{
		int original = x;

		if (x < 0)
		{
			std::cout << "PalindromeNumber Valid for \"" << original << "\": False." << std::endl;
			return false;
		}

		//if x = 823454328
		//=> d = 100000000

		long d = 1;
		while (d * 10 < x)
			d *= 10;

		//std::cout << d << std::endl;

		while (x > 0)
		{
			if (x / d != x % 10)//compare the 1st digit of x (by x/d) and the last digit of x (by x%10)
			{
				std::cout << "PalindromeNumber Valid for \"" << original << "\": False." << std::endl;
				return false;
			}

			//if the 1st digit matches the last digit
			x = (x % d) / 10;//remove the 1st digit by x %= 10, and remove the last digit by that result /= 10
			d /= 100;//remove two digits

			//(when 0 < x < 10, x /= 10 will be 0)
		}

		std::cout << "PalindromeNumber Valid for \"" << original << "\": True." << std::endl;
		return true;
	}

};
/*
PalindromeNumber Valid for "123454321": True.
*/
#endif