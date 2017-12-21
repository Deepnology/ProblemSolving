#ifndef PACIFIC_ATLANTIC_WATER_FLOW_H
#define PACIFIC_ATLANTIC_WATER_FLOW_H
#include "Debug.h"
/*
Leetcode: Pacific Atlantic Water Flow
Given an m x n matrix of non-negative integers representing the height of each unit cell in a continent, the "Pacific ocean" touches the left and top edges of the matrix and the "Atlantic ocean" touches the right and bottom edges.
Water can only flow in four directions (up, down, left, or right) from a cell to another one with height equal or lower.
Find the list of grid coordinates where water can flow to both the Pacific and Atlantic ocean.
Note:
The order of returned grid coordinates does not matter.
Both m and n are less than 150.
Example:
Given the following 5x5 matrix:

  Pacific ~   ~   ~   ~   ~ 
       ~  1   2   2   3  (5) *
       ~  3   2   3  (4) (4) *
       ~  2   4  (5)  3   1  *
       ~ (6) (7)  1   4   5  *
       ~ (5)  1   1   2   4  *
          *   *   *   *   * Atlantic

Return:
[[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]] (positions with parentheses in above matrix).
*/
class PacificAtlanticWaterFlow
{
public:
	PacificAtlanticWaterFlow() {}

	std::vector<std::pair<int, int>> Recur(std::vector<std::vector<int>> & matrix)
	{
		std::vector<std::pair<int, int>> res;
		int N = matrix.size();
		if (N == 0) return res;
		int M = matrix[0].size();
		if (M == 0) return res;
		std::vector<std::vector<int>> dp(N, std::vector<int>(M, 0));
		for (int i = 0; i < N; ++i)
		{
			recur(matrix, i, 0, dp, 1);//mark left pacific reachable cells w/ lowest 1 bit
			recur(matrix, i, M - 1, dp, 2);//mark right atlantic reachable cells w/ 2nd lowest 1 bit
		}
		for (int j = 0; j < M; ++j)
		{
			recur(matrix, 0, j, dp, 1);//mark upper pacific reachable cells w/ lowest 1 bit
			recur(matrix, N - 1, j, dp, 2);//mark lower atlantic reachable cells w/ 2nd lowest 1 bit
		}
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < M; ++j)
				if (dp[i][j] == 3)
					res.push_back({ i, j });
		Debug::Print2D<int>()(matrix, false);
		std::cout << "PacificAtlanticWaterFlow Recur for the above matrix: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void recur(std::vector<std::vector<int>> & matrix, int i, int j, std::vector<std::vector<int>> & dp, int mark)
	{
		dp[i][j] |= mark;
		int N = matrix.size();
		int M = matrix[0].size();
		std::vector<std::vector<int>> dir = { { -1,0 },{ 1,0 },{ 0,-1 },{ 0,1 } };
		for (int k = 0; k < 4; ++k)
		{
			int ii = i + dir[k][0];
			int jj = j + dir[k][1];
			if (ii >= 0 && ii < N && jj >= 0 && jj < M && matrix[ii][jj] >= matrix[i][j] && ((dp[ii][jj] >> (mark - 1)) & 1) == 0)
				recur(matrix, ii, jj, dp, mark);
		}
	}
};
/*
[rY][cX]
Row#0	= 1, 2, 2, 3, 5
Row#1	= 3, 2, 3, 4, 4
Row#2	= 2, 4, 5, 3, 1
Row#3	= 6, 7, 1, 4, 5
Row#4	= 5, 1, 1, 2, 4

PacificAtlanticWaterFlow Recur for the above matrix: [0,4], [1,3], [1,4], [2,2], [3,0], [3,1], [4,0]
*/
#endif
