#ifndef PAINT_ALL_SAME_COLOR_PIXELS_H
#define PAINT_ALL_SAME_COLOR_PIXELS_H
#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include "Debug.h"
/*
Elements of programming interview, Graph: Paint a boolean matrix
Cracking the coding interview: Recursion and DP

DFS/BFS search and MARK consecutive same color pixels.

See also AllDistinctSubAreaInMatrix.h
*/
class PaintAllSameColorPixels
{
public:
	PaintAllSameColorPixels(){}
	~PaintAllSameColorPixels(){}

	bool DFSRecur(std::vector<std::vector<int> > & board, int rowY, int colX, int newColor)
	{
		if (board[rowY][colX] == newColor)
			return false;
		Debug::Print2D<int>()(board, false);
		bool res = this->dFSRecur(board, rowY, colX, board[rowY][colX], newColor);
		Debug::Print2D<int>()(board, false);
		std::cout << "PaintFillAllSameColorPixels DFSRecur at [" << rowY << ", " << colX << "]: " << newColor << std::endl;
		return res;
	}
private:
	bool dFSRecur(std::vector<std::vector<int> > & board, int rowY, int colX, int originalColor, int newColor)
	{
		int N = board.size();
		int M = board[0].size();
		if (rowY < 0 || rowY >= N || colX < 0 || colX >= M)
			return false;
		if (board[rowY][colX] == originalColor)
		{
			board[rowY][colX] = newColor;
			this->dFSRecur(board, rowY - 1, colX, originalColor, newColor);
			this->dFSRecur(board, rowY + 1, colX, originalColor, newColor);
			this->dFSRecur(board, rowY, colX - 1, originalColor, newColor);
			this->dFSRecur(board, rowY, colX + 1, originalColor, newColor);
		}
		return true;
	}

public:
	bool BFSIterate(std::vector<std::vector<int> > & board, int rowY, int colX, int newColor)
	{
		if (board[rowY][colX] == newColor)
			return false;
		Debug::Print2D<int>()(board, false);

		int N = board.size();
		int M = board[0].size();

		int originalColor = board[rowY][colX];
		std::queue<std::pair<int, int> > que;
		que.push({ rowY, colX });
		while (!que.empty())
		{
			auto p = que.front();
			que.pop();
			board[p.first][p.second] = newColor;//now visit the pixel
			if (p.first - 1 >= 0 && board[p.first - 1][p.second] == originalColor)
				que.push({ p.first - 1, p.second });
			if (p.first + 1 < N && board[p.first + 1][p.second] == originalColor)
				que.push({ p.first + 1, p.second });
			if (p.second - 1 >= 0 && board[p.first][p.second - 1] == originalColor)
				que.push({ p.first, p.second - 1 });
			if (p.second + 1 < M && board[p.first][p.second + 1] == originalColor)
				que.push({ p.first, p.second + 1 });
		}
		Debug::Print2D<int>()(board, false);
		std::cout << "PaintFillAllSameColorPixels BFSIterate at [" << rowY << ", " << colX << "]: " << newColor << std::endl;
		return true;
	}
};
/*
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#2	= 0, 0, 0, 0, 1, 1, 0, 0, 0, 0
Row#3	= 0, 0, 0, 1, 1, 1, 1, 0, 0, 0
Row#4	= 1, 1, 1, 1, 1, 1, 1, 0, 0, 0
Row#5	= 1, 0, 1, 1, 1, 1, 1, 1, 0, 0
Row#6	= 1, 0, 1, 1, 1, 1, 1, 1, 0, 0
Row#7	= 0, 0, 1, 1, 0, 0, 1, 0, 0, 0
Row#8	= 0, 0, 1, 0, 0, 0, 1, 1, 0, 0
Row#9	= 1, 1, 0, 0, 0, 0, 0, 1, 1, 1

[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#2	= 0, 0, 0, 0, 7, 7, 0, 0, 0, 0
Row#3	= 0, 0, 0, 7, 7, 7, 7, 0, 0, 0
Row#4	= 7, 7, 7, 7, 7, 7, 7, 0, 0, 0
Row#5	= 7, 0, 7, 7, 7, 7, 7, 7, 0, 0
Row#6	= 7, 0, 7, 7, 7, 7, 7, 7, 0, 0
Row#7	= 0, 0, 7, 7, 0, 0, 7, 0, 0, 0
Row#8	= 0, 0, 7, 0, 0, 0, 7, 7, 0, 0
Row#9	= 1, 1, 0, 0, 0, 0, 0, 7, 7, 7

PaintFillAllSameColorPixels DFSRecur at [4, 4]: 7
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#2	= 0, 0, 0, 0, 1, 1, 0, 0, 0, 0
Row#3	= 0, 0, 0, 1, 1, 1, 1, 0, 0, 0
Row#4	= 1, 1, 1, 1, 1, 1, 1, 0, 0, 0
Row#5	= 1, 0, 1, 1, 1, 1, 1, 1, 0, 0
Row#6	= 1, 0, 1, 1, 1, 1, 1, 1, 0, 0
Row#7	= 0, 0, 1, 1, 0, 0, 1, 0, 0, 0
Row#8	= 0, 0, 1, 0, 0, 0, 1, 1, 0, 0
Row#9	= 1, 1, 0, 0, 0, 0, 0, 1, 1, 1

[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#2	= 0, 0, 0, 0, 7, 7, 0, 0, 0, 0
Row#3	= 0, 0, 0, 7, 7, 7, 7, 0, 0, 0
Row#4	= 7, 7, 7, 7, 7, 7, 7, 0, 0, 0
Row#5	= 7, 0, 7, 7, 7, 7, 7, 7, 0, 0
Row#6	= 7, 0, 7, 7, 7, 7, 7, 7, 0, 0
Row#7	= 0, 0, 7, 7, 0, 0, 7, 0, 0, 0
Row#8	= 0, 0, 7, 0, 0, 0, 7, 7, 0, 0
Row#9	= 1, 1, 0, 0, 0, 0, 0, 7, 7, 7

PaintFillAllSameColorPixels BFSIterate at [4, 4]: 7
*/
#endif