#ifndef _WORD_SEARCH_H
#define _WORD_SEARCH_H
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "Debug.h"
/*
Elements of programming interview, DynamicProgramming: Search for a sequence in a 2D array
Leetcode: Word Search
// Word Search
// Given a 2D board and a word, find if the word exists in the grid.
//
// The word can be constructed from letters of sequentially adjacent cell,
// where "adjacent" cells are those horizontally or vertically neighboring.
// The same letter cell may not be used more than once.
//
// For example,
// Given board =
//
// [
//   ["ABCE"],
//   ["SFCS"],
//   ["ADEE"]
// ]
// word = "ABCCED", -> returns true,
// word = "SEE", -> returns true,
// word = "ABCB", -> returns false.
*/
class WordSearch
{
public:
	WordSearch(){}
	~WordSearch(){}

	bool DFS_LinearSpace(const std::vector<std::vector<char> > & board, std::string word)//[rowY][columnX]
	{
		if (board.empty() || board[0].empty() || word.empty())
			return false;
		Debug::Print2D<char>()(board, false);

		int M = board.size();
		int N = board[0].size();

		std::vector<std::vector<int> > visitedBoard(M, std::vector<int>(N, 0));//std::vector<>(size_t, init_val)

		for (int i = 0; i < M; ++i)//for each row from top to bottom
		{
			for (int j = 0; j < N; ++j)//for each col from left to right
			{
				if (board[i][j] == word[0] &&//check every pos in board if it matches the first char of word
					this->dfs_LinearSpace_Recur(board, visitedBoard, i, j, word, 0))//recur down to 4 dirs of current pos
				{
					std::cout << "WordSearch DFS_LinearSpace Found \"" << word << "\" at [" << i << "][" << j << "]" << std::endl;
					return true;
				}
			}
		}

		std::cout << "WordSearch DFS_LinearSpace Not Found \"" << word << "\"." << std::endl;
		return false;
	}
private:
	bool dfs_LinearSpace_Recur(const std::vector<std::vector<char> > & board, std::vector<std::vector<int> > & visitedBoard
		, int curRow, int curCol, std::string & word, int curIndex)
	{
		++curIndex;
		if (curIndex == word.size())
			return true;
		int M = board.size();
		int N = board[0].size();

		visitedBoard[curRow][curCol] = 1;//mark current pos as true since it was matched

		if ((curRow > 0 && !visitedBoard[curRow - 1][curCol]) && board[curRow - 1][curCol] == word[curIndex] &&//up pos matches word[curIndex]
			this->dfs_LinearSpace_Recur(board, visitedBoard, curRow - 1, curCol, word, curIndex))//recur down to up pos
			return true;
		if ((curRow < M - 1 && !visitedBoard[curRow + 1][curCol]) && board[curRow + 1][curCol] == word[curIndex] &&//down pos matches word[curIndex]
			this->dfs_LinearSpace_Recur(board, visitedBoard, curRow + 1, curCol, word, curIndex))//recur down to down pos
			return true;
		if ((curCol > 0 && !visitedBoard[curRow][curCol - 1]) && board[curRow][curCol - 1] == word[curIndex] &&//left pos matches word[curIndex]
			this->dfs_LinearSpace_Recur(board, visitedBoard, curRow, curCol - 1, word, curIndex))//recur down to left pos
			return true;
		if ((curCol < N - 1 && !visitedBoard[curRow][curCol + 1]) && board[curRow][curCol + 1] == word[curIndex] &&//right pos matches word[curIndex]
			this->dfs_LinearSpace_Recur(board, visitedBoard, curRow, curCol + 1, word, curIndex))//recur down to right pos
			return true;

		visitedBoard[curRow][curCol] = 0;//restore current pos as false when exiting recur call when none of left/right/down/up pos matches
		return false;
	}

public:
	bool DFS_ConstSpace(std::vector<std::vector<char> > & board, std::string word)//[rowY][columnX]
	{
		if (board.empty() || board[0].empty() || word.empty())
			return false;
		Debug::Print2D<char>()(board, false);

		int M = board.size();
		int N = board[0].size();

		for (int i = 0; i < M; ++i)//for each row from top to bottom
		{
			for (int j = 0; j < N; ++j)//for each col from left to right
			{
				if (board[i][j] == word[0])//check every pos in board if it matches the first char of word
				{
					if (this->dfs_ConstSpace_Recur(board, i, j, word, 0))//recur down to 4 dirs of current pos
					{
						std::cout << "WordSearch DFS_ConstSpace Found \"" << word << "\" at [" << i << "][" << j << "]" << std::endl;
						return true;
					}
				}
			}
		}

		std::cout << "WordSearch DFS_ConstSpace Not Found \"" << word << "\"." << std::endl;
		return false;
	}
private:
	bool dfs_ConstSpace_Recur(std::vector<std::vector<char> > & board
		, int curRow, int curCol, std::string & word, int curIndex)
	{
		++curIndex;
		if (curIndex == word.size())
			return true;
		int M = board.size();
		int N = board[0].size();

		char c = board[curRow][curCol];
		board[curRow][curCol] = '.';

		if (curRow - 1 >= 0 && board[curRow - 1][curCol] == word[curIndex])//up pos matches word[curIndex]
		{
			if (this->dfs_ConstSpace_Recur(board, curRow - 1, curCol, word, curIndex))//recur down to up pos
			{
				board[curRow][curCol] = c;
				return true;
			}
		}
		if (curRow + 1 < M && board[curRow + 1][curCol] == word[curIndex])//down pos matches word[curIndex]
		{
			if (this->dfs_ConstSpace_Recur(board, curRow + 1, curCol, word, curIndex))//recur down to down pos
			{
				board[curRow][curCol] = c;
				return true;
			}
		}
		if (curCol - 1 >= 0 && board[curRow][curCol - 1] == word[curIndex])//left pos matches word[curIndex]
		{
			if (this->dfs_ConstSpace_Recur(board, curRow, curCol - 1, word, curIndex))//recur down to left pos
			{
				board[curRow][curCol] = c;
				return true;
			}
		}
		if (curCol + 1 < N && board[curRow][curCol + 1] == word[curIndex])//right pos matches word[curIndex]
		{
			if (this->dfs_ConstSpace_Recur(board, curRow, curCol + 1, word, curIndex))//recur down to right pos
			{
				board[curRow][curCol] = c;
				return true;
			}
		}

		board[curRow][curCol] = c;
		return false;
	}
};
/*
[rY][cX]
Row#0	= A, B, C, E
Row#1	= S, F, C, S
Row#2	= A, D, E, E

WordSearch DFS_LinearSpace Found "ABCCED" at [0][0]
[rY][cX]
Row#0	= A, B, C, E
Row#1	= S, F, C, S
Row#2	= A, D, E, E

WordSearch DFS_LinearSpace Found "SEE" at [1][3]
[rY][cX]
Row#0	= A, B, C, E
Row#1	= S, F, C, S
Row#2	= A, D, E, E

WordSearch DFS_LinearSpace Not Found "ABCB".
[rY][cX]
Row#0	= A, B, C, E
Row#1	= S, F, C, S
Row#2	= A, D, E, E

WordSearch DFS_ConstSpace Found "ABCCED" at [0][0]
[rY][cX]
Row#0	= A, B, C, E
Row#1	= S, F, C, S
Row#2	= A, D, E, E

WordSearch DFS_ConstSpace Found "SEE" at [1][3]
[rY][cX]
Row#0	= A, B, C, E
Row#1	= S, F, C, S
Row#2	= A, D, E, E

WordSearch DFS_ConstSpace Not Found "ABCB".
*/
#endif