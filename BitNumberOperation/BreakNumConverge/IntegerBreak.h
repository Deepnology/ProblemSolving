#ifndef INTEGER_BREAK_H
#define INTEGER_BREAK_H
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "Debug.h"
/*
Leetcode: Integer Break
Given a positive integer n, break it into the sum of at least two positive integers and maximize the product of those integers.
Return the maximum product you can get.
For example, given n = 2, return 1 (2 = 1 + 1); given n = 10, return 36 (10 = 3 + 3 + 4).
Note: you may assume that n is not less than 2.
Hint:
There is a simple O(n) solution to this problem.
You may check the breaking results of n ranging from 7 to 10 to discover the regularities.
2  ->  1 * 1
3  ->  2 * 1

4  ->  2 * 2				3^0 * 4
5  ->  3 * 2				3^1 * 2
6  ->  3 * 3				3^2

7  ->  3 * 2 * 2			3^1 * 4
8  ->  3 * 3 * 2			3^2 * 2
9  ->  3 * 3 * 3			3^3

10 ->  3 * 3 * 2 * 2		3^2 * 4
11 ->  3 * 3 * 3 * 2		3^3 * 2
12 ->  3 * 3 * 3 * 3		3^4

n%3==1: 3^(n/3-1) * 4
n%3==2: 3^(n/3) * 2
n%3==0: 3^(n/3)

Recur: O(2^n) time
DP: O(n) time
Observation: O(1) time
see also MaxProductCutting.h
*/
class IntegerBreak
{
public:
	IntegerBreak() {}
	~IntegerBreak() {}

	int Recur(int n)
	{
		int res = this->recur(n);
		std::cout << "Integer Break Recur for \"" << n << "\": " << res << std::endl;
		return res;
	}
	int recur(int n)
	{
		if (n == 1)
			return 0;//0*1
		if (n == 2)
			return 1;//1*1
		if (n == 3)
			return 2;//2*1

		return std::max(2 * std::max(n - 2, this->recur(n - 2)), 3 * std::max(n - 3, this->recur(n - 3)));
	}

	int DP(int n)
	{
		if (n == 1)
			return 0;//0*1
		if (n == 2)
			return 1;//1*1
		if (n == 3)
			return 2;//2*1

		std::vector<int> dp(n + 1, 0);
		dp[1] = 0;
		dp[2] = 2;//max(2 (no break), 1*1)
		dp[3] = 3;//max(3 (no break), 2*1)
		for (int i = 4; i <= n; ++i)
			dp[i] = std::max(2 * dp[i - 2], 3 * dp[i - 3]);

		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "Integer Break DP for \"" << n << "\": " << dp[n] << std::endl;
		return dp[n];
	}

	int FromObservation(int n)
	{
		if (n == 1)
			return 0;//0*1
		if (n == 2)
			return 1;//1*1
		if (n == 3)
			return 2;//2*1

		int res;
		if (n % 3 == 0)
			res = (int)std::pow(3, n / 3);
		else if (n % 3 == 2)
			res = (int)std::pow(3, n / 3) * 2;
		else
			res = (int)std::pow(3, n / 3 - 1) * 4;

		std::cout << "IntegerBreak FromObservation for \"" << n << "\": " << res << std::endl;
		return res;
	}
};
/*
Integer Break Recur for "10": 36
0, 0, 2, 3, 4, 6, 9, 12, 18, 27, 36
Integer Break DP for "10": 36
IntegerBreak FromObservation for "10": 36
Integer Break Recur for "40": 2125764
0, 0, 2, 3, 4, 6, 9, 12, 18, 27, 36, 54, 81, 108, 162, 243, 324, 486, 729, 972, 1458, 2187, 2916, 4374, 6561, 8748, 13122, 19683, 26244, 39366, 59049, 78732, 118098, 177147, 236196, 354294, 531441, 708588, 1062882, 1594323, 2125764
Integer Break DP for "40": 2125764
IntegerBreak FromObservation for "40": 2125764
*/
#endif
