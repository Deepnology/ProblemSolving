#ifndef SUM_OF_AT_MOST_4_PERFECT_SQUARES_H
#define SUM_OF_AT_MOST_4_PERFECT_SQUARES_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Perfect Squares
Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.
For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13, return 2 because 13 = 4 + 9.

FourSquareTheorem: every natural number can be represented as the sum of four integer squares
==> the number of perfect square numbers (1,4,9,16,...) which sum to n is AT MOST 4, but can still be less than 4
*/
class SumOfAtMost4PerfectSquares
{
public:
	SumOfAtMost4PerfectSquares() {}
	~SumOfAtMost4PerfectSquares() {}

	int FourSquareTheorem(int n)
	{
		int N = n;

		int res;//res is AT MOST 4

		//1. remove factor of 4, which doesn't affect the result
		while (n % 4 == 0)
			n /= 4;

		//2. res must be 4 if n mod 8 is 7 (don't know why)
		if (n % 8 == 7)
			res = 4;
		else//res can be 3 or 2 or 1
		{
			res = 3;

			//3. enumerate all pair perfect squares that sum to n
			for (int a = 0; a*a <= n; ++a)
			{
				int b = (int)sqrt(n - a*a);
				if (a*a + b*b == n)
				{
					res = !!a + !!b;//!! is to transform a non-zero to 1, and zero to zero, so res can be 1 or 2 (0 is impossible)
					break;
				}
			}
		}

		std::cout << "SumOfAtMost4PerfectSquares FourSquareTheorem for \"" << N << "\": " << res << std::endl;
		return res;
	}

	int DP(int n)
	{
		std::vector<int> dp(n + 1, INT_MAX);
		dp[0] = 0;
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 1; j * j <= i; ++j)
				dp[i] = std::min(dp[i], dp[i - j*j] + 1);
		}

		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "SumOfAtMost4PerfectSquares DP for \"" << n << "\": " << dp[n] << std::endl;
		return dp[n];
	}
};
/*
PerfectSquares FourSquareTheorem for "1": 1
0, 1
PerfectSquares DP for "1": 1
PerfectSquares FourSquareTheorem for "2": 2
0, 1, 2
PerfectSquares DP for "2": 2
PerfectSquares FourSquareTheorem for "3": 3
0, 1, 2, 3
PerfectSquares DP for "3": 3
PerfectSquares FourSquareTheorem for "4": 1
0, 1, 2, 3, 1
PerfectSquares DP for "4": 1
PerfectSquares FourSquareTheorem for "5": 2
0, 1, 2, 3, 1, 2
PerfectSquares DP for "5": 2
PerfectSquares FourSquareTheorem for "6": 3
0, 1, 2, 3, 1, 2, 3
PerfectSquares DP for "6": 3
PerfectSquares FourSquareTheorem for "7": 4
0, 1, 2, 3, 1, 2, 3, 4
PerfectSquares DP for "7": 4
PerfectSquares FourSquareTheorem for "8": 2
0, 1, 2, 3, 1, 2, 3, 4, 2
PerfectSquares DP for "8": 2
PerfectSquares FourSquareTheorem for "9": 1
0, 1, 2, 3, 1, 2, 3, 4, 2, 1
PerfectSquares DP for "9": 1
PerfectSquares FourSquareTheorem for "10": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2
PerfectSquares DP for "10": 2
PerfectSquares FourSquareTheorem for "11": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3
PerfectSquares DP for "11": 3
PerfectSquares FourSquareTheorem for "12": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3
PerfectSquares DP for "12": 3
PerfectSquares FourSquareTheorem for "13": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2
PerfectSquares DP for "13": 2
PerfectSquares FourSquareTheorem for "14": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3
PerfectSquares DP for "14": 3
PerfectSquares FourSquareTheorem for "15": 4
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4
PerfectSquares DP for "15": 4
PerfectSquares FourSquareTheorem for "16": 1
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1
PerfectSquares DP for "16": 1
PerfectSquares FourSquareTheorem for "17": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2
PerfectSquares DP for "17": 2
PerfectSquares FourSquareTheorem for "18": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2
PerfectSquares DP for "18": 2
PerfectSquares FourSquareTheorem for "19": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3
PerfectSquares DP for "19": 3
PerfectSquares FourSquareTheorem for "20": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2
PerfectSquares DP for "20": 2
PerfectSquares FourSquareTheorem for "21": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3
PerfectSquares DP for "21": 3
PerfectSquares FourSquareTheorem for "22": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3
PerfectSquares DP for "22": 3
PerfectSquares FourSquareTheorem for "23": 4
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4
PerfectSquares DP for "23": 4
PerfectSquares FourSquareTheorem for "24": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3
PerfectSquares DP for "24": 3
PerfectSquares FourSquareTheorem for "25": 1
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1
PerfectSquares DP for "25": 1
PerfectSquares FourSquareTheorem for "26": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2
PerfectSquares DP for "26": 2
PerfectSquares FourSquareTheorem for "27": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3
PerfectSquares DP for "27": 3
PerfectSquares FourSquareTheorem for "28": 4
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4
PerfectSquares DP for "28": 4
PerfectSquares FourSquareTheorem for "29": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2
PerfectSquares DP for "29": 2
PerfectSquares FourSquareTheorem for "30": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3
PerfectSquares DP for "30": 3
PerfectSquares FourSquareTheorem for "31": 4
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4
PerfectSquares DP for "31": 4
PerfectSquares FourSquareTheorem for "32": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2
PerfectSquares DP for "32": 2
PerfectSquares FourSquareTheorem for "33": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3
PerfectSquares DP for "33": 3
PerfectSquares FourSquareTheorem for "34": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2
PerfectSquares DP for "34": 2
PerfectSquares FourSquareTheorem for "35": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3
PerfectSquares DP for "35": 3
PerfectSquares FourSquareTheorem for "36": 1
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1
PerfectSquares DP for "36": 1
PerfectSquares FourSquareTheorem for "37": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2
PerfectSquares DP for "37": 2
PerfectSquares FourSquareTheorem for "38": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3
PerfectSquares DP for "38": 3
PerfectSquares FourSquareTheorem for "39": 4
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4
PerfectSquares DP for "39": 4
PerfectSquares FourSquareTheorem for "40": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2
PerfectSquares DP for "40": 2
PerfectSquares FourSquareTheorem for "41": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2
PerfectSquares DP for "41": 2
PerfectSquares FourSquareTheorem for "42": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3
PerfectSquares DP for "42": 3
PerfectSquares FourSquareTheorem for "43": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3
PerfectSquares DP for "43": 3
PerfectSquares FourSquareTheorem for "44": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3
PerfectSquares DP for "44": 3
PerfectSquares FourSquareTheorem for "45": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2
PerfectSquares DP for "45": 2
PerfectSquares FourSquareTheorem for "46": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3
PerfectSquares DP for "46": 3
PerfectSquares FourSquareTheorem for "47": 4
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4
PerfectSquares DP for "47": 4
PerfectSquares FourSquareTheorem for "48": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3
PerfectSquares DP for "48": 3
PerfectSquares FourSquareTheorem for "49": 1
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1
PerfectSquares DP for "49": 1
PerfectSquares FourSquareTheorem for "50": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2
PerfectSquares DP for "50": 2
PerfectSquares FourSquareTheorem for "51": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3
PerfectSquares DP for "51": 3
PerfectSquares FourSquareTheorem for "52": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2
PerfectSquares DP for "52": 2
PerfectSquares FourSquareTheorem for "53": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2
PerfectSquares DP for "53": 2
PerfectSquares FourSquareTheorem for "54": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3
PerfectSquares DP for "54": 3
PerfectSquares FourSquareTheorem for "55": 4
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4
PerfectSquares DP for "55": 4
PerfectSquares FourSquareTheorem for "56": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3
PerfectSquares DP for "56": 3
PerfectSquares FourSquareTheorem for "57": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3
PerfectSquares DP for "57": 3
PerfectSquares FourSquareTheorem for "58": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2
PerfectSquares DP for "58": 2
PerfectSquares FourSquareTheorem for "59": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3
PerfectSquares DP for "59": 3
PerfectSquares FourSquareTheorem for "60": 4
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4
PerfectSquares DP for "60": 4
PerfectSquares FourSquareTheorem for "61": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2
PerfectSquares DP for "61": 2
PerfectSquares FourSquareTheorem for "62": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3
PerfectSquares DP for "62": 3
PerfectSquares FourSquareTheorem for "63": 4
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4
PerfectSquares DP for "63": 4
PerfectSquares FourSquareTheorem for "64": 1
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1
PerfectSquares DP for "64": 1
PerfectSquares FourSquareTheorem for "65": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2
PerfectSquares DP for "65": 2
PerfectSquares FourSquareTheorem for "66": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3
PerfectSquares DP for "66": 3
PerfectSquares FourSquareTheorem for "67": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3
PerfectSquares DP for "67": 3
PerfectSquares FourSquareTheorem for "68": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2
PerfectSquares DP for "68": 2
PerfectSquares FourSquareTheorem for "69": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3
PerfectSquares DP for "69": 3
PerfectSquares FourSquareTheorem for "70": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3
PerfectSquares DP for "70": 3
PerfectSquares FourSquareTheorem for "71": 4
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4
PerfectSquares DP for "71": 4
PerfectSquares FourSquareTheorem for "72": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2
PerfectSquares DP for "72": 2
PerfectSquares FourSquareTheorem for "73": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2
PerfectSquares DP for "73": 2
PerfectSquares FourSquareTheorem for "74": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2
PerfectSquares DP for "74": 2
PerfectSquares FourSquareTheorem for "75": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3
PerfectSquares DP for "75": 3
PerfectSquares FourSquareTheorem for "76": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3, 3
PerfectSquares DP for "76": 3
PerfectSquares FourSquareTheorem for "77": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3, 3, 3
PerfectSquares DP for "77": 3
PerfectSquares FourSquareTheorem for "78": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3, 3, 3, 3
PerfectSquares DP for "78": 3
PerfectSquares FourSquareTheorem for "79": 4
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3, 3, 3, 3, 4
PerfectSquares DP for "79": 4
PerfectSquares FourSquareTheorem for "80": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3, 3, 3, 3, 4, 2
PerfectSquares DP for "80": 2
PerfectSquares FourSquareTheorem for "81": 1
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3, 3, 3, 3, 4, 2, 1
PerfectSquares DP for "81": 1
PerfectSquares FourSquareTheorem for "82": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3, 3, 3, 3, 4, 2, 1, 2
PerfectSquares DP for "82": 2
PerfectSquares FourSquareTheorem for "83": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3, 3, 3, 3, 4, 2, 1, 2, 3
PerfectSquares DP for "83": 3
PerfectSquares FourSquareTheorem for "84": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3, 3, 3, 3, 4, 2, 1, 2, 3, 3
PerfectSquares DP for "84": 3
PerfectSquares FourSquareTheorem for "85": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3, 3, 3, 3, 4, 2, 1, 2, 3, 3, 2
PerfectSquares DP for "85": 2
PerfectSquares FourSquareTheorem for "86": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3, 3, 3, 3, 4, 2, 1, 2, 3, 3, 2, 3
PerfectSquares DP for "86": 3
PerfectSquares FourSquareTheorem for "87": 4
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3, 3, 3, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4
PerfectSquares DP for "87": 4
PerfectSquares FourSquareTheorem for "88": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3, 3, 3, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 3
PerfectSquares DP for "88": 3
PerfectSquares FourSquareTheorem for "89": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3, 3, 3, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 3, 2
PerfectSquares DP for "89": 2
PerfectSquares FourSquareTheorem for "90": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3, 3, 3, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 3, 2, 2
PerfectSquares DP for "90": 2
PerfectSquares FourSquareTheorem for "91": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3, 3, 3, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 3, 2, 2, 3
PerfectSquares DP for "91": 3
PerfectSquares FourSquareTheorem for "92": 4
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3, 3, 3, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 3, 2, 2, 3, 4
PerfectSquares DP for "92": 4
PerfectSquares FourSquareTheorem for "93": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3, 3, 3, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 3, 2, 2, 3, 4, 3
PerfectSquares DP for "93": 3
PerfectSquares FourSquareTheorem for "94": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3, 3, 3, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 3, 2, 2, 3, 4, 3, 3
PerfectSquares DP for "94": 3
PerfectSquares FourSquareTheorem for "95": 4
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3, 3, 3, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 3, 2, 2, 3, 4, 3, 3, 4
PerfectSquares DP for "95": 4
PerfectSquares FourSquareTheorem for "96": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3, 3, 3, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 3, 2, 2, 3, 4, 3, 3, 4, 3
PerfectSquares DP for "96": 3
PerfectSquares FourSquareTheorem for "97": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3, 3, 3, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 3, 2, 2, 3, 4, 3, 3, 4, 3, 2
PerfectSquares DP for "97": 2
PerfectSquares FourSquareTheorem for "98": 2
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3, 3, 3, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 3, 2, 2, 3, 4, 3, 3, 4, 3, 2, 2
PerfectSquares DP for "98": 2
PerfectSquares FourSquareTheorem for "99": 3
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3, 3, 3, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 3, 2, 2, 3, 4, 3, 3, 4, 3, 2, 2, 3
PerfectSquares DP for "99": 3
PerfectSquares FourSquareTheorem for "100": 1
0, 1, 2, 3, 1, 2, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 3, 1, 2, 3, 4, 2, 3, 4, 2, 3, 2, 3, 1, 2, 3, 4, 2, 2, 3, 3, 3, 2, 3, 4, 3, 1, 2, 3, 2, 2, 3, 4, 3, 3, 2, 3, 4, 2, 3, 4, 1, 2, 3, 3, 2, 3, 3, 4, 2, 2, 2, 3, 3, 3, 3, 4, 2, 1, 2, 3, 3, 2, 3, 4, 3, 2, 2, 3, 4, 3, 3, 4, 3, 2, 2, 3, 1
PerfectSquares DP for "100": 1
*/
#endif
