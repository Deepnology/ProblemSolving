#ifndef _KNAPSACK_H_
#define _KNAPSACK_H_
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, DynamicProgramming: The knapsack problem (MaxVal_NoRepeats_DP1D)
http://www.geeksforgeeks.org/dynamic-programming-set-10-0-1-knapsack-problem/
培養與鍛鍊程式設計的邏輯腦 Chapter 2-3
Recur: O(2^n) Time
DP: O(nW) Time
*/
class Knapsack
{
public:
	Knapsack(){}
	~Knapsack(){}

	int MaxVal_NoRepeats_Recur(int wt[], int val[], int n, int MaxWt)
	{
		int res = 0;
		res = this->maxVal_NoRepeats_Recur(wt, val, n, MaxWt);
		std::cout << "Knapsack MaxVal_NoRepeats_Recur for MaxWt=\"" << MaxWt << "\" from wt=\"" << Debug::ToStr1D<int>()(wt, n) << "\", val=\"" << Debug::ToStr1D<int>()(val, n) << "\": " << res << std::endl;
		return res;
	}
private:
	int maxVal_NoRepeats_Recur(int wt[], int val[], int n, int MaxWt)
	{
		if (n == 0 || MaxWt == 0)
			return 0;

		if (wt[n - 1] > MaxWt)
			return this->maxVal_NoRepeats_Recur(wt, val, n - 1, MaxWt);//exclude cur item
		else
			return std::max(val[n - 1] + this->maxVal_NoRepeats_Recur(wt, val, n - 1, MaxWt - wt[n - 1]),//include cur item
			this->maxVal_NoRepeats_Recur(wt, val, n - 1, MaxWt));//exclude cur item
	}

public:
	int MaxVal_NoRepeats_DP2D(int wt[], int val[], int n, int MaxWt)
	{
		std::vector<std::vector<int> > dp(MaxWt + 1, std::vector<int>(n + 1, 0));
		//dp[curWt][curItem]: curMaxVal for items from wt/val[0]~wt/val[curItem-1] with max curWt
		
		for (int curWtY = 0; curWtY <= MaxWt; ++curWtY)
		{
			for (int curItemX = 0; curItemX <= n; ++curItemX)
			{
				if (curWtY == 0 || curItemX == 0)//first row || first column
					dp[curWtY][curItemX] = 0;

				else if (wt[curItemX - 1] <= curWtY)
					dp[curWtY][curItemX] = std::max(
					val[curItemX - 1] + dp[curWtY - wt[curItemX - 1]][curItemX - 1],//include curItemX
					dp[curWtY][curItemX - 1]);//exclude curItemX
				else
					dp[curWtY][curItemX] = dp[curWtY][curItemX - 1];//exclude curItemX
			}
		}
		Debug::Print2D<int>()(dp);
		std::cout << "Knapsack MaxVal_NoRepeats_DP2D for MaxWt=\"" << MaxWt << "\" from wt=\"" << Debug::ToStr1D<int>()(wt, n) << "\", val=\"" << Debug::ToStr1D<int>()(val, n) << "\": " << dp[MaxWt][n] << std::endl;
		return dp[MaxWt][n];
	}

	int MaxVal_AllowRepeats_DP2D(int wt[], int val[], int n, int MaxWt)
	{
		std::vector<std::vector<int> > dp(MaxWt + 1, std::vector<int>(n + 1, 0));
		//dp[curWt][curItem]: curMaxVal for items from wt/val[0]~wt/val[curItem-1] with max curWt

		for (int curWtY = 0; curWtY <= MaxWt; ++curWtY)
		{
			for (int curItemX = 0; curItemX <= n; ++curItemX)
			{
				if (curWtY == 0 || curItemX == 0)//first row || first column
					dp[curWtY][curItemX] = 0;

				else if (wt[curItemX - 1] <= curWtY)
					dp[curWtY][curItemX] = std::max(
					val[curItemX - 1] + dp[curWtY - wt[curItemX - 1]][curItemX],//include curItemX
					dp[curWtY][curItemX - 1]);//exclude curItemX
				else
					dp[curWtY][curItemX] = dp[curWtY][curItemX - 1];//exclude curItemX
			}
		}
		Debug::Print2D<int>()(dp);
		std::cout << "Knapsack MaxVal_AllowRepeats_DP2D for MaxWt=\"" << MaxWt << "\" from wt=\"" << Debug::ToStr1D<int>()(wt, n) << "\", val=\"" << Debug::ToStr1D<int>()(val, n) << "\": " << dp[MaxWt][n] << std::endl;
		return dp[MaxWt][n];
	}

	int MaxVal_NoRepeats_DP1D(int wt[], int val[], int n, int MaxWt)
	{
		std::vector<int> dp(MaxWt + 1, 0);
		for (int curItem = 0; curItem < n; ++curItem)
		{
			for (int curWt = MaxWt; curWt >= wt[curItem]; --curWt)//decrementing
			{
				dp[curWt] = std::max(val[curItem] + dp[curWt - wt[curItem]],//include curItem
					dp[curWt]);//exclude curItem
			}
		}
		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "Knapsack MaxVal_NoRepeats_DP1D for MaxWt=\"" << MaxWt << "\" from wt=\"" << Debug::ToStr1D<int>()(wt, n) << "\", val=\"" << Debug::ToStr1D<int>()(val, n) << "\": " << dp[MaxWt] << std::endl;
		return dp[MaxWt];
	}

	int MaxVal_AllowRepeats_DP1D(int wt[], int val[], int n, int MaxWt)
	{
		std::vector<int> dp(MaxWt + 1, 0);
		for (int curItem = 0; curItem < n; ++curItem)
		{
			for (int curWt = wt[curItem]; curWt <= MaxWt; ++curWt)//incrementing
			{
				dp[curWt] = std::max(val[curItem] + dp[curWt - wt[curItem]],//include curItem
					dp[curWt]);//exclude curItem
			}
		}
		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "Knapsack MaxVal_AllowRepeats_DP1D for MaxWt=\"" << MaxWt << "\" from wt=\"" << Debug::ToStr1D<int>()(wt, n) << "\", val=\"" << Debug::ToStr1D<int>()(val, n) << "\": " << dp[MaxWt] << std::endl;
		return dp[MaxWt];
	}
};

/*
Knapsack MaxVal_NoRepeats_Recur for MaxWt="5" from wt="2, 1, 3, 2", val="3, 2, 4, 2": 7
[cX][rY]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 3, 3, 3, 3
Row#2	= 0, 2, 3, 5, 5, 5
Row#3	= 0, 2, 3, 5, 6, 7
Row#4	= 0, 2, 3, 5, 6, 7

Knapsack MaxVal_NoRepeats_DP2D for MaxWt="5" from wt="2, 1, 3, 2", val="3, 2, 4, 2": 7
[cX][rY]
Row#0	= 0, 0, 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 0, 4, 4, 4, 8, 8
Row#2	= 0, 0, 0, 4, 5, 5, 8, 9
Row#3	= 0, 0, 3, 4, 6, 7, 9, 10

Knapsack MaxVal_AllowRepeats_DP2D for MaxWt="7" from wt="3, 4, 2", val="4, 5, 3": 10
0, 2, 3, 5, 6, 7
Knapsack MaxVal_NoRepeats_DP1D for MaxWt="5" from wt="2, 1, 3, 2", val="3, 2, 4, 2": 7
0, 0, 3, 4, 6, 7, 9, 10
Knapsack MaxVal_AllowRepeats_DP1D for MaxWt="7" from wt="3, 4, 2", val="4, 5, 3": 10
*/
#endif