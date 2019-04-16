#ifndef _SHORTEST_BRIDGE_BTW_2_ISLANDS_H
#define _SHORTEST_BRIDGE_BTW_2_ISLANDS_H
#include "Debug.h"
/*
Leetcode: Shortest Bridge
In a given 2D binary array A, there are two islands.  (An island is a 4-directionally connected group of 1s not connected to any other 1s.)
Now, we may change 0s to 1s so as to connect the two islands together to form 1 island.
Return the smallest number of 0s that must be flipped.  (It is guaranteed that the answer is at least 1.)
Example 1:
Input: [[0,1],[1,0]]
Output: 1
Example 2:
Input: [[0,1,0],[0,0,0],[0,0,1]]
Output: 2
Example 3:
Input: [[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
Output: 1
 */
class ShortestBridgeBtw2Islands
{
    const std::vector<std::vector<int>> dir = {{0,1},{1,0},{0,-1},{-1,0}};
public:
    ShortestBridgeBtw2Islands(){}
    ~ShortestBridgeBtw2Islands(){}

    int DFSplus2DirBFS(std::vector<std::vector<int>> && A)
    {
        Debug::Print2D<int>()(A, false);
        std::cout << "ShortestBridgeBtw2Islands DFSplsu2DirBFS for above grid: ";
        int N = A.size();
        int M = A[0].size();
        std::unordered_set<int> fwdLevel;
        std::unordered_set<int> bwdLevel;
        std::unordered_set<int> visit;
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < M; ++j)
            {
                if (A[i][j] == 1)
                {
                    if (fwdLevel.empty())
                    {
                        fwdLevel.insert(i*M+j);
                        DFS(A, i, j, fwdLevel);
                    }
                    else if (!fwdLevel.count(i*M+j) && bwdLevel.empty())
                    {
                        bwdLevel.insert(i*M+j);
                        DFS(A, i, j, bwdLevel);
                    }
                }
                if (!fwdLevel.empty() && !bwdLevel.empty()) break;
            }
            if (!fwdLevel.empty() && !bwdLevel.empty()) break;
        }
        for (auto & i : fwdLevel) visit.insert(i);
        for (auto & i : bwdLevel) visit.insert(i);
        int dist = 0;
        while (!fwdLevel.empty() && !bwdLevel.empty())
        {
            if (bwdLevel.size() < fwdLevel.size())
                std::swap(fwdLevel, bwdLevel);
            std::unordered_set<int> nxtLevel;
            for (auto & cur : fwdLevel)
            {
                int i = cur / M;
                int j = cur % M;
                for (const auto & d : dir)
                {
                    int ii = i + d[0];
                    int jj = j + d[1];
                    if (ii >= 0 && ii < N && jj >= 0 && jj < M)
                    {
                        if (bwdLevel.count(ii*M+jj))
                        {
                            std::cout << dist << std::endl;
                            return dist;
                        }
                        if (!visit.count(ii*M+jj))
                        {
                            visit.insert(ii*M+jj);
                            nxtLevel.insert(ii*M+jj);
                        }
                    }
                }
            }
            ++dist;
            std::swap(fwdLevel, nxtLevel);
        }
        return -1;
    }

    int DFSplusBFS(std::vector<std::vector<int>> && A)
    {
        Debug::Print2D<int>()(A, false);
        std::cout << "ShortestBridgeBtw2Islands DFSplsuBFS for above grid: ";
        int N = A.size();
        int M = A[0].size();
        std::unordered_set<int> visit;
        std::queue<int> que;
        bool found = false;
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < M; ++j)
            {
                if (A[i][j] == 1)
                {
                    visit.insert(i*M+j);
                    que.push(i*M+j);
                    DFS(A, i, j, visit, que);
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        //now visit and que contain the 1st found island (all 1s)
        int steps = 0;
        while (!que.empty())
        {
            int levelCount = que.size();
            while (levelCount-- > 0)
            {
                int i = que.front() / M;
                int j = que.front() % M;
                que.pop();
                for (const auto & d : dir)
                {
                    int ii = i + d[0];
                    int jj = j + d[1];
                    if (ii >= 0 && ii < N && jj >= 0 && jj < M && !visit.count(ii*M+jj))
                    {
                        if (A[ii][jj] == 1)//met 2nd island
                        {
                            std::cout << steps << std::endl;
                            return steps;
                        }
                        //otherwise, A[ii][jj]==0: expand to water
                        visit.insert(ii*M+jj);
                        que.push(ii*M+jj);
                    }
                }
            }
            ++steps;
        }
        return -1;
    }
private:
    void DFS(std::vector<std::vector<int>> & A, int i, int j, std::unordered_set<int> & visit)
    {
        int N = A.size();
        int M = A[0].size();
        for (const auto & d : dir)
        {
            int ii = i + d[0];
            int jj = j + d[1];
            if (ii >= 0 && ii < N && jj >= 0 && jj < M && A[ii][jj] == 1 && !visit.count(ii*M+jj))
            {
                visit.insert(ii*M+jj);
                DFS(A, ii, jj, visit);
            }
        }
    }
    void DFS(std::vector<std::vector<int>> & A, int i, int j, std::unordered_set<int> & visit, std::queue<int> & que)
    {
        int N = A.size();
        int M = A[0].size();
        for (const auto & d : dir)
        {
            int ii = i + d[0];
            int jj = j + d[1];
            if (ii >= 0 && ii < N && jj >= 0 && jj < M && A[ii][jj] == 1 && !visit.count(ii*M+jj))
            {
                visit.insert(ii*M+jj);
                que.push(ii*M+jj);
                DFS(A, ii, jj, visit, que);
            }
        }
    }
};
/*
[rY][cX]
Row#0	= 1, 1, 1, 1, 1
Row#1	= 1, 0, 0, 0, 1
Row#2	= 1, 0, 1, 0, 1
Row#3	= 1, 0, 0, 0, 1
Row#4	= 1, 1, 1, 1, 1

ShortestBridgeBtw2Islands DFSplsuBFS for above grid: 1
[rY][cX]
Row#0	= 1, 1, 1, 1, 1
Row#1	= 1, 0, 0, 0, 1
Row#2	= 1, 0, 1, 0, 1
Row#3	= 1, 0, 0, 0, 1
Row#4	= 1, 1, 1, 1, 1

ShortestBridgeBtw2Islands DFSplsu2DirBFS for above grid: 1
 */
#endif
