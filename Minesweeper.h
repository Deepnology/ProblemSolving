#ifndef MINESWEEPER_H
#define MINESWEEPER_H
#include "Debug.h"
/*
Leetcode: Minesweeper
You are given a 2D char matrix representing the game board. 'M' represents an unrevealed mine, 'E' represents an unrevealed empty square, 'B' represents a revealed blank square that has no adjacent (above, below, left, right, and all 4 diagonals) mines, digit ('1' to '8') represents how many mines are adjacent to this revealed square, and finally 'X' represents a revealed mine.
Now given the next click position (row and column indices) among all the unrevealed squares ('M' or 'E'), return the board after revealing this position according to the following rules:
1. If a mine ('M') is revealed, then the game is over - change it to 'X'.
2. If an empty square ('E') with no adjacent mines is revealed, then change it to revealed blank ('B') and all of its adjacent unrevealed squares should be revealed recursively.
3. If an empty square ('E') with at least one adjacent mine is revealed, then change it to a digit ('1' to '8') representing the number of adjacent mines.
4. Return the board when no more squares will be revealed.
Example 1:
Input:
[['E', 'E', 'E', 'E', 'E'],
 ['E', 'E', 'M', 'E', 'E'],
 ['E', 'E', 'E', 'E', 'E'],
 ['E', 'E', 'E', 'E', 'E']]
Click : [3,0]
Output:
[['B', '1', 'E', '1', 'B'],
 ['B', '1', 'M', '1', 'B'],
 ['B', '1', '1', '1', 'B'],
 ['B', 'B', 'B', 'B', 'B']]

*/
class Minesweeper
{
public:
	Minesweeper() {}
	std::vector<std::vector<char>> UpdateBoard(std::vector<std::vector<char>> & board, std::vector<int> & click)
	{
		Debug::Print2D<char>()(board, false);
		recur(board, click[0], click[1]);
		std::cout << "Minesweeper UpdateBoard for the above board w/ click=\"" << Debug::ToStr1D<int>()(click) << "\":" << std::endl;
		Debug::Print2D<char>()(board, false);
		return board;
	}
	void recur(std::vector<std::vector<char>> & board, int i, int j)
	{
		if (board[i][j] == 'M')
		{
			board[i][j] = 'X';
			return;
		}
		if (board[i][j] != 'E') return;//skip 'X', '1'~'8', 'B'

		int N = board.size();
		int M = board[0].size();
		std::vector<std::vector<int>> dir = { { -1,0 },{ 1,0 },{ 0,-1 },{ 0,1 },{ -1,-1 },{ 1,-1 },{ -1,1 },{ 1,1 } };
		int countM = 0;
		for (int k = 0; k < 8; ++k)
		{
			int ii = i + dir[k][0];
			int jj = j + dir[k][1];
			if (ii >= 0 && ii < N && jj >= 0 && jj < M)
			{
				if (board[ii][jj] == 'M')
					++countM;
			}
		}
		if (countM == 0)
		{
			board[i][j] = 'B';
			for (int k = 0; k < 8; ++k)
			{
				int ii = i + dir[k][0];
				int jj = j + dir[k][1];
				if (ii >= 0 && ii < N && jj >= 0 && jj < M)
				{
					recur(board, ii, jj);
				}
			}
		}
		else
			board[i][j] = countM + '0';
	}
};
/*
[rY][cX]
Row#0	= E, E, E, E, E
Row#1	= E, E, M, E, E
Row#2	= E, E, E, E, E
Row#3	= E, E, E, E, E

Minesweeper UpdateBoard for the above board w/ click="3, 0":
[rY][cX]
Row#0	= B, 1, E, 1, B
Row#1	= B, 1, M, 1, B
Row#2	= B, 1, 1, 1, B
Row#3	= B, B, B, B, B
*/
#endif
