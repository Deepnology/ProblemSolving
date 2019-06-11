#ifndef _ESCAPE_IN_LARGE_2D_MAZE_WITH_BLOCKS_H
#define _ESCAPE_IN_LARGE_2D_MAZE_WITH_BLOCKS_H
#include "Debug.h"
/*
Leetcode: Escape a Large Maze
In a 1 million by 1 million grid, the coordinates of each grid square are (x, y) with 0 <= x, y < 10^6.
We start at the source square and want to reach the target square.
Each move, we can walk to a 4-directionally adjacent square in the grid that isn't in the given list of blocked squares.
Return true if and only if it is possible to reach the target square through a sequence of moves.
Example 1:
Input: blocked = [[0,1],[1,0]], source = [0,0], target = [0,2]
Output: false
Explanation:
The target square is inaccessible starting from the source square, because we can't walk outside the grid.
Example 2:
Input: blocked = [], source = [0,0], target = [999999,999999]
Output: true
Explanation:
Because there are no blocked cells, it's possible to reach the target square.
Note:
0 <= blocked.length <= 200
blocked[i].length == 2
0 <= blocked[i][j] < 10^6
source.length == target.length == 2
0 <= source[i][j], target[i][j] < 10^6
source != target
 */
class EscapeInLarge2DMazeWithBlocks
{
public:
    EscapeInLarge2DMazeWithBlocks(){}

    /*
    the max area that blocked can loop is
    1. blocked forms a line that intercept x and y coord as a triangle: 1+2+3+...+B = B*(B-1)/2 = 19900
    2. blockked forms a circle: (B/3.14/2)*(B/3.14/2)*3.14 = 3185
    where blocked has max size of 200
    */
    const int MAX_AREA = 19901;
    bool IsEscapePossible(std::vector<std::vector<int>> && blocked, std::vector<int> && source, std::vector<int> && target)
    {
        std::unordered_set<long> blocks;
        for (auto v : blocked) blocks.insert((long)v[0]*1000000+(long)v[1]);
        std::vector<long> src({(long)source[0],(long)source[1]});
        std::vector<long> tgt({(long)target[0],(long)target[1]});
        bool res = BFS(blocks, src, tgt) && BFS(blocks, tgt, src);
        std::cout << "EscapeInLarge2DMazeWithBlocks IsEscapePossible for blocks=[" << Debug::ToStr1D<int>()(blocked) << "], src=[" << Debug::ToStr1D<int>()(source) << "], tgt=[" << Debug::ToStr1D<int>()(target) << "]: " << res << std::endl;
        return res;
    }
private:
    bool BFS(std::unordered_set<long> & blocks, std::vector<long> & src, std::vector<long> & tgt)
    {
        std::unordered_set<long> visit;
        std::vector<std::vector<long>> dir({{0,-1},{0,1},{-1,0},{1,0}});
        std::queue<long> que;
        que.push(src[0]*1000000+src[1]);
        visit.insert(src[0]*1000000+src[1]);
        while (!que.empty())
        {
            long r = que.front() / 1000000;
            long c = que.front() % 1000000;
            que.pop();
            if (r==tgt[0]&&c==tgt[1]) return true;//src reaches tgt in loop area
            if (visit.size()>=MAX_AREA) return true;//src escapes the loop area
            for (int d = 0; d < 4; ++d)
            {
                long rr = r + dir[d][0];
                long cc = c + dir[d][1];
                if (rr>=0&&rr<1000000&&cc>=0&&cc<1000000&&!blocks.count(rr*1000000+cc)&&!visit.count(rr*1000000+cc))
                {
                    visit.insert(rr*1000000+cc);
                    que.push(rr*1000000+cc);
                }
            }
        }
        return false;//src doesn't reach tgt in loop area and doesn't escape the loop area
    }
};
/*
EscapeInLarge2DMazeWithBlocks IsEscapePossible for blocks=[[0,1], [1,0]], src=[0, 0], tgt=[0, 2]: 0
 */
#endif
