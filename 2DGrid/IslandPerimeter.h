#ifndef ISLAND_PERIMETER_H
#define ISLAND_PERIMETER_H
#include "Debug.h"
/*
Leetcode: Island Perimeter
You are given a map in form of a two-dimensional integer grid where 1 represents land and 0 represents water.
Grid cells are connected horizontally/vertically (not diagonally).
The grid is completely surrounded by water, and there is exactly one island (i.e., one or more connected land cells).
The island doesn't have "lakes" (water inside that isn't connected to the water around the island).
One cell is a square with side length 1.
The grid is rectangular, width and height don't exceed 100. Determine the perimeter of the island.
Example:
[[0,1,0,0],
[1,1,1,0],
[0,1,0,0],
[1,1,0,0]]
Answer: 16
*/
class IslandPerimeter
{
public:
	IslandPerimeter() {}

	int Count(const std::vector<std::vector<int>> & grid)
	{
		int N = grid.size();
		if (N == 0) return 0;
		int M = grid[0].size();
		if (M == 0) return 0;
		int res = 0;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j< M; ++j)
			{
				if (grid[i][j] == 1)
				{
					res += 4;
					if (i - 1 >= 0 && grid[i - 1][j] == 1)
						res -= 1;
					if (i + 1 < N && grid[i + 1][j] == 1)
						res -= 1;
					if (j - 1 >= 0 && grid[i][j - 1] == 1)
						res -= 1;
					if (j + 1 < M && grid[i][j + 1] == 1)
						res -= 1;
				}
			}
		}
		Debug::Print2D<int>()(grid, false);
		std::cout << "IslandPerimeter Count for the above grid: " << res << std::endl;
		return res;
	}

	int CountWaterNeighbors(std::vector<std::vector<int>> && grid)
	{
		int N = grid.size();
		if (N == 0) return 0;
		int M = grid[0].size();
		if (M == 0) return 0;
		std::vector<std::vector<int>> dir({{-1,0},{1,0},{0,1},{0,-1}});
		int res = 0;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j< M; ++j)
			{
				if (grid[i][j] == 1)
				{
                    for (int d = 0; d < 4; ++d)
                    {
                        int ii = i + dir[d][0];
                        int jj = j + dir[d][1];
                        if (ii < 0 || ii == N || jj < 0 || jj == M || grid[ii][jj] == 0)
                            ++res;
                    }
				}
			}
		}
		return res;
	}

	//this works for finding an island w/ max perimeter in a multiple islands map
	int CountWaterNeighborsRecur(std::vector<std::vector<int>> && grid)
	{
		int N = grid.size();
		if (N == 0) return 0;
		int M = grid[0].size();
		if (M == 0) return 0;
		std::vector<std::vector<int>> dir({{-1,0},{1,0},{0,1},{0,-1}});
		int res = 0;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j< M; ++j)
			{
				if (grid[i][j] == 1)
				{
					res = recur(grid, i, j);
				}
			}
		}
		return res;
	}
	int recur(std::vector<std::vector<int>> & grid, int i, int j)
	{
		int N = grid.size(); int M = grid[0].size();
		grid[i][j] = -1;
		int count = 0;
		std::vector<std::vector<int>> dir({{-1,0},{1,0},{0,1},{0,-1}});
		for (int d = 0; d < 4; ++d)
		{
			int ii = i + dir[d][0];
			int jj = j + dir[d][1];
			if (ii < 0 || ii == N || jj < 0 || jj == M || grid[ii][jj] == 0)
				++count;
			else if (grid[ii][jj] == 1) //to skip grid[ii][jj]==-1
				count += recur(grid, ii, jj);
		}
		return count;
	}
};
/*
[rY][cX]
Row#0	= 0, 1, 0, 0
Row#1	= 1, 1, 1, 0
Row#2	= 0, 1, 0, 0
Row#3	= 1, 1, 0, 0

IslandPerimeter Count for the above grid: 16
*/
#endif
