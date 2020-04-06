/*MUST*/
#ifndef ALL_NON_GREATER_PRIMES_H
#define ALL_NON_GREATER_PRIMES_H
#include <iostream>
#include <vector>
#include <deque>
#include "Debug.h"
/*
Leetcode: Count Primes
Count the number of prime numbers less than a non-negative number, n.
Elements of programming interview, Array: Enumerate all primes to n
http://www.geeksforgeeks.org/sieve-of-eratosthenes/
Given a number n, print all primes smaller than or equal to n.
It is also given that n is a small number.
10: 2, 3, 5, 7
20: 2, 3, 5, 7, 11, 13, 17, 19

The "Sieve of Eratosthenes" is one of the most efficient ways to find all primes smaller than n when n is smaller than 10 million or so.

Sieve: O(n/2 + n/3 + n/5 + n/7 + n/11 + ....) = O(n * log log n) time, O(n) space

TrialDivision: O(n^(3/2) / (logn)^2) time, which is theoretically superior, O(n/2) space
Cache and test only odd numbers
Mark multiples of current odd number as false in prime
*/
class AllNonGreaterPrimes
{
public:
	AllNonGreaterPrimes(){}
	~AllNonGreaterPrimes(){}

	std::vector<int> TrialDivision(int n)
	{
		const int kSize = (int)floor(0.5 * (n - 3)) + 1;
		std::vector<int> isPrime(kSize, 1);
		//isPrime[i]: 1 means (2i+3) is a prime
		//idx:       0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13,
		//num(2i+3): 3,  5,  7,  9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29,
		for (int i = 0; i < kSize; ++i)
		{
			if (!isPrime[i])
				continue;

			//now (2i+3) is a prime: mark all (2i+3)'s multiples as non-prime starting from (2i+3)^2 = 4i^2+12i+9
			//the corresponding idx of num (4i^2+12i+9) is (2i^2+6i+3)

			//2 * idx + 3 = 4i^2 + 12i + 9
			//idx = ((4i^2 + 12i + 9) - 3)/2 = 2i^2 + 6i + 3
			for (int j = ((i*i) * 2) + 6 * i + 3; j < kSize; j += (2*i + 3))
				isPrime[j] = 0;
		}

		std::vector<int> res;
		res.push_back(2);
		for (int i = 0; i < kSize; ++i)
			if (isPrime[i])
				res.push_back(2 * i + 3);

		std::cout << "AllNonGreaterPrimes TrialDivision for \"" << n << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> Sieve(int n)
	{
		std::vector<int> isPrime(n + 1, 1);
		//isPrime[i]: 1 means i is a prime

		for (int i = 2; i * i <= n; ++i)//starting from 2
		{
			if (!isPrime[i])
				continue;

			//now i is a prime: mark all i's multiples as non-prime starting from i^2
			for (int j = i * i; j <= n; j += i)
				isPrime[j] = 0;
		}

		std::vector<int> res;
		for (int i = 2; i <= n; ++i)
			if (isPrime[i])
				res.push_back(i);

		std::cout << "AllNonGreaterPrimes Sieve for \"" << n << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	//leetcode
	std::vector<int> Sieve_LessThan(int n)
	{
		std::vector<int> isPrime(n, 1);
		//isPrime[i]: 1 means i is a prime

		for (int i = 2; i * i < n; ++i)//starting from 2
		{
			if (!isPrime[i])
				continue;

			//now i is a prime: mark all i's multiples as non-prime starting from i^2
			for (int j = i * i; j < n; j += i)
				isPrime[j] = 0;
		}

		std::vector<int> res;
		for (int i = 2; i < n; ++i)
			if (isPrime[i])
				res.push_back(i);

		std::cout << "AllNonGreaterPrimes Sieve_LessThan for \"" << n << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
AllNonGreaterPrimes TrialDivision for "70": 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67
AllNonGreaterPrimes Sieve for "70": 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67
AllNonGreaterPrimes Sieve_LessThan for "70": 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67
*/
#endif