#ifndef SURROUNDED_REGIONS_H
#define SURROUNDED_REGIONS_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Graph: compute enclosed regions
Leetcode: Surrounded Regions
// Given a 2D board containing 'X' and 'O', capture all regions surrounded
// by 'X'.
//
// A region is captured by flipping all 'O's into 'X's in that surrounded
// region.
//
// For example,
// X X X X
// X O O X
// X X O X
// X O X X
// After running your function, the board should be:
//
// X X X X
// X X X X
// X X X X
// X O X X
//
// Complexity:
// BFS: O(n^2) time, O(n) space
*/
class SurroundedRegions
{
public:
	SurroundedRegions(){}
	~SurroundedRegions(){}

	//DFS will cause runtime error in online judge
	void FlipAll_DFS(std::vector<std::vector<char> > & board)//[rowY][columnX]
	{
		if (board.empty() || board[0].empty())
			return;
		std::cout << "SurroundedRegions FlipAll_DFS Before and After:" << std::endl;
		Debug::Print2D<char>()(board, false);

		int M = board.size();
		int N = board[0].size();

		/*1. mark all leftmost/rightmost-column-connected 'O' regions as 'D'*/
		for (int i = 0; i < M; ++i)//from top to bottom
		{
			if (board[i][0] == 'O')//check leftmost column
				this->dfsRecur(board, M, N, i, 0);
			if (board[i][N - 1] == 'O')//check rightmost column
				this->dfsRecur(board, M, N, i, N - 1);
		}

		/*2. mark all top/bottom-row-connected 'O' regions as 'D'*/
		for (int j = 0; j < N; ++j)//from left to right
		{
			if (board[0][j] == 'O')//check top row
				this->dfsRecur(board, M, N, 0, j);
			if (board[M - 1][j] == 'O')//check bottom row
				this->dfsRecur(board, M, N, M - 1, j);
		}

		Debug::Print2D<char>()(board, false);

		/*3. restore all 'D' to 'O'. replace all 'O' to 'X'.*/
		for (int i = 0; i < M; ++i)//from top to bottom
			for (int j = 0; j < N; ++j)//from left to right
			{
				if (board[i][j] == 'D')
					board[i][j] = 'O';
				else if (board[i][j] == 'O')
					board[i][j] = 'X';
			}

		Debug::Print2D<char>()(board, false);
	}
private:
	void dfsRecur(std::vector<std::vector<char> > & board, int M, int N, int x, int y)
	{
		board[x][y] = 'D';
		
		if (x - 1 >= 0 && board[x - 1][y] == 'O')//up neighbor
			this->dfsRecur(board, M, N, x - 1, y);
		if (x + 1 < M && board[x + 1][y] == 'O')//down neighbor
			this->dfsRecur(board, M, N, x + 1, y);
		if (y - 1 >= 0 && board[x][y - 1] == 'O')//left neighbor
			this->dfsRecur(board, M, N, x, y - 1);
		if (y + 1 < N && board[x][y + 1] == 'O')//right neighbor
			this->dfsRecur(board, M, N, x, y + 1);
	}
public:
	void FlipAll_BFS(std::vector<std::vector<char> > & board)//[rowY][columnX]
	{
		if (board.empty() || board[0].empty())
			return;
		std::cout << "SurroundedRegions FlipAll_BFS Before and After:" << std::endl;
		Debug::Print2D<char>()(board, false);

		int M = board.size();
		int N = board[0].size();

		/*1. mark all 'O' as 'D' if it connects to leftmost column or rightmost column*/
		for (int i = 0; i < M; ++i)//from top to bottom
		{
			if (board[i][0] == 'O')//check leftmost column
				this->bfs(board, M, N, i, 0);
			if (board[i][N - 1] == 'O')//check rightmost column
				this->bfs(board, M, N, i, N - 1);
		}

		/*2. mark all 'O' as 'D' if it connects to top row or bottom row*/
		for (int j = 0; j < N; ++j)//from left to right
		{
			if (board[0][j] == 'O')//check top row
				this->bfs(board, M, N, 0, j);
			if (board[M - 1][j] == 'O')//check bottom row
				this->bfs(board, M, N, M - 1, j);
		}

		Debug::Print2D<char>()(board, false);

		/*3. restore all 'D' to 'O'. replace all 'O' to 'X'.*/
		for (int i = 0; i < M; ++i)//from top to bottom
		{
			for (int j = 0; j < N; ++j)//from left to right
			{
				if (board[i][j] == 'D')//boundary connected points
					board[i][j] = 'O';
				else if (board[i][j] == 'O')//'O' that is not connected to boundary
					board[i][j] = 'X';
			}
		}
		Debug::Print2D<char>()(board, false);
	}

private:
	void bfs(std::vector<std::vector<char> > & board, int M, int N, int i, int j)
	{
		board[i][j] = 'D';
		std::queue<int> qs;
		qs.push(i*N + j);//centered at (i,j). (i*N+j is the index of (i,j) from left to right, top to bottom scan)
		while (!qs.empty())
		{
			i = qs.front() / N;//get i from qs.front()
			j = qs.front() % N;//get j from qs.front()
			qs.pop();
			if (i - 1 >= 0 && board[i - 1][j] == 'O')//up neighbor
			{
				board[i - 1][j] = 'D';
				qs.push((i - 1)*N + j);
			}
			if (i + 1 < M && board[i + 1][j] == 'O')//down neighbor
			{
				board[i + 1][j] = 'D';
				qs.push((i + 1)*N + j);
			}
			if (j - 1 >= 0 && board[i][j - 1] == 'O')//left neighbor
			{
				board[i][j - 1] = 'D';
				qs.push(i*N + j - 1);
			}
			if (j + 1 < N && board[i][j + 1] == 'O')//right neighbor
			{
				board[i][j + 1] = 'D';
				qs.push(i*N + j + 1);
			}
		}
	}

};
/*
SurroundedRegions FlipAll_BFS Before and After:
[rY][cX]
Row#0	= X, X, X, X
Row#1	= X, O, O, X
Row#2	= X, O, X, O
Row#3	= O, X, O, X
Row#4	= O, O, X, O

[rY][cX]
Row#0	= X, X, X, X
Row#1	= X, O, O, X
Row#2	= X, O, X, D
Row#3	= D, X, O, X
Row#4	= D, D, X, D

[rY][cX]
Row#0	= X, X, X, X
Row#1	= X, X, X, X
Row#2	= X, X, X, O
Row#3	= O, X, X, X
Row#4	= O, O, X, O

SurroundedRegions FlipAll_DFS Before and After:
[rY][cX]
Row#0	= X, X, X, X
Row#1	= X, O, O, X
Row#2	= X, O, X, O
Row#3	= O, X, O, X
Row#4	= O, O, X, O

[rY][cX]
Row#0	= X, X, X, X
Row#1	= X, O, O, X
Row#2	= X, O, X, D
Row#3	= D, X, O, X
Row#4	= D, D, X, D

[rY][cX]
Row#0	= X, X, X, X
Row#1	= X, X, X, X
Row#2	= X, X, X, O
Row#3	= O, X, X, X
Row#4	= O, O, X, O
*/

#endif