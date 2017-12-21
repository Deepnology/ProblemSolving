#ifndef ALL_PRIME_FACTORS_H
#define ALL_PRIME_FACTORS_H
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/print-all-prime-factors-of-a-given-number/
Given a number n, write an efficient function to print all prime factors of n.
12: 2, 2, 3
315: 3, 3, 5, 7
*/
class AllPrimeFactors
{
public:
	AllPrimeFactors(){}
	~AllPrimeFactors(){}

	std::vector<int> Solve(int n)
	{
		int before = n;
		std::vector<int> res;

		//1. remove all 2 factors
		while (n % 2 == 0)
		{
			res.push_back(2);
			n /= 2;
		}
		//now n must be odd

		//2. for i = 3 to sqrt(n), remove odd-number factors by incrementing 2
		for (int i = 3; i * i <= n; i += 2)
		{
			while (n % i == 0)
			{
				res.push_back(i);
				n /= i;
			}
		}

		//3. if n is a prime number and is greater than 2, then n will not become 1 by above steps
		if (n > 2)
			res.push_back(n);

		std::cout << "AllPrimeFactors for \"" << before << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
AllPrimeFactors for "345235": 5, 11, 6277
AllPrimeFactors for "315": 3, 3, 5, 7
*/
#endif