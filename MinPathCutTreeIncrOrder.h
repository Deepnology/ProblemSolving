#ifndef MIN_PATH_CUT_TREE_INCR_ORDER_H
#define MIN_PATH_CUT_TREE_INCR_ORDER_H
#include "Debug.h"
/*
Amazon
http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=288738&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D5%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
Min path cut tree in increasing order in a matrix
0: obstacle
1: path
>=2: tree height
*/
class MinPathCutTreeIncrOrder
{
public:
	MinPathCutTreeIncrOrder() {}

	struct Greater
	{
		bool operator()(const std::vector<int> & a, const std::vector<int> & b)
		{
			return a[0] > b[0];
		}
	};

	int UseBFS(std::vector<std::vector<int>> & field)
	{
		int N = field.size();
		int M = field[0].size();
		std::map<int, std::vector<int>> treeMap;//<height,<i,j>> where height is sorted in incr order
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < M; ++j)
				if (field[i][j] >= 2)
					treeMap.insert({ field[i][j], { i,j } });
		if (treeMap.empty()) return 0;

		int res = INT_MAX;
		std::vector<std::vector<int>> start({ { 0,0 }, { 0,M - 1 }, { N - 1,0 }, {N - 1,M - 1} });
		for (int i = 0; i < 4; ++i)//enumerate starting position of 4 corners
		{
			int total = 0;
			std::vector<int> begin = start[i];
			for (auto & p : treeMap)
			{
				int dist = BFS(field, begin, p.second);
				if (dist < 0)
				{
					total = -1;
					break;
				}
				total += dist;
				begin = p.second;
			}
			if (total != -1)
				res = std::min(res, total);
		}
		if (res == INT_MAX) return -1;
		return res;
	}
private:
	int BFS(std::vector<std::vector<int>> & field, std::vector<int> & start, std::vector<int> & dest)
	{
		int N = field.size();
		int M = field[0].size();
		std::vector<std::vector<int>> dir({ { -1,0 }, { 1,0 }, { 0,-1 }, { 0,1 } });
		
		//use minHeap to keep track of minDistFromStart of each node ONLY WHEN edge distance between nodes are different!
		//otherwise, just use a queue and keep track of levels

		std::vector<std::vector<int>> visit(N, std::vector<int>(M, 0));
		visit[start[0]][start[1]] = 1;
		std::queue<int> que;
		que.push(start[0] * M + start[1]);
		int dist = 0;
		while (!que.empty())
		{
			int count = que.size();//count of neighbors (all neighbors of cur node must have same dist)
			for (int k = 0; k < count; ++k)
			{
				int cur = que.front();
				que.pop();
				int i = cur / M;
				int j = cur % M;
				if (i == dest[0] && j == dest[1])//reach dest
				{
					field[i][j] = 1;//cut the tree, make it a path
					return dist;
				}
				if (field[i][j] != 1) continue;//hit a tree that is non-dest
				for (int d = 0; d < 4; ++d)
				{
					int ii = i + dir[d][0];
					int jj = j + dir[d][1];
					if (ii >= 0 && ii < N && jj >= 0 && jj < M && !visit[ii][jj] && field[ii][jj] > 0)//non-visit && non-obstacle
					{
						visit[ii][jj] = 1;
						que.push(ii*M + jj);
					}
				}
			}
			++dist;
		}
		return -1;//can't find dest
	}
};
#endif
