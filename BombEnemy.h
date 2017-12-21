#ifndef BOMB_ENEMY_H
#define BOMB_ENEMY_H
#include "Debug.h"
/*
Leetcode: Bomb Enemy
Given a 2D grid, each cell is either a wall 'W', an enemy 'E' or empty '0' (the number zero), return the maximum enemies you can kill using one bomb.
The bomb kills all the enemies in the same row and column from the planted point until it hits the wall since the wall is too strong to be destroyed.
Note that you can only put the bomb at an empty cell.

Example:
For the given grid

0 E 0 0
E 0 W E
0 E 0 0

return 3. (Placing a bomb at (1,1) kills 3 enemies)
*/
class BombEnemy
{
public:
	BombEnemy() {}
	~BombEnemy() {}

	int MaxKilledEnemies(const std::vector<std::vector<char>> & board)
	{
		int N = board.size();
		int M = board[0].size();

		//For each empty cell, need to compute left, up, right, down reachable enemies
		//if we perform a 2D scan from up to down, left to right, we can simultaneously keep track of the count of enemies from left in each row
		//as well as using an array to keep track of the count of enemies from up in each column
		//but we don't have the count of enemies from cur to right and from cur to down, so need to precompute 2D enemy count matrices from right and from down
		std::vector<std::vector<int>> down(N, std::vector<int>(M, 0));
		std::vector<std::vector<int>> right(N, std::vector<int>(M, 0));

		//1. precompute down[][] and right[][] by scanning from down to up, right to left
		for (int i = N - 1; i >= 0; --i)
		{
			for (int j = M - 1; j >= 0; --j)
			{
				if (board[i][j] == 'W')
				{
					down[i][j] = 0;
					right[i][j] = 0;
				}
				else if (board[i][j] == 'E')
				{
					if (j + 1 <= M - 1)
						right[i][j] = right[i][j + 1] + 1;
					else
						++right[i][j];
					if (i + 1 <= N - 1)
						down[i][j] = down[i + 1][j] + 1;
					else
						++down[i][j];
				}
				else//'0'
				{
					if (j + 1 <= M - 1)
						right[i][j] = right[i][j + 1];
					if (i + 1 <= N - 1)
						down[i][j] = down[i + 1][j];
				}
			}
		}

		std::vector<int> up(M, 0);
		int res = 0;
		int resRow = 0;
		int resCol = 0;
		//2. scan from up to down, left to right
		for (int i = 0; i < N; ++i)
		{
			int left = 0;
			for (int j = 0; j < M; ++j)
			{
				if (board[i][j] == 'W')
				{
					left = 0;
					up[j] = 0;
				}
				else if (board[i][j] == 'E')
				{
					++left;
					++up[j];
				}
				else
				{
					int count = left + up[j] + right[i][j] + down[i][j];
					if (count > res)
					{
						res = count;
						resRow = i;
						resCol = j;
					}
				}
			}
		}

		Debug::Print2D<int>()(down, false);
		Debug::Print2D<int>()(right, false);
		Debug::Print2D<char>()(board, false);
		std::cout << "BombEnemy MaxKillEnemies for the above board: " << res << " (" << resRow << "," << resCol << ")" << std::endl;
		return res;
	}
};
/*
[rY][cX]
Row#0	= 1, 2, 0, 1
Row#1	= 1, 1, 0, 1
Row#2	= 0, 1, 0, 0

[rY][cX]
Row#0	= 1, 1, 0, 0
Row#1	= 1, 0, 0, 1
Row#2	= 1, 1, 0, 0

[rY][cX]
Row#0	= 0, E, 0, 0
Row#1	= E, 0, W, E
Row#2	= 0, E, 0, 0

BombEnemy MaxKillEnemies for the above board: 3 (1,1)
[rY][cX]
Row#0	= 1, 4, 0, 2, 3, 1, 1, 2
Row#1	= 1, 3, 0, 1, 2, 0, 1, 1
Row#2	= 0, 3, 0, 1, 1, 1, 0, 1
Row#3	= 0, 2, 3, 0, 1, 0, 0, 0
Row#4	= 3, 2, 2, 0, 0, 0, 2, 2
Row#5	= 2, 1, 1, 1, 2, 0, 1, 1
Row#6	= 1, 0, 0, 1, 1, 0, 0, 1

[rY][cX]
Row#0	= 1, 1, 0, 4, 3, 2, 1, 1
Row#1	= 2, 1, 1, 1, 1, 0, 1, 0
Row#2	= 1, 1, 0, 3, 2, 2, 1, 1
Row#3	= 0, 2, 2, 1, 1, 0, 0, 0
Row#4	= 3, 2, 1, 0, 0, 0, 2, 1
Row#5	= 5, 4, 3, 2, 2, 1, 1, 0
Row#6	= 1, 0, 0, 3, 2, 1, 1, 1

[rY][cX]
Row#0	= 0, E, W, E, E, E, 0, E
Row#1	= E, 0, 0, 0, E, W, E, 0
Row#2	= 0, E, W, E, 0, E, 0, E
Row#3	= W, 0, E, 0, E, 0, W, W
Row#4	= E, E, E, W, W, W, E, E
Row#5	= E, E, E, 0, E, 0, E, 0
Row#6	= E, 0, W, E, E, 0, 0, E

BombEnemy MaxKillEnemies for the above board: 7 (5,7)
*/
#endif
