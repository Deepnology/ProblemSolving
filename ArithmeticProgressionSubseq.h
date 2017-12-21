#ifndef ARITHMETIC_PROGRESSION_SUBSEQ_H
#define ARITHMETIC_PROGRESSION_SUBSEQ_H
#include "Debug.h"
/*
Leetcode: Arithmetic Slices I
A sequence of number is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.
For example, these are arithmetic sequence:
1, 3, 5, 7, 9
7, 7, 7, 7
3, -1, -5, -9
The following sequence is not arithmetic.
1, 1, 2, 5, 7

A zero-indexed array A consisting of N numbers is given.
A slice of that array is any pair of integers (P, Q) such that 0 <= P < Q < N.
A slice (P, Q) of array A is called arithmetic if the sequence:
A[P], A[p + 1], ..., A[Q - 1], A[Q] is arithmetic.
In particular, this means that P + 1 < Q.
The function should return the number of arithmetic slices in the array A.
Example:
A = [1, 2, 3, 4]
return: 3, for 3 arithmetic slices in A: [1, 2, 3], [2, 3, 4] and [1, 2, 3, 4] itself.


Leetcode: Arithmetic Slices II
A sequence of numbers is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.
For example, these are arithmetic sequences:
1, 3, 5, 7, 9
7, 7, 7, 7
3, -1, -5, -9
The following sequence is not arithmetic.
1, 1, 2, 5, 7

A zero-indexed array A consisting of N numbers is given.
A subsequence slice of that array is any sequence of integers (P0, P1, ..., Pk) such that 0 <=  P0 < P1 < ... < Pk < N.
A subsequence slice (P0, P1, ..., Pk) of array A is called arithmetic if the sequence A[P0], A[P1], ..., A[Pk-1], A[Pk] is arithmetic.
In particular, this means that k >= 2.
The function should return the number of arithmetic subsequence slices in the array A.
The input contains N integers.
Every integer is in the range of -2^31 and 2^31-1 and 0 <= N <= 1000.
The output is guaranteed to be less than 2^31-1.
Example:
Input: [2, 4, 6, 8, 10]
Output: 7
Explanation:
All arithmetic subsequence slices are:
[2,4,6]
[4,6,8]
[6,8,10]
[2,4,6,8]
[4,6,8,10]
[2,4,6,8,10]
[2,6,10]
*/
class ArithmeticProgressionSubseq
{
public:
	ArithmeticProgressionSubseq() {}

	int CountArithmeticSubarr(std::vector<int> & A)
	{
		//a subarray w/ size >= 3 and diffs between consecutive nums are equal is called an arithmetic slice
		int N = A.size();
		if (N < 3) return 0;
		std::vector<int> dp(N, 0);
		if (A[1] - A[0] == A[2] - A[1])
			dp[2] = 1;
		int res = dp[2];
		for (int i = 3; i < N; ++i)
		{
			if (A[i - 1] - A[i - 2] == A[i] - A[i - 1])
				dp[i] = dp[i - 1] + 1;
			res += dp[i];
		}

		std::cout << "ArithmeticProgressionSubseq CountArithmeticSubarr for \"" << Debug::ToStr1D<int>()(A) << "\": " << res << std::endl;
		return res;
	}

	int CountArithmeticSubseq(std::vector<int> & A)
	{
		int N = A.size();
		std::vector<std::unordered_map<long long, int>> dp(N, std::unordered_map<long long, int>());//<diff, diff count at cur idx>
		int res = 0;
		for (int i = 1; i < N; ++i)
		{
			for (int j = 0; j < i; ++j)
			{
				long long diff = (long long)A[i] - (long long)A[j];
				if (diff > INT_MAX || diff < INT_MIN) continue;
				if (dp[j].count(diff))
				{
					dp[i][diff] += dp[j][diff] + 1;
					res += dp[j][diff];
				}
				else//A[i:j] w/ diff contains only 2 nums
				{
					dp[i][diff] += 1;
				}
			}
		}

		std::cout << "ArithmeticProgressionSubseq CountArithmeticSubseq for \"" << Debug::ToStr1D<int>()(A) << "\": " << res << std::endl;
		return res;
	}
};
/*
ArithmeticProgressionSubseq CountArithmeticSubarr for "1, 2, 3, 4": 3
ArithmeticProgressionSubseq CountArithmeticSubseq for "2, 4, 6, 8, 10": 7
*/
#endif
