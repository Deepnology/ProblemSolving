/*MUST*/
#ifndef POW_H
#define POW_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "Debug.h"
/*
Elements of programming interview, PrimitiveTypes: Compute x^y
Leetcode: Pow
// Pow(x, n)
// x^n
// Implement pow(x, n).
//
// Binary: O(logn) time, where logn means the number of bits to represent n
*/
class Pow
{
public:
	Pow(){}
	~Pow(){}

	double BinaryRecur(double x, int n)
	{
		if (x == 0)
			return 0;

		double res;
		if (n < 0)
			res = 1.0 / this->binaryRecur(x, -n);
		else
			res = this->binaryRecur(x, n);

		std::cout << "Pow BinaryRecur for \"" << x << " to the power of " << n << "\": " << res << std::endl;
		return res;
	}
private:
	double binaryRecur(double x, int n)
	{
		if (n == 0)
			return 1.0;
		double halfPow = this->binaryRecur(x, n / 2);
		if (n % 2 == 0)
			return halfPow * halfPow;
		else
			return halfPow * halfPow * x;
	}

public:
	double BinaryIterate(double x, int n)
	{
		double base = x;
		double res = 1.0;
		for (int power = abs(n); power > 0; power >>= 1, base *= base)//power/=2
		{
			if (power & 1)//power%2==1
				res *= base;
		}

		if (n < 0)
			res = 1.0 / res;

		std::cout << "Pow BinaryIterate for \"" << x << " to the power of " << n << "\": " << res << std::endl;
		return res;
	}

	double Naive(double x, int n)
	{
		if (n == 0)
			return 1.0;

		double res = 1.0;
		for (int i = 0; i < abs(n); ++i)
			res *= x;

		if (n < 0)
			res = 1.0 / res;

		std::cout << "Pow Naive for \"" << x << " to the power of " << n << "\": " << res << std::endl;
		return res;
	}
};
/*
Pow BinaryRecur for "2 to the power of 7": 128
Pow BinaryRecur for "-2 to the power of -7": -0.0078125
Pow BinaryIterate for "2 to the power of 7": 128
Pow BinaryIterate for "-2 to the power of -7": -0.0078125
Pow Naive for "2 to the power of 7": 128
Pow Naive for "-2 to the power of -7": -0.0078125
*/
#endif