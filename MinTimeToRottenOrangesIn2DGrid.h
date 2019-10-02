#ifndef _MIN_TIME_TO_ROTTEN_ORANGES_IN_2D_GRID_H
#define _MIN_TIME_TO_ROTTEN_ORANGES_IN_2D_GRID_H
/*
Leetcode: Rotting Oranges
In a given grid, each cell can have one of three values:
the value 0 representing an empty cell;
the value 1 representing a fresh orange;
the value 2 representing a rotten orange.
Every minute, any fresh orange that is adjacent (4-directionally) to a rotten orange becomes rotten.
Return the minimum number of minutes that must elapse until no cell has a fresh orange.  If this is impossible, return -1 instead.
Example 1:
Input: [[2,1,1],[1,1,0],[0,1,1]]
Output: 4
Example 2:
Input: [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation:  The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.
Example 3:
Input: [[0,2]]
Output: 0
Explanation:  Since there are already no fresh oranges at minute 0, the answer is just 0.
 */
class MinTimeToRottenOrangesIn2DGrid
{
public:
    MinTimeToRottenOrangesIn2DGrid(){}

    int BFS(std::vector<std::vector<int>> && grid)
    {
        int N = grid.size();
        int M = grid[0].size();
        int countFresh = 0;
        std::queue<int> que;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                if (grid[i][j] == 2)
                    que.push(i*M+j);
                else if (grid[i][j] == 1)
                    ++countFresh;
        if (countFresh == 0) return 0;
        std::vector<std::vector<int>> dir({{-1,0},{1,0},{0,-1},{0,1}});
        int dist = 0;
        while (!que.empty())
        {
            int levelCount = que.size();
            while (levelCount-->0)
            {
                int r = que.front() / M;
                int c = que.front() % M;
                que.pop();
                for (int d = 0; d < 4; ++d)
                {
                    int rr = r + dir[d][0];
                    int cc = c + dir[d][1];
                    if (rr>=0 && rr<N && cc>=0 && cc<M && grid[rr][cc] == 1)
                    {
                        grid[rr][cc] = 2;//mark rotten when first time visit
                        --countFresh;
                        que.push(rr*M+cc);
                    }
                }
            }
            ++dist;
        }
        if (countFresh != 0) return -1;
        return dist-1;
    }

};
#endif
