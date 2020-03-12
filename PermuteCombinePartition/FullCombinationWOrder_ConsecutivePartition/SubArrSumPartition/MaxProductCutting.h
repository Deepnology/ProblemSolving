#ifndef MAX_PRODUCT_CUTTING_H
#define MAX_PRODUCT_CUTTING_H
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/dynamic-programming-set-36-cut-a-rope-to-maximize-product/
Given a rope of length N meters, cut the rope in different parts of integer lengths in a way 
that maximizes product of lengths of all parts.
You must make at least one cut.
Assume the length of rope is more than 2 meters.

Recur:
DP1D: O(n^2) time, O(n) space
see also MaxPriceCutting.h, PaintersPartitionFairWorkload.h
see also IntegerBreak.h
*/
class MaxProductCutting
{
public:
	MaxProductCutting(){}
	~MaxProductCutting(){}

	int Recur(int N)
	{
		int res = this->recur(N);
		std::cout << "MaxProductCutting Recur for \"" << N << "\": " << res << std::endl;
		return res;
	}
private:
	int recur(int N)
	{
		if (N == 0 || N == 1)//when length is smaller than 2, it cannot be cut, so max product is 0
			return 0;

		int maxProduct = 0;
		for (int i = 1; i < N; ++i)
		{
			maxProduct = std::max(maxProduct,
				std::max(i * (N - i), i * this->recur(N - i)));//i*(N-i): product of one cut; i*(recur(N-i)): max product of at least 2 cuts 
		}
		return maxProduct;
	}

public:
	int DP1D_Recur(int N)
	{
		if (N == 0 || N == 1)
			return 0;
		std::vector<int> dp(N, 0);
		int res = this->dp1d_recur(N, dp);
		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "MaxProductCutting DP1D_Recur for \"" << N << "\": " << res << std::endl;
		return res;
	}
private:
	int dp1d_recur(int N, std::vector<int> & dp)
	{
		int maxProduct = 0;
		for (int i = 1; i < N; ++i)
		{
			if (dp[N - i] == 0)//not visited yet
				dp[N - i] = this->dp1d_recur(N - i, dp);
			maxProduct = std::max(maxProduct,
				std::max(i * (N - i), i * dp[N - i]));
		}
		return maxProduct;
	}

public:
	int DP1D_Iterate(int N)
	{
		std::vector<int> dp(N + 1);
		dp[0] = dp[1] = 0;//when length is smaller than 2, it cannot be cut, so max product is 0

		for (int i = 1; i <= N; ++i)
		{
			int maxProduct = 0;
			for (int j = 1; j <= i / 2; ++j)
			{
				maxProduct = std::max(maxProduct, std::max(j*(i - j), j*dp[i - j]));//cur max produce = length j * length of max((i-j), dp[i-j])
			}
			dp[i] = maxProduct;
		}
		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "MaxProductCutting DP1D_Iterate for \"" << N << "\": " << dp[N] << std::endl;
		return dp[N];
	}

public:
	int Tricky(int N)
	{
		if (N == 2 || N == 3)
			return (N - 1);

		int N_before = N;
		/*
		The max product can be obtained by repeatedly cutting parts of size 3 while size is greater than 4.
		Keeping the last part as size of 2 or 3 or 4.
		*/
		int res = 1;
		while (N > 4)
		{
			N -= 3;
			res *= 3;
		}
		res *= N;
		std::cout << "MaxProductCutting Tricky for \"" << N_before << "\": " << res << std::endl;
		return res;
	}
};
/*
MaxProductCutting Recur for "10": 36
0, 0, 1, 2, 4, 6, 9, 12, 18, 27
MaxProductCutting DP1D_Recur for "10": 36
0, 0, 1, 2, 4, 6, 9, 12, 18, 27, 36
MaxProductCutting DP1D_Iterate for "10": 36
MaxProductCutting Tricky for "10": 36

0, 0, 1, 2, 4, 6, 9, 12, 18, 27, 36, 54, 81, 108, 162, 243, 324, 486, 729, 972, 1458, 2187, 2916, 4374, 6561, 8748, 13122, 19683, 26244, 39366, 59049, 78732, 118098, 177147, 236196, 354294, 531441, 708588, 1062882, 1594323
MaxProductCutting DP1D_Recur for "40": 2125764
0, 0, 1, 2, 4, 6, 9, 12, 18, 27, 36, 54, 81, 108, 162, 243, 324, 486, 729, 972, 1458, 2187, 2916, 4374, 6561, 8748, 13122, 19683, 26244, 39366, 59049, 78732, 118098, 177147, 236196, 354294, 531441, 708588, 1062882, 1594323, 2125764
MaxProductCutting DP1D_Iterate for "40": 2125764
MaxProductCutting Tricky for "40": 2125764
*/
#endif