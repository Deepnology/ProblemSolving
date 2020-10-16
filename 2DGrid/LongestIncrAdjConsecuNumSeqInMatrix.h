#ifndef	LONGEST_INCR_ADJ_CONSECU_NUM_SEQ_IN_MATRIX_H
#define LONGEST_INCR_ADJ_CONSECU_NUM_SEQ_IN_MATRIX_H
#include <vector>
#include <queue>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Longest Increasing Path in a Matrix
Google
http://www.careercup.com/question?id=5147801809846272
Given a NxN matrix which contains all distinct 1 to N^2 numbers.
Find the longest increasing adjacent consecutive number sequence in the matrix.

DP2D: O(N^2) time, O(N^2) space
*/
class LongestIncrAdjConsecuNumSeqInMatrix
{
public:
	LongestIncrAdjConsecuNumSeqInMatrix(){}
	~LongestIncrAdjConsecuNumSeqInMatrix(){}

    int LongestPathInDAG_BFS(const std::vector<std::vector<int> > & board)
    {
        //LongestPathInDAG_BFS
        if (board.empty() || board[0].empty())
            return 0;
        int N = board.size();
        int M = board[0].size();
        std::vector<std::vector<int>> dir({{1,0},{-1,0},{0,1},{0,-1}});
        std::vector<std::vector<int>> inDegree(N, std::vector<int>(M, 0));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                for (int d = 0; d < 4; ++d)
                {
                    int r = i + dir[d][0];
                    int c = j + dir[d][1];
                    if (r>=0&&r<N&&c>=0&&c<M)
                    {
                        if (board[r][c] < board[i][j])
                            inDegree[i][j]++;
                    }
                }
        std::queue<std::vector<int>> que;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                if (inDegree[i][j] == 0)
                    que.push({i,j});
        int dist = 0;
        while (!que.empty())
        {
            int count = que.size();
            while(count-- > 0)
            {
                auto cur = que.front();
                que.pop();
                for (int d = 0; d < 4; ++d)
                {
                    int r = cur[0] + dir[d][0];
                    int c = cur[1] + dir[d][1];
                    if (r>=0&&r<N&&c>=0&&c<M)
                    {
                        if (board[r][c] > board[cur[0]][cur[1]])
                        {
                            --inDegree[r][c];
                            if (inDegree[r][c] == 0)
                                que.push({r, c});
                        }
                    }
                }
            }
            ++dist;
        }
        return dist;
    }

	void DFS_DP2D(const std::vector<std::vector<int> > & board)
	{
		if (board.empty() || board[0].empty())
			return;
		int N = board.size();
		int M = board[0].size();
		std::vector<std::vector<int> > used(N, std::vector<int>(M, -1));
		int maxLen = 0;
		for (int i = 0; i < N; ++i)//from top to bottom
		{
			for (int j = 0; j < M; ++j)//from left to right
			{
				int curLen = this->DFSRecur(board, i, j, used);
				if (curLen > maxLen)
					maxLen = curLen;
			}
		}
		Debug::Print2D<int>()(board, false);
		Debug::Print2D<int>()(used, false);
		std::cout << "LongestIncrAdjConsecuNumSeqInMatrix DFS_DP2D: " << maxLen << std::endl;
	}
private:
	int DFSRecur(const std::vector<std::vector<int> > & board, int x, int y, std::vector<std::vector<int> > & used)
	{
		int N = board.size();//num of rows
		int M = board[0].size();//num of cols

		if (used[x][y] != -1)
			return used[x][y];

		static std::vector<std::vector<int>> dir({{-1,0},{1,0},{0,1},{0,-1}});
		int len = 0;
		for (int d = 0; d < 4; ++d)
		{
			int i = x + dir[d][0];
			int j = y + dir[d][1];
			if (i >= 0 && i < N && j >= 0 && j < M && board[i][j] > board[x][y])
				len = std::max(len, DFSRecur(board, i, j, used));
		}

		return used[x][y] = len + 1;
	}
};
/*
[rY][cX]
Row#0	= 20, 13, 12, 11, 10
Row#1	= 21, 14, 6, 5, 4
Row#2	= 22, 15, 7, 16, 3
Row#3	= 23, 9, 8, 17, 2
Row#4	= 24, 25, 19, 18, 1

[rY][cX]
Row#0	= 6, 3, 4, 5, 6
Row#1	= 5, 2, 4, 5, 6
Row#2	= 4, 1, 3, 4, 7
Row#3	= 3, 1, 2, 3, 8
Row#4	= 2, 1, 1, 2, 9

LongestIncrAdjConsecuNumSeqInMatrix DFS_DP2D: 9
*/
#endif