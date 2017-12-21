#ifndef MIN_DIST_TO_0_IN_01_MATRIX_H
#define MIN_DIST_TO_0_IN_01_MATRIX_H
#include "Debug.h"
/*
Leetcode: 01 Matrix
Given a matrix consists of 0 and 1, find the distance of the nearest 0 for each cell.
The distance between two adjacent cells is 1.
Example 1:
Input:
0 0 0
0 1 0
0 0 0
Output:
0 0 0
0 1 0
0 0 0
Example 2:
Input:
0 0 0
0 1 0
1 1 1
Output:
0 0 0
0 1 0
1 2 1
Note:
The number of elements of the given matrix will not exceed 10,000.
There are at least one 0 in the given matrix.
The cells are adjacent in only four directions: up, down, left and right.
*/
class MinDistTo0In01Matrix
{
public:
	MinDistTo0In01Matrix() {}

	std::vector<std::vector<int>> BFS(std::vector<std::vector<int>> & matrix)//Time Limit Exceeded
	{
		Debug::Print2D<int>()(matrix, false);
		int N = matrix.size();
		int M = matrix[0].size();
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				if (matrix[i][j] != 0)
					matrix[i][j] = INT_MAX;
			}
		}
		std::vector<std::vector<int>> dir = { { -1,0 },{ 1,0 },{ 0,1 },{ 0,-1 } };
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				if (matrix[i][j] == 0)
				{
					std::queue<int> que;
					que.push(i*M + j);
					int dist = 1;
					while (!que.empty())
					{
						int count = que.size();
						while (count-->0)
						{
							int ii = que.front() / M;
							int jj = que.front() % M;
							que.pop();
							for (int k = 0; k < 4; ++k)
							{
								int x = ii + dir[k][0];
								int y = jj + dir[k][1];
								if (x >= 0 && x < N && y >= 0 && y < M && dist < matrix[x][y])
								{
									matrix[x][y] = dist;
									que.push(x*M + y);
								}
							}
						}
						++dist;
					}
				}
			}
		}

		std::cout << "MinDistTo0In01Matrix BFS for the above matrix: " << std::endl;
		Debug::Print2D<int>()(matrix, false);
		return matrix;
	}

	std::vector<std::vector<int>> DP(std::vector<std::vector<int>> & matrix)
	{
		int N = matrix.size();
		int M = matrix[0].size();
		std::vector<std::vector<int>> dist(N, std::vector<int>(M, INT_MAX));
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				if (matrix[i][j] == 0)
					dist[i][j] = 0;
				else
				{
					if (i - 1 >= 0 && dist[i - 1][j] != INT_MAX) dist[i][j] = std::min(dist[i][j], dist[i - 1][j] + 1);
					if (j - 1 >= 0 && dist[i][j - 1] != INT_MAX) dist[i][j] = std::min(dist[i][j], dist[i][j - 1] + 1);
				}
			}
		}
		for (int i = N - 1; i >= 0; --i)
		{
			for (int j = M - 1; j >= 0; --j)
			{
				if (matrix[i][j] == 0)
					dist[i][j] = 0;
				else
				{
					if (i + 1 < N && dist[i + 1][j] != INT_MAX) dist[i][j] = std::min(dist[i][j], dist[i + 1][j] + 1);
					if (j + 1 < M && dist[i][j + 1] != INT_MAX) dist[i][j] = std::min(dist[i][j], dist[i][j + 1] + 1);
				}
			}
		}

		Debug::Print2D<int>()(matrix, false);
		std::cout << "MinDistTo0In01Matrix DP for the above matrix: " << std::endl;
		Debug::Print2D<int>()(dist, false);
		return dist;
	}
};
/*

[rY][cX]
Row#0	= 0, 0, 0
Row#1	= 0, 1, 0
Row#2	= 1, 1, 1

MinDistTo0In01Matrix BFS for the above matrix:
[rY][cX]
Row#0	= 0, 0, 0
Row#1	= 0, 1, 0
Row#2	= 1, 2, 1

[rY][cX]
Row#0	= 0, 0, 0
Row#1	= 0, 1, 0
Row#2	= 1, 1, 1

MinDistTo0In01Matrix DP for the above matrix:
[rY][cX]
Row#0	= 0, 0, 0
Row#1	= 0, 1, 0
Row#2	= 1, 2, 1
*/
#endif
