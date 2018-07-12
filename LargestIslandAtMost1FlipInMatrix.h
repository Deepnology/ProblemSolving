#ifndef _LARGEST_ISLAND_AT_MOST_1_FLIP_IN_MATRIX_H
#define _LARGEST_ISLAND_AT_MOST_1_FLIP_IN_MATRIX_H
#include "Debug.h"
/*
Leetcode: Making a large island
In a 2D grid of 0s and 1s, we change at most one 0 to a 1.
After, what is the size of the largest island?
(An island is a 4-directionally connected group of 1s).
Example 1:
Input: [[1, 0], [0, 1]]
Output: 3
Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.
Example 2:
Input: [[1, 1], [1, 0]]
Output: 4
Explanation: Change the 0 to 1 and make the island bigger, only one island with area = 1.
Example 3:
Input: [[1, 1], [1, 1]]
Output: 4
Explanation: Can't change any 0 to 1, only one island with area = 1.
 */
class LargestIslandAtMost1FlipInMatrix
{
public:
    LargestIslandAtMost1FlipInMatrix(){}

    int UnionFind(const std::vector<std::vector<int>> & grid)
    {
        int N = grid.size();
        std::vector<std::vector<int>> dir({{-1,0},{1,0},{0,1},{0,-1}});
        int res = 1;
        std::vector<int> father(N*N, -1);
        std::vector<int> area(N*N, 0);
        for (int i = 0; i < N; ++i)//1st iteration on 1
            for (int j = 0; j < N; ++j)
            {
                if (grid[i][j] == 1)
                {
                    father[i*N+j] = i*N+j;
                    area[i*N+j] = 1;
                    if (i-1 >= 0 && grid[i-1][j] == 1)
                    {
                        int root = find(father, (i-1)*N+j);
                        int curRoot = find(father, i*N+j);
                        //root must be diff from curRoot
                        father[curRoot] = root;
                        area[root] += area[curRoot];
                        res = std::max(res, area[root]);
                    }
                    if (j-1 >= 0 && grid[i][j-1] == 1)
                    {
                        int root = find(father, i*N+j-1);
                        int curRoot = find(father, i*N+j);
                        if (root != curRoot)
                        {
                            father[curRoot] = root;
                            area[root] += area[curRoot];
                            res = std::max(res, area[root]);
                        }
                    }
                }
            }

        for (int i = 0; i < N; ++i)//2nd iteration on 0
            for (int j = 0; j < N; ++j)
            {
                if (grid[i][j] == 0)
                {
                    area[i*N+j] = 1;
                    std::unordered_map<int,int> rootToArea;
                    for (int d = 0; d < 4; ++d)
                    {
                        int ii = i + dir[d][0];
                        int jj = j + dir[d][1];
                        if (ii >= 0 && ii < N && jj >= 0 && jj < N && grid[ii][jj] == 1)
                        {
                            int root = find(father, ii*N+jj);
                            rootToArea[root] = area[root];
                        }
                    }
                    for (auto & p : rootToArea)
                        area[i*N+j] += p.second;
                    res = std::max(res, area[i*N+j]);
                }
            }

        Debug::Print2D<int>()(grid, false);
        std::cout << "LargestIslandAtMost1FlipInMatrix UnionFind for above matrix: " << res << std::endl;
        return res;
    }
    int find(std::vector<int> & father, int idx)
    {
        while (father[idx] != idx)
        {
            father[idx] = father[father[idx]];
            idx = father[idx];
        }
        return idx;
    }

    int BruteForceBFS(const std::vector<std::vector<int>> & grid)
    {
        int N = grid.size();
        std::vector<std::vector<int>> dir({{-1,0},{1,0},{0,1},{0,-1}});
        int res = 0;
        std::unordered_set<int> visit;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
            {
                if (grid[i][j] == 1 && !visit.count(i*N+j))//BFS on 1
                {
                    int area = 0;
                    std::queue<int> que;
                    que.push(i*N+j);
                    visit.insert(i*N+j);
                    while (!que.empty())
                    {
                        int curI = que.front() / N;
                        int curJ = que.front() % N;
                        que.pop();
                        ++area;
                        for (int d = 0; d < 4; ++d)
                        {
                            int nxtI = curI + dir[d][0];
                            int nxtJ = curJ + dir[d][1];
                            if (nxtI >= 0 && nxtI < N && nxtJ >= 0 && nxtJ < N && grid[nxtI][nxtJ] == 1 && !visit.count(nxtI*N+nxtJ))
                            {
                                visit.insert(nxtI*N+nxtJ);
                                que.push(nxtI*N+nxtJ);
                            }
                        }
                    }
                    res = std::max(res, area);
                }
            }


        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
            {
                if (grid[i][j] == 0)//BFS on 0
                {
                    int area = 0;
                    std::queue<int> que;
                    std::unordered_set<int> visit2;
                    que.push(i * N + j);
                    visit2.insert(i * N + j);
                    while (!que.empty())
                    {
                        int curI = que.front() / N;
                        int curJ = que.front() % N;
                        que.pop();
                        ++area;
                        for (int d = 0; d < 4; ++d)
                        {
                            int nxtI = curI + dir[d][0];
                            int nxtJ = curJ + dir[d][1];
                            if (nxtI >= 0 && nxtI < N && nxtJ >= 0 && nxtJ < N && grid[nxtI][nxtJ] == 1 && !visit2.count(nxtI*N+nxtJ))
                            {
                                visit2.insert(nxtI*N+nxtJ);
                                que.push(nxtI*N+nxtJ);
                            }
                        }
                    }
                    res = std::max(res, area);
                }
            }

        Debug::Print2D<int>()(grid, false);
        std::cout << "LargestIslandAtMost1FlipInMatrix BruteForceBFS for above matrix: " << res << std::endl;
        return res;
    }
};
/*
[rY][cX]
Row#0	= 1, 0
Row#1	= 0, 1

LargestIslandAtMost1FlipInMatrix BruteForceBFS for above matrix: 3
[rY][cX]
Row#0	= 1, 0
Row#1	= 0, 1

LargestIslandAtMost1FlipInMatrix UnionFind for above matrix: 3
 */
#endif
