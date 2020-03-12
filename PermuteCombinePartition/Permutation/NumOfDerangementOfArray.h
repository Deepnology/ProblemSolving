#ifndef NUM_OF_DERANGEMENT_OF_ARRAY_H
#define NUM_OF_DERANGEMENT_OF_ARRAY_H
#include "Debug.h"
/*
Leetcode: Find the Derangement of an Array
In combinatorial mathematics, a derangement is a permutation of the elements of a set
, such that no element appears in its original position.
There's originally an array consisting of n integers from 1 to n in ascending order
, you need to find the number of derangement it can generate.
Also, since the answer may be very large, you should return the output mod 109 + 7.
Example 1:
Input: 3
Output: 2
Explanation: The original array is [1,2,3]. The two derangements are [2,3,1] and [3,1,2].

*/
class NumOfDerangementOfArray
{
public:
	NumOfDerangementOfArray() {}

	const int mod = pow(10, 9) + 7;
	int DP1D(int n)
	{
		if (n == 1) return 0;
		std::vector<unsigned long long> dp(n + 1);
		dp[2] = 1;//1,2: 2,1 (one way)
		for (int i = 3; i <= n; ++i)
		{
			//for the ith number i, it can select i-1 positions prior to it, i.e., 1,2,3,...,i-1
			//if the selected number by the ith number selects the ith number, it reduces to n-2 numbers' derangement problem
			//if the selected number by the ith number doesn't select the ith number, it reduces to n-1 numbers' derangement problem
			dp[i] = (i - 1) * (dp[i - 2] + dp[i - 1]) % mod;
		}
		return (int)dp[n];
	}
};
#endif
