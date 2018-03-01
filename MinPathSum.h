/*AmazonOA*/
#ifndef MIN_PATH_SUM_H
#define MIN_PATH_SUM_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, DynamicProgramming: Plan a fishing trip
http://www.geeksforgeeks.org/dynamic-programming-set-6-min-cost-path/
Leetcode: Minimum Path Sum
// Given a m x n grid filled with non-negative numbers, find a path from "top
// left" to "bottom right" which minimizes the sum of all numbers along its path.
//
// Note: You can only move either "down" or "right" at any point in time.
//
// Complexity:
// DP, O(m*n) time, O(m*n) space
// DP, O(m*n) time, O(n) space
*/
class MinPathSum
{
public:
	MinPathSum(){}
	~MinPathSum(){}

	int DP_2D(const std::vector<std::vector<int> > & grid)//[rowY][columnX]
	{
		if (grid.empty() || grid[0].empty())
			return 0;
		Debug::Print2D<int>()(grid, false);
		int M = grid.size();
		int N = grid[0].size();
		std::vector<std::vector<int> > dp(M, std::vector<int>(N, 0));
		for (int rowY = 0; rowY < M; ++rowY)
		{
			for (int colX = 0; colX < N; ++colX)
			{
				if (rowY == 0 && colX == 0)//the top left corner element
					dp[rowY][colX] = grid[rowY][colX];
					/*current = current in grid*/
				else if (rowY == 0)//top row
					dp[rowY][colX] = dp[rowY][colX - 1] + grid[rowY][colX];
					/*current = left in dp + current in grid*/
				else if (colX == 0)//first element of each row
					dp[rowY][colX] = dp[rowY - 1][colX] + grid[rowY][colX];
					/*current = up in dp + current in grid*/
				else
					dp[rowY][colX] = 
					std::min(dp[rowY - 1][colX], dp[rowY][colX - 1]) + grid[rowY][colX];
					/*current = min of (up, left) in dp + current in grid*/
			}
			
		}
		Debug::Print2D<int>()(dp, false);
		std::cout << "MinPathSum DP_2D: " << dp[M - 1][N - 1] << std::endl;
		return dp[M - 1][N - 1];
	}

	int DP_1D(const std::vector<std::vector<int> > & grid)//[rowY][columnX]
	{
		if (grid.empty() || grid[0].empty())
			return 0;
		Debug::Print2D<int>()(grid, false);
		int M = grid.size();
		int N = grid[0].size();
		std::vector<int> dp(N, 0);
		for (int rowY = 0; rowY < M; ++rowY)//for each row (top down)
		{
			for (int colX = 0; colX < N; ++colX)//for each col (left to right)
			{
				if (colX == 0)//first element of each row
					dp[colX] += grid[rowY][colX];
					/*current = current in dp + current in grid*/
				else if (rowY == 0)//top row
					dp[colX] = dp[colX - 1] + grid[rowY][colX];
					/*current = left in dp + current in grid*/
				else
					dp[colX] = 
					std::min(dp[colX], dp[colX - 1]) + grid[rowY][colX];
					/*current = min of (current, left) in dp + current in grid*/
			}
			std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		}
		std::cout << "MinPathSum DP_1D: " << dp[N - 1] << std::endl;
		return dp[N - 1];
	}


	struct Greater
	{
		bool operator()(const std::pair<int,int> & a, const std::pair<int,int> & b) const
		{
			return a.first > b.first;
		}
	};
	//Goldman Sachs onsite
    int BFS_GeneralCase_WNegativeNums(const std::vector<std::vector<int>> & maze, const std::vector<int> & start, const std::vector<int> & dest)
    {
        int N = maze.size();
        if (N == 0) return 0;
        int M = maze[0].size();
        std::vector<std::vector<int>> dist(N, std::vector<int>(M, INT_MAX));
        std::vector<std::vector<int>> dir({{-1,0},{1,0},{0,1},{0,-1}});
        std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, Greater> minHeap;
        //<dist from start, i*M+j> where dist is min on top

        minHeap.push({maze[start[0]][start[1]], start[0]*M+start[1]});
        while (!minHeap.empty())
        {
            auto p = minHeap.top();
            minHeap.pop();
            int d = p.first;
            int i = p.second / M;
            int j = p.second % M;
            if (dist[i][j] < d)//2nd check
			{
				std::cout << "skip 2nd visit [" << i << "," << j << "]=" << dist[i][j] << ": " << d << std::endl;
				continue;
			}
            dist[i][j] = d;
            for (int k = 0; k < 4; ++k)
            {
                int ii = i + dir[k][0];
                int jj = j + dir[k][1];
                if (ii >= 0 && ii < N && jj >= 0 && jj < M
                    && dist[ii][jj] == INT_MAX)//1st check (ensure visit once only. this also works for negative numbers.)
                    minHeap.push({d + maze[ii][jj], ii*M+jj});
            }
        }

        Debug::Print2D<int>()(dist, false);
        Debug::Print2D<int>()(maze, false);
        int res = dist[dest[0]][dest[1]] == INT_MAX ? -1 : dist[dest[0]][dest[1]];
        std::cout << "MinPathSum BFS_GeneralCase_WNegativeNums for above maze from [" << Debug::ToStr1D<int>()(start) << "] to [" << Debug::ToStr1D<int>()(dest) << "]: " << res << std::endl;
        return res;
    }
};
/*
[rY][cX]
Row#0	= 1, 7, 3, 7
Row#1	= 9, 6, 1, 2
Row#2	= 3, 8, 4, 5

[rY][cX]
Row#0	= 1, 8, 11, 18
Row#1	= 10, 14, 12, 14
Row#2	= 13, 21, 16, 19

MinPathSum DP_2D: 19
[rY][cX]
Row#0	= 1, 7, 3, 7
Row#1	= 9, 6, 1, 2
Row#2	= 3, 8, 4, 5

1, 8, 11, 18
10, 14, 12, 14
13, 21, 16, 19
MinPathSum DP_1D: 19


skip 2nd visit [1,1]=14: 16
skip 2nd visit [1,1]=14: 18
skip 2nd visit [2,3]=19: 21
skip 2nd visit [0,3]=18: 21
skip 2nd visit [2,1]=21: 22
skip 2nd visit [2,1]=21: 24
[rY][cX]
Row#0	= 1, 8, 11, 18
Row#1	= 10, 14, 12, 14
Row#2	= 13, 21, 16, 19

[rY][cX]
Row#0	= 1, 7, 3, 7
Row#1	= 9, 6, 1, 2
Row#2	= 3, 8, 4, 5

MinPathSum BFS_GeneralCase_WNegativeNums for above maze from [0, 0] to [2, 3]: 19
skip 2nd visit [1,3]=40: 43
skip 2nd visit [0,3]=41: 47
skip 2nd visit [3,0]=80: 83
skip 2nd visit [3,4]=85: 88
skip 2nd visit [3,2]=82: 89
skip 2nd visit [3,0]=80: 90
skip 2nd visit [3,4]=85: 91
skip 2nd visit [3,2]=82: 99
skip 2nd visit [2,2]=82: 105
skip 2nd visit [1,1]=92: 139
skip 2nd visit [1,2]=139: 144
skip 2nd visit [1,0]=102: 152
skip 2nd visit [3,2]=82: 158
skip 2nd visit [1,2]=139: 181
skip 2nd visit [1,2]=139: 191
skip 2nd visit [1,0]=102: 191
[rY][cX]
Row#0	= 53, 52, 45, 41, 34
Row#1	= 102, 92, 139, 40, 31
Row#2	= 3, 5, 82, 28, 29
Row#3	= 80, 6, 82, 23, 85
Row#4	= 13, 10, 13, 18, 26

[rY][cX]
Row#0	= 1, 7, 4, 7, 3
Row#1	= 99, 87, 99, 12, 2
Row#2	= 3, 2, 77, 5, 1
Row#3	= 77, 1, 76, 5, 62
Row#4	= 3, 4, 3, 5, 8

MinPathSum BFS_GeneralCase_WNegativeNums for above maze from [2, 0] to [0, 0]: 53
skip 2nd visit [1,0]=100: 102
skip 2nd visit [1,0]=100: 104
skip 2nd visit [1,2]=102: 104
skip 2nd visit [3,1]=103: 105
skip 2nd visit [3,1]=103: 107
skip 2nd visit [4,2]=107: 109
skip 2nd visit [4,2]=107: 109
skip 2nd visit [4,2]=107: 111
skip 2nd visit [4,2]=107: 111
skip 2nd visit [2,3]=104: 112
skip 2nd visit [3,2]=104: 112
skip 2nd visit [2,3]=104: 112
skip 2nd visit [3,2]=104: 112
skip 2nd visit [4,4]=111: 113
skip 2nd visit [4,4]=111: 113
skip 2nd visit [2,3]=104: 114
skip 2nd visit [2,3]=104: 114
skip 2nd visit [4,4]=111: 115
skip 2nd visit [4,4]=111: 115
skip 2nd visit [5,4]=110: 116
skip 2nd visit [1,4]=114: 116
skip 2nd visit [1,4]=114: 116
skip 2nd visit [5,4]=110: 116
skip 2nd visit [1,4]=114: 116
skip 2nd visit [1,4]=114: 116
skip 2nd visit [1,4]=114: 118
skip 2nd visit [1,4]=114: 118
skip 2nd visit [1,4]=114: 118
skip 2nd visit [1,4]=114: 118
skip 2nd visit [0,2]=101: 119
skip 2nd visit [0,2]=101: 119
skip 2nd visit [0,2]=101: 119
skip 2nd visit [0,2]=101: 119
skip 2nd visit [1,2]=102: 120
skip 2nd visit [1,2]=102: 120
skip 2nd visit [2,3]=104: 120
skip 2nd visit [1,2]=102: 120
skip 2nd visit [1,4]=114: 120
skip 2nd visit [2,3]=104: 120
skip 2nd visit [1,4]=114: 120
skip 2nd visit [1,4]=114: 120
skip 2nd visit [2,3]=104: 120
skip 2nd visit [1,2]=102: 120
skip 2nd visit [1,4]=114: 120
skip 2nd visit [2,3]=104: 120
skip 2nd visit [1,2]=102: 200
skip 2nd visit [3,2]=104: 202
skip 2nd visit [4,2]=107: 203
skip 2nd visit [4,4]=111: 209
skip 2nd visit [4,4]=111: 209
[rY][cX]
Row#0	= 1, 2, 101, 20, 19, 18
Row#1	= 100, 3, 102, 21, 114, 17
Row#2	= 5, 4, 5, 104, 15, 16
Row#3	= 6, 103, 104, 13, 14, 15
Row#4	= 7, 8, 107, 12, 111, 16
Row#5	= 8, 9, 10, 11, 110, 17

[rY][cX]
Row#0	= 1, 1, 99, 1, 1, 1
Row#1	= 99, 1, 99, 1, 99, 1
Row#2	= 1, 1, 1, 99, 1, 1
Row#3	= 1, 99, 99, 1, 1, 1
Row#4	= 1, 1, 99, 1, 99, 1
Row#5	= 1, 1, 1, 1, 99, 1

MinPathSum BFS_GeneralCase_WNegativeNums for above maze from [0, 0] to [5, 5]: 17
skip 2nd visit [3,5]=13: 15
skip 2nd visit [3,5]=13: 15
skip 2nd visit [1,0]=100: 102
skip 2nd visit [1,0]=100: 104
skip 2nd visit [1,2]=102: 104
skip 2nd visit [3,1]=103: 105
skip 2nd visit [3,1]=103: 107
skip 2nd visit [2,3]=104: 109
skip 2nd visit [1,2]=102: 109
skip 2nd visit [4,2]=107: 109
skip 2nd visit [4,2]=107: 109
skip 2nd visit [4,2]=107: 111
skip 2nd visit [4,2]=107: 111
skip 2nd visit [1,4]=109: 112
skip 2nd visit [2,3]=104: 112
skip 2nd visit [3,2]=104: 112
skip 2nd visit [2,3]=104: 112
skip 2nd visit [3,2]=104: 112
skip 2nd visit [2,3]=104: 113
skip 2nd visit [2,3]=104: 113
skip 2nd visit [4,4]=111: 113
skip 2nd visit [1,4]=109: 113
skip 2nd visit [4,4]=111: 113
skip 2nd visit [4,4]=111: 113
skip 2nd visit [1,4]=109: 113
skip 2nd visit [1,4]=109: 114
skip 2nd visit [5,4]=110: 114
skip 2nd visit [0,2]=101: 115
skip 2nd visit [1,2]=102: 200
skip 2nd visit [3,2]=104: 202
skip 2nd visit [4,2]=107: 203
skip 2nd visit [4,4]=111: 209
skip 2nd visit [4,4]=111: 209
[rY][cX]
Row#0	= 1, 2, 101, 16, 15, 14
Row#1	= 100, 3, 102, 10, 109, 13
Row#2	= 5, 4, 5, 104, 14, 12
Row#3	= 6, 103, 104, 13, 14, 13
Row#4	= 7, 8, 107, 12, 111, 14
Row#5	= 8, 9, 10, 11, 110, 15

[rY][cX]
Row#0	= 1, 1, 99, 1, 1, 1
Row#1	= 99, 1, 99, -6, 99, 1
Row#2	= 1, 1, 1, 99, 0, -2
Row#3	= 1, 99, 99, 1, 1, 1
Row#4	= 1, 1, 99, 1, 99, 1
Row#5	= 1, 1, 1, 1, 99, 1

MinPathSum BFS_GeneralCase_WNegativeNums for above maze from [0, 0] to [5, 5]: 15
*/
#endif