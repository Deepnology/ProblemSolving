#ifndef MAX_PROFIT_BUY_SELL_STOCK_H
#define MAX_PROFIT_BUY_SELL_STOCK_H
#include "Debug.h"
/*
https://discuss.leetcode.com/topic/97310/most-consistent-ways-of-dealing-with-the-series-of-stock-problems
Leetcode:
121. Best Time to Buy and Sell Stock
122. Best Time to Buy and Sell Stock II
123. Best Time to Buy and Sell Stock III
188. Best Time to Buy and Sell Stock IV
309. Best Time to Buy and Sell Stock with Cooldown
714. Best Time to Buy and Sell Stock with Transaction Fee

*/
class MaxProfitBuySellStock
{
public:
	MaxProfitBuySellStock() {}

	int OneTransaction(std::vector<int> & prices)
	{
		int N = prices.size();
		int hold0 = 0;
		int hold1 = INT_MIN;
		for (int i = 0; i < N; ++i)
		{
			hold0 = std::max(hold0, hold1 + prices[i]);//after action we hold 0 stock: can rest or sell
			hold1 = std::max(hold1, -prices[i]);//after action we hold 1 stock: can rest or buy
		}
		return hold0;
	}

	int UnlimitedTransactions(std::vector<int> & prices)
	{
		int N = prices.size();
		int hold0 = 0;
		int hold1 = INT_MIN;
		for (int i = 0; i < N; ++i)
		{
			int hold0_old = hold0;
			hold0 = std::max(hold0, hold1 + prices[i]);//after action we hold 0 stock: can rest or sell
			hold1 = std::max(hold1, hold0_old - prices[i]);//after action we hold 1 stock: can rest or buy
		}
		return hold0;
	}

	int AtMost2Transactions(std::vector<int> & prices)
	{
		int N = prices.size();
		int hold0_1 = 0;//first transaction
		int hold1_1 = INT_MIN;//first transaction
		int hold0_2 = 0;
		int hold1_2 = INT_MIN;
		for (int i = 0; i < N; ++i)
		{
			hold0_2 = std::max(hold0_2, hold1_2 + prices[i]);
			hold1_2 = std::max(hold1_2, hold0_1 - prices[i]);//after action we hold 1 stock for 2nd transaction: can rest or buy
			hold0_1 = std::max(hold0_1, hold1_1 + prices[i]);
			hold1_1 = std::max(hold1_1, -prices[i]);
		}
		return hold0_2;
	}

	int AtMostKTransactions(std::vector<int> & prices, int k)
	{
		int N = prices.size();
		if (k >= N / 2)
		{
			int hold0 = 0;
			int hold1 = INT_MIN;
			for (int i = 0; i < N; ++i)
			{
				int hold0_old = hold0;
				hold0 = std::max(hold0, hold1 + prices[i]);
				hold1 = std::max(hold1, hold0_old - prices[i]);
			}
			return hold0;
		}

		std::vector<int> hold0(k + 1, 0);
		std::vector<int> hold1(k + 1, INT_MIN);
		for (int i = 0; i < N; ++i)
		{
			for (int j = k; j > 0; --j)
			{
				hold0[j] = std::max(hold0[j], hold1[j] + prices[i]);
				hold1[j] = std::max(hold1[j], hold0[j - 1] - prices[i]);
			}
		}
		return hold0[k];
	}

	int UnlimitedTransactionsWithCooldown(std::vector<int> & prices)
	{
		int N = prices.size();
		int preHold0 = 0;
		int hold0 = 0;
		int hold1 = INT_MIN;
		for (int i = 0; i < N; ++i)
		{
			int hold0_old = hold0;
			hold0 = std::max(hold0, hold1 + prices[i]);//after action we hold 0 stock: can rest or sell
			hold1 = std::max(hold1, preHold0 - prices[i]);//after action we hold 1 stock: can rest or buy
			preHold0 = hold0_old;
		}
		return hold0;
	}
	int UnlimitedTransactionsWithTransactionFee(std::vector<int> & prices, int fee)
	{
		int N = prices.size();
		long long hold0 = 0;
		long long hold1 = INT_MIN;
		for (int i = 0; i < N; ++i)
		{
			long long hold0_old = hold0;
			hold0 = std::max(hold0, hold1 + prices[i] - fee);//after action we hold 0 stock: can rest or sell
			hold1 = std::max(hold1, hold0_old - prices[i]);//after action we hold 1 stock: can rest or buy
		}
		return hold0;
	}
};
#endif
