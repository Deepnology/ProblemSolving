#ifndef _COUNT_REGIONS_CUT_BY_SLASHES_2D_GRID_H
#define _COUNT_REGIONS_CUT_BY_SLASHES_2D_GRID_H
#include "Debug.h"
/*
Leetcode: Regions Cut By Slashes
In a N x N grid composed of 1 x 1 squares, each 1 x 1 square consists of a /, \, or blank space.
These characters divide the square into contiguous regions.
(Note that backslash characters are escaped, so a \ is represented as "\\".)
Return the number of regions.
Example 1:
Input:
[
  " /",
  "/ "
]
Output: 2
Explanation: The 2x2 grid is as follows:
Example 2:
Input:
[
  " /",
  "  "
]
Output: 1
Explanation: The 2x2 grid is as follows:
Example 3:
Input:
[
  "\\/",
  "/\\"
]
Output: 4
Explanation: (Recall that because \ characters are escaped, "\\/" refers to \/, and "/\\" refers to /\.)
The 2x2 grid is as follows:
Example 4:
Input:
[
  "/\\",
  "\\/"
]
Output: 5
Explanation: (Recall that because \ characters are escaped, "/\\" refers to /\, and "\\/" refers to \/.)
The 2x2 grid is as follows:
Example 5:
Input:
[
  "//",
  "/ "
]
Output: 3
Explanation: The 2x2 grid is as follows:
 */
class CountRegionsCutBySlashes2DGrid
{
public:
    CountRegionsCutBySlashes2DGrid(){}

    std::vector<std::vector<int>> dir = {{0,-1},{-1,0},{0,1},{1,0}};
    int UnionFind(std::vector<std::string> && grid)
    {
        //Union Find: O(N^2logN) time
        int N = grid.size();
        std::vector<std::vector<int>> grid2(N*3, std::vector<int>(N*3, 0));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
            {
                if (grid[i][j] == '\\')
                    grid2[i*3][j*3] = grid2[i*3+1][j*3+1] = grid2[i*3+2][j*3+2] = 1;
                else if (grid[i][j] == '/')
                    grid2[i*3][j*3+2] = grid2[i*3+1][j*3+1] = grid2[i*3+2][j*3] = 1;
            }
        //now it becomes the number of islands problem
        int res = 0;
        N = grid2.size();
        std::vector<int> chdToP(N*N,-1);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
            {
                if (grid2[i][j] == 0)
                {
                    chdToP[i*N+j] = i*N+j;
                    ++res;
                    for (int d = 0; d < 2; ++d)//only left and upper grid
                    {
                        int ii = i + dir[d][0];
                        int jj = j + dir[d][1];
                        if (ii >= 0 && jj >= 0 && grid2[ii][jj] == 0)
                        {
                            int root = Find(chdToP, ii*N+jj);
                            if (root != i*N+j)
                            {
                                chdToP[root] = i*N+j;
                                --res;
                            }
                        }
                    }
                }
            }

        Debug::Print2D<std::string>()(grid, false);
        std::cout << "CountRegionsCutBySlashes2DGrid UnionFind for above grid: " << res << std::endl;
        return res;
    }
    int DFS(std::vector<std::string> && grid)
    {
        //DFS: O(N^3) time
        int N = grid.size();
        std::vector<std::vector<int>> grid2(N*3, std::vector<int>(N*3, 0));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
            {
                if (grid[i][j] == '\\')
                    grid2[i*3][j*3] = grid2[i*3+1][j*3+1] = grid2[i*3+2][j*3+2] = 1;
                else if (grid[i][j] == '/')
                    grid2[i*3][j*3+2] = grid2[i*3+1][j*3+1] = grid2[i*3+2][j*3] = 1;
            }
        //now it becomes the number of islands problem
        int res = 0;
        N = grid2.size();
        std::unordered_set<int> visit;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
            {
                if (grid2[i][j] == 0 && !visit.count(i*N+j))
                {
                    visit.insert(i*N+j);
                    DFS(grid2, i, j, visit);
                    ++res;
                }
            }

        Debug::Print2D<std::string>()(grid, false);
        std::cout << "CountRegionsCutBySlashes2DGrid DFS for above grid: " << res << std::endl;
        return res;
    }
private:
    int Find(std::vector<int> & chdToP, int chd)
    {
        int cur = chd;
        while (cur != chdToP[cur])
        {
            chdToP[cur] = chdToP[chdToP[cur]];
            cur = chdToP[cur];
        }
        return cur;
    }
    void DFS(std::vector<std::vector<int>> & grid, int i, int j, std::unordered_set<int> & visit)
    {
        int N = grid.size();
        for (auto & d : dir)
        {
            int ii = i + d[0];
            int jj = j + d[1];
            if (ii >= 0 && ii < N && jj >= 0 && jj < N && grid[ii][jj] == 0 && !visit.count(ii*N+jj))
            {
                visit.insert(ii*N+jj);
                DFS(grid, ii, jj, visit);
            }
        }
    }
};
/*
[rY][cX]
Row#0	= /, \
Row#1	= \, /

CountRegionsCutBySlashes2DGrid DFS for above grid: 5
[rY][cX]
Row#0	= /, \
Row#1	= \, /

CountRegionsCutBySlashes2DGrid UnionFind for above grid: 5
 */
#endif
