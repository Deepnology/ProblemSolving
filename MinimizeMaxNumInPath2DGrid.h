#ifndef _MINIMIZE_MAX_NUM_IN_PATH_2D_GRID_H
#define _MINIMIZE_MAX_NUM_IN_PATH_2D_GRID_H
#include "Debug.h"
/*
Leetcode: Swim in rising water
On an N x N grid, each square grid[i][j] represents the elevation at that point (i,j).
Now rain starts to fall.
At time t, the depth of the water everywhere is t.
You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most t.
You can swim infinite distance in zero time. Of course, you must stay within the boundaries of the grid during your swim.
You start at the top left square (0, 0). What is the least time until you can reach the bottom right square (N-1, N-1)?
Example 1:
Input: [[0,2],[1,3]]
Output: 3
Explanation:
At time 0, you are in grid location (0, 0).
You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.
You cannot reach point (1, 1) until time 3.
When the depth of water is 3, we can swim anywhere inside the grid.
Example 2:
Input: [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
Output: 16
Explanation:
 0  1  2  3  4
24 23 22 21  5
12 13 14 15 16
11 17 18 19 20
10  9  8  7  6
The final route is marked in bold.
We need to wait until time 16 so that (0, 0) and (4, 4) are connected.
 */
class MinimizeMaxNumInPath2DGrid
{
public:
    MinimizeMaxNumInPath2DGrid(){}
private:
    struct Greater
    {
        bool operator()(const std::vector<int> & a, const std::vector<int> & b) const
        {
            return a[0] > b[0];
        }
    };
    bool reachBFS(std::vector<std::vector<int>> & grid, int height)
    {
        int N = grid.size();
        std::queue<int> que;
        std::unordered_set<int> visit;
        if (grid[0][0] <= height)
        {
            que.push(0);
            visit.insert(0);
            int dist = 0;
            std::vector<std::vector<int>> dir({{0,1},{1,0},{0,-1},{-1,0}});
            while (!que.empty())
            {
                int levelCount = que.size();
                while (levelCount-- > 0)
                {
                    int i = que.front() / N;
                    int j = que.front() % N;
                    que.pop();
                    if (i==N-1 && j==N-1)
                        return true;
                    for (auto & d : dir)
                    {
                        int ii = i + d[0];
                        int jj = j + d[1];
                        if (ii>=0 && ii<N && jj>=0 && jj<N && !visit.count(ii*N+jj) && grid[ii][jj] <= height)
                        {
                            visit.insert(ii*N+jj);
                            que.push(ii*N+jj);
                        }
                    }
                }
                ++dist;
            }
        }
        return false;
    }
public:
    //find a path from (0,0) to (N-1,N-1) such that the max num in the path is minimized
    int BFS_MinHeap(std::vector<std::vector<int>> && grid)
    {
        //minHeap: O(N^2logN) time
        int N = grid.size();
        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, Greater> minHeap;
        minHeap.push({grid[0][0],0,0});
        std::vector<std::vector<int>> visit(N, std::vector<int>(N, 0));
        visit[0][0] = 1;
        std::vector<std::vector<int>> dir({{0,1},{1,0},{0,-1},{-1,0}});
        int dist = 0;
        int resHeight = grid[0][0];
        while (!minHeap.empty())
        {
            int levelCount = minHeap.size();
            while (levelCount-- > 0)
            {
                auto cur = minHeap.top();
                minHeap.pop();
                resHeight = std::max(resHeight, cur[0]);
                if (cur[1] == N-1 && cur[2] == N-1)
                {
                    Debug::Print2D<int>()(grid, false);
                    std::cout << "MinimizeMaxNumInPath2DGrid BFS_MinHeap for above grid: " << resHeight << std::endl;
                    return resHeight;
                }
                for (auto & d : dir)
                {
                    int i = cur[1] + d[0];
                    int j = cur[2] + d[1];
                    if (i>=0 && i<N && j>=0 && j<N && !visit[i][j])
                    {
                        visit[i][j] = 1;
                        minHeap.push({grid[i][j],i,j});
                    }
                }
            }
            ++dist;
        }
        return resHeight;
    }

    int BinarySearch_BFS(std::vector<std::vector<int>> && grid)
    {
        //binary search: O(log(N^2)) time
        //grid[i][j] is a permutation of [0,1,...,N*N-1]
        int N = grid.size();
        int left = 0;
        int right = N*N-1;
        while (left <= right)//find lower bound
        {
            int mid = (left + right) / 2;
            if (reachBFS(grid, mid))
                right = mid - 1;
            else
                left = mid + 1;
        }

        Debug::Print2D<int>()(grid, false);
        std::cout << "MinimizeMaxNumInPath2DGrid BinarySearch_BFS for above grid: " << left << std::endl;
        return left;
    }
};
/*
[rY][cX]
Row#0	= 0, 1, 2, 3, 4
Row#1	= 24, 23, 22, 21, 5
Row#2	= 12, 13, 14, 15, 16
Row#3	= 11, 17, 18, 19, 20
Row#4	= 10, 9, 8, 7, 6

MinimizeMaxNumInPath2DGrid BFS_MinHeap for above grid: 16
[rY][cX]
Row#0	= 0, 1, 2, 3, 4
Row#1	= 24, 23, 22, 21, 5
Row#2	= 12, 13, 14, 15, 16
Row#3	= 11, 17, 18, 19, 20
Row#4	= 10, 9, 8, 7, 6

MinimizeMaxNumInPath2DGrid BinarySearch_BFS for above grid: 16
 */
#endif
