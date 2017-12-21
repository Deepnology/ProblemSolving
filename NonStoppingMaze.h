#ifndef NON_STOPPING_MAZE_H
#define NON_STOPPING_MAZE_H
#include "Debug.h"
/*
Leetcode: The Maze I
There is a ball in a maze with empty spaces and walls.
The ball can go through empty spaces by rolling up, down, left or right, but it won't stop rolling until hitting a wall.
When the ball stops, it could choose the next direction.
Given the ball's start position, the destination and the maze, determine whether the ball could stop at the destination.
The maze is represented by a binary 2D array.
1 means the wall and 0 means the empty space.
You may assume that the borders of the maze are all walls.
The start and destination coordinates are represented by row and column indexes.

Leetcode: The Maze II
There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by rolling up, down, left or right, but it won't stop rolling until hitting a wall.
When the ball stops, it could choose the next direction.
Given the ball's start position, the destination and the maze, find the shortest distance for the ball to stop at the destination.
The distance is defined by the number of empty spaces traveled by the ball from the start position (excluded) to the destination (included).
If the ball cannot stop at the destination, return -1.
The maze is represented by a binary 2D array.
1 means the wall and 0 means the empty space. You may assume that the borders of the maze are all walls.
The start and destination coordinates are represented by row and column indexes.

Leetcode: The Maze III
There is a ball in a maze with empty spaces and walls.
The ball can go through empty spaces by rolling up (u), down (d), left (l) or right (r), but it won't stop rolling until hitting a wall.
When the ball stops, it could choose the next direction.
There is also a hole in this maze.
The ball will drop into the hole if it rolls on to the hole.
Given the ball position, the hole position and the maze, find out how the ball could drop into the hole by moving the shortest distance.
The distance is defined by the number of empty spaces traveled by the ball from the start position (excluded) to the hole (included).
Output the moving directions by using 'u', 'd', 'l' and 'r'.
Since there could be several different shortest ways, you should output the lexicographically smallest way.
If the ball cannot reach the hole, output "impossible".
The maze is represented by a binary 2D array.
1 means the wall and 0 means the empty space.
You may assume that the borders of the maze are all walls.
The ball and the hole coordinates are represented by row and column indexes.
*/
class NonStoppingMaze
{
public:
	NonStoppingMaze() {}

	bool HasPath_BFS(std::vector<std::vector<int>> & maze, std::vector<int> & start, std::vector<int> & destination)
	{
		int N = maze.size();
		if (N == 0) return 0;
		int M = maze[0].size();
		if (M == 0) return 0;
		std::vector<std::vector<int>> visit(N, std::vector<int>(M, 0));
		std::vector<std::vector<int>> dir = { { -1,0 },{ 1,0 },{ 0,-1 },{ 0,1 } };
		std::queue<int> que;//i*N+j
		que.push(start[0] * M + start[1]);
		while (!que.empty())
		{
			auto p = que.front();
			que.pop();
			int i = p/M;
			int j = p%M;
			visit[i][j] = 1;
			for (int k = 0; k < 4; ++k)
			{
				int ii = i;
				int jj = j;
				while (ii + dir[k][0] >= 0 && ii + dir[k][0] < N &&jj + dir[k][1] >= 0 && jj + dir[k][1] < M && maze[ii + dir[k][0]][jj + dir[k][1]] == 0)
				{
					ii += dir[k][0];
					jj += dir[k][1];
				}
				if (ii == destination[0] && jj == destination[1])
				{
					Debug::Print2D<int>()(maze, false);
					std::cout << "NonStoppingMaze HasPath_BFS for the above maze from \"" << Debug::ToStr1D<int>()(start) << "\", to \"" << Debug::ToStr1D<int>()(destination) << "\": " << 1 << std::endl;
					return true;
				}
				if (!visit[ii][jj])
					que.push(ii*M + jj);
			}
		}

		Debug::Print2D<int>()(maze, false);
		std::cout << "NonStoppingMaze HasPath_BFS for the above maze from \"" << Debug::ToStr1D<int>()(start) << "\", to \"" << Debug::ToStr1D<int>()(destination) << "\": " << 0 << std::endl;
		return 0;
	}

	struct Greater
	{
		bool operator()(const std::pair<int, int> & a, const std::pair<int, int> & b) const
		{
			return a.first > b.first;
		}
	};
public:
	int ShortestDist_BFS(std::vector<std::vector<int>> & maze, std::vector<int>& start, std::vector<int>& destination)
	{
		int N = maze.size();
		if (N == 0) return 0;
		int M = maze[0].size();
		if (M == 0) return 0;
		std::vector<std::vector<int>> dist(N, std::vector<int>(M, INT_MAX));//dist from start to (i,j)
		std::vector<std::vector<int>> dir = { { -1,0 },{ 1,0 },{ 0,-1 },{ 0,1 } };
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, Greater> minHeap;//<dist from start, i*M+j>
		minHeap.push({ 0, start[0] * M + start[1] });
		while (!minHeap.empty())//Dijkstra shortest path
		{
			auto p = minHeap.top();
			minHeap.pop();
			int d = p.first;
			int i = p.second / M;
			int j = p.second % M;
			if (dist[i][j] < d) continue;
			dist[i][j] = d;
			for (int k = 0; k < 4; ++k)
			{
				int ii = i;
				int jj = j;
				int dd = d;
				while (ii + dir[k][0] >= 0 && ii + dir[k][0] < N && jj + dir[k][1] >= 0 && jj + dir[k][1] < M && maze[ii + dir[k][0]][jj + dir[k][1]] == 0)
				{
					ii += dir[k][0];
					jj += dir[k][1];
					++dd;
				}
				if (dist[ii][jj] > dd)
					minHeap.push({ dd,ii*M + jj });
			}
		}
		int res = dist[destination[0]][destination[1]] == INT_MAX ? -1 : dist[destination[0]][destination[1]];

		Debug::Print2D<int>()(maze, false);
		std::cout << "NonStoppingMaze ShortestDist_BFS for the above maze from \"" << Debug::ToStr1D<int>()(start) << "\", to \"" << Debug::ToStr1D<int>()(destination) << "\": " << res << std::endl;
		return res;
	}

	struct Greater2
	{
		bool operator()(const std::tuple<int, int, std::string> & a, const std::tuple<int, int, std::string> & b) const
		{
			return std::get<0>(a) > std::get<0>(b);
		}
	};
public:
	std::string ShortestWayToHole_BFS(std::vector<std::vector<int>> & maze, std::vector<int>& start, std::vector<int>& hole)
	{
		int N = maze.size();
		if (N == 0) return "impossible";
		int M = maze[0].size();
		if (M == 0) return "impossible";
		int holeDist = INT_MAX;
		std::string holeStrs;
		std::vector<std::vector<int>> dist(N, std::vector<int>(M, INT_MAX));//dist from start to (i,j)
		std::vector<std::vector<std::string>> strs(N, std::vector<std::string>(M, ""));//dir list from start to (i,j)
		std::vector<std::vector<int>> dir = { { -1,0 },{ 1,0 },{ 0,-1 },{ 0,1 } };
		std::vector<std::string> dir2 = { "u","d","l","r" };
		std::priority_queue<std::tuple<int, int, std::string>, std::vector<std::tuple<int, int, std::string>>, Greater2> minHeap;//<dist from start, i*M+j, dirStr>
		minHeap.push({ 0, start[0] * M + start[1], "" });
		while (!minHeap.empty())//Dijkstra shortest path
		{
			auto p = minHeap.top();
			minHeap.pop();
			int d = std::get<0>(p);
			int i = std::get<1>(p)/M;
			int j = std::get<1>(p)%M;
			std::string dirStr = std::get<2>(p);
			if (dist[i][j] < d) continue;
			dist[i][j] = d;
			strs[i][j] = strs[i][j].empty() ? dirStr : std::min(strs[i][j], dirStr);
			for (int k = 0; k < 4; ++k)
			{
				int ii = i;
				int jj = j;
				int dd = d;
				std::string dirStr2 = strs[i][j] + dir2[k];
				while (ii + dir[k][0] >= 0 && ii + dir[k][0]<N && jj + dir[k][1] >= 0 && jj + dir[k][1] < M && maze[ii + dir[k][0]][jj + dir[k][1]] == 0)
				{
					ii += dir[k][0];
					jj += dir[k][1];
					++dd;
					if (ii == hole[0] && jj == hole[1] && dd <= holeDist)
					{
						holeDist = dd;
						holeStrs = holeStrs.empty() ? dirStr2 : std::min(holeStrs, dirStr2);
					}
				}
				if (!(ii == hole[0] && jj == hole[1]) && dist[ii][jj] > dd)
					minHeap.push({ dd,ii*M + jj,dirStr2 });
			}
		}
		std::string res = holeStrs == "" ? "impossible" : holeStrs;

		Debug::Print2D<int>()(maze, false);
		std::cout << "NonStoppingMaze ShortestWayToHole_BFS for the above maze from \"" << Debug::ToStr1D<int>()(start) << "\", to \"" << Debug::ToStr1D<int>()(hole) << "\": " << res << std::endl;
		return res;
	}
};
/*
[rY][cX]
Row#0	= 0, 0, 1, 0, 0
Row#1	= 0, 0, 0, 0, 0
Row#2	= 0, 0, 0, 1, 0
Row#3	= 1, 1, 0, 1, 1
Row#4	= 0, 0, 0, 0, 0

NonStoppingMaze HasPath_BFS for the above maze from "0, 4", to "4, 4": 1
[rY][cX]
Row#0	= 0, 0, 1, 0, 0
Row#1	= 0, 0, 0, 0, 0
Row#2	= 0, 0, 0, 1, 0
Row#3	= 1, 1, 0, 1, 1
Row#4	= 0, 0, 0, 0, 0

NonStoppingMaze ShortestDist_BFS for the above maze from "0, 4", to "4, 4": 12
[rY][cX]
Row#0	= 0, 0, 0, 0, 0
Row#1	= 1, 1, 0, 0, 1
Row#2	= 0, 0, 0, 0, 0
Row#3	= 0, 1, 0, 0, 1
Row#4	= 0, 1, 0, 0, 0

NonStoppingMaze ShortestWayToHole_BFS for the above maze from "4, 3", to "0, 1": lul
*/
#endif
