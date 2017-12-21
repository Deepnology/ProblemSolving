#ifndef ALL_SHORTEST_PATHS_IN_MATRIX_H
#define ALL_SHORTEST_PATHS_IN_MATRIX_H
#include <vector>
#include <queue>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Walls and Gates
Given a 2D N*M matrix with obstacles, find the shortest distance of each non-obstacle to a (nearest) source.
1. single source: ∞ˆæiªP¡Î¡Â Shortest path in maze
2. multi-source:
Google
http://www.careercup.com/question?id=4716965625069568

To find shortest paths, use BFS
(DFS will repeate calculated paths)
O(N*M) time, O(N*M) space
*/
class AllShortestPathsInMatrix
{
public:
	AllShortestPathsInMatrix(){}
	~AllShortestPathsInMatrix(){}

	//'S': source, '#': obstacle, '.': target
	//find the shortest path of each target to a nearest source
	std::vector<std::vector<int> > BFS(const std::vector<std::vector<char> > & board)
	{
		int N = board.size();
		int M = board[0].size();
		std::vector<std::vector<int> > dist(N, std::vector<int>(M, INT_MAX));
		std::queue<std::pair<int, int> > queue;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				if (board[i][j] == 'S')//source
				{
					dist[i][j] = 0;
					queue.push(std::make_pair(i, j));
					while (!queue.empty())
					{
						auto p = queue.front();
						queue.pop();

						if (p.first - 1 >= 0 && board[p.first - 1][p.second] == '.' && dist[p.first][p.second] + 1 < dist[p.first - 1][p.second])
						{
							queue.push(std::make_pair(p.first - 1, p.second));
							dist[p.first - 1][p.second] = dist[p.first][p.second] + 1;
						}
						if (p.first + 1 < N && board[p.first + 1][p.second] == '.' && dist[p.first][p.second] + 1 < dist[p.first + 1][p.second])
						{
							queue.push(std::make_pair(p.first + 1, p.second));
							dist[p.first + 1][p.second] = dist[p.first][p.second] + 1;
						}
						if (p.second - 1 >= 0 && board[p.first][p.second - 1] == '.' && dist[p.first][p.second] + 1 < dist[p.first][p.second - 1])
						{
							queue.push(std::make_pair(p.first, p.second - 1));
							dist[p.first][p.second - 1] = dist[p.first][p.second] + 1;
						}
						if (p.second + 1 < M && board[p.first][p.second + 1] == '.' && dist[p.first][p.second] + 1 < dist[p.first][p.second + 1])
						{
							queue.push(std::make_pair(p.first, p.second + 1));
							dist[p.first][p.second + 1] = dist[p.first][p.second] + 1;
						}
					}
				}
				else if (board[i][j] == '#')//obstacle
					dist[i][j] = -1;
			}
		}

		Debug::Print2D<char>()(board, false);
		std::cout << "AllShortestPathsInMatrix BFS for the above board:" << std::endl;
		Debug::Print2D<int>()(dist, false, true);
		return dist;
	}

	//Leetcode: walls(-1) and gates(0). empty(INT_MAX)
	void WallsAndGates_BFS(std::vector<std::vector<int>> & board)
	{
		int N = board.size();
		if (N == 0) return;
		int M = board[0].size();
		if (M == 0) return;

		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				if (board[i][j] == 0)
				{
					std::queue<int> que;
					que.push(i*M + j);
					while (!que.empty())
					{
						int ii = que.front() / M;
						int jj = que.front() % M;
						que.pop();
						static std::vector<std::vector<int>> dir({ { -1,0 },{ 1,0 },{ 0,1 },{ 0,-1 } });
						for (int k = 0; k < 4; ++k)
						{
							int x = ii + dir[k][0];
							int y = jj + dir[k][1];
							if (x >= 0 && x < N && y >= 0 && y < M && board[x][y] != -1 && board[ii][jj] + 1 < board[x][y])
							{
								board[x][y] = board[ii][jj] + 1;
								que.push(x*M + y);
							}
						}
					}
				}
			}
		}
	}
};
/*
[rY][cX]
Row#0	= ., ., ., ., ., ., .
Row#1	= ., ., ., ., ., S, .
Row#2	= ., ., ., ., ., ., .
Row#3	= ., ., S, ., ., ., .
Row#4	= ., ., ., ., ., ., .
Row#5	= ., ., ., ., ., ., .

AllShortestPathsInMatrix BFS for the above board:
[rY][cX]
Row#0	=	5,	4,	3,	3,	2,	1,	2
Row#1	=	4,	3,	2,	2,	1,	0,	1
Row#2	=	3,	2,	1,	2,	2,	1,	2
Row#3	=	2,	1,	0,	1,	2,	2,	3
Row#4	=	3,	2,	1,	2,	3,	3,	4
Row#5	=	4,	3,	2,	3,	4,	4,	5

[rY][cX]
Row#0	= #, S, #, #, #, #, #, #, ., #
Row#1	= ., ., ., ., ., ., #, ., ., #
Row#2	= ., #, ., #, #, ., #, #, ., #
Row#3	= ., #, ., ., ., ., ., ., ., .
Row#4	= #, #, ., #, #, ., #, #, #, #
Row#5	= ., ., ., ., #, ., ., ., ., #
Row#6	= ., #, #, #, #, #, #, #, ., #
Row#7	= ., ., ., ., #, ., ., ., ., .
Row#8	= ., #, #, #, #, ., #, #, #, .
Row#9	= ., ., ., ., #, ., ., ., ., #

AllShortestPathsInMatrix BFS for the above board:
[rY][cX]
Row#0	=	-1,	0,	-1,	-1,	-1,	-1,	-1,	-1,	13,	-1
Row#1	=	2,	1,	2,	3,	4,	5,	-1,	13,	12,	-1
Row#2	=	3,	-1,	3,	-1,	-1,	6,	-1,	-1,	11,	-1
Row#3	=	4,	-1,	4,	5,	6,	7,	8,	9,	10,	11
Row#4	=	-1,	-1,	5,	-1,	-1,	8,	-1,	-1,	-1,	-1
Row#5	=	8,	7,	6,	7,	-1,	9,	10,	11,	12,	-1
Row#6	=	9,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	13,	-1
Row#7	=	10,	11,	12,	13,	-1,	17,	16,	15,	14,	15
Row#8	=	11,	-1,	-1,	-1,	-1,	18,	-1,	-1,	-1,	16
Row#9	=	12,	13,	14,	15,	-1,	19,	20,	21,	22,	-1
*/
#endif