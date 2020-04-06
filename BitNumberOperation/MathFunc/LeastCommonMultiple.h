/*MUST*/
#ifndef LEAST_COMMON_MULTIPLE_H
#define LEAST_COMMON_MULTIPLE_H
#include <iostream>
#include <string>
/*
LCM
http://www.programiz.com/c-programming/examples/lcm
*/
class LeastCommonMultiple
{
public:
	LeastCommonMultiple(){}
	~LeastCommonMultiple(){}

	int FromGCD(int a, int b)
	{
		int res = a * b / this->gcd(a, b);
		std::cout << "LeastCommonMultiple FromGCD for \"" << a << "," << b << "\": " << res << std::endl;
		return res;
	}

	int Iterate(int a, int b)
	{
		int max = a > b ? a : b;
		while (true)
		{
			if (max % a == 0 && max % b == 0)
				break;
			++max;
		}
		std::cout << "LeastCommonMultiple Iterate for \"" << a << "," << b << "\": " << max << std::endl;
		return max;
	}

	int Recur(int a, int b)
	{
		int max = a > b ? a : b;
		int res = this->recur(a, b, max);
		std::cout << "LeastCommonMultiple Recur for \"" << a << "," << b << "\": " << res << std::endl;
		return res;
	}
private:
	int recur(int a, int b, int & common)
	{
		if (common % a == 0 && common % b == 0)
			return common;
		++common;
		this->recur(a, b, common);
		return common;
	}

	int gcd(int m, int n)
	{
		while (m)
		{
			int tmp = m;
			m = n % m;
			n = tmp;
		}
		return n;
	}
};
/*
LeastCommonMultiple FromGCD for "15,9": 45
LeastCommonMultiple Iterate for "15,9": 45
LeastCommonMultiple Recur for "15,9": 45
*/
#endif