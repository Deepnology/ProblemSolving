#ifndef COMBINATION_PRIME_SUM_1_TO_N_H
#define COMBINATION_PRIME_SUM_1_TO_N_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
http://www.careercup.com/question?id=11641125
Given a set of numbers from 1 to n.
Find the number of subsets such that the sum of numbers in the subset is a prime number.

The max subset sum is n*(n+1)/2.
We can compute the (no repeat) number of ways dp[targetSum+1][N+1] for 1 to n with a target sum of n*(n+1)/2.
Then sum up all number of ways for prime sums, i.e., dp[primeSum1][N+1] + dp[primeSum2][N+1] + ...

See also CombinationSum.h: NumOfWays_NoRepeats_FromDupArray_DP2D, SubsetSumProblem.h
*/
class CombinationPrimeSum1toN
{
public:
	CombinationPrimeSum1toN(){}
	~CombinationPrimeSum1toN(){}

	int NumOfWays_NoRepeats_DP2D(int n)
	{
		int targetSum = n * (n + 1) / 2;/*cumulative sum from 1 to n, which is the max subset sum*/
		int N = n;
		std::vector<std::vector<int> > dp(targetSum + 1, std::vector<int>(N + 1, 0));
		/*
		dp[sumY][numX]: count of ways for sumY from 1 to numX
		*/
		for (int sumY = 0; sumY <= targetSum; ++sumY)
		{
			for (int numX = 0; numX <= N; ++numX)
			{
				if (sumY == 0)//(first row) sum is 0: we can always select nothing, so it's a valid one way
					dp[sumY][numX] = 1;
				else if (numX == 0)//(first column) sum is not 0, but select nothing: impossible (no way)
					dp[sumY][numX] = 0;
				else
				{
					/*current number is numX*/
					int countIncludeThis = (sumY - numX) >= 0 ? dp[sumY - numX][numX - 1] : 0;
					int countExcludeThis = dp[sumY][numX - 1];
					dp[sumY][numX] = countIncludeThis + countExcludeThis;
				}
			}
		}
		Debug::Print2D<int>()(dp, false);

		int res = 0;
		for (int i = 1; i <= targetSum; ++i)
		{
			if (this->isPrime(i))
			{
				res += dp[i][N];
				std::cout << i << ": " << dp[i][N] << std::endl;
			}
		}

		std::cout << "CombinationPrimeSum1toN NumOfWays_NoRepeats_DP2D for \"1 to " << N << "\", \"MaxSum=" << targetSum << "\": " << res << std::endl;
		return res;
	}

private:
	bool isPrime(int n)
	{
		if (n == 2 || n == 3)
			return true;

		if (n == 1 || n % 2 == 0)
			return false;

		/*
		for i = 3 to sqrt(n)
		(for any non prime number, one of its factors is smaller or equal to its sqrt)
		(skip even numbers by incrementing 2)
		*/
		for (int i = 3; i * i <= n; i += 2)
			if (n % i == 0)
				return false;

		return true;
	}
	
};
/*
[rY][cX]
Row#0	= 1, 1, 1, 1, 1, 1, 1
Row#1	= 0, 1, 1, 1, 1, 1, 1
Row#2	= 0, 0, 1, 1, 1, 1, 1
Row#3	= 0, 0, 1, 2, 2, 2, 2
Row#4	= 0, 0, 0, 1, 2, 2, 2
Row#5	= 0, 0, 0, 1, 2, 3, 3
Row#6	= 0, 0, 0, 1, 2, 3, 4
Row#7	= 0, 0, 0, 0, 2, 3, 4
Row#8	= 0, 0, 0, 0, 1, 3, 4
Row#9	= 0, 0, 0, 0, 1, 3, 5
Row#10	= 0, 0, 0, 0, 1, 3, 5
Row#11	= 0, 0, 0, 0, 0, 2, 5
Row#12	= 0, 0, 0, 0, 0, 2, 5
Row#13	= 0, 0, 0, 0, 0, 1, 4
Row#14	= 0, 0, 0, 0, 0, 1, 4
Row#15	= 0, 0, 0, 0, 0, 1, 4
Row#16	= 0, 0, 0, 0, 0, 0, 3
Row#17	= 0, 0, 0, 0, 0, 0, 2
Row#18	= 0, 0, 0, 0, 0, 0, 2
Row#19	= 0, 0, 0, 0, 0, 0, 1
Row#20	= 0, 0, 0, 0, 0, 0, 1
Row#21	= 0, 0, 0, 0, 0, 0, 1

2: 1
3: 2
5: 3
7: 4
11: 5
13: 4
17: 2
19: 1
CombinationPrimeSum1toN NumOfWays_NoRepeats_DP2D for "1 to 6", "MaxSum=21": 22
*/
#endif