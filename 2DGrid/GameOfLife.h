#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H
#include <vector>
#include <iostream>
#include <string>
#include "Debug.h"
/*
Leetcode: Game of Life
According to the Wikipedia's article: "The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970."
Given a board with m by n cells, each cell has an initial state live (1) or dead (0).
Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia article):

Any live cell with fewer than two live neighbors dies, as if caused by under-population.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by over-population..
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
Write a function to compute the next state (after one update) of the board given its current state.

Follow up:
Could you solve it in-place? Remember that the board needs to be updated at the same time: You cannot update some cells first and then use their updated values to update other cells.
In this question, we represent the board using a 2D array. In principle, the board is infinite, which would cause problems when the active area encroaches the border of the array. How would you address these problems?
*/
class GameOfLife
{
public:
	GameOfLife() {}
	~GameOfLife() {}

	//UseExtraSpace
	void UseExtraSpace(std::vector<std::vector<int>> & board)
	{
		Debug::Print2D<int>()(board, false);

		int N = board.size();
		int M = board[0].size();

		std::vector<std::vector<int>> tmp(N, std::vector<int>(M, 0));//record the next state while keeping original state unchanged
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				int count = this->countNeighbor(board, i, j);
				if (board[i][j])//live
				{
					if (count < 2 || count > 3)
						tmp[i][j] = 0;//live->dead
					else
						tmp[i][j] = 1;//not changed
				}
				else//dead
				{
					if (count == 3)
						tmp[i][j] = 1;//dead->live
					else
						tmp[i][j] = 0;//not changed
				}
			}
		}
		board.swap(tmp);

		std::cout << "GameOfLife UseExtraSpace for above board:" << std::endl;
		Debug::Print2D<int>()(board, false);
	}
	int countNeighbor(const std::vector<std::vector<int>> & board, int row, int col)
	{
		int N = board.size();
		int M = board[0].size();
		int count = 0;
		if (row - 1 >= 0)
		{
			count += board[row - 1][col];
			if (col - 1 >= 0)
				count += board[row - 1][col - 1];
			if (col + 1 < M)
				count += board[row - 1][col + 1];
		}
		if (col - 1 >= 0)
			count += board[row][col - 1];
		if (col + 1 < M)
			count += board[row][col + 1];
		if (row + 1 < N)
		{
			count += board[row + 1][col];
			if (col - 1 >= 0)
				count += board[row + 1][col - 1];
			if (col + 1 < M)
				count += board[row + 1][col + 1];
		}
		return count;
	}

	//InPlace
	void InPlace(std::vector<std::vector<int>> & board)
	{
		Debug::Print2D<int>()(board, false);

		int N = board.size();
		int M = board[0].size();

		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				int count = this->countNeighbor2(board, i, j);
				if (board[i][j])//live
				{
					if (count < 2 || count > 3)
						board[i][j] = 2;//live->dead (which means it was originally live! so should count this neighbor in when computing its neighbors)
					else
						board[i][j] = 1;//not changed
				}
				else//dead
				{
					if (count == 3)
						board[i][j] = 3;//dead->live
					else
						board[i][j] = 0;//not changed
				}
			}
		}

		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				board[i][j] = board[i][j] % 2;
			}
		}

		std::cout << "GameOfLife InPlace for above board:" << std::endl;
		Debug::Print2D<int>()(board, false);
	}
	int countNeighbor2(const std::vector<std::vector<int>> & board, int row, int col)
	{
		//++count if neighbor == 1(originally live or live->live) or neighbor == 2(live->dead, which means it was originally live)
		int N = board.size();
		int M = board[0].size();
		int count = 0;
		if (row - 1 >= 0)
		{
			count += board[row - 1][col] == 1 || board[row - 1][col] == 2 ? 1 : 0;
			if (col - 1 >= 0)
				count += board[row - 1][col - 1] == 1 || board[row - 1][col - 1] == 2 ? 1 : 0;
			if (col + 1 < M)
				count += board[row - 1][col + 1] == 1 || board[row - 1][col + 1] == 2 ? 1 : 0;
		}
		if (col - 1 >= 0)
			count += board[row][col - 1] == 1 || board[row][col - 1] == 2 ? 1 : 0;
		if (col + 1 < M)
			count += board[row][col + 1] == 1 || board[row][col + 1] == 2 ? 1 : 0;
		if (row + 1 < N)
		{
			count += board[row + 1][col] == 1 || board[row + 1][col] == 2 ? 1 : 0;
			if (col - 1 >= 0)
				count += board[row + 1][col - 1] == 1 || board[row + 1][col - 1] == 2 ? 1 : 0;
			if (col + 1 < M)
				count += board[row + 1][col + 1] == 1 || board[row + 1][col + 1] == 2 ? 1 : 0;
		}
		return count;
	}
};
/*
[rY][cX]
Row#0	= 1, 0, 0, 0, 1, 0, 0, 0
Row#1	= 0, 0, 0, 1, 0, 0, 1, 1
Row#2	= 0, 0, 1, 0, 1, 0, 1, 0
Row#3	= 0, 0, 0, 1, 0, 0, 0, 0
Row#4	= 1, 0, 0, 0, 1, 0, 0, 1
Row#5	= 0, 1, 1, 0, 0, 0, 0, 1
Row#6	= 0, 0, 1, 1, 0, 0, 1, 0

GameOfLife UseExtraSpace for above board:
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 0, 1, 1, 0, 1, 1
Row#2	= 0, 0, 1, 0, 1, 1, 1, 1
Row#3	= 0, 0, 0, 1, 1, 1, 0, 0
Row#4	= 0, 1, 1, 1, 0, 0, 0, 0
Row#5	= 0, 1, 1, 0, 0, 0, 1, 1
Row#6	= 0, 1, 1, 1, 0, 0, 0, 0

[rY][cX]
Row#0	= 1, 0, 0, 0, 1, 0, 0, 0
Row#1	= 0, 0, 0, 1, 0, 0, 1, 1
Row#2	= 0, 0, 1, 0, 1, 0, 1, 0
Row#3	= 0, 0, 0, 1, 0, 0, 0, 0
Row#4	= 1, 0, 0, 0, 1, 0, 0, 1
Row#5	= 0, 1, 1, 0, 0, 0, 0, 1
Row#6	= 0, 0, 1, 1, 0, 0, 1, 0

GameOfLife InPlace for above board:
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 0, 1, 1, 0, 1, 1
Row#2	= 0, 0, 1, 0, 1, 1, 1, 1
Row#3	= 0, 0, 0, 1, 1, 1, 0, 0
Row#4	= 0, 1, 1, 1, 0, 0, 0, 0
Row#5	= 0, 1, 1, 0, 0, 0, 1, 1
Row#6	= 0, 1, 1, 1, 0, 0, 0, 0
*/
#endif
