/*MUST*/
#ifndef GREATEST_COMMON_DIVISOR_H
#define GREATEST_COMMON_DIVISOR_H
#include <iostream>
#include <string>
/*
GCD
Elements of programming interview, PrimitiveTypes: Compute the greatest common divisor
http://www.programiz.com/c-programming/examples/hcf-gcd

WoMulDivMod: O(loga + logb) time
3 cases:
1. when both a and b are even:
   2 must be a common factor of both, so divide both by 2 and recur down, then multiply 2 with the result
2. when one is even and one is odd:
   2 must not be a factor of the odd number, so discard it by dividing the even number by 2 and recur down
3. when both a and b are odd:
   use subtraction
*/
class GreatestCommonDivisor
{
public:
	GreatestCommonDivisor(){}
	~GreatestCommonDivisor(){}

	long long WoMulDivMod_Recur(long long a, long long b)
	{
		long long res = this->woMulDivMod_recur(a, b);
		std::cout << "GreatestCommonDivisior WoMulDivMod_Recur for \"" << a << "," << b << "\": " << res << std::endl;
		return res;
	}
private:
	long long woMulDivMod_recur(long long a, long long b)
	{
		if (a == 0)
			return b;
		if (b == 0)
			return a;

		if (!(a & 1) && !(b & 1))/*both a and b are even*/
			return this->woMulDivMod_recur(a >> 1, b >> 1) << 1;
		if (!(a & 1) && (b & 1))/*a is even, b is odd*/
			return this->woMulDivMod_recur(a >> 1, b);
		if ((a & 1) && !(b & 1))/*a is odd, b is even*/
			return this->woMulDivMod_recur(a, b >> 1);
		if (a > b)/*both a and b are odd, a > b*/
			return this->woMulDivMod_recur(a - b, b);
		/*both a and b are odd, a <= b*/
		return this->woMulDivMod_recur(a, b - a);
	}

public:
	int Mod_Iterate(int a, int b)
	{
		std::cout << "GreatestCommonDivisor Mod_Iterate for \"" << a << "," << b << "\": ";

		while (a)
		{
			int tmp = a;
			//std::cout << b << "%" << a << "=" << (b%a) << std::endl;
			a = b % a;
			b = tmp;
		}

		std::cout << b << std::endl;
		return b;
	}

	int Subtract_Iterate(int a, int b)
	{
		std::cout << "GreatestCommonDivisor Subtract_Iterate for \"" << a << "," << b << "\": ";

		while (a != b)
		{
			if (a > b)
				a -= b;
			else
				b -= a;
		}

		std::cout << a << std::endl;
		return a;
	}

	int Mod_Recur(int a, int b)
	{
		int res = this->mod_recur(a, b);
		std::cout << "GreatestCommonDivisor Mod_Recur for \"" << a << "," << b << "\": " << res << std::endl;
		return res;
	}
private:
	int mod_recur(int a, int b)
	{
		if (b == 0)
			return a;
		else
			return this->mod_recur(b, a%b);
	}


public:
	std::pair<int, int> GetCanonicalFraction(int a, int b)//GCD application: ¬ù¤À (see also MaxPointsOnALine.h)
	{
		//1. remove GCD for both
		int gcd = this->mod_recur(std::abs(a), std::abs(b));
		a /= gcd;
		b /= gcd;
		//2. make sure b (denominator) is non-negative
		return b < 0 ? std::make_pair(-a, -b) : std::make_pair(a, b);
	}
};
/*
GreatestCommonDivisior WoMulDivMod_Recur for "5,3": 1
GreatestCommonDivisor Mod_Iterate for "5,3": 1
GreatestCommonDivisor Subtract_Iterate for "5,3": 1
GreatestCommonDivisor Mod_Recur for "5,3": 1
GreatestCommonDivisior WoMulDivMod_Recur for "3,5": 1
GreatestCommonDivisor Mod_Iterate for "3,5": 1
GreatestCommonDivisor Subtract_Iterate for "3,5": 1
GreatestCommonDivisor Mod_Recur for "3,5": 1
GreatestCommonDivisior WoMulDivMod_Recur for "2,3": 1
GreatestCommonDivisor Mod_Iterate for "2,3": 1
GreatestCommonDivisor Subtract_Iterate for "2,3": 1
GreatestCommonDivisor Mod_Recur for "2,3": 1
GreatestCommonDivisior WoMulDivMod_Recur for "3,2": 1
GreatestCommonDivisor Mod_Iterate for "3,2": 1
GreatestCommonDivisor Subtract_Iterate for "3,2": 1
GreatestCommonDivisor Mod_Recur for "3,2": 1
GreatestCommonDivisior WoMulDivMod_Recur for "42,35": 7
GreatestCommonDivisor Mod_Iterate for "42,35": 7
GreatestCommonDivisor Subtract_Iterate for "42,35": 7
GreatestCommonDivisor Mod_Recur for "42,35": 7
*/
#endif