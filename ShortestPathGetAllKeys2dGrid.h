#ifndef _SHORTEST_PATH_GET_ALL_KEYS_2D_GRID_H
#define _SHORTEST_PATH_GET_ALL_KEYS_2D_GRID_H
#include "Debug.h"
/*
Leetcode: Shortest Path to Get All Keys
We are given a 2-dimensional grid.
"." is an empty cell, "#" is a wall, "@" is the starting point, ("a", "b", ...) are keys, and ("A", "B", ...) are locks.
We start at the starting point, and one move consists of walking one space in one of the 4 cardinal directions.
We cannot walk outside the grid, or walk into a wall.
If we walk over a key, we pick it up.
We can't walk over a lock unless we have the corresponding key.
For some 1 <= K <= 6, there is exactly one lowercase and one uppercase letter of the first K letters of the English alphabet in the grid.
This means that there is exactly one key for each lock, and one lock for each key;
 and also that the letters used to represent the keys and locks were chosen in the same order as the English alphabet.
Return the lowest number of moves to acquire all keys.  If it's impossible, return -1.
Example 1:
Input: ["@.a.#",
        "###.#",
        "b.A.B"]
Output: 8
Example 2:
Input: ["@..aA",
        "..B#.",
        "....b"]
Output: 6
1 <= grid.length <= 30
1 <= grid[0].length <= 30
grid[i][j] contains only '.', '#', '@', 'a'-'f' and 'A'-'F'
The number of keys is in [1, 6].  Each key has a different letter and opens exactly one lock.
 */
class ShortestPathGetAllKeys
{
public:
    ShortestPathGetAllKeys(){}

    int BFS(std::vector<std::string> && grid)
    {
        int N = grid.size();
        int M = grid[0].size();
        std::vector<std::vector<int>> dir({{0,1},{1,0},{-1,0},{0,-1}});
        std::unordered_set<std::string> visit;
        int startR = -1;
        int startC = -1;
        int keyCount = 0;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
            {
                if (grid[i][j] == '@')
                {
                    startR = i;
                    startC = j;
                }
                else if (grid[i][j] >= 'a' && grid[i][j] <= 'f')
                {
                    keyCount = std::max(keyCount, grid[i][j]-'a'+1);
                }
            }
        std::queue<std::vector<int>> que;
        que.push({0,startR,startC});
        visit.insert(std::to_string(0)+","+std::to_string(startR)+","+std::to_string(startC));
        int dist = 0;
        while (!que.empty())
        {
            int levelCount = que.size();
            while (levelCount-- > 0)
            {
                int keys = que.front()[0];
                int row = que.front()[1];
                int col = que.front()[2];
                //std::cout << row << "," << col << ":" << keys << std::endl;
                que.pop();
                if (keys == (1<<keyCount)-1)
                    return dist;
                for (int d = 0; d < 4; ++d)
                {
                    int rr = row + dir[d][0];
                    int cc = col + dir[d][1];
                    if (rr>=0 && rr<N && cc>=0 && cc<M)
                    {
                        if (grid[rr][cc]=='#')
                            continue;//skip walls
                        if (grid[rr][cc] >= 'A' && grid[rr][cc] <= 'F' && ((keys>>(grid[rr][cc]-'A'))&1)==0)
                            continue;//skip locks w/o key
                        //now grid[rr][cc] can be either '@' or '.' or 'A'~'F' or 'a'~'f'
                        int nxtKeys = keys;
                        if (grid[rr][cc]>='a' && grid[rr][cc]<='f')
                            nxtKeys |= (1<<(grid[rr][cc]-'a'));
                        if (!visit.count(std::to_string(nxtKeys)+","+std::to_string(rr)+","+std::to_string(cc)))
                        {
                            visit.insert(std::to_string(nxtKeys)+","+std::to_string(rr)+","+std::to_string(cc));
                            que.push({nxtKeys,rr,cc});
                        }
                    }
                }
            }
            ++dist;
        }
        return -1;
    }
};
#endif
