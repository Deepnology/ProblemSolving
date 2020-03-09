#ifndef OPTIMAL_BINARY_SEARCH_TREE_H
#define OPTIMAL_BINARY_SEARCH_TREE_H
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/dynamic-programming-set-24-optimal-binary-search-tree/
Given a sorted array keys[0...n-1] of search keys and an array freq[0...n-1] of frequency counts
, where freq[i] is the number of searches to keys[i].
Construct a binary search tree of all keys such that the total cost of all the searches is as small as possible.

The cost of a BST node is level of that node multiplied by its frequency.

The optimal cost for freq[i...j] can be recursively calculated using the formula.
                     j                j
optCost(i,j) = Sigma    freq[k] + min    [optCost(i, r-1) + optCost(r+1, j)]
                     k=i              r=i
The result is optCost(0, n-1).


Recur: exponential time
DP2D: O(n^3) time, O(n^2) space

See also MatrixChainMultiplication.h, MaxVerticesSumOfPolygon.h, MaxSumParenthesizeArithmeticExpr.h
*/
class OptimalBinarySearchTree
{
public:
	OptimalBinarySearchTree(){}
	~OptimalBinarySearchTree(){}

	int Cost_Recur(const std::vector<int> & freq)
	{
		int N = freq.size();
		int res = this->cost_recur(freq, 0, N - 1);
		std::cout << "OptimalBinarySearchTree Cost_Recur for \"" << Debug::ToStr1D<int>()(freq) << "\": " << res << std::endl;
		return res;
	}
private:
	int cost_recur(const std::vector<int> & freq, int left, int right)
	{
		if (left > right)
			return 0;
		if (left == right)
			return freq[left];
		int sum = this->sum(freq, left, right);//repeatedly count and add the sum of freq as depth goes down, which is equivalent to multiply level with freq
		int min = INT_MAX;
		for (int mid = left; mid <= right; ++mid)
		{
			/*calculate the cost considering mid as root*/
			int cost = this->cost_recur(freq, left, mid - 1) + this->cost_recur(freq, mid + 1, right);
			if (cost < min)
				min = cost;
		}
		return sum + min;//cur level freq sum + min of all possible 2-way partition freq sum of left subtree plus right subtree
	}
	int sum(const std::vector<int> & freq, int left, int right)
	{
		int sum = 0;
		for (int i = left; i <= right; ++i)
			sum += freq[i];
		return sum;
	}

public:
	int Cost_DP2D(const std::vector<int> & freq)
	{
		int N = freq.size();
		std::vector<std::vector<int> > dp(N, std::vector<int>(N));
		std::vector<std::vector<int> > sumFreq(N, std::vector<int>(N));
		/*
		sumFreq[left][right]: cur level freq sum in between [left,right]
		dp[left][right]: optimum freq sum in between [left,right]
		= cur level freq sum + min of all possible 2-way partition freq sum of left subtree plus right subtree
		*/
		for (int i = 0; i < N; ++i)
			dp[i][i] = freq[i];

		for (int i = 0; i < N; ++i)
		{
			for (int j = i; j < N; ++j)
			{
				sumFreq[i][j] = 0;
				for (int s = i; s <= j && s < N; ++s)
					sumFreq[i][j] += freq[s];
			}
		}

		for (int len = 2; len <= N; ++len)
		{
			for (int left = 0; left < N - len + 1; ++left)
			{
				int right = left + len - 1;
				dp[left][right] = INT_MAX;
				for (int mid = left; mid <= right; ++mid)
				{
					/*calculate the cost considering mid as root*/
					int cost = (mid > left ? dp[left][mid - 1] : 0) +//optimum freq sum of left subtree
						(mid < right ? dp[mid + 1][right] : 0) +//optimum freq sum of right subtree
						sumFreq[left][right];//cur level freq sum

					if (cost < dp[left][right])
						dp[left][right] = cost;
				}
			}
		}

		Debug::Print2D<int>()(sumFreq, false);
		Debug::Print2D<int>()(dp, false);
		std::cout << "OptimalBinarySearchTree Cost_DP2D for \"" << Debug::ToStr1D<int>()(freq) << "\": " << dp[0][N - 1] << std::endl;
		return dp[0][N - 1];
	}
};
/*
OptimalBinarySearchTree Cost_Recur for "10, 12, 20": 72
[rY][cX]
Row#0	= 10, 22, 42
Row#1	= 0, 12, 32
Row#2	= 0, 0, 20

[rY][cX]
Row#0	= 10, 32, 72
Row#1	= 0, 12, 44
Row#2	= 0, 0, 20

OptimalBinarySearchTree Cost_DP2D for "10, 12, 20": 72
OptimalBinarySearchTree Cost_Recur for "34, 8, 50": 142
[rY][cX]
Row#0	= 34, 42, 92
Row#1	= 0, 8, 58
Row#2	= 0, 0, 50

[rY][cX]
Row#0	= 34, 50, 142
Row#1	= 0, 8, 66
Row#2	= 0, 0, 50

OptimalBinarySearchTree Cost_DP2D for "34, 8, 50": 142
*/
#endif