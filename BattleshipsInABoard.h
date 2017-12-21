#ifndef BATTLESHIPS_IN_A_BOARD_H
#define BATTLESHIPS_IN_A_BOARD_H
#include "Debug.h"
/*
Leetcode: Battleships in a board
Given an 2D board, count how many battleships are in it.
The battleships are represented with 'X's, empty slots are represented with '.'s. You may assume the following rules:
You receive a valid board, made of only battleships or empty slots.
Battleships can only be placed horizontally or vertically.
In other words, they can only be made of the shape 1xN (1 row, N columns) or Nx1 (N rows, 1 column), where N can be of any size.
At least one horizontal or vertical cell separates between two battleships - there are no adjacent battleships.
Example:
X..X
...X
...X
In the above board there are 2 battleships.
Invalid Example:
...X
XXXX
...X
This is an invalid board that you will not receive - as battleships will always have a cell separating between them.
Follow up:
Could you do it in one-pass, using only O(1) extra memory and without modifying the value of the board?

*/
class BattleshipsInABoard
{
public:
	BattleshipsInABoard() {}

	int CountUpperLeftCorners(std::vector<std::vector<char>> & board)
	{
		int N = board.size();
		if (N == 0) return 0;
		int M = board[0].size();
		if (M == 0) return 0;
		int res = 0;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				if ((i == 0 || board[i - 1][j] == '.') && (j == 0 || board[i][j - 1] == '.') && board[i][j] == 'X')
					++res;
			}
		}

		Debug::Print2D<char>()(board, false);
		std::cout << "BattleshipsInABoard CountUpperLeftCorners for above board: " << res << std::endl;
		return res;
	}
};
/*
[rY][cX]
Row#0	= X, ., ., X
Row#1	= ., ., ., X
Row#2	= ., ., ., X

BattleshipsInABoard CountUpperLeftCorners for above board: 2
*/
#endif
