#ifndef TILE_CHESSBOARD_W_DOMINOS_H
#define TILE_CHESSBOARD_W_DOMINOS_H
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
∞ˆæiªP¡Î¡Â
http://tech-queries.blogspot.tw/2011/07/fit-12-dominos-in-2n-strip.html
http://www.careercup.com/question?id=5940697714655232
http://stackoverflow.com/questions/10154775/dynamic-programming-tiles
Given a NxM board containing 0s and 1s, and unlimited 2x1 dominos.
A domino can be tiled only on 2 consecutive 0s.
Count the total number of ways to completely tile dominos on the board.

special case for 2xn board containing all 0s:
the total number of ways = Fibonacci Number of (n+1)
This problem reduces to find the number of ways to partition n using the numbers 1 and 2 with order considered relevant.
Suppose we have Xn possible arrangements for n.
Then for (n+1), we can either place just 1 domino in the end.
Or we can find possible arrangements for (n-1) and put 2 dominos in the end.
So X(n+1) = Xn + X(n-1)
*/
class TileChessboardWDominos
{
public:
	TileChessboardWDominos(){}
	~TileChessboardWDominos(){}

	int Count_Recur(const std::vector<std::vector<int> > & board)
	{
		int N = board.size();
		int M = board[0].size();
		std::vector<std::vector<int> > used(N, std::vector<int>(M, 0));
		int res = this->recur(board, 0, 0, used);
		Debug::Print2D<int>()(board, false);
		//Debug::Print2D<int>()(used, false);
		std::cout << "TileChessboardWDominos Count_Recur: " << res << std::endl;
		return res;
	}
private:
	int recur(const std::vector<std::vector<int> > & board, int rowY, int colX, std::vector<std::vector<int> > & used)
	{
		int N = board.size();
		int M = board[0].size();
		if (colX == M)
			return this->recur(board, rowY + 1, 0, used);
		if (rowY == N)
			return 1;

		if (used[rowY][colX] || board[rowY][colX])//current pixel cannot be tiled: skip it and try the next one
			return this->recur(board, rowY, colX + 1, used);

		int res = 0;
		used[rowY][colX] = 1;
		if (colX + 1 < M && !used[rowY][colX + 1] && !board[rowY][colX + 1])
		{
			used[rowY][colX + 1] = 1;//tile a domino on [rowY,colX] and [rowY,colX+1] (horizontally)
			res += this->recur(board, rowY, colX + 1, used);
			used[rowY][colX + 1] = 0;
		}
		if (rowY + 1 < N && !used[rowY + 1][colX] && !board[rowY + 1][colX])
		{
			used[rowY + 1][colX] = 1;//tile a domino on [rowY,colX] and [rowY+1,colX] (vertically)
			res += this->recur(board, rowY, colX + 1, used);
			used[rowY + 1][colX] = 0;
		}
		used[rowY][colX] = 0;
		return res;
	}

public:
	int Count_DP1D(const std::vector<std::vector<int> > & board)
	{
		int N = board.size();
		int M = board[0].size();
		/*
		refer to ∞ˆæiªP¡Î¡Â
		*/
		return 0;
	}

	//special case for 2xn chessboard
public:
	//1) use Fibonacci sequences: First few Fibonacci numbers = 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 141, ...
	int FibonacciRecur_2xn(int n)
	{
		int res = this->fibonacciRecur(n + 1);
		std::cout << "TileChessboardWDominos FibonacciRecur_2xn for \"" << n << "\": " << res << std::endl;
		return res;
	}
private:
	int fibonacciRecur(int n)
	{
		if (n <= 1)
			return n;
		return this->fibonacciRecur(n - 1) + this->fibonacciRecur(n - 2);
	}

public:
	//2) climbing stairs: First few numbers = 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 141, ...
	int ClimbStairRecur_2xn(int n)
	{
		int res = this->climbStairRecur(n);
		std::cout << "TileChessboardWDominos ClimbStairRecur_2xn for \"" << n << "\": " << res << std::endl;
		return res;
	}
private:
	int climbStairRecur(int n)
	{
		if (n <= 1)
			return 1;
		return this->climbStairRecur(n - 1) + this->climbStairRecur(n - 2);
	}
};
/*
[rY][cX]
Row#0	= 0, 0, 0
Row#1	= 0, 1, 0
Row#2	= 0, 0, 0

TileChessboardWDominos Count_Recur: 2
[rY][cX]
Row#0	= 0, 0, 0, 0
Row#1	= 0, 0, 0, 0
Row#2	= 0, 0, 0, 0
Row#3	= 0, 0, 0, 0

TileChessboardWDominos Count_Recur: 36
[rY][cX]
Row#0	= 0, 0
Row#1	= 0, 0
Row#2	= 0, 0
Row#3	= 0, 0

TileChessboardWDominos Count_Recur: 5
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 0, 0, 0, 0, 0

TileChessboardWDominos Count_Recur: 21
TileChessboardWDominos FibonacciRecur_2xn for "4": 5
TileChessboardWDominos FibonacciRecur_2xn for "7": 21
TileChessboardWDominos ClimbStairRecur_2xn for "4": 5
TileChessboardWDominos ClimbStairRecur_2xn for "7": 21
*/
#endif