#ifndef N_QUEENS_H
#define N_QUEENS_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Recursion: Enumerate all non-attacking placements of n-Queens
Leetcode: N-Queens I
// The n-queens puzzle is the problem of placing n queens on an n¡Ñn chessboard
// such that no two queens attack each other. 
// (any two queens cannot be on the same row, column, or diagonal.)
// Complexity:
// O(n^(n+2)) time

Leetcode: N-Queens II
// Follow up for N-Queens problem.
//
// Now, instead outputting board configurations, return the total number of
// distinct solutions.
//
// Complexity:
// O(n^n)
*/
class NQueens
{
public:
	NQueens(){}
	~NQueens(){}
	std::vector<std::vector<std::string> > Solve1(int n)
	{
		/*
		a path is a valid solution
		index: row index, value: column index of Q
		for example, {1, 3, 5, 0, 2, 4} represents the following configuration of a 6x6 board:
		.Q....
		...Q..
		.....Q
		Q.....
		..Q...
		....Q.
		*/
		std::vector<int> path(n, -1);
		std::vector<std::vector<std::string> > res;//[columnX][rowY]. but each solution res[i] should be a board[rowY][colX]
		this->solve1Recur(path, 0, res);

		std::cout << "NQueens1 for \"" << n << "\":" << std::endl;
		Debug::Print2D<std::string>()(res);
		return res;
	}
private:
	void solve1Recur(std::vector<int> & path, int curRow, std::vector<std::vector<std::string> > & res)//backtracking
	{
		int N = path.size();
		if (curRow == N)//reach end of each path
		{
			std::vector<std::string> board(N, std::string(N, '.'));//[rowY][colX]. init with N rows, each row filled with '.'
			for (int rowY = 0; rowY < N; ++rowY)
				board[rowY][path[rowY]] = 'Q';//(path[rowY] is the valid 'Q' column index at current row index)
			res.push_back(board);
			return;
		}

		/*at current row, try to place Q at each column*/
		for (int col = 0; col < N; ++col)
		{
			if (!this->isValid(path, curRow, col))
				continue;
			path[curRow] = col;//place Q at col
			this->solve1Recur(path, curRow + 1, res);//go down to the next row
		}
	}
	/*check if the (curRow,curCol) point can be a valid Q with comparison to previous Qs on the path*/
	bool isValid(std::vector<int> & path, int curRow, int curCol)
	{
		/*for each prevRow:
		1. curCol can't be same as Q's col => not in the same column
		2. the dist of curCol to Q's col (horizontal) can't be same as dist of curRow to prevRow (vertical) => not in the same diagonal
		*/
		for (int preRow = 0; preRow < curRow; ++preRow)
			if (path[preRow] == curCol || std::abs(path[preRow] - curCol) == curRow - preRow)
				return false;
		return true;
	}

public:
	std::vector<std::vector<std::string> > Solve2(int n)
	{
		std::vector<int> board(n, -1);
		std::vector<std::vector<std::string> > res;//[columnX][rowY]
		this->Solve2Recur(board, 0, 0, 0, 0, res);

		std::cout << "NQueens2 for \"" << n << "\":" << std::endl;
		Debug::Print2D<std::string>()(res);
		return res;
	}
private:
	void Solve2Recur(std::vector<int> & board, int row, int cur, int ld, int rd, std::vector<std::vector<std::string> > & res)
	{
		int N = board.size();
		int mask = (1 << N) - 1;
		if (cur == mask)
		{
			std::vector<std::string> sub(N, std::string(N, '.'));
			for (int r = 0; r < N; ++r)
			{
				for (int c = 0; c < N; ++c)
				{
					if (board[r] & (1 << c))
						sub[r][c] = 'Q';
				}
			}
			res.push_back(sub);
			return;
		}

		int cs = ~(cur | ld | rd) & mask;
		while (cs > 0)
		{
			int p = cs & -cs;
			cs -= p;
			board[row] = p;
			this->Solve2Recur(board, row + 1, cur | p, (ld | p) << 1, (rd | p) >> 1, res);
		}
	}




public:
	int TotalQueens1(int n)
	{
		std::vector<int> path(n, -1);
		int res = 0;
		this->totalQueens1Recur(path, 0, res);
		std::cout << "NQueens1 Total Queens for \"" << n << "\" is: " << res << std::endl;
		return res;
	}
private:
	void totalQueens1Recur(std::vector<int> & path, int curRow, int & res)
	{
		int N = path.size();
		if (curRow == N)
		{
			++res;
			return;
		}
		for (int col = 0; col < N; ++col)
		{
			if (!this->isValid(path, curRow, col))
				continue;
			path[curRow] = col;
			this->totalQueens1Recur(path, curRow + 1, res);
		}
	}

public:
	int TotalQueens2(int n)
	{
		int res = 0;
		this->totalQueens2Recur(n, 0, 0, 0, 0, res);
		std::cout << "NQueens2 Total Queens for \"" << n << "\" is: " << res << std::endl;
		return res;
	}
private:
	void totalQueens2Recur(int N, int row, int cur, int ld, int rd, int & res)
	{
		int mask = (1 << N) - 1;
		if (cur == mask)
		{
			++res;
			return;
		}
		int cs = ~(cur | ld | rd) &mask;
		while (cs > 0)
		{
			int p = cs & -cs;
			cs -= p;
			this->totalQueens2Recur(N, row + 1, cur | p, (ld | p) << 1, (rd | p) >> 1, res);
		}
	}
};
/*
NQueens1 for "6":
[cX][rY]
Row#0	= .Q...., ..Q..., ...Q.., ....Q.
Row#1	= ...Q.., .....Q, Q....., ..Q...
Row#2	= .....Q, .Q...., ....Q., Q.....
Row#3	= Q....., ....Q., .Q...., .....Q
Row#4	= ..Q..., Q....., .....Q, ...Q..
Row#5	= ....Q., ...Q.., ..Q..., .Q....

NQueens2 for "6":
[cX][rY]
Row#0	= .Q...., ..Q..., ...Q.., ....Q.
Row#1	= ...Q.., .....Q, Q....., ..Q...
Row#2	= .....Q, .Q...., ....Q., Q.....
Row#3	= Q....., ....Q., .Q...., .....Q
Row#4	= ..Q..., Q....., .....Q, ...Q..
Row#5	= ....Q., ...Q.., ..Q..., .Q....

NQueens1 Total Queens for "6" is: 4
NQueens2 Total Queens for "6" is: 4
*/
#endif