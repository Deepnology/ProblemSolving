#ifndef ALL_DISTINCT_SUB_AREAS_IN_MATRIX_H
#define ALL_DISTINCT_SUB_AREAS_IN_MATRIX_H
#include <vector>
#include <queue>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Graph: Design an algorithm for computing the black region (up-down-left-right connected 1s) that contains the most points.
Google
http://www.careercup.com/question?id=5696362200956928
Find the max sub area in a N*M matrix

∞ˆæiªP¡Î¡Â Lake Counting DFS

For each UNMARKED pixel, DFS/BFS search and MARK consecutive pixels.

O(N*M) time, O(N*M) space
*/
class AllDistinctSubAreasInMatrix
{
public:
	AllDistinctSubAreasInMatrix(){}
	~AllDistinctSubAreasInMatrix(){}

	void FindAll_DFS(const std::vector<std::vector<int> > & board)
	{
		if (board.empty() || board[0].empty())
			return;
		int N = board.size();
		int M = board[0].size();
		std::vector<std::vector<int> > used(N, std::vector<int>(M, 0));
		std::vector<int> areas;
		for (int i = 0; i < N; ++i)//from top to bottom
		{
			for (int j = 0; j < M; ++j)//from left to right
			{
				int curArea = this->DFSRecur(board, i, j, used);
				if (curArea != 0)
					areas.push_back(curArea);
			}
		}
		Debug::Print2D<int>()(board, false);
		std::cout << "AllDistinctSubAreasInMatrix DFS: " << Debug::ToStr1D<int>()(areas) << std::endl;
	}
private:
	int DFSRecur(const std::vector<std::vector<int> > & board, int x, int y, std::vector<std::vector<int> > & used)
	{
		int N = board.size();//num of rows
		int M = board[0].size();//num of cols
		if (x < 0 || y < 0 || x > N - 1 || y > M - 1)
			return 0;
		if (board[x][y] != 1)
			return 0;
		if (used[x][y] == 1)
			return 0;

		used[x][y] = 1;//mark
		int curArea = 1 + this->DFSRecur(board, x - 1, y, used)//up
			+ this->DFSRecur(board, x + 1, y, used)//down
			+ this->DFSRecur(board, x, y - 1, used)//left
			+ this->DFSRecur(board, x, y + 1, used);//right
		return curArea;
	}

public:
	void FindAll_BFS(const std::vector<std::vector<int> > & board)
	{
		if (board.empty() || board[0].empty())
			return;
		int N = board.size();
		int M = board[0].size();
		std::vector<std::vector<int> > used(N, std::vector<int>(M, 0));
		std::vector<int> areas;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				int curArea = this->BFS(board, i, j, used);
				if (curArea != 0)
					areas.push_back(curArea);
			}
		}
		Debug::Print2D<int>()(board, false);
		std::cout << "AllDistinctSubAreasInMatrix BFS: " << Debug::ToStr1D<int>()(areas) << std::endl;
	}
private:
	int BFS(const std::vector<std::vector<int> > & board, int x, int y, std::vector<std::vector<int> > & used)
	{
		if (board[x][y] != 1)
			return 0;
		if (used[x][y] == 1)
			return 0;
		used[x][y] = 1;
		int N = board.size();
		int M = board[0].size();
		int curArea = 0;
		std::queue<int> queue;
		queue.push(x * M + y);
		while (!queue.empty())
		{
			x = queue.front() / M;
			y = queue.front() % M;
			queue.pop();
			++curArea;
			if (x - 1 >= 0 && board[x - 1][y] == 1 && used[x - 1][y] == 0)//up
			{
				used[x - 1][y] = 1;
				queue.push((x - 1)*M + y);
			}
			if (x + 1 < N && board[x + 1][y] == 1 && used[x + 1][y] == 0)//down
			{
				used[x + 1][y] = 1;
				queue.push((x + 1)*M + y);
			}
			if (y - 1 >= 0 && board[x][y - 1] == 1 && used[x][y - 1] == 0)//left
			{
				used[x][y - 1] = 1;
				queue.push(x*M + y - 1);
			}
			if (y + 1 < M && board[x][y + 1] == 1 && used[x][y + 1] == 0)//left
			{
				used[x][y + 1] = 1;
				queue.push(x*M + y + 1);
			}
		}
		return curArea;
	}
};
/*
[rY][cX]
Row#0	= 0, 0, 1, 1, 0, 0, 0, 0, 0, 0
Row#1	= 0, 1, 1, 1, 1, 0, 1, 1, 1, 0
Row#2	= 0, 1, 0, 0, 1, 0, 1, 0, 0, 0
Row#3	= 0, 1, 0, 1, 1, 0, 1, 1, 1, 1
Row#4	= 0, 1, 1, 1, 0, 0, 0, 0, 0, 0
Row#5	= 0, 0, 0, 0, 1, 1, 0, 0, 1, 0
Row#6	= 0, 0, 0, 0, 0, 1, 1, 1, 1, 0

AllDistinctSubAreasInMatrix DFS: 14, 8, 7
[rY][cX]
Row#0	= 0, 0, 1, 1, 0, 0, 0, 0, 0, 0
Row#1	= 0, 1, 1, 1, 1, 0, 1, 1, 1, 0
Row#2	= 0, 1, 0, 0, 1, 0, 1, 0, 0, 0
Row#3	= 0, 1, 0, 1, 1, 0, 1, 1, 1, 1
Row#4	= 0, 1, 1, 1, 0, 0, 0, 0, 0, 0
Row#5	= 0, 0, 0, 0, 1, 1, 0, 0, 1, 0
Row#6	= 0, 0, 0, 0, 0, 1, 1, 1, 1, 0

AllDistinctSubAreasInMatrix BFS: 14, 8, 7
*/
#endif