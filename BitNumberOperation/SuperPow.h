#ifndef SUPER_POW_H
#define SUPER_POW_H
#include "Debug.h"
/*
Leetcode: Super Pow
Your task is to calculate pow(a,b) mod 1337 where a is a positive integer and b is an extremely large positive integer given in the form of an array.

Example1:
a = 2
b = [3]
Result: 8

Example2:
a = 2
b = [1,0]
Result: 1024


2^23 = (2^10)^2 * 2^3
*/
class SuperPow
{
public:
	SuperPow() {}
	~SuperPow() {}

	int BinaryRecur(int a, const std::vector<int> & b)
	{
		long long res = 1;
		int N = b.size();
		for (int i = 0; i < N; ++i)
			res = this->powRecur((int)res, 10) * this->powRecur(a, b[i]) % 1337;

		std::cout << "SuperPow BinaryRecur for pow(\"" << a << "\", \"" << Debug::ToStr1D<int>()(b) << "\"): " << res << std::endl;
		return (int)res;
	}

	int powRecur(int x, int n)
	{
		if (n == 0) return 1;
		if (n == 1) return x % 1337;

		return this->powRecur(x % 1337, n / 2) * this->powRecur(x % 1337, n - n / 2) % 1337;
	}

	int powIterate(int x, int n)
	{
		int res = 1;
		int base = x % 1337;
		while (n)
		{
			if (n % 2 == 1)
				res = res * base % 1337;
			n /= 2;
			base = base * base % 1337;
		}
		return res % 1337;
	}
};
/*
SuperPow BinaryRecur for pow("2", "3"): 8
SuperPow BinaryRecur for pow("2", "1, 0"): 1024
*/
#endif
