#ifndef SEARCH_A_MAZE_H
#define SEARCH_A_MAZE_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Graph: Search a maze

See also AllShortestPathsInMatrix.h for searching shortest paths by BFS
*/
class SearchAMaze
{
public:
	SearchAMaze(){}
	~SearchAMaze(){}
	//in v: 0 is path, 1 is obstacle. similar to NonStoppingMaze.h II. can use minHeap instead of queue
	int ShortestPath_BFS(std::vector<std::vector<int>> & v, std::vector<int> & start, std::vector<int> & end)
	{
		int N = v.size();
		if (N == 0) return 0;
		int M = v[0].size();
		std::vector<std::vector<int>> dist(N, std::vector<int>(M, INT_MAX));//tracks "visit" as well
		std::queue<int> que;
		que.push(start[0] * M + start[1]);
		dist[start[0]][start[1]] = 0;
		while (!que.empty())
		{
			auto cur = que.front();
			que.pop();
			int i = cur / M;
			int j = cur % M;
			static std::vector<std::vector<int>> dir({ {0,-1},{0,1},{-1,0},{1,0} });
			for (int d = 0; d < 4; ++d)
			{
				int ii = i + dir[d][0];
				int jj = j + dir[d][1];
				if (ii >= 0 && ii < N && jj >= 0 && jj < M && v[ii][jj] == 0 && dist[i][j] + 1 < dist[ii][jj])
				{
					dist[ii][jj] = dist[i][j] + 1;
					que.push(ii * M + jj);
				}
			}
		}
		return dist[end[0]][end[1]] == INT_MAX ? -1 : dist[end[0]][end[1]];
	}


	std::vector<std::pair<int, int> > DFSRecur(const std::vector<std::vector<char> > & board, std::pair<int, int> start, std::pair<int, int> end)
	{
		int N = board.size();
		int M = board[0].size();
		std::vector<std::vector<int> > visited(N, std::vector<int>(M, 0));
		std::vector<std::pair<int, int> > path;
		path.push_back(start);
		bool res = this->dFSRecur(board, start, end, visited, path);
		Debug::Print2D<char>()(board, false);
		std::cout << "SearchAMaze DFSRecur for the above matrix, start=[" << start.first << "," << start.second << "], end=[" << end.first << "," << end.second << "]: " << res << ", (" << Debug::ToStr1D<int>()(path) << ")" << std::endl;
		return path;
	}
private:
	bool dFSRecur(const std::vector<std::vector<char> > & board, std::pair<int, int> cur, const std::pair<int, int> & end, std::vector<std::vector<int> > & visited, std::vector<std::pair<int, int> > & path)
	{
		int N = board.size();
		int M = board[0].size();
		if (cur.first == end.first && cur.second == end.second)
			return true;

		if (cur.first - 1 >= 0 && !visited[cur.first - 1][cur.second] && board[cur.first - 1][cur.second] == '.')
		{
			visited[cur.first - 1][cur.second] = 1;
			path.push_back({ cur.first - 1, cur.second });
			if (this->dFSRecur(board, { cur.first - 1, cur.second }, end, visited, path))
				return true;
			path.pop_back();
			visited[cur.first - 1][cur.second] = 0;
		}
		if (cur.first + 1 < N && !visited[cur.first + 1][cur.second] && board[cur.first + 1][cur.second] == '.')
		{
			visited[cur.first + 1][cur.second] = 1;
			path.push_back({ cur.first + 1, cur.second });
			if (this->dFSRecur(board, { cur.first + 1, cur.second }, end, visited, path))
				return true;
			path.pop_back();
			visited[cur.first + 1][cur.second] = 0;
		}
		if (cur.second - 1 >= 0 && !visited[cur.first][cur.second - 1] && board[cur.first][cur.second - 1] == '.')
		{
			visited[cur.first][cur.second - 1] = 1;
			path.push_back({ cur.first, cur.second - 1 });
			if (this->dFSRecur(board, { cur.first, cur.second - 1 }, end, visited, path))
				return true;
			path.pop_back();
			visited[cur.first][cur.second - 1] = 0;
		}
		if (cur.second + 1 < M && !visited[cur.first][cur.second + 1] && board[cur.first][cur.second + 1] == '.')
		{
			visited[cur.first][cur.second + 1] = 1;
			path.push_back({ cur.first, cur.second + 1 });
			if (this->dFSRecur(board, { cur.first, cur.second + 1 }, end, visited, path))
				return true;
			path.pop_back();
			visited[cur.first][cur.second + 1] = 0;
		}
		return false;
	}
};
/*
[rY][cX]
Row#0	= #, ., #, #, #, #, #, #, ., #
Row#1	= ., ., ., ., ., ., #, ., ., #
Row#2	= ., #, ., #, #, ., #, #, ., #
Row#3	= ., #, ., ., ., ., ., ., ., .
Row#4	= #, #, ., #, #, ., #, #, #, #
Row#5	= ., ., ., ., #, ., ., ., ., #
Row#6	= ., #, #, #, #, #, #, #, ., #
Row#7	= ., ., ., ., #, ., ., ., ., .
Row#8	= ., #, #, #, #, ., #, #, #, .
Row#9	= ., ., ., ., #, ., ., ., ., #

SearchAMaze DFSRecur for the above matrix, start=[0,1], end=[9,8]: 1, ([0,1], [1,1], [1,2], [2,2], [3,2], [3,3], [3,4], [3,5], [4,5], [5,5], [5,6], [5,7], [5,8], [6,8], [7,8], [7,7], [7,6], [7,5], [8,5], [9,5], [9,6], [9,7], [9,8])
*/
#endif