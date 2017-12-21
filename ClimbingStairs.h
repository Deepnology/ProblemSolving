#ifndef CLIMBING_STAIRS_H
#define CLIMBING_STAIRS_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
/*
Leetcode: Climbing Stairs
Notes:
You are climbing a stair case. It takes n steps to reach to the top.
Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

Solution:
Suppose there are f(n) ways to reach the n-step top, and the last step is either 1 or 2. Thus
we can get f(n) = f(n-1) + f(n-2). This is exactly the Fibonacci sequence. Thus we can compute
the nth fibonacci number by recursive calls and memorization.
The time complexity of Fibonacci sequence is about O(1.618^n), (1.616 is the gold ratio).
Here are good discussions about this.

First few Fibonacci numbers: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 141, ...
Climbing stair sequence (num of ways): 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 141, ... 
                               stairs: 0, 1, 2, 3, 4, 5, 6,  7,  8,  9,  10, 11,  ...

// Complexity:
// DP, O(n) time, O(n) space
// DP, O(n) time, O(1) space
// Matrix Pow, O(log(n)) time, O(1) space
*/

class ClimbingStairs
{
public:
	ClimbingStairs(){}
	~ClimbingStairs(){}

	int DP1DRecur(int n)
	{
		std::vector<int> dp(n + 1, 0);
		int r = this->dP1DRecur(n, dp);

		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "ClimbingStairs DP1DRecur for \"" << n << "\": " << r << std::endl;
		return r;
	}
private:
	int dP1DRecur(int n, std::vector<int> & dp)
	{
		if (n <= 1)
			return dp[n] = 1;
		if (dp[n] != 0)
			return dp[n];
		return dp[n] = this->dP1DRecur(n - 1, dp) + this->dP1DRecur(n - 2, dp);
	}
public:
	int DP1DIterate(int n)
	{
		std::vector<int> dp(n + 1, 0);
		dp[0] = 1;
		dp[1] = 1;
		for (int i = 2; i <= n; ++i)
			dp[i] = dp[i - 1] + dp[i - 2];

		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "ClimbingStairs DP1DIterate for \"" << n << "\": " << dp[n] << std::endl;
		return dp[n];
	}
	int Iterate(int n)
	{
		if (n <= 1)
			return 1;
		int prev1 = 1;
		int prev2 = 1;
		int cur;
		for (int i = 2; i <= n; ++i)
		{
			cur = prev1 + prev2;
			prev1 = prev2;
			prev2 = cur;
		}
		std::cout << "ClimbingStairs Iterate for \"" << n << "\": " << cur << std::endl;
		return cur;
	}

	int Matrix_Pow(int n)
	{
		std::vector<std::vector<int> > m =
		{
			{ 1, 1 },
			{ 1, 0 }
		};
		m = this->pow(m, n);

		std::cout << "ClimbingStairs Matrix_Pow for \"" << n << "\": " << m[1][0] + m[1][1] << std::endl;
		return m[1][0] + m[1][1];
	}
private:
	std::vector<std::vector<int> > pow(const std::vector<std::vector<int> > & m, int n) 
	{
		if (n == 1)
			return m;
		auto t = this->pow(m, n / 2);
		t = this->mul(t, t);
		if (n % 2 == 1) 
			t = this->mul(t, m);
		return t;
	}
	std::vector<std::vector<int> > mul(const std::vector<std::vector<int> > & a, const std::vector<std::vector<int> > & b)
	{
		int n = a.size();
		std::vector<std::vector<int> > c(n, std::vector<int>(n, 0));
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				for (int k = 0; k < n; ++k)
				{
					c[i][j] += a[i][k] * b[k][j];
				}
			}
		}
		return c;
	}

public:
	//2. Climb 1 or 2 or 3 steps, f(n) = f(n-1) + f(n-2) + f(n-3)
	//first few sequence: 1, 1, 2, 4, 7, 13, ...
	//            stairs: 0, 1, 2, 3, 4, 5,  ...
public:
	int DP1DRecur_3(int n)
	{
		std::vector<int> dp(n + 1, 0);
		//dp[n] is the count of ways of climbing a stair with n steps
		int res = this->dP1DRecur_3(n, dp);
		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "ClimbingStairs DP1DRecur_3 for \"" << n << "\": " << res << std::endl;
		return res;
	}
private:
	int dP1DRecur_3(int n, std::vector<int> & dp)
	{
		if (n <= 1)
			return dp[n] = 1;
		if (n == 2)
			return dp[n] = 2;
		if (dp[n] != 0)
			return dp[n];
		return dp[n] = this->dP1DRecur_3(n - 1, dp) + this->dP1DRecur_3(n - 2, dp) + this->dP1DRecur_3(n - 3, dp);
	}
public:
	int DP1DIterate_3(int n)
	{
		std::vector<int> dp(n + 1, 0);
		dp[0] = 1;
		dp[1] = 1;
		dp[2] = 2;
		for (int i = 3; i <= n; ++i)
			dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];

		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "ClimbingStairs DP1DIterate_3 for \"" << n << "\": " << dp[n] << std::endl;
		return dp[n];
	}
	int Iterate_3(int n)
	{
		if (n <= 1) return 1;
		if (n == 2) return 2;
		int prev1 = 1;
		int prev2 = 1;
		int prev3 = 2;
		int cur;
		for (int i = 3; i <= n; ++i)
		{
			cur = prev1 + prev2 + prev3;
			prev1 = prev2;
			prev2 = prev3;
			prev3 = cur;
		}
		
		std::cout << "ClimbingStairs Iterate_3 for \"" << n << "\": " << cur << std::endl;
		return cur;
	}
};
/*
1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269
ClimbingStairs DP1DRecur for "30": 1346269
1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269
ClimbingStairs DP1DIterate for "30": 1346269
ClimbingStairs Iterate for "30": 1346269
ClimbingStairs Matrix_Pow for "30": 1346269
1, 1, 2, 4, 7, 13, 24, 44, 81, 149, 274, 504, 927, 1705, 3136, 5768, 10609, 19513, 35890, 66012, 121415, 223317, 410744, 755476, 1389537, 2555757, 4700770, 8646064, 15902591, 29249425, 53798080
ClimbingStairs DP1DRecur_3 for "30": 53798080
1, 1, 2, 4, 7, 13, 24, 44, 81, 149, 274, 504, 927, 1705, 3136, 5768, 10609, 19513, 35890, 66012, 121415, 223317, 410744, 755476, 1389537, 2555757, 4700770, 8646064, 15902591, 29249425, 53798080
ClimbingStairs DP1DIterate_3 for "30": 53798080
ClimbingStairs Iterate_3 for "30": 53798080
*/
#endif