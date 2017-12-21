#ifndef ALL_STOCK_SPANS_H
#define ALL_STOCK_SPANS_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/the-stock-span-problem/
http://en.wikipedia.org/wiki/Stack_(abstract_data_type)#The_Stock_Span_Problem

Given a series of n daily price quotes for a stock:
Price = [9,7,4,5,4,6,8]
Calculate span of stock's price for all n days.
The span of a stock's price on a given day is:
the max number of consecutive days just before the given day, for which the price of the stock on the current day is less than or equal to its price on the given day
(the number of all left consecutive days of the given day, including the given day itself, that has a less equal price than the given day)
Span = [1,1,1,2,1,4,6]

9  X
8  |           X
7  | X         |
6  | |         |
5  | |   X   X |
4  | | X | X | |
3  | | | | | | |
2  | | | | | | |
1  | | | | | | |
0  0 1 2 3 4 5 6

see also LargestRectHistogram.h, CartesianTree.h, MaxBandwidthOverWindowTimeInterval.h

BruteForce: O(n^2) time, O(1) space
SortedStack: O(n) time, O(n) space in worst case when all elements are sorted in decreasing order
*/
class AllStockSpans
{
public:
	AllStockSpans(){}
	~AllStockSpans(){}

	std::vector<int> SortedStack(const std::vector<int> & prices)
	{
		int N = prices.size();
		std::stack<int> stk;//store the index of the price bar in strckly decreasing order (pop out all smaller equal indices before pushing new index)
		stk.push(0);
		std::vector<int> spans(N);
		spans[0] = 1;
		for (int i = 1; i < N; ++i)
		{
			while (!stk.empty() && prices[stk.top()] <= prices[i])
			{
				stk.pop();
			}
			int curSpan = stk.empty() ? (i + 1) : (i - stk.top());//curSapn excludes left boundary includes right boundary
			spans[i] = curSpan;
			stk.push(i);
		}
		std::cout << "AllStockSpans SortedStack for \"" << Debug::ToStr1D<int>()(prices) << "\": " << Debug::ToStr1D<int>()(spans) << std::endl;
		return spans;
	}
};
/*
AllStockSpans SortedStack for "9, 7, 4, 5, 4, 5, 8": 1, 1, 1, 2, 1, 4, 6
*/
#endif