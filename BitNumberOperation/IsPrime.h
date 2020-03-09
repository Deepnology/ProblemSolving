#ifndef IS_PRIME_H
#define IS_PRIME_H
#include <iostream>
/*
http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/CuckooHashTable.cpp
http://www.careercup.com/question?id=5763123118080000

Check6PlusMinus1:
All primes are in the form of 6*i-1 or 6*i+1.
But not all numbers in the form of 6*i-1 or 6*i+1 are primes.
=> Only numbers that are not multiples of 2 and 3, and are also in the form of 6*i-1 or 6*i+1 are primes.
Proof:
For any number % 6, the remainder can be 0, 1, 2, 3, 4, 5
If the remainder is 0, 2, 4, then the number is divisible by 2, which cannot be prime.
If the remainder is 3, then the number is divisible by 3, which cannot be prime.
So if the number is prime, the remainder is either
1 (and the number is 6*i+1) or
5 (and the number is 6*i-1)
*/
class IsPrime
{
public:
	IsPrime(){}
	~IsPrime(){}

	bool CheckOddNums(int n)
	{
		bool res = this->checkOddNums(n);
		std::cout << "IsPrime CheckOddNums for \"" << n << "\": " << res << std::endl;
		return res;
	}

	bool checkOddNums(int n)
	{
		if (n == 1)
			return false;
		if (n == 2 || n == 3)
			return true;
		if (n % 2 == 0)
			return false;

		/*
		for i = 3 to sqrt(n)
		(for any non prime number, one of its factors is smaller or equal to its sqrt)
		(we check only odd numbers by skipping all even numbers by incrementing 2 till its sqrt)
		*/
		for (int i = 3; i * i <= n; i += 2)
		{
			if (n % i == 0)
				return false;
		}
		return true;
	}

	bool Check6PlusMinus1(int n)
	{
		bool res = this->check6PlusMinus1(n);
		std::cout << "IsPrime Check6PlusMinus1 for \"" << n << "\": " << res << std::endl;
		return res;
	}

	bool check6PlusMinus1(int n)
	{
		if (n == 1)
			return false;
		if (n == 2 || n == 3)
			return true;
		if (n % 2 == 0 || n % 3 == 0)
			return false;

		/*
		for i = 1 to the max value of (6*i-1)^2 that is smaller or equal to n
		(6*i-1)^2 = 36*i^2 - 12*i - 1 should be <= n
		36*i^2 - 12*i < n
		we have already checked 2 and 3, and so for 0, 4, 6
		now need to check if n is a multiple of 6*i+1 or 6*i-1
		*/
		for (int i = 1; 36 * i * i - 12 * i < n; ++i)
		{
			if (n % (6 * i + 1) == 0 || n % (6 * i - 1) == 0)
				return false;
		}
		return true;
	}
};
/*
IsPrime CheckOddNums for "48271": 1
IsPrime CheckOddNums for "217": 0
IsPrime Check6PlusMinus1 for "48271": 1
IsPrime Check6PlusMinus1 for "217": 0
*/
#endif