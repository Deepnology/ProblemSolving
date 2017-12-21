/*MUST*/
#ifndef DIVIDE_2_INT_WO_MUL_DIV_MOD_H
#define DIVIDE_2_INT_WO_MUL_DIV_MOD_H
#include <string>
#include <iostream>
#include <sstream>
/*
Elements of programming interview, PrimitiveTypes: Compute x/y
Leetcode: Divide Two Integers
// Divide two integers without using multiplication, division and mod operator.
// If it is overflow, return MAX_INT.

INT_MAX =  2147483647
INT_MIN = -2147483648
INT_MIN/-1 > INT_MAX, overflow
*/
class Divide2IntWoMulDivMod
{
public:
	Divide2IntWoMulDivMod(){}
	~Divide2IntWoMulDivMod(){}

	//this one passes online judge
	int Simplest(int dividend, int divisor)//best
	{
		if (divisor == 0)
			return dividend >= 0 ? INT_MAX : INT_MIN;
		if (dividend == INT_MIN && divisor == -1)//overflow
			return INT_MAX;

		bool isNegative = false;
		if (dividend < 0 && divisor > 0 || dividend > 0 && divisor < 0)
			isNegative = true;

		long long dvd = std::abs((long long)dividend);
		long long dvs = std::abs((long long)divisor);

		int res = 0;
		while (dvs <= dvd)
		{
			//find the largest i such that dvs*2^i <= dvd, and subtract dvs*2^i from dvd
			int i = 0;
			while ((dvs << (i + 1)) <= dvd)// dvs*2^i <= dvd
				++i;
			dvd -= (dvs << i);// dvd -= dvs*2^i
			res += (1 << i);// res += 2^i
		}

		int quotient = isNegative ? (int)(0 - res) : (int)res;
		std::cout << "Divide2IntWoMulDivMod Simplest for \"" << dividend << "\" and \"" << divisor << "\": " << quotient << std::endl;
		return quotient;
	}

	//this one passes online judge
	int MultiplicationBinarySearch(int dividend, int divisor)
	{
		if (divisor == 0)
			return dividend >= 0 ? INT_MAX : INT_MIN;
		if (dividend == INT_MIN && divisor == -1)//overflow
			return INT_MAX;

		bool isNegative = false;
		if (dividend < 0 && divisor > 0 || dividend > 0 && divisor < 0)
			isNegative = true;

		unsigned long long dvd = std::abs((long long)dividend);
		unsigned long long dvs = std::abs((long long)divisor);

		int i = 0;//number of multiplications of 2
		//1. find i such that dvs*2^i <= dvd < dvs*2^(i+1)
		//apporach1. linear search bit
		
		//while (dvs << (i + 1) <= dvd)
		//	++i;

		//approach2. binary search bit, see aslo IndexOfOnlyOneSetBit.h
		int left = 0;
		int right = 31;
		while (left <= right)
		{
			int mid = (left + right) / 2;
			if (dvs << mid >= dvd)// dvs*2^mid >= dvd
				right = mid - 1;
			else// dvs*2^mid < dvd
				left = mid + 1;
		}
		i = left;

		//2. subtract dvd by dvs*2^i and add 2^i to res until dvs > dvd
		int res = 0;
		while (dvs <= dvd)
		{
			if ((dvs << i) <= dvd)// dvs*2^i <= dvd
			{
				dvd -= dvs << i;// subtract dvs*2^i
				res += 1 << i;// add 2^i
			}
			--i;
		}

		int quotient = isNegative ? (int)(0 - res) : (int)res;
		std::cout << "Divide2IntWoMulDivMod MultiplicationBinarySearch for \"" << dividend << "\" and \"" << divisor << "\": " << quotient << std::endl;
		return quotient;
	}

	unsigned BinarySearch_Unsigned(unsigned dividend, unsigned divisor)//dividend / divisor = quotient ... remainder
	{
		unsigned positiveDividend = dividend;
		unsigned positiveDivisor = divisor;
		unsigned quotient = 0;

		while (positiveDividend >= positiveDivisor)
		{
			/*1. binary search for the lower bound of counts of multiplication of 2 of positiveDivisor toward positiveDividend*/
			int left = -1;
			int right = 32;
			while (right - left > 1)
			{
				int middle = (left + right) / 2;
				//std::cout << left << "," << right << " -> " << middle << std::endl;
				if ((positiveDivisor << middle) >= positiveDividend)
					right = middle;
				else
					left = middle;
			}

			/*
			2. now "right" is the lower bound of count of multiplication of 2 of positiveDivisor toward positiveDividend
			   subtract it from positiveDividend
			   add quotient
			*/
			unsigned maxDivisorMultiplicationOf2 = positiveDivisor << right;
			if (maxDivisorMultiplicationOf2 > positiveDividend)//lower bound is equivalent to upper bound
			{
				positiveDividend -= positiveDivisor << (right - 1);
				quotient += 1LL << (right - 1);
			}
			else//maxDivisorMultiplicationOf2 == positiveDividend
			{
				if (maxDivisorMultiplicationOf2 != positiveDividend)
					std::cout << "Divide2IntWoMulDivMod BinarySearch Error: invalid lower bound" << std::endl;
				positiveDividend -= positiveDivisor << (right);
				quotient += 1LL << (right);
			}
			//std::cout << positiveDividend << "," << quotient << "," << right << std::endl;
		}

		std::cout << "Divide2IntWoMulDivMod BinarySearch_Unsigned for \"" << dividend << "\" and \"" << divisor << "\": " << quotient << std::endl;
		return quotient;
	}

	unsigned LinearSearch_Unsigned(unsigned dividend, unsigned divisor)//dividend / divisor = quotient ... remainder
	{
		unsigned positiveDividend = dividend;
		unsigned positiveDivisor = divisor;
		unsigned quotient = 0;

		while (positiveDividend >= positiveDivisor)
		{
			int countMultiplicationOf2 = 1;

			/*
			1. linearly accumulate countMultiplicationOf2
			check (positiveDivisor << countMultiplicationOf2) >= (positiveDivisor << (countMultiplicationOf2 - 1)) to prevent potential overflow of unsigned
			*/
			while ((positiveDivisor << countMultiplicationOf2) >= (positiveDivisor << (countMultiplicationOf2 - 1)) && (positiveDivisor << countMultiplicationOf2) <= positiveDividend)
			{
				++countMultiplicationOf2;
			}

			/*2. subtract maxDivisorMultiply2 from positiveDividend*/
			positiveDividend -= positiveDivisor << (countMultiplicationOf2 - 1);

			/*3. add the quotient from countMultiplicationOf2*/
			quotient += 1U << (countMultiplicationOf2 - 1);
		}

		std::cout << "Divide2IntWoMulDivMod LinearSearch_Unsigned for \"" << dividend << "\" and \"" << divisor << "\": " << quotient << std::endl;
		return quotient;
	}

	int LinearSearch(int dividend, int divisor)//dividend / divisor = quotient ... remainder
	{
		int sign = 1;
		long long positiveDividend = dividend;
		long long positiveDivisor = divisor;
		if (positiveDividend < 0)
			positiveDividend = -positiveDividend, sign = -sign;
		if (positiveDivisor < 0)
			positiveDivisor = -positiveDivisor, sign = -sign;

		long long quotient = 0;

		while (positiveDividend >= positiveDivisor)
		{
			int countMultiplicationOf2 = 0;
			long long maxDivisorMultiply2 = positiveDivisor;

			/*1. shift maxDivisorMultiply2, and linearly accumulate countMultiplicationOf2*/
			while ((maxDivisorMultiply2 << 1) <= positiveDividend)
			{
				maxDivisorMultiply2 <<= 1;//maxDivisorMultiply2 *= 2
				++countMultiplicationOf2;
			}

			/*2. subtract maxDivisorMultiply2 from positiveDividend*/
			positiveDividend -= maxDivisorMultiply2;

			/*3. insert the quotient bit from countMultiplicationOf2*/
			long long a = ((long long)1 << countMultiplicationOf2);//transform countMultiplicationOf2 to a bit (binary representation)
			quotient |= a;//insert the countMulitplicationOf2 bit to binary quotient
		}

		std::cout << "Divide2IntWoMulDivMod LinearSearch for \"" << dividend << "\" and \"" << divisor << "\": " << sign * quotient << std::endl;
		return (int)(sign * quotient);
	}




};
/*
Divide2IntWoMulDivMod Simplest for "56" and "7": 8
Divide2IntWoMulDivMod Simplest for "77" and "8": 9
Divide2IntWoMulDivMod Simplest for "-56" and "7": -8
Divide2IntWoMulDivMod Simplest for "-77" and "-8": 9
Divide2IntWoMulDivMod MultiplicationBinarySearch for "56" and "7": 8
Divide2IntWoMulDivMod MultiplicationBinarySearch for "77" and "8": 9
Divide2IntWoMulDivMod BinarySearch_Unsigned for "56" and "7": 8
Divide2IntWoMulDivMod BinarySearch_Unsigned for "77" and "8": 9
Divide2IntWoMulDivMod LinearSearch_Unsigned for "56" and "7": 8
Divide2IntWoMulDivMod LinearSearch_Unsigned for "77" and "8": 9
Divide2IntWoMulDivMod LinearSearch for "-56" and "7": -8
Divide2IntWoMulDivMod LinearSearch for "-77" and "-8": 9
*/
#endif