#ifndef SHORTEST_DIST_FROM_ALL_BUILDINGS_H
#define SHORTEST_DIST_FROM_ALL_BUILDINGS_H
#include "Debug.h"
/*
Leetcode: Shortest Distance from All Buildings
You want to build a house on an empty land which reaches all buildings in the shortest amount of distance.
You can only move up, down, left and right.
You are given a 2D grid of values 0, 1 or 2, where:
Each 0 marks an empty land which you can pass by freely.
Each 1 marks a building which you cannot pass through.
Each 2 marks an obstacle which you cannot pass through.
For example, given three buildings at (0,0), (0,4), (2,2), and an obstacle at (0,2):
1 - 0 - 2 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0
The point (1,2) is an ideal empty land to build a house, as the total travel distance of 3+3+1=7 is minimal. So return 7.
Note:
There will be at least one building. If it is not possible to build such house according to the above rules, return -1.
*/
class ShortestDistFromAllBuildings
{
public:
	ShortestDistFromAllBuildings() {}
	~ShortestDistFromAllBuildings() {}

	int BFS(const std::vector<std::vector<int>> & board)
	{
		int N = board.size();
		int M = board[0].size();

		std::vector<std::vector<int>> dist(N, std::vector<int>(M, 0));//the sum of distance to each building from each empty land
		std::vector<std::vector<int>> reachable(N, std::vector<int>(M, 0));//the reachable building count of each empty land
		int buildingCount = 0;

		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				if (board[i][j] == 1)
				{
					++buildingCount;

					//BFS from (i,j)
					std::vector<std::vector<int>> visit(N, std::vector<int>(M, 0));//without keep track of visit: time limit exceeded!
					std::queue<std::pair<int, int>> que;
					que.push({ i, j });
					int distBFS = -1;//-1 is to cancel the increment for the first element in queue which is a building
					while (!que.empty())
					{
						++distBFS;//increment distance for each level
						int curLevelCount = que.size();
						for (int k = 0; k < curLevelCount; ++k)//just pop out curLevelCount elements from queue (keep nextLevel elements in queue for next incremented distBFS)
						{
							//now visit the node
							int ii = que.front().first;
							int jj = que.front().second;
							que.pop();
							if (board[ii][jj] == 0)//condition just to skip the first element in queue which is a building
							{
								++reachable[ii][jj];
								dist[ii][jj] += distBFS;
							}

							//check for node's neighbors
							if (ii - 1 >= 0 && visit[ii - 1][jj] == 0 && board[ii - 1][jj] == 0)
							{
								visit[ii - 1][jj] = 1;
								que.push({ ii - 1, jj });
							}
							if (ii + 1 < N && visit[ii + 1][jj] == 0 && board[ii + 1][jj] == 0)
							{
								visit[ii + 1][jj] = 1;
								que.push({ ii + 1, jj });
							}
							if (jj - 1 >= 0 && visit[ii][jj - 1] == 0 && board[ii][jj - 1] == 0)
							{
								visit[ii][jj - 1] = 1;
								que.push({ ii, jj - 1 });
							}
							if (jj + 1 < M && visit[ii][jj + 1] == 0 && board[ii][jj + 1] == 0)
							{
								visit[ii][jj + 1] = 1;
								que.push({ ii, jj + 1 });
							}
						}
					}
				}
			}
		}

		int x = 0;
		int y = 0;
		int sumDist = INT_MAX;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				//record the empty land that is able to reach all buildings and has min sum of distances to all buildings
				if (reachable[i][j] == buildingCount && dist[i][j] < sumDist)
				{
					x = i;
					y = j;
					sumDist = dist[i][j];
				}
			}
		}

		Debug::Print2D<int>()(board, false);
		Debug::Print2D<int>()(reachable, false);
		Debug::Print2D<int>()(dist, false);
		std::cout << "ShortestDistFromAllBuildings BFS: " << sumDist << ", at (" << x << ", " << y << ")" << std::endl;
		return sumDist;
	}
};
/*
[rY][cX]
Row#0	= 1, 0, 2, 0, 1
Row#1	= 0, 0, 0, 0, 0
Row#2	= 0, 0, 1, 0, 0

[rY][cX]
Row#0	= 0, 3, 0, 3, 0
Row#1	= 3, 3, 3, 3, 3
Row#2	= 3, 3, 0, 3, 3

[rY][cX]
Row#0	= 0, 9, 0, 9, 0
Row#1	= 9, 8, 7, 8, 9
Row#2	= 10, 9, 0, 9, 10

ShortestDistFromAllBuildings BFS: 7, at (1, 2)
[rY][cX]
Row#0	= 2, 1, 2, 2, 1, 0, 1
Row#1	= 1, 0, 2, 0, 0, 0, 1
Row#2	= 1, 0, 2, 0, 2, 0, 1
Row#3	= 2, 0, 1, 0, 2, 1, 2
Row#4	= 2, 0, 0, 0, 2, 2, 0
Row#5	= 2, 2, 1, 0, 0, 0, 1

[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 11, 0
Row#1	= 0, 11, 0, 11, 11, 11, 0
Row#2	= 0, 11, 0, 11, 0, 11, 0
Row#3	= 0, 11, 0, 11, 0, 0, 0
Row#4	= 0, 11, 11, 11, 0, 0, 1
Row#5	= 0, 0, 0, 11, 11, 11, 0

[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 69, 0
Row#1	= 0, 78, 0, 58, 59, 62, 0
Row#2	= 0, 71, 0, 57, 0, 69, 0
Row#3	= 0, 66, 0, 56, 0, 0, 0
Row#4	= 0, 63, 58, 57, 0, 0, 1
Row#5	= 0, 0, 0, 64, 73, 82, 0

ShortestDistFromAllBuildings BFS: 56, at (3, 3)
*/
#endif
