#ifndef _SHORTEST_PATH_W_ALT_COLORS_IN_GRAPH_H
#define _SHORTEST_PATH_W_ALT_COLORS_IN_GRAPH_H
#include "Debug.h"
/*
Leetcode: Shortest Path with Alternating Colors
Consider a directed graph, with nodes labelled 0, 1, ..., n-1.
In this graph, each edge is either red or blue, and there could be self-edges or parallel edges.
Each [i, j] in red_edges denotes a red directed edge from node i to node j.
Similarly, each [i, j] in blue_edges denotes a blue directed edge from node i to node j.
Return an array answer of length n, where each answer[X] is the length of the shortest path from node 0 to node X
 such that the edge colors alternate along the path (or -1 if such a path doesn't exist).
Example 1:
Input: n = 3, red_edges = [[0,1],[1,2]], blue_edges = []
Output: [0,1,-1]
Example 2:
Input: n = 3, red_edges = [[0,1]], blue_edges = [[2,1]]
Output: [0,1,-1]
Example 3:
Input: n = 3, red_edges = [[1,0]], blue_edges = [[2,1]]
Output: [0,-1,-1]
Example 4:
Input: n = 3, red_edges = [[0,1]], blue_edges = [[1,2]]
Output: [0,1,2]
Example 5:
Input: n = 3, red_edges = [[0,1],[0,2]], blue_edges = [[1,0]]
Output: [0,1,1]
 */
class ShortestPathWAltColorsInGraph
{
public:
    std::vector<int> BFS(int N, std::vector<std::vector<int>> && red_edges, std::vector<std::vector<int>> && blue_edges)
    {
        std::vector<std::vector<std::vector<int>>> adjList(N, std::vector<std::vector<int>>());
        for (auto & e : red_edges)
            adjList[e[0]].push_back({e[1],0});//0 for red edge
        for (auto & e : blue_edges)
            adjList[e[0]].push_back({e[1],1});//1 for blue edge
        std::vector<std::vector<int>> visit(N, std::vector<int>({-1,-1}));
        //visit[i][c]: shortest length from node-0 to node-i ending w/ c color
        std::queue<std::vector<int>> que;//<node, color>
        que.push({0,0});//<0, red>
        que.push({0,1});//<0, blue>
        visit[0][0] = 0;
        visit[0][1] = 0;
        while (!que.empty())
        {
            int levelCount = que.size();
            while (levelCount-->0)
            {
                auto v = que.front(); que.pop();//<node, color>
                for (auto & nxt : adjList[v[0]])
                {
                    if (nxt[1]==v[1] || visit[nxt[0]][nxt[1]] != -1)//same color or visited
                        continue;
                    visit[nxt[0]][nxt[1]] = 1 + visit[v[0]][v[1]];
                    que.push({nxt[0],nxt[1]});
                }
            }
        }
        std::vector<int> res;
        for (auto & v : visit)
        {
            //v[0]: shortest len from node-0 to this node ending w/ red edge
            //v[1]: shortest len from node-0 to this node ending w/ blue edge
            std::sort(v.begin(), v.end());//shorter len first
            res.push_back(v[0]!=-1?v[0]:v[1]);
        }

        std::cout << "ShortestPathWAltColorsInGraph BFS for " << N << " nodes, redEdge=[" << Debug::ToStr1D<int>()(red_edges) << "], blueEdge=[" << Debug::ToStr1D<int>()(blue_edges) << "]: " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }
};
/*
ShortestPathWAltColorsInGraph BFS for 3 nodes, redEdge=[[0,1], [0,2]], blueEdge=[[1,0]]: 0, 1, 1
 */
#endif
