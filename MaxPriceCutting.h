#ifndef MAX_PRICE_CUTTING_H
#define MAX_PRICE_CUTTING_H
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/dynamic-programming-set-13-cutting-a-rod/
Given a rod of length N inches and an array of prices that contains prices of all pieces of size smaller than N.
Determine the maximum value obtainable by cutting up the rod and selling the pieces.

price[0]: price for length of 1
price[1]: price for length of 2
. . . 
price[N-1]: price for length of N

Recur: 
DP1D: O(n^2) time, O(n) space
see also MaxProductCutting.h, PaintersPartitionFairWorkload.h
*/
class MaxPriceCutting
{
public:
	MaxPriceCutting(){}
	~MaxPriceCutting(){}

	int Recur(const std::vector<int> & price, int N)//price[i]: price of length i+1
	{
		int res = this->recur(price, N);
		std::cout << "MaxPriceCutting Recur for \"" << N << "\", \"" << Debug::ToStr1D<int>()(price) << "\": " << res << std::endl;
		return res;
	}
private:
	int recur(const std::vector<int> & price, int N)
	{
		if (N <= 0)
			return 0;
		
		int maxPrice = 0;
		for (int i = 0; i < N; ++i)
		{
			maxPrice = std::max(maxPrice, price[i] + this->recur(price, N - i - 1));//remaining length = N - (i + 1) = N - i - 1
		}
		return maxPrice;
	}

public:
	int DP1D_Recur(const std::vector<int> & price, int N)
	{
		if (N <= 0)
			return 0;
		std::vector<int> dp(N, 0);
		int res = this->dp1d_recur(price, N, dp);
		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "MaxPriceCutting DP1D_Recur for \"" << N << "\", \"" << Debug::ToStr1D<int>()(price) << "\": " << res << std::endl;
		return res;
	}
private:
	int dp1d_recur(const std::vector<int> & price, int N, std::vector<int> & dp)
	{
		int maxPrice = 0;
		for (int i = 0; i < N; ++i)
		{
			if (dp[N - i - 1] == 0)//not visited yet
				dp[N - i - 1] = this->dp1d_recur(price, N - i - 1, dp);
			maxPrice = std::max(maxPrice, price[i] + dp[N - i - 1]);
		}
		return maxPrice;
	}

public:
	int DP1D_Iterate(const std::vector<int> & price, int N)
	{
		std::vector<int> dp(N + 1);
		dp[0] = 0;
		for (int i = 1; i <= N; ++i)
		{
			int maxPrice = 0;
			for (int j = 0; j < i; ++j)
			{
				maxPrice = std::max(maxPrice, price[j] + dp[i - j - 1]);//cur max price = price of length j+1 (price[j]) + max price of length i-j (dp[i-j-1])
			}
			dp[i] = maxPrice;
		}
		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "MaxPriceCutting DP1D_Iterate for \"" << N << "\", \"" << Debug::ToStr1D<int>()(price) << "\": " << dp[N] << std::endl;
		return dp[N];
	}
};
/*
MaxPriceCutting Recur for "8", "1, 5, 8, 9, 10, 17, 17, 20": 22
0, 1, 5, 8, 10, 13, 17, 18
MaxPriceCutting DP1D_Recur for "8", "1, 5, 8, 9, 10, 17, 17, 20": 22
0, 1, 5, 8, 10, 13, 17, 18, 22
MaxPriceCutting DP1D_Iterate for "8", "1, 5, 8, 9, 10, 17, 17, 20": 22
MaxPriceCutting Recur for "8", "3, 5, 18, 9, 10, 17, 17, 20": 42
0, 3, 6, 18, 21, 24, 36, 39
MaxPriceCutting DP1D_Recur for "8", "3, 5, 18, 9, 10, 17, 17, 20": 42
0, 3, 6, 18, 21, 24, 36, 39, 42
MaxPriceCutting DP1D_Iterate for "8", "3, 5, 18, 9, 10, 17, 17, 20": 42
*/
#endif