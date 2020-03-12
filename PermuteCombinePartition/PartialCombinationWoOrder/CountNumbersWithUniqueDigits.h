#ifndef COUNT_NUMBERS_WITH_UNIQUE_DIGITS_H
#define COUNT_NUMBERS_WITH_UNIQUE_DIGITS_H
#include "Debug.h"
/*
Leetcode: Count Numbers With Unique Digits
Given a non-negative integer n, count all numbers with unique digits, x, where 0 <= x < 10^n.

Example:
Given n = 2, return 91. (The answer should be the total numbers in the range of 0 <= x < 100, excluding [11,22,33,44,55,66,77,88,99])

Hint:
1. A direct way is to use the backtracking approach.
2. Backtracking should contains three states which are (the current number, number of steps to get that number and a bitmask which represent which number is marked as visited so far in the current number).
Start with state (0,0,0) and count all valid number till we reach number of steps equals to 10^n.
3. This problem can also be solved using a dynamic programming approach and some knowledge of combinatorics.
4. Let f(k) = count of numbers with unique digits with length equals k.
5. f(1) = 10, ..., f(k) = 9 * 9 * 8 * ... (9 - k + 2) [The first factor is 9 because a number cannot start with 0].


This problem is combination + permutation.

Length			1		2		3			4			5				6				7					8					9						10

combination		10		9*9		9*9*8		9*9*8*7		9*9*8*7*6		9*9*8*7*6*5		9*9*8*7*6*5*4		9*9*8*7*6*5*4*3		9*9*8*7*6*5*4*3*2		9*9*8*7*6*5*4*3*2*1
	+
permutation


len==1: 10 (can choose 0~9)
len==2: 9*9 (first 1~9, second: include 0 exclude first, 9)
len==3: 9*9*8 (third: include 0 exclude first and second, 8)
...
len==k: 9*9*8*7*...*(9-k+2)

Similar to
Combination-NoRepeat-FromNoDupArray Plus Permutation-FromNoDupArray:
Given a collection of n numbers that don't contain duplicates (1...n), count the number of DISTINCT ORDER combinations of k-distinct numbers out of n.
    n!                 k!               n!
------------ * ------------------  =  ------
k! * (n-k)!    1! * 1! * ... * 1!     (n-k)!
*/
class CountNumbersWithUniqueDigits
{
public:
	CountNumbersWithUniqueDigits() {}
	~CountNumbersWithUniqueDigits() {}

	int DP(int n)
	{
		if (n == 0) return 1;//special case

		if (n > 10)
			n = 10;

		std::vector<int> dp(11, 0);//use dp[1]~dp[10] for len==1~10
		dp[1] = 10;
		dp[2] = 9 * 9;
		dp[3] = 9 * 9 * 8;
		dp[4] = 9 * 9 * 8 * 7;
		dp[5] = 9 * 9 * 8 * 7 * 6;
		dp[6] = 9 * 9 * 8 * 7 * 6 * 5;
		dp[7] = 9 * 9 * 8 * 7 * 6 * 5 * 4;
		dp[8] = 9 * 9 * 8 * 7 * 6 * 5 * 4 * 3;
		dp[9] = 9 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2;
		dp[10] = 9 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1;

		int res = 0;
		for (int i = 1; i <= n; ++i)//accumulate from len==1 to len==n
			res += dp[i];

		std::cout << "CountNumbersWithUniqueDigits DP1D for \"" << n << "\": " << res << std::endl;
		return res;
	}

	int Recur(int n)
	{
		int res = 1;
		long long max = (long long)pow(10, n);
		int used = 0;//we only use the lower 10 digits to indicate if it has been used

		for (int i = 1; i < 10; ++i)//first digit is [1:9]
		{
			if (i < max)
			{
				used |= (1 << i);
				res += this->recur(i, max, used);
				used &= ~(1 << i);
			}
		}

		std::cout << "CountNumbersWithUniqueDigits Recur for \"" << n << "\": " << res << std::endl;
		return res;
	}
private:
	int recur(int num, long long max, int used)
	{
		int res = 1;
		for (int i = 0; i < 10; ++i)//non-first digit is [0:9]
		{
			int cur = 10 * num + i;
			if (cur < max)
			{
				if ((used & (1 << i)) == 0)
				{
					used |= (1 << i);
					res += this->recur(cur, max, used);
					used &= ~(1 << i);
				}
			}
		}

		return res;
	}
};
/*
CountNumbersWithUniqueDigits DP1D for "10": 8877691
CountNumbersWithUniqueDigits Recur for "10": 8877691
*/
#endif
