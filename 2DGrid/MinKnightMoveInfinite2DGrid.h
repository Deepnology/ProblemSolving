#ifndef _MIN_KNIGHT_MOVE_INFINITE_2D_GRID_H
#define _MIN_KNIGHT_MOVE_INFINITE_2D_GRID_H
#include "Debug.h"
/*
Leetcode: Minimum Knight Moves
In an infinite chess board with coordinates from -infinity to +infinity, you have a knight at square [0, 0].
A knight has 8 possible moves it can make, as illustrated below. Each move is two squares in a cardinal direction, then one square in an orthogonal direction.
Return the minimum number of steps needed to move the knight to the square [x, y].  It is guaranteed the answer exists.
Example 1:
Input: x = 2, y = 1
Output: 1
Explanation: [0, 0] → [2, 1]
Example 2:
Input: x = 5, y = 5
Output: 4
Explanation: [0, 0] → [2, 1] → [4, 2] → [3, 4] → [5, 5]
see also LMoveIdxSeqCombinationInMatrix.h
 */
class MinKnightMoveInfinite2DGrid
{
public:
    struct Greater
    {
        bool operator()(const std::vector<int>&a, const std::vector<int>&b) const
        {
            return a[3] > b[3];
        }
    };
    int AStarSearch(int x, int y)
    {
        x = std::abs(x); y = std::abs(y);//switch (x,y) to 1st quadrant
        std::vector<std::vector<int>> dir = {{1,2},{2,1},{2,-1},{1,-2},{-1,2},{-2,1},{-1,-2},{-2,-1}};
        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, Greater> minHeap;//<curX,curY,step,score=3*step+dist(curX,curY,tgtX,tgtY)>
        minHeap.push({0,0,0,0});//score of (0,0) doesn't matter, just use 0
        std::unordered_map<int,std::unordered_set<int>> visit;
        visit[0].insert(0);
        while (!minHeap.empty())
        {
            int curX = minHeap.top()[0];
            int curY = minHeap.top()[1];
            int step = minHeap.top()[2];
            minHeap.pop();
            if (curX==x && curY==y)
            {
                std::cout << "MinKKnightMoveInfinite2DGrid AStarSearch from (0,0) to (" << x << "," << y << "): " << step << std::endl;
                return step;
            }
            for (int d = 0; d < 8; ++d)
            {
                int nxtX = curX + dir[d][0];
                int nxtY = curY + dir[d][1];
                if (nxtX < -1 || nxtY < -1) continue;
                if (!visit.count(nxtX) || !visit[nxtX].count(nxtY))
                {
                    visit[nxtX].insert(nxtY);
                    int dist = (int)std::sqrt((nxtX-x)*(nxtX-x)+(nxtY-y)*(nxtY-y));
                    int score = 3*step + dist;
                    minHeap.push({nxtX,nxtY,step+1,score});
                }
            }
        }
        return -1;
    }

    int BidirectionalBFS(int x, int y)
    {
        if (x==0 && y==0) return 0;
        x = std::abs(x); y = std::abs(y);//switch (x,y) to 1st quadrant
        std::unordered_map<int,std::unordered_set<int>> fwd;
        fwd[0].insert(0);
        std::unordered_map<int,std::unordered_set<int>> bwd;
        bwd[x].insert(y);
        std::unordered_map<int,std::unordered_set<int>> visit;
        visit[0].insert(0);
        visit[x].insert(y);
        int dist = 0;
        std::vector<std::vector<int>> dir = {{1,2},{2,1},{2,-1},{1,-2},{-1,2},{-2,1},{-1,-2},{-2,-1}};
        while (!fwd.empty() && !bwd.empty())
        {
            if (bwd.size() < fwd.size())
                std::swap(fwd,bwd);
            std::unordered_map<int,std::unordered_set<int>> nxtLevel;
            for (auto & itr : fwd)
            {
                int curX = itr.first;
                for (auto & curY : itr.second)
                {
                    for (int d = 0; d < 8; ++d)
                    {
                        int nxtX = curX + dir[d][0];
                        int nxtY = curY + dir[d][1];
                        if (nxtX < -1 || nxtY < -1) continue;
                        //limit (x,y) to 1st quadrant but must allow x=-1 or y=-1
                        //ex:(0,0) to (1,1) number of steps is 2 which needs to step on either x=-1 or y=-1
                        if (bwd.count(nxtX) && bwd[nxtX].count(nxtY))
                        {
                            std::cout << "MinKKnightMoveInfinite2DGrid BidirectionalBFS from (0,0) to (" << x << "," << y << "): " << dist+1 << std::endl;
                            return dist + 1;
                        }
                        if (!visit.count(nxtX) || !visit[nxtX].count(nxtY))
                        {
                            visit[nxtX].insert(nxtY);
                            nxtLevel[nxtX].insert(nxtY);
                        }
                    }
                }
            }
            ++dist;
            std::swap(fwd, nxtLevel);
        }
        return -1;
    }
};
/*
MinKKnightMoveInfinite2DGrid AStarSearch from (0,0) to (5,5): 4
MinKKnightMoveInfinite2DGrid BidirectionalBFS from (0,0) to (5,5): 4
 */
#endif
