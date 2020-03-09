#ifndef POW_OF_4_H
#define POW_OF_4_H
#include <iostream>
#include <string>
#include <algorithm>
/*
Leetcode: Power of 4
Given an integer (signed 32 bits), write a function to check whether it is a power of 4.

Example:
Given num = 16, return true. Given num = 5, return false.

Follow up: Could you solve it without loops/recursion?
*/
class PowOf4
{
public:
	PowOf4() {}
	~PowOf4() {}

	bool Naive(int n)
	{
		if (n == 0)
			return false;
		while (n % 4 == 0)
			n /= 4;
		return n == 1;
	}

	bool Math(int n)
	{
		return n > 0 && log(n) / log(4) - (int)(log(n) / log(4)) == 0;//see PowOf3.h
	}

	bool BitWise(int n)
	{
		//n & (n - 1) == 0 means n is pow of 2 (only 1 set bit)
		//n & 0x55555555 == n means n is pow of 4 (the only one set bit is at odd index)
		//where 0x55555555=01010101010101010101010101010101
		return n > 0 && (n & (n - 1)) == 0 && (n & 0x55555555) == n;
	}

	bool BitWise2(int n)
	{
		//n & (n - 1) == 0 means n is pow of 2 (only 1 set bit)
		return n > 0 && (n & (n - 1)) == 0 && ((n - 1)%3) == 0;
	}

	bool Solve(int num)
	{
		bool naive = this->Naive(num);
		bool math = this->Math(num);
		bool bitwise = this->BitWise(num);
		bool bitwise2 = this->BitWise2(num);

		std::cout << "PowOf4 for \"" << num << "\": " << naive << ", " << math << ", " << bitwise << ", " << bitwise2 << std::endl;
		return math;
	}
};
/*
PowOf4 for "32": 0, 0, 0, 0
PowOf4 for "64": 1, 1, 1, 1
*/
#endif
