#ifndef _MATRIX_CHAIN_MULTIPLICATION_H_
#define _MATRIX_CHAIN_MULTIPLICATION_H_
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/dynamic-programming-set-8-matrix-chain-multiplication/
http://www.careercup.com/question?id=15168662

Given an array A which contains dimensions of matrices.
Find the minimum number of multiplications needed to multiply the chain of matrices.
(A[i-1],A[i]) forms a dimension pair of a matrix A[i].
The count of multiplications of 2 matrices A[i] (A[i-1],A[i]) and A[i+1] (A[i],A[i+1]) is A[i-1]*A[i]*A[i+1].
The result matrix A[i+1] has dimension (A[i-1],A[i+1]).

Recur: exponential time
DP2D: O(n^3) time, O(n^2) space

See also MaxVerticesSumOfPolygon.h, MaxSumParenthesizeArithmeticExpr.h, OptimalBinarySearchTree.h, LongestPalindromeSubseq.h
*/

class MatrixChainMultiplication
{
public:
	MatrixChainMultiplication(){}
	~MatrixChainMultiplication(){}

	int Recur(const std::vector<int> & v)
	{
		int N = v.size();
		int res = this->recur(v, 1, N - 1);
		std::cout << "MatrixChainMultiplication Recur for \"" << Debug::ToStr1D<int>()(v) << "\": " << res << std::endl;
		return res;
	}
private:
	int recur(const std::vector<int> & v, int left, int right)
	{
		if (left == right)
			return 0;
		/*
		place parenthesis at different places between first and last matrix,
		recursively calculate count of multiplcations for each parenthesis
		placement and return the minimum count
		*/
		int min = INT_MAX;
		for (int mid = left; mid < right; ++mid)
		{
			int count = this->recur(v, left, mid) +
				this->recur(v, mid + 1, right) +
				v[left - 1] * v[mid] * v[right];

			if (count < min)
				min = count;
		}
		return min;
	}




public:
	int DP2D(const std::vector<int> & v)
	{
		int N = v.size();
		std::vector<std::vector<int> > dp(N + 1, std::vector<int>(N + 1));
		/*
		0th row and 0th column are not used
		dp[i][j]: min count of multiplications between v[i] and v[j]
		*/
		
		/*
		1. cost is 0 when multiplying one matrix
		*/
		for (int i = 1; i < N; ++i)
			dp[i][i] = 0;

		/*
		2. 
		left index: first matrix (v[left-1],v[left])
		right index: last matrix (v[right-1],v[right])
		len: length of matrices between [i,j] inclusive
		len = 2: only one matrix
		len = 3: two matrices
		matrix count = len - 1

		len = 2: 1 <= left < N-1, right = left+1
		len = 3: 1 <= left < N-2, right = left+2

		len = N-2: left = 1, left = 2, right = left+N-3
		len = N-1: left = 1, right = N-1
		*/

		for (int len = 2; len < N; ++len)
		{
			for (int left = 1; left < N - len + 1; ++left)
			{
				int right = left + len - 1;
				dp[left][right] = INT_MAX;

				for (int mid = left; mid < right; ++mid)
				{
					int cost = dp[left][mid] + 
						dp[mid + 1][right] + 
						v[left - 1] * v[mid] * v[right];

					if (cost < dp[left][right])
						dp[left][right] = cost;
				}
			}
		}

		Debug::Print2D<int>()(dp, false);
		std::cout << "MatrixChainMultiplication DP2D for \"" << Debug::ToStr1D<int>()(v) << "\": " << dp[1][N - 1] << std::endl;
		return dp[1][N - 1];
	}
	
};

/*
MatrixChainMultiplication Recur for "40, 20, 30, 10, 30": 26000
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 24000, 14000, 26000, 0
Row#2	= 0, 0, 0, 6000, 12000, 0
Row#3	= 0, 0, 0, 0, 9000, 0
Row#4	= 0, 0, 0, 0, 0, 0
Row#5	= 0, 0, 0, 0, 0, 0

MatrixChainMultiplication DP2D for "40, 20, 30, 10, 30": 26000
*/



#endif

