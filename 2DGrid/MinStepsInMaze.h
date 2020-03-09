/*Facebook*AmazonOA*/
#ifndef _MIN_STEPS_IN_MAZE_H
#define _MIN_STEPS_IN_MAZE_H
#include "Debug.h"
/*
Given a 2D integer array, where 0 represents an empty spot and 1 represents a wall.
Find the min steps from a start location to a destination location.
see also NonStoppingMaze.h
 */
class MinStepsInMaze
{
public:
    MinStepsInMaze(){}

    struct Greater
    {
        bool operator()(const std::pair<int,int> & a, const std::pair<int,int> & b) const
        {
            return a.first > b.first;
        }
    };
    int BFS_MinHeap(const std::vector<std::vector<int>> & maze, const std::vector<int> & start, const std::vector<int> & dest)
    {
        int N = maze.size();
        if (N == 0) return 0;
        int M = maze[0].size();
        std::vector<std::vector<int>> dist(N, std::vector<int>(M, INT_MAX));
        std::vector<std::vector<int>> dir({{-1,0},{1,0},{0,1},{0,-1}});
        std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, Greater> minHeap;
        //<dist from start, i*M+j> where dist is min on top

        minHeap.push({0, start[0]*M+start[1]});
        while (!minHeap.empty())
        {
            auto p = minHeap.top();
            minHeap.pop();
            int d = p.first;
            int i = p.second / M;
            int j = p.second % M;
            if (dist[i][j] < d) continue;//2nd check
            dist[i][j] = d;
            for (int k = 0; k < 4; ++k)
            {
                int ii = i + dir[k][0];
                int jj = j + dir[k][1];
                int dd = d + 1;
                if (ii >= 0 && ii < N && jj >= 0 && jj < M && maze[ii][jj] == 0
                    && dist[ii][jj] == INT_MAX)//1st check
                    minHeap.push({dd, ii*M+jj});
            }
        }

        Debug::Print2D<int>()(dist, false);
        Debug::Print2D<int>()(maze, false);
        int res = dist[dest[0]][dest[1]] == INT_MAX ? -1 : dist[dest[0]][dest[1]];
        std::cout << "MinStepsInMaze BFS_MinHeap for above maze from [" << Debug::ToStr1D<int>()(start) << "] to [" << Debug::ToStr1D<int>()(dest) << "]: " << res << std::endl;
        return res;
    }

    //Leetcode: Shortest Path in Binary Matrix
    //use minHeap to keep track of minDistFromStart of each node ONLY WHEN "edge distance between nodes are different"!
    //otherwise, just use a queue and keep track of levels
    int BFS_Queue(const std::vector<std::vector<int>> & maze, const std::vector<int> & start, const std::vector<int> & dest)
    {
        int N = maze.size();
        if (N == 0) return 0;
        int M = maze[0].size();
        std::vector<std::vector<int>> visit(N, std::vector<int>(M, 0));
        std::vector<std::vector<int>> dir({{-1,0},{1,0},{0,1},{0,-1}});
        std::queue<int> que;
        int dist = 0;
        que.push(start[0]*M+start[1]);
        visit[start[0]][start[1]] = 1;
        bool reach = false;
        while (!que.empty())
        {
            int levelCount = que.size();
            while (levelCount--)
            {
                auto p = que.front();
                que.pop();
                int i = p / M;
                int j = p % M;
                if (i == dest[0] && j == dest[1])
                {
                    reach = true;
                    break;
                }
                for (int k = 0; k < 4; ++k)
                {
                    int ii = i + dir[k][0];
                    int jj = j + dir[k][1];
                    if (ii >= 0 && ii < N && jj >= 0 && jj < M && maze[ii][jj] == 0 && !visit[ii][jj])
                    {
                        visit[ii][jj] = 1;
                        que.push(ii * M + jj);
                    }
                }
            }
            if (reach) break;
            ++dist;
        }
        if (!reach) dist = -1;

        Debug::Print2D<int>()(visit, false);
        Debug::Print2D<int>()(maze, false);
        std::cout << "MinStepsInMaze BFS_Queue for above maze from [" << Debug::ToStr1D<int>()(start) << "] to [" << Debug::ToStr1D<int>()(dest) << "]: " << dist << std::endl;
        return dist;
    }

    int BFS_Queue_2dir(const std::vector<std::vector<int>> & maze, const std::vector<int> & start, const std::vector<int> & dest)
    {
        return 0;
    }
};
/*
[rY][cX]
Row#0	= 0, 1, 2147483647, 19, 18, 17
Row#1	= 2147483647, 2, 2147483647, 20, 2147483647, 16
Row#2	= 4, 3, 4, 2147483647, 14, 15
Row#3	= 5, 2147483647, 2147483647, 12, 13, 14
Row#4	= 6, 7, 2147483647, 11, 2147483647, 15
Row#5	= 7, 8, 9, 10, 2147483647, 16

[rY][cX]
Row#0	= 0, 0, 1, 0, 0, 0
Row#1	= 1, 0, 1, 0, 1, 0
Row#2	= 0, 0, 0, 1, 0, 0
Row#3	= 0, 1, 1, 0, 0, 0
Row#4	= 0, 0, 1, 0, 1, 0
Row#5	= 0, 0, 0, 0, 1, 0

MinStepsInMaze BFS_MinHeap for above maze from [0, 0] to [5, 5]: 16
[rY][cX]
Row#0	= 1, 1, 0, 0, 0, 1
Row#1	= 0, 1, 0, 0, 0, 1
Row#2	= 1, 1, 1, 0, 1, 1
Row#3	= 1, 0, 0, 1, 1, 1
Row#4	= 1, 1, 0, 1, 0, 1
Row#5	= 1, 1, 1, 1, 0, 1

[rY][cX]
Row#0	= 0, 0, 1, 0, 0, 0
Row#1	= 1, 0, 1, 0, 1, 0
Row#2	= 0, 0, 0, 1, 0, 0
Row#3	= 0, 1, 1, 0, 0, 0
Row#4	= 0, 0, 1, 0, 1, 0
Row#5	= 0, 0, 0, 0, 1, 0

MinStepsInMaze BFS_Queue for above maze from [0, 0] to [5, 5]: 16
 */

class MinStepsInMazeLeftToRight //from leftmost column to rightmost column
{
public:
    MinStepsInMazeLeftToRight(){}

    int BFS_Queue(const std::vector<std::vector<int>> & maze)
    {
        int N = maze.size();
        if (N == 0) return 0;
        int M = maze[0].size();
        std::vector<std::vector<std::vector<int>>> parent(N, std::vector<std::vector<int>>(M, std::vector<int>(2, -1)));
        std::vector<std::vector<int>> visit(N, std::vector<int>(M, 0));
        std::vector<std::vector<int>> dir({{-1,0},{1,0},{0,1},{0,-1}});
        std::queue<int> que;
        int dist = 0;

        for (int i = 0; i < N; ++i)
            if (maze[i][0] == 0)
                que.push(i*M+0); //add all 0s in leftmost column to queue

        bool reach = false;
        std::vector<int> end;
        while (!que.empty())
        {
            int levelCount = que.size();
            for (int count = 0; count < levelCount; ++count)
            {
                auto p = que.front();
                que.pop();
                int i = p / M;
                int j = p % M;
                if (j == M-1)
                {
                    reach = true;
                    end = {i, j};
                    break;
                }
                for (int k = 0; k < 4; ++k)
                {
                    int ii = i + dir[k][0];
                    int jj = j + dir[k][1];
                    if (ii >= 0 && ii < N && jj >= 0 && jj < M && maze[ii][jj] == 0 && !visit[ii][jj])
                    {
                        visit[ii][jj] = 1;
                        que.push(ii * M + jj);
                        parent[ii][jj] = {i, j};
                    }
                }
            }
            if (reach) break;
            ++dist;
        }
        if (!reach) dist = -1;

        Debug::Print2D<int>()(visit, false);
        Debug::Print2D<int>()(maze, false);
        std::cout << "MinStepsInMaze BFS_Queue for above maze from left to right: " << dist << std::endl;

        if (reach)
        {
            std::vector<std::vector<int>> path;
            int d = dist;
            while (d--)
            {
                path.push_back(end);
                end = parent[end[0]][end[1]];
            }
            std::reverse(path.begin(), path.end());
            std::cout << "Path: " << Debug::ToStr1D<int>()(path) << std::endl;
        }

        return dist;
    }
};
/*
[rY][cX]
Row#0	= 0, 0, 0, 1, 0, 0
Row#1	= 0, 0, 1, 1, 1, 1
Row#2	= 0, 1, 1, 0, 0, 0
Row#3	= 1, 0, 1, 1, 1, 0
Row#4	= 1, 1, 0, 1, 0, 0
Row#5	= 1, 1, 1, 1, 1, 0

[rY][cX]
Row#0	= 0, 1, 1, 0, 1, 1
Row#1	= 1, 1, 0, 0, 0, 0
Row#2	= 1, 0, 0, 1, 1, 0
Row#3	= 0, 1, 0, 0, 0, 1
Row#4	= 0, 0, 1, 0, 1, 0
Row#5	= 0, 0, 0, 0, 0, 1

MinStepsInMaze BFS_Queue for above maze from left to right: 11
Path: [5,1], [5,2], [5,3], [4,3], [3,3], [3,2], [2,2], [1,2], [1,3], [1,4], [1,5]
 */
#endif
