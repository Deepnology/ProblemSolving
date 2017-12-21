#ifndef TIC_TAC_TOE_GAME_H
#define TIC_TAC_TOE_GAME_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "Debug.h"
/*
http://www.cnblogs.com/grandyang/p/5467118.html
Leetcode: Design Tic-Tac-Toe
Design a Tic-tac-toe game that is played between two players on a n x n grid.
You may assume the following rules:
A move is guaranteed to be valid and is placed on an empty block.
Once a winning condition is reached, no more moves is allowed.
A player who succeeds in placing n of their marks in a horizontal, vertical, or diagonal row wins the game.
Example:
Given n = 3, assume that player 1 is "X" and player 2 is "O" in the board.
Follow up:
Could you do better than O(n2) per move() operation?
Hint:
Could you trade extra space such that move() operation can be done in O(1)?
You need two arrays: int rows[n], int cols[n], plus two variables: diagonal, anti_diagonal.

Cracking the coding interview: Moderate
O . X
. O O
X X X
return 'X'
*/
class TicTacToeGame
{
public:
	TicTacToeGame(){}
	~TicTacToeGame(){}
	
public:
	//Leetcode: keep track sum of each row, each col, diag, and revDiag
	explicit TicTacToeGame(int n): m_rows(n, 0), m_cols(n, 0), m_diag(0), m_revDiag(0), m_N(n) {}
	std::vector<int> m_rows;
	std::vector<int> m_cols;
	int m_diag;
	int m_revDiag;
	int m_N;
	int move(int row, int col, int player)//return 0: continue; 1: player1 win; 2: player2 win
	{
		int add = player == 1 ? 1 : -1;//player1: add1; player2: subtract1
		m_rows[row] += add;
		m_cols[col] += add;
		m_diag += (row == col ? add : 0);
		m_revDiag += (row == m_N - col - 1 ? add : 0);

		if (std::abs(m_rows[row]) == m_N || std::abs(m_cols[col]) == m_N || std::abs(m_diag) == m_N || std::abs(m_revDiag) == m_N)
		{
			std::cout << "TicTacToeGame: " << player << ", (" << row << ", " << col << "). Wins." << std::endl;
			return player;
		}
		else
		{
			std::cout << "TicTacToeGame: " << player << ", (" << row << ", " << col << "). Continue." << std::endl;
			return 0;
		}
	}



	int Board3x3_HashTable(const std::vector<std::vector<char> > & board)
	{
		int N = board.size();
		int M = board[0].size();
		int factor = 1;
		int sum = 0;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				int curVal = 0;//empty
				if (board[i][j] == 'X')
					curVal = 1;//X
				else if (board[i][j] == 'O')
					curVal = 2;//O
				sum += curVal * factor;
				factor *= 3;
			}
		}
		Debug::Print2D<char>()(board, false);
		std::cout << "TicTacToeGame HashTable: " << sum << std::endl;
		return sum;
	}

	char Board3x3(const std::vector<std::vector<char> > & board)
	{
		Debug::Print2D<char>()(board, false);
		int N = board.size();
		for (int i = 0; i < N; ++i)
		{
			//check each rowY
			if (board[i][0] != '.' && board[i][0] == board[i][1] && board[i][0] == board[i][2])
			{
				std::cout << "TicTacToeGame Board3x3: " << board[i][0] << std::endl;
				return board[i][0];
			}
			//check each colX
			if (board[0][i] != '.' && board[0][i] == board[1][i] && board[0][i] == board[2][i])
			{
				std::cout << "TicTacToeGame Board3x3: " << board[0][i] << std::endl;
				return board[0][i];
			}
		}

		//check diagonal
		if (board[0][0] != '.' && board[0][0] == board[1][1] && board[0][0] == board[2][2])
		{
			std::cout << "TicTacToeGame Board3x3: " << board[0][0] << std::endl;
			return board[0][0];
		}
		//check reverse diagonal
		if (board[0][2] != '.' && board[0][2] == board[1][1] && board[0][2] == board[2][0])
		{
			std::cout << "TicTacToeGame Board3x3: " << board[0][2] << std::endl;
			return board[0][2];
		}

		std::cout << "TicTacToeGame Board3x3: " << '.' << std::endl;
		return '.';
	}

	char BoardNxN(const std::vector<std::vector<char> > & board)
	{
		Debug::Print2D<char>()(board, false);
		int N = board.size();

		//check each rowY
		for (int rowY = 0; rowY < N; ++rowY)
		{
			if (board[rowY][0] != '.')
			{
				int colX;
				for (colX = 1; colX < N; ++colX)
				{
					if (board[rowY][0] != board[rowY][colX])
						break;
				}
				if (colX == N)
				{
					std::cout << "TicTacToeGame BoardNxN: " << board[rowY][0] << std::endl;
					return board[rowY][0];
				}
			}
		}

		//check each colX
		for (int colX = 0; colX < N; ++colX)
		{
			if (board[0][colX] != '.')
			{
				int rowY;
				for (rowY = 1; rowY < N; ++rowY)
				{
					if (board[0][colX] != board[rowY][colX])
						break;
				}
				if (rowY == N)
				{
					std::cout << "TicTacToeGame BoardNxN: " << board[0][colX] << std::endl;
					return board[0][colX];
				}
			}
		}

		//check diagonal
		if (board[0][0] != '.')
		{
			int rowY;
			for (rowY = 1; rowY < N; ++rowY)
			{
				if (board[0][0] != board[rowY][rowY])
					break;
			}
			if (rowY == N)
			{
				std::cout << "TicTacToeGame BoardNxN: " << board[0][0] << std::endl;
				return board[0][0];
			}
		}

		//check reverse diagonal
		if (board[0][N - 1] != '.')
		{
			int rowY;
			for (rowY = 1; rowY < N; ++rowY)
			{
				if (board[0][N - 1] != board[rowY][N - 1 - rowY])
					break;
			}
			if (rowY == N)
			{
				std::cout << "TicTacToeGame BoardNxN: " << board[0][N - 1] << std::endl;
				return board[0][N - 1];
			}
		}

		std::cout << "TicTacToeGame BoardNxN: " << '.' << std::endl;
		return '.';
	}
};
/*
TicTacToeGame: 1, (0, 0). Continue.
TicTacToeGame: 2, (0, 2). Continue.
TicTacToeGame: 1, (2, 2). Continue.
TicTacToeGame: 2, (1, 1). Continue.
TicTacToeGame: 1, (2, 0). Continue.
TicTacToeGame: 2, (1, 0). Continue.
TicTacToeGame: 1, (2, 1). Wins.
[rY][cX]
Row#0	= O, O, X
Row#1	= O, X, X
Row#2	= X, ., O

TicTacToeGame HashTable: 14246
[rY][cX]
Row#0	= O, O, X
Row#1	= O, X, X
Row#2	= X, ., O

TicTacToeGame Board3x3: X
[rY][cX]
Row#0	= O, O, X
Row#1	= O, X, X
Row#2	= X, ., O

TicTacToeGame BoardNxN: X
*/
#endif