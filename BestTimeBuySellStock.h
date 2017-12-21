#ifndef BEST_TIME_BUY_SELL_STOCK_H
#define BEST_TIME_BUY_SELL_STOCK_H
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>
#include "Debug.h"
/*
Elements of programming interview, Array: Compute the max difference (MaxProfit_OneTransaction), Generalizations of max difference (MaxProfit_AtMostKTransactions_DP1D, MaxProfit_UnlimitedTransactions)
Leetcode: Best Time Buy Sell Stock I, II, III, IV

1.
Say you have an array for which the ith element is the price of a given stock on day i.
If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.

2.
Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. 
You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). 
However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

3.
Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. 
You may complete at most two transactions.
Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

4. followed up on 3., you may complete at most k transactions.
DP1D: O(k*n) time, O(n) space

A transaction is a pair of (buy,sell) operations.

5.
Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times) with the following restrictions:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)
Example:
prices = [1, 2, 3, 0, 2]
maxProfit = 3
transactions = [buy, sell, cooldown, buy, sell]


See also TwoIncrElementsWMaxDistInArr.h, , ThreeIncrElementsInArray.h
*/

class BestTimeBuySellStock
{
public:
	BestTimeBuySellStock(){}
	~BestTimeBuySellStock(){}

	//1. only 1 transaction
	int MaxProfit_OneTransaction(const std::vector<int> & prices)
	{
		if (prices.empty())
			return 0;
		int N = prices.size();
		int minPrice = INT_MAX;
		int maxProfit = 0;
		for (int i = 0; i < N; ++i)
		{
			minPrice = std::min(prices[i], minPrice);//keep track of the lowest price to buy in
			maxProfit = std::max(maxProfit, prices[i] - minPrice);//keep track of the max profit that sold at this price with the lowest buy in price
		}

		std::cout << "BestTimeBuySellStock MaxProfit_OneTransaction for \"" << Debug::ToStr1D<int>()(prices) << "\": " << maxProfit << std::endl;
		return maxProfit;
	}


	//2. unlimited transactions
	int MaxProfit_UnlimitedTransactions(const std::vector<int> & prices)
	{
		if (prices.empty())
			return 0;
		int N = prices.size();
		int totalProfit = 0;
		for (int i = 0; i < N - 1; ++i)
		{
			int diff = prices[i + 1] - prices[i];
			totalProfit = std::max(totalProfit, totalProfit + diff);//if the next price is higher than this price, buy at this price sell at the next price
		}

		std::cout << "BestTimeBuySellStock MaxProfit_UnlimitedTransactions for \"" << Debug::ToStr1D<int>()(prices) << "\": " << totalProfit << std::endl;
		return totalProfit;
	}


	//3. at most 2 transactions
	int MaxProfit_AtMost2Transactions(const std::vector<int> & prices)
	{
		if (prices.empty())
			return 0;

		int N = prices.size();
		
		int totalProfit = INT_MIN;
		int minPrice = INT_MAX;
		std::vector<int> firstProfit(N);
		for (int i = 0; i < N; ++i)
		{
			minPrice = std::min(prices[i], minPrice);//keep track of the lowest price to buy
			totalProfit = std::max(totalProfit, prices[i] - minPrice);
			firstProfit[i] = totalProfit;//keep track of the profit that sold at this price i with the lowest buy price
		}

		totalProfit = INT_MIN;
		int maxPrice = INT_MIN;
		std::vector<int> secondProfit(N);
		for (int i = N - 1; i >= 0; --i)
		{
			maxPrice = std::max(maxPrice, prices[i]);//keep track of the highest price to sell
			totalProfit = std::max(totalProfit, maxPrice - prices[i]);
			secondProfit[i] = totalProfit;//keep track of the profit that bought at this price with the highest sell price
		}

		totalProfit = INT_MIN;
		for (int i = 0; i < N; ++i)
			totalProfit = std::max(totalProfit, firstProfit[i] + secondProfit[i]);

		std::cout << "BestTimeBuySellStock MaxProfit_AtMost2Transactions for \"" << Debug::ToStr1D<int>()(prices) << "\": " << totalProfit << std::endl;
		return totalProfit;
	}


	//4. at most k transactions
	int MaxProfit_AtMostKTransactions_DP1D(const std::vector<int> & prices, int k)
	{
		int N = prices.size();
		if (N == 0 || k == 0)
			return 0;
		if (k >= N / 2)//unlimited transaction
		{
			int totalProfit = 0;
			for (int i = 0; i < N - 1; ++i)
			{
				int diff = prices[i + 1] - prices[i];
				totalProfit = std::max(totalProfit, totalProfit + diff);
			}
			return totalProfit;
		}

		std::vector<int> profit(2 * k, INT_MIN);//k buys and k sells: [buy, sell, buy, sell, ....]
		/*
		profit[i]: net profit at transaction i/2
		odd: buy index, even: sell index
		*/
		for (int i = 0; i < N; ++i)
		{
			/*
			for current prices[i], update profit[0~i] with the max profit between the original profit value and the new profit value where we buy/sell at prices[i]
			if profit[j] is an odd index, we buy at prices[i]
			if profit[j] is an even index, we sell at prices[i]
			*/
			std::vector<int> preProfit(profit);
			for (int j = 0, sign = -1; j < 2 * k && j <= i; ++j, sign *= -1)
			{
				int diff = sign * prices[i] + (j == 0 ? 0 : preProfit[j - 1]);
				profit[j] = std::max(diff, preProfit[j]);
			}
			std::cout << Debug::ToStr1D<int>()(profit) << std::endl;
		}

		int maxProfit = INT_MIN;
		for (int i = 1; i < 2 * k; ++i)//profit[0] is buy-in, just skip it
			if (maxProfit < profit[i])
				maxProfit = profit[i];

		std::cout << "BestTimeBuySellStock MaxProfit_AtMostKTransactions_DP1D for \"" << k << "\" in \"" << Debug::ToStr1D<int>()(prices) << "\": " << maxProfit << std::endl;
		return maxProfit;
	}

	//this seems easier to understand
	int MaxProfit_AtMostKTransactions_DP2D(const std::vector<int> & prices, int k)
	{
		int N = prices.size();
		if (N == 0)
			return 0;
		if (k >= N / 2)//unlimited transaction
		{
			int totalProfit = 0;
			for (int i = 0; i < N - 1; ++i)
			{
				int diff = prices[i + 1] - prices[i];
				totalProfit = std::max(totalProfit, totalProfit + diff);
			}
			return totalProfit;
		}

		std::vector<std::vector<int>> local(N, std::vector<int>(k + 1, 0));
		std::vector<std::vector<int>> global(N, std::vector<int>(k + 1, 0));
		/*
		for each prices[i], compute its profits for k transactions
		local[i][j]: max profit of j transactions and the last transaction is on the ith price (must sell on the ith price)
		global[i][j]: max profit of j transactions until the ith price (can choose to sell or not on the ith price)
		*/
		for (int i = 1; i < N; ++i)
		{
			int diff = prices[i] - prices[i - 1];

			for (int j = 1; j <= k; ++j)
			{
				local[i][j] = std::max(global[i - 1][j - 1], local[i - 1][j] + diff);//max profit of sell on ith price = max(profit of sell on ith price without buy ith price, profit of sell on ith price with buy ith price)
				global[i][j] = std::max(local[i][j], global[i - 1][j]);//max(profit of sell on ith price, profit of no sell on the ith price)
			}
		}

		std::cout << "BestTimeBuySellStock MaxProfit_AtMostKTransactions_DP2D for \"" << k << "\" in \"" << Debug::ToStr1D<int>()(prices) << "\": " << global[N - 1][k] << std::endl;
		return global[N - 1][k];
	}

	int MaxProfit_AtMostKTransactions_DP1D_2(const std::vector<int> & prices, int k)
	{
		int N = prices.size();
		if (N == 0)
			return 0;
		if (k >= N / 2)//unlimited transaction
		{
			int totalProfit = 0;
			for (int i = 0; i < N - 1; ++i)
			{
				int diff = prices[i + 1] - prices[i];
				totalProfit = std::max(totalProfit, totalProfit + diff);
			}
			return totalProfit;
		}
		
		std::vector<int> local(k + 1, 0);
		std::vector<int> global(k + 1, 0);
		/*
		for each prices[i], compute its profits for k transactions
		*/
		for (int i = 0; i < N - 1; ++i)
		{
			int diff = prices[i + 1] - prices[i];

			for (int j = k; j >= 1; --j)
			{
				local[j] = std::max(global[j - 1], local[j] + diff);
				global[j] = std::max(local[j], global[j]);
			}

			std::cout << "local:	" << Debug::ToStr1D<int>()(local) << std::endl;
			std::cout << "global:	" << Debug::ToStr1D<int>()(global) << std::endl;
		}

		std::cout << "BestTimeBuySellStock MaxProfit_AtMostKTransactions_DP1D_2 for \"" << k << "\" in \"" << Debug::ToStr1D<int>()(prices) << "\": " << global[k] << std::endl;
		return global[k];
	}

	//5. cooldown 1 day after sell
	int MaxProfit_Cooldown1DayAfterSell(const std::vector<int> & prices)
	{
		int N = prices.size();
		if (N == 0) return 0;
		std::vector<int> buy(N);//buy[i]: max profit at ith day where the last action on ith day is buy
		std::vector<int> sell(N);//sell[i]: max profit at ith day where the last action on ith day is sell
		std::vector<int> cool(N);//cool[i]: max profit at ith day where the last action on ith day is cooldown
		buy[0] = 0 - prices[0];
		sell[0] = 0;
		cool[0] = 0;
		for (int i = 1; i < N; ++i)
		{
			buy[i] = std::max(buy[i - 1], cool[i - 1] - prices[i]);
			sell[i] = std::max(sell[i - 1], buy[i - 1] + prices[i]);
			cool[i] = std::max(cool[i - 1], std::max(buy[i - 1], sell[i - 1]));//since buy[i]<=cool[i], we can elimiate buy[i]: cool[i]=max(cool[i-1], sell[i-1])
		}

		int res = std::max(cool[N - 1], std::max(buy[N - 1], sell[N - 1]));

		std::cout << "BestTimeBuySellStock MaxProfit_Cooldown1DayAfterSell for \"" << Debug::ToStr1D<int>()(prices) << "\": " << res << std::endl;
		return res;
	}

};
/*
BestTimeBuySellStock MaxProfit_OneTransaction for "15, 30, 24, 33, 11, 13, 17, 16, 21, 12, 24, 18": 18
BestTimeBuySellStock MaxProfit_UnlimitedTransactions for "15, 30, 24, 33, 11, 13, 17, 16, 21, 12, 24, 18": 47
BestTimeBuySellStock MaxProfit_AtMost2Transactions for "15, 30, 24, 33, 11, 13, 17, 16, 21, 12, 24, 18": 31
-15, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648
-15, 15, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648
-15, 15, -9, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648
-15, 18, -9, 24, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648
-11, 18, 7, 24, 13, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648
-11, 18, 7, 24, 13, 26, -2147483648, -2147483648, -2147483648, -2147483648
-11, 18, 7, 24, 13, 30, 9, -2147483648, -2147483648, -2147483648
-11, 18, 7, 24, 13, 30, 14, 25, -2147483648, -2147483648
-11, 18, 7, 28, 13, 34, 14, 35, 4, -2147483648
-11, 18, 7, 28, 16, 34, 22, 35, 23, 16
-11, 18, 7, 31, 16, 40, 22, 46, 23, 47
-11, 18, 7, 31, 16, 40, 22, 46, 28, 47
BestTimeBuySellStock MaxProfit_AtMostKTransactions_DP1D for "5" in "15, 30, 24, 33, 11, 13, 17, 16, 21, 12, 24, 18": 47
BestTimeBuySellStock MaxProfit_AtMostKTransactions_DP2D for "5" in "15, 30, 24, 33, 11, 13, 17, 16, 21, 12, 24, 18": 47
local:	0, 15, 15, 15, 15, 15
global:	0, 15, 15, 15, 15, 15
local:	0, 9, 15, 15, 15, 15
global:	0, 15, 15, 15, 15, 15
local:	0, 18, 24, 24, 24, 24
global:	0, 18, 24, 24, 24, 24
local:	0, 0, 18, 24, 24, 24
global:	0, 18, 24, 24, 24, 24
local:	0, 2, 20, 26, 26, 26
global:	0, 18, 24, 26, 26, 26
local:	0, 6, 24, 30, 30, 30
global:	0, 18, 24, 30, 30, 30
local:	0, 5, 23, 29, 30, 30
global:	0, 18, 24, 30, 30, 30
local:	0, 10, 28, 34, 35, 35
global:	0, 18, 28, 34, 35, 35
local:	0, 1, 19, 28, 34, 35
global:	0, 18, 28, 34, 35, 35
local:	0, 13, 31, 40, 46, 47
global:	0, 18, 31, 40, 46, 47
local:	0, 7, 25, 34, 40, 46
global:	0, 18, 31, 40, 46, 47
BestTimeBuySellStock MaxProfit_AtMostKTransactions_DP1D_2 for "5" in "15, 30, 24, 33, 11, 13, 17, 16, 21, 12, 24, 18": 47
BestTimeBuySellStock MaxProfit_Cooldown1DayAfterSell for "15, 30, 24, 33, 11, 13, 17, 16, 21, 12, 24, 18": 34
-15, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648
-15, 15, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648
-15, 15, -9, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648
-15, 18, -9, 24, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648
-11, 18, 7, 24, 13, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648
-11, 18, 7, 24, 13, 26, -2147483648, -2147483648, -2147483648, -2147483648
-11, 18, 7, 24, 13, 30, 9, -2147483648, -2147483648, -2147483648
-11, 18, 7, 24, 13, 30, 14, 25, -2147483648, -2147483648
-11, 18, 7, 28, 13, 34, 14, 35, 4, -2147483648
-11, 18, 7, 28, 16, 34, 22, 35, 23, 16
-11, 19, 7, 37, 16, 46, 22, 52, 23, 53
-11, 19, 7, 37, 19, 46, 28, 52, 34, 53
BestTimeBuySellStock MaxProfit_AtMostKTransactions_DP1D for "5" in "15, 30, 24, 33, 11, 13, 17, 16, 21, 12, 30, 18": 53
-2, -2147483648
0, -2
0, 2
0, 3
BestTimeBuySellStock MaxProfit_AtMostKTransactions_DP1D for "1" in "2, 0, 2, 3": 3
-1, -2147483648
-1, 1
-1, 2
-1, 2
BestTimeBuySellStock MaxProfit_AtMostKTransactions_DP1D for "1" in "1, 2, 3, 1": 2
-1, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648
-1, 1, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648
-1, 3, -3, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648
-1, 3, 1, -1, -2147483648, -2147483648, -2147483648, -2147483648
-1, 4, 1, 6, -6, -2147483648, -2147483648, -2147483648
-1, 6, 1, 8, -1, 1, -2147483648, -2147483648
-1, 6, 4, 8, 6, 1, -1, -2147483648
-1, 6, 4, 8, 6, 10, -1, 3
-1, 8, 4, 13, 6, 15, 1, 8
0, 8, 8, 13, 13, 15, 15, 8
BestTimeBuySellStock MaxProfit_AtMostKTransactions_DP1D for "4" in "1, 2, 4, 2, 5, 7, 2, 4, 9, 0": 15
BestTimeBuySellStock MaxProfit_AtMostKTransactions_DP2D for "5" in "15, 30, 24, 33, 11, 13, 17, 16, 21, 12, 30, 18": 53
BestTimeBuySellStock MaxProfit_AtMostKTransactions_DP2D for "1" in "2, 0, 2, 3": 3
BestTimeBuySellStock MaxProfit_AtMostKTransactions_DP2D for "1" in "1, 2, 3, 1": 2
BestTimeBuySellStock MaxProfit_AtMostKTransactions_DP2D for "4" in "1, 2, 4, 2, 5, 7, 2, 4, 9, 0": 15
local:	0, 15, 15, 15, 15, 15
global:	0, 15, 15, 15, 15, 15
local:	0, 9, 15, 15, 15, 15
global:	0, 15, 15, 15, 15, 15
local:	0, 18, 24, 24, 24, 24
global:	0, 18, 24, 24, 24, 24
local:	0, 0, 18, 24, 24, 24
global:	0, 18, 24, 24, 24, 24
local:	0, 2, 20, 26, 26, 26
global:	0, 18, 24, 26, 26, 26
local:	0, 6, 24, 30, 30, 30
global:	0, 18, 24, 30, 30, 30
local:	0, 5, 23, 29, 30, 30
global:	0, 18, 24, 30, 30, 30
local:	0, 10, 28, 34, 35, 35
global:	0, 18, 28, 34, 35, 35
local:	0, 1, 19, 28, 34, 35
global:	0, 18, 28, 34, 35, 35
local:	0, 19, 37, 46, 52, 53
global:	0, 19, 37, 46, 52, 53
local:	0, 7, 25, 37, 46, 52
global:	0, 19, 37, 46, 52, 53
BestTimeBuySellStock MaxProfit_AtMostKTransactions_DP1D_2 for "5" in "15, 30, 24, 33, 11, 13, 17, 16, 21, 12, 30, 18": 53
local:	0, 0
global:	0, 0
local:	0, 2
global:	0, 2
local:	0, 3
global:	0, 3
BestTimeBuySellStock MaxProfit_AtMostKTransactions_DP1D_2 for "1" in "2, 0, 2, 3": 3
local:	0, 1
global:	0, 1
local:	0, 2
global:	0, 2
local:	0, 0
global:	0, 2
BestTimeBuySellStock MaxProfit_AtMostKTransactions_DP1D_2 for "1" in "1, 2, 3, 1": 2
local:	0, 1, 1, 1, 1
global:	0, 1, 1, 1, 1
local:	0, 3, 3, 3, 3
global:	0, 3, 3, 3, 3
local:	0, 1, 3, 3, 3
global:	0, 3, 3, 3, 3
local:	0, 4, 6, 6, 6
global:	0, 4, 6, 6, 6
local:	0, 6, 8, 8, 8
global:	0, 6, 8, 8, 8
local:	0, 1, 6, 8, 8
global:	0, 6, 8, 8, 8
local:	0, 3, 8, 10, 10
global:	0, 6, 8, 10, 10
local:	0, 8, 13, 15, 15
global:	0, 8, 13, 15, 15
local:	0, 0, 8, 13, 15
global:	0, 8, 13, 15, 15
BestTimeBuySellStock MaxProfit_AtMostKTransactions_DP1D_2 for "4" in "1, 2, 4, 2, 5, 7, 2, 4, 9, 0": 15
BestTimeBuySellStock MaxProfit_Cooldown1DayAfterSell for "1, 2, 3, 0, 2": 3
*/
#endif