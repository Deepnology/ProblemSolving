#ifndef NUMBER_OF_ISLANDS_IN_MATRIX_H
#define NUMBER_OF_ISLANDS_IN_MATRIX_H
#include <vector>
#include <queue>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Number of Islands
Given a 2d grid map of '1's (land) and '0's (water), count the number of islands.
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
You may assume all four edges of the grid are all surrounded by water.

Example 1:
11110
11010
11000
00000
Answer: 1

Example 2:
11000
11000
00100
00011
Answer: 3

See also AllDistinctSubAreasInMatrix.h

Leetcode: Number of Islands II
https://discuss.leetcode.com/topic/29613/easiest-java-solution-with-explanations/2
A 2d grid map of m rows and n columns is initially filled with water.
We may perform an addLand operation which turns the water at position (row, col) into a land.
Given a list of positions to operate, count the number of islands after each addLand operation.
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
You may assume all four edges of the grid are all surrounded by water.
Example:
Given m = 3, n = 3, positions = [[0,0], [0,1], [1,2], [2,1]].
Initially, the 2d grid grid is filled with water. (Assume 0 represents water and 1 represents land).
0 0 0
0 0 0
0 0 0
Operation #1: addLand(0, 0) turns the water at grid[0][0] into a land.
1 0 0
0 0 0   Number of islands = 1
0 0 0
Operation #2: addLand(0, 1) turns the water at grid[0][1] into a land.
1 1 0
0 0 0   Number of islands = 1
0 0 0
Operation #3: addLand(1, 2) turns the water at grid[1][2] into a land.
1 1 0
0 0 1   Number of islands = 2
0 0 0
Operation #4: addLand(2, 1) turns the water at grid[2][1] into a land.
1 1 0
0 0 1   Number of islands = 3
0 1 0
We return the result as an array: [1, 1, 2, 3]
Challenge:
Can you do it in time complexity O(k log mn), where k is the length of the positions?

See also UnionFindGraphComponent.h


Leetcode: Number of Distinct Islands
(number of islands with distinct shapes)
=> concatenate all cell idx(i*M+j) of an island into a string, ex: "0,1,8,9,10,16", and shift the front idx to 0.
   For another island "29,30,37,38,39,45", shift its front idx to 0 to get "0,1,8,9,10,16", which has same shape as above.
   Then insert these strings into a set.
   1 1 0 0 0 0 0
   0 1 1 1 0 0 0
   0 0 1 0 0 0 0
   0 0 0 0 0 0 0
   0 1 1 0 0 0 0
   0 0 1 1 1 0 0
   0 0 0 1 0 0 0

Leetcode: Number of Distinct Island II
(number of islands with distinct shapes after rotation with any degree)

Leetcode: Max Area of Island
Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.)
You may assume all four edges of the grid are surrounded by water.
Find the maximum area of an island in the given 2D array. (If there is no island, the maximum area is 0.)
*/
class NumberOfIslandsInMatrix
{
public:
	NumberOfIslandsInMatrix(){}
	~NumberOfIslandsInMatrix(){}
	void Count_DFS(std::vector<std::vector<char>> && board)
	{
		if (board.empty() || board[0].empty())
			return;
		Debug::Print2D<char>()(board, false);

		int N = board.size();
		int M = board[0].size();
		int count = 0;
		for (int i = 0; i < N; ++i)//from top to bottom
		{
			for (int j = 0; j < M; ++j)//from left to right
			{
				if (this->DFSRecur(board, i, j))
					++count;
			}
		}
		
		std::cout << "NumberOfIslandsInMatrix Count_DFS: " << count << std::endl;
	}
private:
	bool DFSRecur(std::vector<std::vector<char>> & board, int x, int y)
	{
		int N = board.size();//num of rows
		int M = board[0].size();//num of cols
		if (x < 0 || y < 0 || x > N - 1 || y > M - 1)
			return false;
		if (board[x][y] == '0')
			return false;

		board[x][y] = '0';//mark visited
		this->DFSRecur(board, x - 1, y);//up
		this->DFSRecur(board, x + 1, y);//down
		this->DFSRecur(board, x, y - 1);//left
		this->DFSRecur(board, x, y + 1);//right
		return true;
	}
};
class NumberOfIslandsInMatrixII
{
public:
	NumberOfIslandsInMatrixII() {}
	~NumberOfIslandsInMatrixII() {}

	std::vector<int> GetCount_ConvertTo1DUnionFind(int m, int n, const std::vector<std::pair<int, int>> & positions)
	{
		std::vector<int> res;
		if (m <= 0 || n <= 0)
			return res;

		std::vector<int> rootIndex(m * n, -1);//-1 means current position is non-island; otherwise, means current position is island whose value is root index
		int count = 0;
		for (const auto & p : positions)//O(k * m*n) time for linear findRoot, O(k * log(m*n)) time for path compression findRoot, where k is the size of positions
		{
			//1. add current position as a new island
			int idx = n * p.first + p.second;
			rootIndex[idx] = idx;//mark current position a new root of island
			++count;

			//2. union current position with upper, lower, left, right positions
			if (p.first - 1 >= 0 && rootIndex[n * (p.first - 1) + p.second] != -1)//upper is island
			{
				int rootOfUpper = this->findRootPathCompression(rootIndex, n * (p.first - 1) + p.second);
				if (rootOfUpper != idx)//upper is a different island
				{
					rootIndex[idx] = rootOfUpper;//union current position with upper
					idx = rootOfUpper;//current tree root = joined root
					--count;
				}
			}
			if (p.first + 1 < m && rootIndex[n * (p.first + 1) + p.second] != -1)//lower is island
			{
				int rootOfLower = this->findRootPathCompression(rootIndex, n * (p.first + 1) + p.second);
				if (rootOfLower != idx)//lower is a different island
				{
					rootIndex[idx] = rootOfLower;//union current position with lower
					idx = rootOfLower;//current tree root = joined root
					--count;
				}
			}
			if (p.second - 1 >= 0 && rootIndex[n * p.first + p.second - 1] != -1)//left is island
			{
				int rootOfLeft = this->findRootPathCompression(rootIndex, n * p.first + p.second - 1);
				if (rootOfLeft != idx)//left is a different island
				{
					rootIndex[idx] = rootOfLeft;//union current position with left
					idx = rootOfLeft;//current tree root = joined root
					--count;
				}
			}
			if (p.second + 1 < n && rootIndex[n * p.first + p.second + 1] != -1)//right is island
			{
				int rootOfRight = this->findRootPathCompression(rootIndex, n * p.first + p.second + 1);
				if (rootOfRight != idx)//right is a differernt island
				{
					rootIndex[idx] = rootOfRight;//union current position with right
					idx = rootOfRight;//current tree root = joined root
					--count;
				}
			}

			res.push_back(count);
		}

		std::cout << "NumberOfIslandsInMatrixII GetCount_ConvertTo1DUnionFind for matrix=\"" << m << "x" << n << "\", positions=\"" << Debug::ToStr1D<int>()(positions) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	//linear find root: O(m*n) time
	int findRoot(const std::vector<int> & rootIndex, int idx)//idx != -1 && rootIndex[idx] != -1
	{
		while (idx != rootIndex[idx])
			idx = rootIndex[idx];
		return idx;
	}
	int findRootRecur(const std::vector<int> & rootIndex, int idx)//idx != -1 && rootIndex[idx] != -1
	{
		if (rootIndex[idx] == idx)
			return idx;
		return this->findRootRecur(rootIndex, rootIndex[idx]);
	}

	//path compression find root: O(log(m*n)) time
	int findRootPathCompression(std::vector<int> & rootIndex, int idx)//idx != -1 && rootIndex[idx] != -1
	{
		while (idx != rootIndex[idx])
		{
			rootIndex[idx] = rootIndex[rootIndex[idx]];//only one line added
			idx = rootIndex[idx];
		}
		return idx;
	}
};
class NumberOfDistinctIslandsInMatrix
{
public:
	NumberOfDistinctIslandsInMatrix() {}

	int Count_DFSHashMap(const std::vector<std::vector<int>> & grid)
	{
		int N = grid.size();
		if (N == 0) return 0;
		int M = grid[0].size();
		if (M == 0) return 0;
		std::unordered_set<std::string> shapes;
		std::vector<std::vector<int>> visit(N, std::vector<int>(M, 0));
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < M; ++j)
			{
				if (grid[i][j] == 1 && !visit[i][j])
				{
					visit[i][j] = 1;
					std::string curShape;
					DFS(grid, i*M + j, i, j, visit, curShape);
					shapes.insert(curShape);
				}
			}


		Debug::Print2D<int>()(grid, false);
		for (auto & s : shapes)
			std::cout << s << std::endl;

		std::cout << "NumberOfDistinctIslandsInMatrix Count_DFSHashMap for the above grid: " << shapes.size() << std::endl;
		return shapes.size();
	}
private:
	void DFS(const std::vector<std::vector<int>> & grid, int initIdx, int i, int j, std::vector<std::vector<int>> & visit, std::string & shape)
	{
		int N = grid.size();
		int M = grid[0].size();
		int curIdx = i * M + j;
		if (curIdx != initIdx) shape += ",";
		shape += std::to_string(curIdx - initIdx);//transform to 1D idx, then shift to left w/ initIdx = 0
		static std::vector<std::vector<int>> dir({ { -1,0 },{ 0,-1 },{ 0,1 },{ 1,0 } });
		for (int d = 0; d < 4; ++d)
		{
			int ii = i + dir[d][0];
			int jj = j + dir[d][1];
			if (ii >= 0 && ii < N && jj >= 0 && jj < M && grid[ii][jj] == 1 && !visit[ii][jj])
			{
				visit[ii][jj] = 1;
				DFS(grid, initIdx, ii, jj, visit, shape);
			}
		}
	}
};
class NumberOfDistinctIslandsAfterRotationInMatrix
{
	struct Hash
	{
		size_t operator()(const std::vector<std::pair<int, int>> & a) const
		{
			size_t res = 0;
			for (auto & p : a)
				res ^= (p.first ^ p.second);
			return res;
		}
	};
public:
	NumberOfDistinctIslandsAfterRotationInMatrix() {}
	
	int Count_DFS_HashMap(const std::vector<std::vector<int>> & grid)
	{
		int N = grid.size();
		if (N == 0) return 0;
		int M = grid[0].size();
		if (M == 0) return 0;
		std::unordered_set<std::vector<std::pair<int, int>>, Hash> normShapes;
		std::vector<std::vector<int>> visit(N, std::vector<int>(M, 0));
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < M; ++j)
			{
				if (grid[i][j] == 1 && !visit[i][j])
				{
					visit[i][j] = 1;
					std::vector<std::pair<int, int>> curShape;
					DFS(grid, i, j, visit, curShape);
					normShapes.insert(Norm(curShape));
				}
			}
		return normShapes.size();
	}
private:
	void DFS(const std::vector<std::vector<int>> & grid, int i, int j, std::vector<std::vector<int>> & visit, std::vector<std::pair<int, int>> & shape)
	{
		int N = grid.size();
		int M = grid[0].size();
		shape.push_back({ i,j });
		static std::vector<std::vector<int>> dir({ { -1,0 },{ 0,-1 },{ 0,1 },{ 1,0 } });
		for (int d = 0; d < 4; ++d)
		{
			int ii = i + dir[d][0];
			int jj = j + dir[d][1];
			if (ii >= 0 && ii < N && jj >= 0 && jj < M && grid[ii][jj] == 1 && !visit[ii][jj])
			{
				visit[ii][jj] = 1;
				DFS(grid, ii, jj, visit, shape);
			}
		}
	}
	std::vector<std::pair<int, int>> Norm(const std::vector<std::pair<int, int>> & shape)
	{
		std::vector<std::vector<std::pair<int, int>>> res(8, std::vector<std::pair<int, int>>());
		//compute rotations/reflections
		for (const auto & p : shape)
		{
			int x = p.first;
			int y = p.second;
			res[0].push_back({ x,y });
			res[1].push_back({ -x,y });
			res[2].push_back({ x,-y });
			res[3].push_back({ -x,-y });
			res[4].push_back({ y,x });
			res[5].push_back({ -y,x });
			res[6].push_back({ y,-x });
			res[7].push_back({ -y,-x });
		}
		for (auto & v : res)
			std::sort(v.begin(), v.end());
		for (auto & v : res)
		{
			int N = v.size();
			for (int i = 1; i < N; ++i)
				v[i] = { v[i].first - v[0].first, v[i].second - v[0].second };
			v[0] = { 0,0 };
		}
		std::sort(res.begin(), res.end());
		return res[0];//only need to return the 1st vector
	}
};
class MaxAreaOfIslandsInMatrix
{
public:
	MaxAreaOfIslandsInMatrix() {}

	int DFS_FindMaxIsland(const std::vector<std::vector<int>> & grid)
	{
		int N = grid.size();
		if (N == 0) return 0;
		int M = grid[0].size();
		if (M == 0) return 0;
		int res = 0;
		std::vector<std::vector<int>> visit(N, std::vector<int>(M, 0));
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < M; ++j)
			{
				if (grid[i][j] == 1 && !visit[i][j])
				{
					visit[i][j] = 1;
					int area = 0;
					DFS(grid, i, j, area, visit);
					res = std::max(res, area);
				}
			}
		return res;
	}
private:
	void DFS(const std::vector<std::vector<int>> & grid, int i, int j, int & area, std::vector<std::vector<int>> & visit)
	{
		int N = grid.size();
		int M = grid[0].size();
		++area;
		static std::vector<std::vector<int>> dir({ { -1,0 },{ 0,-1 },{ 1,0 },{ 0,1 } });
		for (int d = 0; d < 4; ++d)
		{
			int ii = i + dir[d][0];
			int jj = j + dir[d][1];
			if (ii >= 0 && ii < N && jj >= 0 && jj < M && grid[ii][jj] == 1 && !visit[ii][jj])
			{
				visit[ii][jj] = 1;
				DFS(grid, ii, jj, area, visit);
			}
		}
	}
};
/*
[rY][cX]
Row#0	= 1, 1, 1, 1, 0
Row#1	= 1, 1, 0, 1, 0
Row#2	= 1, 1, 0, 0, 0
Row#3	= 0, 0, 0, 0, 0

NumberOfIslandsInMatrix Count_DFS: 1
[rY][cX]
Row#0	= 1, 1, 0, 0, 0
Row#1	= 1, 1, 0, 0, 0
Row#2	= 0, 0, 1, 0, 0
Row#3	= 0, 0, 0, 1, 1

NumberOfIslandsInMatrix Count_DFS: 3
NumberOfIslandsInMatrixII GetCount_ConvertTo1DUnionFind for matrix="3x3", positions="[0,0], [0,1], [1,2], [2,1]": 1, 1, 2, 3

[rY][cX]
Row#0	= 1, 1, 0, 1, 1
Row#1	= 1, 0, 0, 0, 0
Row#2	= 0, 0, 0, 0, 1
Row#3	= 1, 1, 0, 1, 1

0,1,5
0,1
0,5,4
NumberOfDistinctIslandsInMatrix Count_DFSHashMap for the above grid: 3
[rY][cX]
Row#0	= 1, 1, 0, 0, 0, 0, 0
Row#1	= 0, 1, 1, 1, 0, 0, 0
Row#2	= 0, 0, 1, 0, 0, 0, 0
Row#3	= 0, 0, 0, 0, 0, 0, 0
Row#4	= 0, 1, 1, 0, 0, 0, 0
Row#5	= 0, 0, 1, 1, 1, 0, 0
Row#6	= 0, 0, 0, 1, 0, 0, 0

0,1,8,9,10,16
NumberOfDistinctIslandsInMatrix Count_DFSHashMap for the above grid: 1
*/
#endif