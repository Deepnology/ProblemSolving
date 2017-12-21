/*MUST*/
#ifndef MIN_NUM_BY_ALL_SINGLE_DIGIT_FACTORS_H
#define MIN_NUM_BY_ALL_SINGLE_DIGIT_FACTORS_H
#include <iostream>
#include <string>
#include <vector>
/*
Leetcode: Minimum Factorization
http://www.geeksforgeeks.org/find-smallest-number-whose-digits-multiply-given-number-n/
Given a number "n", find the smallest number "p" such that if we multiply all digits of "p", we get "n".
The result "p" should have minimum two digits.

7: 17 (1*7=7)
36: 49 (4*9=36)
100: 455 (4*5*5=100)
13: not possible

Algorithm
Find all factors in [9,2] of the target num. (search from 9 to 2 to keep the total number of digits minimized)
If the target num can be broken into factors in [9,2], then the min solution should be a number with all the factors in [9,2] in reversed order.
Otherwise, there is no solution.
*/
class MinNumByAllSingleDigitFactors
{
public:
	MinNumByAllSingleDigitFactors() {}
	~MinNumByAllSingleDigitFactors() {}

	int Solve(int n)
	{
		int before = n;
		int res;
		if (n < 10)
		{
			/*1. n is in 0~9: 10~19*/
			res = n + 10;
		}
		else
		{
			/*
			2. find all factors of n which are between 2 and 9 (both inclusive)
			start searching from 9 so that the number of digits in result are minimized
			(9 is preferred over 33, and 8 is preferred over 24)
			*/
			std::vector<int> factor9to2;
			for (int i = 9; i > 1; --i)
			{
				while (n % i == 0)
				{
					n /= i;//remove all n's factors from 9 to 2
					factor9to2.push_back(i);
				}
			}

			/*2.1 n cannot be broken in form of digits, at least one of its prime factors is greater than 9*/
			if (n > 10)
				res = -1;
			else
			{
				/*2.2 reverse the factors*/
				res = 0;
				for (int i = (int)factor9to2.size() - 1; i >= 0; --i)
					res = res * 10 + factor9to2[i];
			}
		}

		std::cout << "MinNumByAllSingleDigitFactors for \"" << before << "\": " << res << std::endl;
		return res;
	}
};
/*
MinNumByAllSingleDigitFactors for "7": 17
MinNumByAllSingleDigitFactors for "100": 455
MinNumByAllSingleDigitFactors for "27": 39
MinNumByAllSingleDigitFactors for "31": -1
*/
#endif
