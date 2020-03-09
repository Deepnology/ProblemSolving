/*MEMO*/
#ifndef VALID_SUDOKU_H
#define VALID_SUDOKU_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Debug.h"
/*
Elements of programming interview, Array: The Sudoku checker problem
Leetcode: Valid Sudoku
// Valid Sudoku
// Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.
//
// The Sudoku board could be partially filled, where empty cells are filled
// with the character '.'.
//
// Complexity:
// O(N^2) time, where N is the size of board
*/
class ValidSudoku
{
public:
	ValidSudoku(){}
	~ValidSudoku(){}

	bool GO(std::vector<std::vector<char> > & board)//board is supposed to be 9x9
	{
		Debug::Print2D<char>()(board, false);//[rowY][columnX]

		if (board.size() != 9 || board[0].size() != 9)
		{
			std::cout << "ValidSudoku: False." << std::endl;
			return false;
		}

		//check if each row contains a straight #1 to #9
		for (int i = 0; i < 9; ++i)
		{
			std::vector<int> visited(9, 0);
			for (int j = 0; j < 9; ++j)
			{
				if (!this->isValid(board[i][j], visited))//[i][j]
				{
					std::cout << "ValidSudoku: False." << std::endl;
					return false;
				}
			}
		}

		//check if each column contains a straight #1 to #9
		for (int i = 0; i < 9; ++i)
		{
			std::vector<int> visited(9, 0);
			for (int j = 0; j < 9; ++j)
			{
				if (!this->isValid(board[j][i], visited))//[j][i]
				{
					std::cout << "ValidSudoku: False." << std::endl;
					return false;
				}
			}
		}

		//check if each 3x3 square contains a straight #1 to #9
		for (int i = 0; i < 9; ++i)//iterate thru each 3x3 square
		{
			std::vector<int> visited(9, 0);
			for (int j = 0; j < 9; ++j)//iterate thru each value in local 3x3 square
			{
				int row = (i / 3) * 3 + j / 3;// (i/3)*3: starting row index of current 3x3 square, j/3: local 3x3 square row index
				int col = (i % 3) * 3 + j % 3;// (i%3)*3: starting col index of current 3x3 square, j%3: local 3x3 square col index
				/*
				0  1  2    9  10 11    18 19 20
				3  4  5    12 13 14    21 22 23
				6  7  8    15 16 17    24 25 26
				*/
				//std::cout << row << " " << col << std::endl;
				if (!this->isValid(board[row][col], visited))
				{
					std::cout << "ValidSudoku: False." << std::endl;
					return false;
				}
			}
			//std::cout << std::endl;
		}

		std::cout << "ValidSudoku: True." << std::endl;
		return true;
	}
private:
	bool isValid(char c, std::vector<int> & visited)
	{
		if (c == '.')
			return true;
		if (c < '1' || c > '9' || visited[c - '1'])//c locates out or 1~9 range or already exists in visited
			return false;
		visited[c - '1'] = 1;//mark c in visited
		return true;
	}
};
/*
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

ValidSudoku: True.
*/
#endif