/*MEMO*/
#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Recursion: Implement a Sudoku solver
Leetcode: Sudoku Solver
// Write a program to solve a Sudoku puzzle by filling the empty cells.
//
// Empty cells are indicated by the character '.'.
//
// You may assume that there will be only one unique solution.
//
// Complexity:
// O(M*N^2) time, M is # of empty cells, N is size of board
*/
class SudokuSolver
{
public:
	SudokuSolver(){}
	~SudokuSolver(){}

	void BacktrackRecur(std::vector<std::vector<char> > & board)//[rowY][columnX]
	{
		std::cout << "SudokuSolver1 Before and After:" << std::endl;
		Debug::Print2D<char>()(board, false);
		this->recur(board, 0, 0);
		Debug::Print2D<char>()(board, false);
	}
private:
	bool recur(std::vector<std::vector<char> > & board, int curRow, int curCol)
	{
		int N = board.size();
		if (curCol == N)
		{
			curCol = 0;
			++curRow;
			if (curRow == N)
				return true;
		}
		if (board[curRow][curCol] != '.')
			return this->recur(board, curRow, curCol + 1);//look for the next dot

		//try all possible vals from 1 to N
		for (int val = 1; val <= N; ++val)
		{
			if (this->valid(board, curRow, curCol, val))
			{
				board[curRow][curCol] = '0' + val;//use current valid val, and recur down to look for the next dot
				if (this->recur(board, curRow, curCol + 1))
					return true;
			}
		}

		board[curRow][curCol] = '.';//restore
		return false;
	}
	bool valid(std::vector<std::vector<char> > & board, int curRow, int curCol, int val)
	{
		int N = board.size();
		//1. check row constraints (see if duplicate of val presents)
		for (int row = 0; row < N; ++row)
			if ('0' + val == board[row][curCol])
				return false;
		//2. check col constraints (see if duplicate of val presents)
		for (int col = 0; col < N; ++col)
			if ('0' + val == board[curRow][col])
				return false;
		//3. check region constraints (see if duplicate of val presents)
		int regionSize = (int)sqrt(N);
		int rowOffset = curRow / regionSize;
		int colOffset = curCol / regionSize;
		for (int row = 0; row < regionSize; ++row)
		{
			for (int col = 0; col < regionSize; ++col)
				if ('0' + val == board[regionSize * rowOffset + row][regionSize * colOffset + col])
					return false;
		}
		return true;
	}

public:
	void Solve(std::vector<std::vector<char> > & board)//[rowY][columnX]
	{
		std::cout << "SudokuSolver2 Before and After:" << std::endl;
		Debug::Print2D<char>()(board, false);
		this->solveRecur(board, 0, 0);
		Debug::Print2D<char>()(board, false);
	}
private:
	bool solveRecur(std::vector<std::vector<char> > & board, int curRow, int curCol)//backtracking
	{
		if (!this->getNextDotPos(board, curRow, curCol))//get next dot pos from left to right, top to down
			return true;//reach the end of recursion when there is no more dot after [curRow][curCol]

		//now [curRow][curCol] has been updated to the next dot position in this->getNextDotPos()

		std::vector<char> psVec = this->getPossible(board, curRow, curCol);
		for (int i = 0; i < (int)psVec.size(); ++i)//try each possible value at [curRow][curCol]
		{
			board[curRow][curCol] = psVec[i];//replace the dot at [curRow][curCol] with the possible value
			if (this->solveRecur(board, curRow, curCol))//go to next dot
				return true;
			board[curRow][curCol] = '.';//restore [curRow][curCol] with dot
		}
		return false;//the dot at [curRow][curCol] doesn't have a solution
	}
	/*scan from left to right, top to down*/
	bool getNextDotPos(std::vector<std::vector<char> > & board, int & curRow, int & curCol)
	{
		while (curRow < 9)
		{
			if (board[curRow][curCol] == '.')
				return true;//return true when there exists after [curRow][curCol]
			if (curCol + 1 == 9)
			{
				curRow += 1;
				curCol = 0;
			}
			else
				curCol += 1;
		}
		return false;//(curRow == 9) but can't find a dot
	}
	std::vector<char> getPossible(std::vector<std::vector<char> > & board, int curRow, int curCol)
	{
		bool visit[9];//an array of 1-9 numbers with bool values to indicate that number already appeared in either same row, same column, or same local 3x3 grid
		memset(visit, 0, sizeof(visit));//init visit with all 0s
		for (int i = 0; i < 9; ++i)
		{
			if (board[curRow][i] != '.')
				visit[board[curRow][i] - '1'] = true;//mark the number that already appeared on the same row so far
			if (board[i][curCol] != '.')
				visit[board[i][curCol] - '1'] = true;//mark the number that already appeared on the same column so far
			int rr = curRow / 3 * 3 + i / 3;//curRow/3*3: starting row index of local 3x3 grid. i/3: local row index of 3x3 grid. (suppose scan is from left to right, up to down)
			int cc = curCol / 3 * 3 + i % 3;//curCol/3*3: starting col index of local 3x3 grid. i%3: local col index of 3x3 grid. (suppose scan is from left to right, up to down)
			if (board[rr][cc] != '.')
				visit[board[rr][cc] - '1'] = true;//mark the number that already appeared on the local 3x3 grid so far
		}
		std::vector<char> res;//put all those numbers from 1-9 that haven't been visited in res
		for (int j = 0; j < 9; ++j)
			if (!visit[j])
				res.push_back('1' + j);
		return res;
	}
};
/*
SudokuSolver2 Before and After:
[rY][cX]
Row#0	= 5, 3, ., ., 7, ., ., ., .
Row#1	= 6, ., ., 1, 9, 5, ., ., .
Row#2	= ., 9, 8, ., ., ., ., 6, .
Row#3	= 8, ., ., ., 6, ., ., ., 3
Row#4	= 4, ., ., 8, ., 3, ., ., 1
Row#5	= 7, ., ., ., 2, ., ., ., 6
Row#6	= ., 6, ., ., ., ., 2, 8, .
Row#7	= ., ., ., 4, 1, 9, ., ., 5
Row#8	= ., ., ., ., 8, ., ., 7, 9

[rY][cX]
Row#0	= 5, 3, 4, 6, 7, 8, 9, 1, 2
Row#1	= 6, 7, 2, 1, 9, 5, 3, 4, 8
Row#2	= 1, 9, 8, 3, 4, 2, 5, 6, 7
Row#3	= 8, 5, 9, 7, 6, 1, 4, 2, 3
Row#4	= 4, 2, 6, 8, 5, 3, 7, 9, 1
Row#5	= 7, 1, 3, 9, 2, 4, 8, 5, 6
Row#6	= 9, 6, 1, 5, 3, 7, 2, 8, 4
Row#7	= 2, 8, 7, 4, 1, 9, 6, 3, 5
Row#8	= 3, 4, 5, 2, 8, 6, 1, 7, 9

SudokuSolver1 Before and After:
[rY][cX]
Row#0	= 5, 3, ., ., 7, ., ., ., .
Row#1	= 6, ., ., 1, 9, 5, ., ., .
Row#2	= ., 9, 8, ., ., ., ., 6, .
Row#3	= 8, ., ., ., 6, ., ., ., 3
Row#4	= 4, ., ., 8, ., 3, ., ., 1
Row#5	= 7, ., ., ., 2, ., ., ., 6
Row#6	= ., 6, ., ., ., ., 2, 8, .
Row#7	= ., ., ., 4, 1, 9, ., ., 5
Row#8	= ., ., ., ., 8, ., ., 7, 9

[rY][cX]
Row#0	= 5, 3, 4, 6, 7, 8, 9, 1, 2
Row#1	= 6, 7, 2, 1, 9, 5, 3, 4, 8
Row#2	= 1, 9, 8, 3, 4, 2, 5, 6, 7
Row#3	= 8, 5, 9, 7, 6, 1, 4, 2, 3
Row#4	= 4, 2, 6, 8, 5, 3, 7, 9, 1
Row#5	= 7, 1, 3, 9, 2, 4, 8, 5, 6
Row#6	= 9, 6, 1, 5, 3, 7, 2, 8, 4
Row#7	= 2, 8, 7, 4, 1, 9, 6, 3, 5
Row#8	= 3, 4, 5, 2, 8, 6, 1, 7, 9
*/
#endif