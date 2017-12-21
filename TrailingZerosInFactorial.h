#ifndef TRAILING_ZEROS_IN_FACTORIAL_H
#define TRAILING_ZEROS_IN_FACTORIAL_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
https://leetcode.com/problems/factorial-trailing-zeroes/
Given an integer n, return the number of trailing zeroes in n!.
Note: Your solution should be in logarithmic time complexity.
Cracking the coding interview: Moderate
Trailing zeros are contributed by pairs of 5 and 2, because 5 * 2 = 10.
To count the number of pairs, we just have to count the number of multiples of 5.
Note that while 5 contributes to one multiple of 10, 25 contributes two (because 25 = 5 * 5).
=> count the number of factors of 5 from n!
*/
class TrailingZerosInFactorial
{
public:
	TrailingZerosInFactorial(){}
	~TrailingZerosInFactorial(){}

	int BruteForce(int n)//n! = 1 * 2 * 3 * ... * n
	{
		int count = 0;
		for (int i = 2; i <= n; ++i)
		{
			int f5 = this->factorsOf5(i);
			std::cout << "factorsOf5 in " << i << ": " << f5 << std::endl;
			count += f5;
		}

		std::cout << "TrailingZerosInFactorial BruteForce for \"" << n << "!\": " << count << std::endl;
		return count;
	}
private:
	int factorsOf5(int i)
	{
		int count = 0;
		while (i % 5 == 0)
		{
			++count;
			i /= 5;
		}
		return count;
	}

public:
	int Logarithmic(int n)//n! = 1 * 2 * 3 * ... * n
	{
		int count = 0;
		if (n < 0)
			return -1;

		for (long i = 5; i <= n; i *= 5)
		{
			int countFactor = n / i;
			std::cout << "count of nums in [1..." << n << "] that has factorOf" << i << ": " << countFactor << std::endl;
			count += countFactor;
		}
		/*
		count = count of nums in [1...n] that has factorOf5
		+ count of nums in [1...n] that has factorOf25
		+ count of nums in [1...n] that has factorOf125
		+ count of nums in [1...n] that has factorOf625
		+ ...
		*/

		std::cout << "TrailingZerosInFactorial Logarithmic for \"" << n << "!\": " << count << std::endl;
		return count;
	}


	void TestForFactorK(int n, int k)
	{
		//Brute Force
		int count1 = 0;
		for (int i = 2; i <= n; ++i)
		{
			int cur = i;
			while (cur % k == 0)
			{
				++count1;
				cur /= k;
			}
		}

		//Logarithmic
		int count2 = 0;
		for (int i = k; i <= n; i *= k)
		{
			count2 += n / i;
		}

		std::cout << "TrailingZerosInFactorial TestForFactorK for K=" << k << " in " << n << "!: " << count1 << ", " << count2 << std::endl;
	}
};
/*
factorsOf5 in 2: 0
factorsOf5 in 3: 0
factorsOf5 in 4: 0
factorsOf5 in 5: 1
factorsOf5 in 6: 0
factorsOf5 in 7: 0
factorsOf5 in 8: 0
factorsOf5 in 9: 0
factorsOf5 in 10: 1
factorsOf5 in 11: 0
factorsOf5 in 12: 0
factorsOf5 in 13: 0
factorsOf5 in 14: 0
factorsOf5 in 15: 1
factorsOf5 in 16: 0
factorsOf5 in 17: 0
factorsOf5 in 18: 0
factorsOf5 in 19: 0
factorsOf5 in 20: 1
factorsOf5 in 21: 0
factorsOf5 in 22: 0
factorsOf5 in 23: 0
factorsOf5 in 24: 0
factorsOf5 in 25: 2
factorsOf5 in 26: 0
factorsOf5 in 27: 0
TrailingZerosInFactorial BruteForce for "27!": 6
count of nums in [1...27] that has factorOf5: 5
count of nums in [1...27] that has factorOf25: 1
TrailingZerosInFactorial Logarithmic for "27!": 6
factorsOf5 in 2: 0
factorsOf5 in 3: 0
factorsOf5 in 4: 0
factorsOf5 in 5: 1
factorsOf5 in 6: 0
factorsOf5 in 7: 0
factorsOf5 in 8: 0
factorsOf5 in 9: 0
factorsOf5 in 10: 1
factorsOf5 in 11: 0
factorsOf5 in 12: 0
factorsOf5 in 13: 0
factorsOf5 in 14: 0
factorsOf5 in 15: 1
factorsOf5 in 16: 0
factorsOf5 in 17: 0
factorsOf5 in 18: 0
factorsOf5 in 19: 0
factorsOf5 in 20: 1
factorsOf5 in 21: 0
factorsOf5 in 22: 0
factorsOf5 in 23: 0
factorsOf5 in 24: 0
factorsOf5 in 25: 2
factorsOf5 in 26: 0
factorsOf5 in 27: 0
factorsOf5 in 28: 0
factorsOf5 in 29: 0
factorsOf5 in 30: 1
factorsOf5 in 31: 0
factorsOf5 in 32: 0
factorsOf5 in 33: 0
factorsOf5 in 34: 0
factorsOf5 in 35: 1
factorsOf5 in 36: 0
factorsOf5 in 37: 0
factorsOf5 in 38: 0
factorsOf5 in 39: 0
factorsOf5 in 40: 1
factorsOf5 in 41: 0
factorsOf5 in 42: 0
factorsOf5 in 43: 0
factorsOf5 in 44: 0
factorsOf5 in 45: 1
factorsOf5 in 46: 0
factorsOf5 in 47: 0
factorsOf5 in 48: 0
factorsOf5 in 49: 0
factorsOf5 in 50: 2
factorsOf5 in 51: 0
factorsOf5 in 52: 0
factorsOf5 in 53: 0
factorsOf5 in 54: 0
factorsOf5 in 55: 1
factorsOf5 in 56: 0
factorsOf5 in 57: 0
factorsOf5 in 58: 0
factorsOf5 in 59: 0
factorsOf5 in 60: 1
factorsOf5 in 61: 0
factorsOf5 in 62: 0
factorsOf5 in 63: 0
factorsOf5 in 64: 0
factorsOf5 in 65: 1
factorsOf5 in 66: 0
factorsOf5 in 67: 0
factorsOf5 in 68: 0
factorsOf5 in 69: 0
factorsOf5 in 70: 1
factorsOf5 in 71: 0
factorsOf5 in 72: 0
factorsOf5 in 73: 0
factorsOf5 in 74: 0
factorsOf5 in 75: 2
factorsOf5 in 76: 0
factorsOf5 in 77: 0
factorsOf5 in 78: 0
factorsOf5 in 79: 0
factorsOf5 in 80: 1
factorsOf5 in 81: 0
factorsOf5 in 82: 0
factorsOf5 in 83: 0
factorsOf5 in 84: 0
factorsOf5 in 85: 1
factorsOf5 in 86: 0
factorsOf5 in 87: 0
factorsOf5 in 88: 0
factorsOf5 in 89: 0
factorsOf5 in 90: 1
factorsOf5 in 91: 0
factorsOf5 in 92: 0
factorsOf5 in 93: 0
factorsOf5 in 94: 0
factorsOf5 in 95: 1
factorsOf5 in 96: 0
factorsOf5 in 97: 0
factorsOf5 in 98: 0
factorsOf5 in 99: 0
factorsOf5 in 100: 2
TrailingZerosInFactorial BruteForce for "100!": 24
count of nums in [1...100] that has factorOf5: 20
count of nums in [1...100] that has factorOf25: 4
TrailingZerosInFactorial Logarithmic for "100!": 24
TrailingZerosInFactorial TestForFactorK for K=2 in 1000!: 994, 994
TrailingZerosInFactorial TestForFactorK for K=3 in 1000!: 498, 498
TrailingZerosInFactorial TestForFactorK for K=7 in 1000!: 164, 164
TrailingZerosInFactorial TestForFactorK for K=9 in 1000!: 124, 124
*/
#endif