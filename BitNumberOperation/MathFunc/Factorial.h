#ifndef FACTORIAL_H
#define FACTORIAL_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
http://stackoverflow.com/questions/5721796/how-do-you-implement-the-factorial-function-in-c
*/
class Factorial
{
public:
	Factorial(){}
	~Factorial(){}

	unsigned int Recur(unsigned int n)
	{
		int res = this->recur(n);
		std::cout << "Factorial Recur for \"" << n << "\": " << res << std::endl;
		return res;
	}
private:
	unsigned int recur(unsigned int n)
	{
		if (n == 0)
			return 1;
		return n * this->recur(n - 1);
	}
public:
	unsigned int Iterate(unsigned int n)
	{
		unsigned int res = 1;
		for (unsigned int i = 2; i <= n; ++i)
			res *= i;
		std::cout << "Factorial Iterate for \"" << n << "\": " << res << std::endl;
		return res;
	}
};
/*
Factorial Recur for "10": 3628800
Factorial Iterate for "10": 3628800
*/
#endif