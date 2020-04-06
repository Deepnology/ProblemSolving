#ifndef NEXT_PRIME_H
#define NEXT_PRIME_H
#include <iostream>
#include "IsPrime.h"
/*
http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/CuckooHashTable.cpp
Return the next big prime number that is equal to or greater than n.

Google
http://www.careercup.com/question?id=5763123118080000
Write a method to return first five 10 digit prime numbers.
*/
class NextPrime
{
public:
	NextPrime(){}
	~NextPrime(){}

	int CheckOddNums(int n)
	{
		int res = this->checkOddNums(n);
		std::cout << "NextPrime CheckOddNums for \"" << n << "\": " << res << std::endl;
		return res;
	}

	int checkOddNums(int n)
	{
		if (n == 0 || n == 1 || n == 2)
			return 2;

		//1. if n is even (not prime), increment n
		if (n % 2 == 0)
			++n;

		//2. check n with increment of 2 (skip even numbers)
		while (!IsPrime().checkOddNums(n))
			n += 2;

		return n;
	}

	int Check6PlusMinus1(int n)
	{
		int res = this->check6PlusMinus1(n);
		std::cout << "NextPrime Check6PlusMinus1 for \"" << n << "\": " << res << std::endl;
		return res;
	}
	int check6PlusMinus1(int n)
	{
		if (n == 0 || n == 1 || n == 2)
			return 2;
		if (n == 3)
			return 3;

		int N = n;
		n = n - 1;
		//1. find the first number greater than n which is a multiple of 6
		while (n % 6 != 0)
			++n;

		//2. check if "multiple of 6 plus/minus 1" is a prime, advance n by 6
		while (true)
		{
			if (IsPrime().check6PlusMinus1(n - 1) && n - 1 >= N)
				return n - 1;
			if (IsPrime().check6PlusMinus1(n + 1))
				return n + 1;
			
			if (n < (INT_MAX - 6))
				n += 6;
			else
				return INT_MAX;
		}
	}
};
/*
NextPrime CheckOddNums for "48271": 48271
NextPrime CheckOddNums for "217": 223
NextPrime CheckOddNums for "4347": 4349
NextPrime Check6PlusMinus1 for "48271": 48271
NextPrime Check6PlusMinus1 for "217": 223
NextPrime Check6PlusMinus1 for "4347": 4349
NextPrime CheckOddNums for "0": 2
NextPrime Check6PlusMinus1 for "0": 2
NextPrime CheckOddNums for "1": 2
NextPrime Check6PlusMinus1 for "1": 2
NextPrime CheckOddNums for "2": 2
NextPrime Check6PlusMinus1 for "2": 2
NextPrime CheckOddNums for "3": 3
NextPrime Check6PlusMinus1 for "3": 3
NextPrime CheckOddNums for "4": 5
NextPrime Check6PlusMinus1 for "4": 5
NextPrime CheckOddNums for "5": 5
NextPrime Check6PlusMinus1 for "5": 5
NextPrime CheckOddNums for "6": 7
NextPrime Check6PlusMinus1 for "6": 7
NextPrime CheckOddNums for "7": 7
NextPrime Check6PlusMinus1 for "7": 7
NextPrime CheckOddNums for "8": 11
NextPrime Check6PlusMinus1 for "8": 11
NextPrime CheckOddNums for "9": 11
NextPrime Check6PlusMinus1 for "9": 11
NextPrime CheckOddNums for "1000000000": 1000000007
NextPrime CheckOddNums for "1000000008": 1000000009
NextPrime CheckOddNums for "1000000010": 1000000021
NextPrime CheckOddNums for "1000000022": 1000000033
NextPrime CheckOddNums for "1000000034": 1000000087
NextPrime Check6PlusMinus1 for "1000000000": 1000000007
NextPrime Check6PlusMinus1 for "1000000008": 1000000009
NextPrime Check6PlusMinus1 for "1000000010": 1000000021
NextPrime Check6PlusMinus1 for "1000000022": 1000000033
NextPrime Check6PlusMinus1 for "1000000034": 1000000087
*/
#endif