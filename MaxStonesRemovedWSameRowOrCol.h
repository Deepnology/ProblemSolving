#ifndef _MAX_STONES_REMOVED_W_SAME_ROW_OR_COL_H
#define _MAX_STONES_REMOVED_W_SAME_ROW_OR_COL_H
#include "Debug.h"
/*
Leetcode: Most Stones Removed With Same Row or Column
On a 2D plane, we place stones at some integer coordinate points.
Each coordinate point may have at most one stone.
Now, a move consists of removing a stone that shares a column or row with another stone on the grid.
What is the largest possible number of moves we can make?
Example 1:
Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
Output: 5
Example 2:
Input: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
Output: 3
Example 3:
Input: stones = [[0,0]]
Output: 0
 */
class MaxStonesRemovedWSameRowOrCol
{
public:
    MaxStonesRemovedWSameRowOrCol(){}

    //stones share same rows or cols can form a connected component
    //since one connected component can be removed to one stone left at least
    //max removed stones = total stone count - total connected component count
    //where total connected component count means one stone left for each component
    int DFS(std::vector<std::vector<int>> && stones)
    {
        //DFS: O(N) time
        std::unordered_map<int,std::unordered_set<int>> rowToCols;
        std::unordered_map<int,std::unordered_set<int>> colToRows;
        for (auto & v : stones)
        {
            rowToCols[v[0]].insert(v[1]);
            colToRows[v[1]].insert(v[0]);
        }
        std::unordered_set<std::string> visit;
        int countComponent = 0;
        for (auto & v : stones)
        {
            std::string cur = std::to_string(v[0]) + "," + std::to_string(v[1]);
            if (!visit.count(cur))
            {
                visit.insert(cur);
                DFS(rowToCols, colToRows, v[0], v[1], visit);
                ++countComponent;
            }
        }
        int res = stones.size() - countComponent;

        std::cout << "MaxStonesRemovedWSameRowOrCol DFS for [" << Debug::ToStr1D<int>()(stones) << "]: " << res << std::endl;
        return res;
    }
private:
    void DFS(std::unordered_map<int,std::unordered_set<int>> & rowToCols, std::unordered_map<int,std::unordered_set<int>> & colToRows, int row, int col, std::unordered_set<std::string> & visit)
    {
        for (auto & c : rowToCols[row])
        {
            std::string cur = std::to_string(row) + "," + std::to_string(c);
            if (!visit.count(cur))
            {
                visit.insert(cur);
                DFS(rowToCols, colToRows, row, c, visit);
            }
        }
        for (auto & r : colToRows[col])
        {
            std::string cur = std::to_string(r) + "," + std::to_string(col);
            if (!visit.count(cur))
            {
                visit.insert(cur);
                DFS(rowToCols, colToRows, r, col, visit);
            }
        }
    }
public:
    int UnionFind(std::vector<std::vector<int>> && stones)
    {
        //union find: O(N^2) time
        std::unordered_map<std::string,std::string> chdToP;
        for (auto & v : stones)
        {
            std::string coord = std::to_string(v[0]) + "," + std::to_string(v[1]);
            chdToP.insert({coord,coord});
        }
        int N = stones.size();
        int countComponent = N;
        for (int i = 0; i < N-1; ++i)
        {
            for (int j = i+1; j < N; ++j)
            {
                if (stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1])
                {
                    std::string chd1 = std::to_string(stones[i][0]) + "," + std::to_string(stones[i][1]);
                    std::string root1 = Find(chdToP, chd1);
                    std::string chd2 = std::to_string(stones[j][0]) + "," + std::to_string(stones[j][1]);
                    std::string root2 = Find(chdToP, chd2);
                    if (root1 != root2)
                    {// as long as two points share same row or col, union them in a single component
                        chdToP[root2] = root1;
                        --countComponent;
                    }
                }
            }
        }
        // since one component can be removed to one stone left at least
        int res = N - countComponent;// max removed stones = total stones - num of components

        std::cout << "MaxStonesRemovedWSameRowOrCol UnionFind for [" << Debug::ToStr1D<int>()(stones) << "]: " << res << std::endl;
        return res;
    }
private:
    std::string Find(std::unordered_map<std::string,std::string> & chdToP, std::string chd)
    {
        std::string cur(chd);
        while (chdToP[cur] != cur)
        {
            chdToP[cur] = chdToP[chdToP[cur]];
            cur = chdToP[cur];
        }
        return cur;
    }
};
/*
MaxStonesRemovedWSameRowOrCol DFS for [[0,0], [0,1], [1,0], [1,2], [2,1], [2,2]]: 5
MaxStonesRemovedWSameRowOrCol UnionFind for [[0,0], [0,1], [1,0], [1,2], [2,1], [2,2]]: 5
 */
#endif
