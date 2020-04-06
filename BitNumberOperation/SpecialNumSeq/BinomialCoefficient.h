/*MEMO*/
#ifndef	BINOMIAL_COEFFICIENT_H
#define BINOMIAL_COEFFICIENT_H
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, DynamicProgramming: Compute the binomial coefficients (DP1D)
http://www.geeksforgeeks.org/dynamic-programming-set-9-binomial-coefficient/
http://www.geeksforgeeks.org/space-and-time-efficient-binomial-coefficient/
                                                            / n \
The binomial coefficient indexed by n and k and denoted by |     | is the coefficient of the X^k term in the polynomial expansion of the binomial power (1+X)^n.
                                                            \ k /
												  n!
The value of the this coefficient is given by -----------
                                              k! * (n-k)!

1. A binomial coefficient C(n, k) can be defined as the coefficient of X^k in the expansion of (1 + X)^n
2. A binomial coefficient C(n, k) also gives the number of ways, disregarding order, that k objects can be chosen from among n objects
   ; more formally, the number of k-element subsets (or k-combinations) of an n-element set.

Recur: O(2^k) time
DP2D: O(n*k) time, O(n*k) space
DP1D: O(n*k) time, O(k) space
Formula: O(k) time, O(1) space

Recursion:
C(n, k) = C(n-1, k-1) + C(n-1, k)
C(n, 0) = C(n, n) = 1

Formula:
C(n, k) = n! / [(n-k)! * k!]
        = [n * (n-1) *....* 1]  / [ ( (n-k) * (n-k-1) * .... * 1) * ( k * (k-1) * .... * 1 ) ]
After simplifying, we get
C(n, k) = [n * (n-1) * .... * (n-k+1)] / [k * (k-1) * .... * 1]
        = [n * (n-1) * .... * (n-k+1)] / k!
Also, C(n, k) = C(n, n-k)  // we can change r to n-r if r > n-r 

Arranging binomial coefficients into rows for successive values of n, and in which k ranges from 0 to n, gives a trianglar array called Pascal's triangle.
n
0:                 1
1:               1   1
2:             1   2   1
3:           1   3   3   1
4:         1   4   6   4   1
5:       1   5  10   10  5   1
6:     1   6  15   20  15  6   1
7:   1   7  21  35   35  21  7   1
8: 1   8  28  56  70   56  28  8   1

for n=5: (x+y)^5 = 1*x^5 + 5*x^4*y + 10*x^3*y^2 + 10*x^2*y^3 + 5*x*y^4 + 1*y^5

See also Combinations.h, StricklyMonotoneDecimalNums.h, PascalTriangle.h, CatalanNumber.h
*/
class BinomialCoefficient
{
public:
	BinomialCoefficient(){}
	~BinomialCoefficient(){}

	int Recur(int n, int k)
	{
		int res = this->recur(n, k);
		std::cout << "BinomialCoefficient Recur for \"" << n << ", " << k << "\": " << res << std::endl;
		return res;
	}
private:
	int recur(int n, int k)
	{
		if (k == 0 || k == n)
			return 1;//the coefficients of both X^n and X^0 terms are 1

		return this->recur(n - 1, k - 1) + this->recur(n - 1, k);//up left grid + up grid
	}

public:
	int DP2D_Recur(int n, int k)
	{
		std::vector<std::vector<int> > dp(n + 1, std::vector<int>(k + 1, 0));
		int res = this->dp2d_recur(n, k, dp);
		Debug::Print2D<int>()(dp, false);
		std::cout << "BinomialCoefficient DP2D_Recur for \"" << n << ", " << k << "\": " << res << std::endl;
		return res;
	}
private:
	int dp2d_recur(int n, int k, std::vector<std::vector<int> > & dp)
	{
		if (k == 0 || k == n)
			return dp[n][k] = 1;
		if (dp[n][k] != 0)
			return dp[n][k];
		
		return dp[n][k] = this->dp2d_recur(n - 1, k - 1, dp) + this->dp2d_recur(n - 1, k, dp);
	}

public:
	int DP2D(int n, int k)
	{
		std::vector<std::vector<int> > dp(n + 1, std::vector<int>(k + 1));
		for (int i = 0; i <= n; ++i)
		{
			for (int j = 0; j <= std::min(i, k); ++j)
			{
				if (j == 0 || j == i)
					dp[i][j] = 1;
				else
					dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];//up left grid + up grid
			}
		}
		Debug::Print2D<int>()(dp, false);
		std::cout << "BinomialCoefficient DP2D for \"" << n << ", " << k << "\": " << dp[n][k] << std::endl;
		return dp[n][k];
	}

public:
	int DP1D(int n, int k)
	{
		std::vector<int> dp(k + 1);
		dp[0] = 1;
		for (int i = 1; i <= n; ++i)
		{
			for (int j = std::min(i, k); j > 0; --j)
				dp[j] = dp[j] + dp[j - 1];
		}
		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "BinomialCoefficient DP1D for \"" << n << ", " << k << "\": " << dp[k] << std::endl;
		return dp[k];
	}


public:
	int Formula(int n, int k)
	{
		int res = 1;

		/*since C(n, k) = C(n, n-k)*/
		if (k > n - k)
			k = n - k;

		/*calculate value of [n*(n-1)*...*(n-k+1)] / [k*(k-1)*...*1]*/
		for (int i = 0; i < k; ++i)
		{
			res *= (n - i);
			res /= (i + 1);
		}

		std::cout << "BinomialCoefficient Formula for \"" << n << ", " << k << "\": " << res << std::endl;
		return res;
	}
};
/*
BinomialCoefficient Recur for "5, 2": 10
[rY][cX]
Row#0	= 1, 0, 0
Row#1	= 1, 1, 0
Row#2	= 1, 2, 1
Row#3	= 1, 3, 3
Row#4	= 1, 4, 6
Row#5	= 1, 0, 0

BinomialCoefficient DP2D_Recur for "5, 2": 10
[rY][cX]
Row#0	= 1, 0, 0
Row#1	= 1, 1, 0
Row#2	= 1, 2, 1
Row#3	= 1, 3, 3
Row#4	= 1, 4, 6
Row#5	= 1, 5, 10

BinomialCoefficient DP2D for "5, 2": 10
1, 5, 10
BinomialCoefficient DP1D for "5, 2": 10
BinomialCoefficient Formula for "5, 2": 10
*/
#endif