/*MEMO*/
#ifndef DUNGEON_GAME_H
#define DUNGEON_GAME_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Dungeon Game
http://massivealgorithms.blogspot.tw/2015/01/leetcodedungeon-game.html
The demons had captured the princess (P) and imprisoned her in the bottom-right corner of a dungeon.
The dungeon consists of M x N rooms laid out in a 2D grid.
Our valiant knight (K) was initially positioned in the top-left room and must fight his way through the dungeon to rescue the princess.
The knight has an initial health point represented by a positive integer.
If at any point his health point drops to 0 or below, he dies immediately.
Some of the rooms are guarded by demons, so the knight loses health (negative integers) upon entering these rooms; other rooms are either empty (0's) or contain magic orbs that increase the knight's health (positive integers).
In order to reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.
Write a function to determine the knight's minimum initial health so that he is able to rescue the princess.
For example, given the dungeon below
, the initial health of the knight must be at least 7 if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.
-2 (K)    -3     3
-5       -10     1
10        30    -5 (P)
Notes:
The knight's health has no upper bound.
Any room can contain threats or power-ups
, even the first room the knight enters and the bottom-right room where the princess is imprisoned.

DP2D: O(mn) time, O(mn) space
*/
class DungeonGame
{
public:
	DungeonGame(){}
	~DungeonGame(){}

	int DP2D(const std::vector<std::vector<int>> & v)
	{
		int N = v.size();
		int M = v[0].size();
		std::vector<std::vector<int>> dp(N, std::vector<int>(M));
		//dp[i][j]: minimum POSITIVE-NON-ZERO health required to consume from v[i][j] to v[N-1][M-1]


		for (int row = N - 1; row >= 0; --row)
		{
			for (int col = M - 1; col >= 0; --col)
			{
				if (row == N - 1 && col == M - 1)
					dp[row][col] = std::max(1 - v[row][col], 1);//dp[N-1][M-1] + v[N-1][M-1] must be >= 1, and dp[N-1][M-1] must be >= 1
				else if (col == M - 1)
					dp[row][col] = std::max(dp[row + 1][col] - v[row][col], 1);//dp[row][M-1] + v[row][M-1] must be >= dp[row+1][M-1], and dp[row][M-1] must be >= 1
				else if (row == N - 1)
					dp[row][col] = std::max(dp[row][col + 1] - v[row][col], 1);
				else
				{
					int minDown = std::max(dp[row + 1][col] - v[row][col], 1);
					int minRight = std::max(dp[row][col + 1] - v[row][col], 1);
					dp[row][col] = std::min(minDown, minRight);
				}
			}
		}

		Debug::Print2D<int>()(v, false);
		Debug::Print2D<int>()(dp, false);
		std::cout << "DungeonGame DP2D: " << dp[0][0] << std::endl;
		return dp[0][0];
	}
};
/*
[rY][cX]
Row#0	= -2, -3, 3
Row#1	= -5, -10, 1
Row#2	= 10, 30, -5

[rY][cX]
Row#0	= 7, 5, 2
Row#1	= 6, 11, 5
Row#2	= 1, 1, 6

DungeonGame DP2D: 7
*/
#endif