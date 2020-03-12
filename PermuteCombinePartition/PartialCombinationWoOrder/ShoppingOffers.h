#ifndef SHOPPING_OFFERS_H
#define SHOPPING_OFFERS_H
#include "Debug.h"
/*
Leetcode: Shopping Offers
In LeetCode Store, there are some kinds of items to sell.
Each item has a price.
However, there are some special offers, and a special offer consists of one or more different kinds of items with a sale price.
You are given the each item's price, a set of special offers, and the number we need to buy for each item.
The job is to output the lowest price you have to pay for exactly certain items as given, where you could make optimal use of the special offers.
Each special offer is represented in the form of an array, the last number represents the price you need to pay for this special offer, other numbers represents how many specific items you could get if you buy this offer.
You could use any of special offers as many times as you want.
Example 1:
Input: [2,5], [[3,0,5],[1,2,10]], [3,2]
Output: 14
Explanation:
There are two kinds of items, A and B. Their prices are $2 and $5 respectively.
In special offer 1, you can pay $5 for 3A and 0B
In special offer 2, you can pay $10 for 1A and 2B.
You need to buy 3A and 2B, so you may pay $10 for 1A and 2B (special offer #2), and $4 for 2A.
Example 2:
Input: [2,3,4], [[1,1,0,4],[2,2,1,9]], [1,2,1]
Output: 11
Explanation:
The price of A is $2, and $3 for B, $4 for C.
You may pay $4 for 1A and 1B, and $9 for 2A ,2B and 1C.
You need to buy 1A ,2B and 1C, so you may pay $4 for 1A and 1B (special offer #1), and $3 for 1B, $4 for 1C.
You cannot add more items, though only $9 for 2A ,2B and 1C.
Note:
There are at most 6 kinds of items, 100 special offers.
For each item, you need to buy at most 6 of them.
You are not allowed to buy more items than you want, even if that would lower the overall price.
*/
class ShoppingOffers
{
public:
	ShoppingOffers() {}

	//price: [item0Price,item1Price,...,itemNPrice]
	//special[i]: [item0Count,item1Count,...,itemNCount,price]
	//needs: [item0TotalCount,item1TotalCount,...,itemNTotalCount]
	int DFS(std::vector<int> & price, std::vector<std::vector<int>> & special, std::vector<int> & needs)
	{
		int res = INT_MAX;
		recur(price, special, needs, 0, res);
		return res;//return min cost to buy all items needed
	}
	void recur(std::vector<int> & price, std::vector<std::vector<int>> & special, std::vector<int> & needs, int total, int & minCost)
	{
		//try to use as many special as possible
		int N = special.size();
		for (int i = 0; i < N; ++i)
		{
			bool validSpecial = true;
			int M = special[i].size();
			for (int j = 0; j < M - 1; ++j)
			{
				if (special[i][j] > needs[j])
				{
					validSpecial = false;
					break;
				}
			}
			if (validSpecial)
			{
				for (int j = 0; j < M - 1; ++j)
					needs[j] -= special[i][j];
				total += special[i][M - 1];
				recur(price, special, needs, total, minCost);
				total -= special[i][M - 1];
				for (int j = 0; j < M - 1; ++j)
					needs[j] += special[i][j];
			}
		}
		//try to buy remaining items w/ retail prices
		int M = price.size();
		for (int i = 0; i < M; ++i)
		{
			if (needs[i] == 0) continue;
			total += needs[i] * price[i];
		}
		minCost = std::min(minCost, total);
	}
};
#endif
