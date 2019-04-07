#ifndef _SHORTEST_PATH_VISIT_ALL_NODES_IN_GRAPH_H
#define _SHORTEST_PATH_VISIT_ALL_NODES_IN_GRAPH_H
#include "Debug.h"
/*
Leetcode: Shortest Path Visiting All Nodes
An undirected, connected graph of N nodes (labeled 0, 1, 2, ..., N-1) is given as graph.
graph.length = N, and j != i is in the list graph[i] exactly once, if and only if nodes i and j are connected.
Return the length of the shortest path that visits every node.
You may start and stop at any node, you may revisit nodes multiple times, and you may reuse edges.
Example 1:
Input: [[1,2,3],[0],[0],[0]]
Output: 4
Explanation: One possible path is [1,0,2,0,3]
Example 2:
Input: [[1],[0,2,4],[1,3,4],[2],[1,2]]
Output: 4
Explanation: One possible path is [0,1,4,2,3]
 */
class ShortestPathVisitAllNodesInGraph
{
public:
    ShortestPathVisitAllNodesInGraph(){}
    ~ShortestPathVisitAllNodesInGraph(){}

    void Test(std::vector<std::vector<int>> && graph)
    {
        int res1 = BFS(graph);
        int res2 = BFS2(graph);
        std::cout << "ShortestPathVisitAllNodesInGraph BFS, BFS2 for [" << Debug::ToStr1D<int>()(graph) << "]: " << res1 << "," << res2 << std::endl;
    }

    int BFS(std::vector<std::vector<int>> & graph)
    {
        int N = graph.size();//1<=N<=12
        int finalState = (1<<N) - 1;
        std::vector<std::unordered_set<int>> visit(N);//<node,visitedStates>
        std::queue<std::pair<int,int>> que;//<curNode,curState>
        for (int i = 0; i < N; ++i)
        {
            visit[i].insert(1<<i);
            que.push({i,1<<i});//starting from all nodes
        }
        int steps = 0;
        while (!que.empty())
        {
            int levelCount = que.size();
            while (levelCount-- > 0)
            {
                int curNode = que.front().first;
                int curState = que.front().second;
                que.pop();
                if (curState == finalState)
                    return steps;
                for (int nxtNode : graph[curNode])
                {
                    int nxtState = curState | (1<<nxtNode);
                    if (visit[nxtNode].count(nxtState)) continue;
                    visit[nxtNode].insert(nxtState);
                    que.push({nxtNode,nxtState});
                }
            }
            ++steps;
        }
        return -1;
    }

    int BFS2(std::vector<std::vector<int>> & graph)
    {
        int N = graph.size();//1<=N<=12
        unsigned int finalState = (1<<N) - 1;
        std::unordered_set<unsigned int> visit;//higher 16 bits: node idx, lower 16 bits: state
        std::queue<unsigned int> que;//higher 16 bits: node idx, lower 16 bits: state
        for (int i = 0; i < N; ++i)
        {
            int cur = (1<<(i+16)) | (1<<i);
            visit.insert(cur);
            que.push(cur);//starting from all nodes
        }
        int steps = 0;
        while (!que.empty())
        {
            int levelCount = que.size();
            while (levelCount-- > 0)
            {
                int curNode = log2(que.front()>>16);//higher 16 bits
                unsigned int curState = que.front() & ((1<<16)-1);//lower 16 bits
                que.pop();
                if (curState == finalState)
                    return steps;
                for (int nxtNode : graph[curNode])
                {
                    unsigned int nxt = (1<<(nxtNode+16)) | (curState|(1<<nxtNode));
                    if (visit.count(nxt)) continue;
                    visit.insert(nxt);
                    que.push(nxt);
                }
            }
            ++steps;
        }
        return -1;
    }
};
/*
ShortestPathVisitAllNodesInGraph BFS, BFS2 for [[1,2,3], [0], [0], [0]]: 4,4
ShortestPathVisitAllNodesInGraph BFS, BFS2 for [[1], [0,2,4], [1,3,4], [2], [1,2]]: 4,4
 */
#endif
