/*AmazonOA*/
#ifndef MIN_PATH_CUT_TREE_INCR_ORDER_H
#define MIN_PATH_CUT_TREE_INCR_ORDER_H
#include "Debug.h"
/*
Leetcode: Cut Off Trees for Golf Event
Min path of steps to cut all trees in increasing order in a matrix starting from [0,0].
Return -1 if cannot cut all trees.
0: obstacle
1: path (can walk)
>=2: tree height (can walk)
*/
class MinPathCutTreeIncrOrder
{
public:
	MinPathCutTreeIncrOrder() {}


	int UseBFS(std::vector<std::vector<int>> && field)
	{
		Debug::Print2D<int>()(field, false);

		int N = field.size();
		int M = field[0].size();
		std::map<int, std::vector<int>> treeMap;//<height,<i,j>> where height is sorted in incr order
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < M; ++j)
			{
				if (field[i][j] >= 2)
					treeMap.insert({ field[i][j], { i,j } });
			}
		if (treeMap.empty()) return 0;
		int total = 0;
		std::vector<int> begin({0,0});
		for (auto itr = treeMap.begin(); itr != treeMap.end(); ++itr)
		{
			int dist = BFS(field, begin, itr->second);
			if (dist < 0)
			{
				total = -1;
				break;
			}
			total += dist;
			begin = itr->second;
		}

		std::cout << "MinPathCutTreeIncrOrder BFS for above field: " << total << std::endl;
		return total;
	}
private:
	int BFS(std::vector<std::vector<int>> & field, std::vector<int> & start, std::vector<int> & dest)
	{
		int N = field.size();
		int M = field[0].size();
		static std::vector<std::vector<int>> dir({ { -1,0 }, { 1,0 }, { 0,-1 }, { 0,1 } });

		//use minHeap to keep track of minDistFromStart of each node ONLY WHEN "edge distance between nodes are different"!
		//otherwise, just use a queue and keep track of levels

		std::vector<std::vector<int>> visit(N, std::vector<int>(M, 0));
		visit[start[0]][start[1]] = 1;
		std::queue<std::vector<int>> que;
		que.push(start);
		int dist = 0;
		while (!que.empty())
		{
			int count = que.size();//count of neighbors (all neighbors of cur node must have same dist)
			for (int k = 0; k < count; ++k)
			{
				auto cur = que.front();
				que.pop();
				int i = cur[0];
				int j = cur[1];
				if (i == dest[0] && j == dest[1])//reach dest
				{
					field[i][j] = 1;//cut the tree, make it a path
					return dist;
				}
				for (int d = 0; d < 4; ++d)
				{
					int ii = i + dir[d][0];
					int jj = j + dir[d][1];
					if (ii >= 0 && ii < N && jj >= 0 && jj < M && !visit[ii][jj] && field[ii][jj] > 0)//non-visit && non-obstacle
					{
						visit[ii][jj] = 1;
						que.push({ii, jj});
					}
				}
			}
			++dist;
		}
		return -1;//can't find dest
	}
};
/*
[rY][cX]
Row#0	= 54581641, 64080174, 24346381, 69107959
Row#1	= 86374198, 61363882, 68783324, 79706116
Row#2	= 668150, 92178815, 89819108, 94701471
Row#3	= 83920491, 22724204, 46281641, 47531096
Row#4	= 89078499, 18904913, 25462145, 60813308

MinPathCutTreeIncrOrder BFS for above field: 57
 */
#endif
