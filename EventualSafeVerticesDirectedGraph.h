#ifndef _EVENTUAL_SAFE_VERTICES_DIRECTED_GRAPH_H
#define _EVENTUAL_SAFE_VERTICES_DIRECTED_GRAPH_H
#include "Debug.h"
/*
Leetcode: Find Eventual Safe States
In a directed graph, we start at some node and every turn, walk along a directed edge of the graph.
If we reach a node that is terminal (that is, it has no outgoing directed edges), we stop.
Now, say our starting node is eventually safe if and only if we must eventually walk to a terminal node.
More specifically, there exists a natural number K so that for any choice of where to walk, we must have stopped at a terminal node in less than K steps.
Which nodes are eventually safe?  Return them as an array in sorted order.
The directed graph has N nodes with labels 0, 1, ..., N-1, where N is the length of graph.
The graph is given in the following form: graph[i] is a list of labels j such that (i, j) is a directed edge of the graph.
Example:
Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
Output: [2,4,5,6]
Here is a diagram of the above graph.

3---->0       6
 ^   / \
  \ v   v
   1--->2     4
         \   /
          v v
           5

visit:    0,1,2,5,3,4,6
complete: 5,2,4,6
 */
class EventualSafeVerticesDirectedGraph
{
public:
    EventualSafeVerticesDirectedGraph(){}

    std::vector<int> FindCompletionVertices(const std::vector<std::vector<int>> & graph)
    {
        std::vector<int> res;
        std::unordered_set<int> visit;
        std::unordered_set<int> completion;
        int N = graph.size();
        for (int i = 0; i < N; ++i)
            if (!visit.count(i))
                isConnectedToCycleRecur(graph, i, visit, completion);
        for (int i = 0; i < N; ++i)
            if (completion.count(i))
                res.push_back(i);
        Debug::Print2D<int>()(graph, false);
        std::cout << "EventualSafeVerticesDirectedGraph FindCompletionVertices for above graph: " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }
    bool isConnectedToCycleRecur(const std::vector<std::vector<int>> & directed, int cur, std::unordered_set<int> & visit, std::unordered_set<int> & completion)
    {
        //std::cout << "visit:" << cur << std::endl;
        visit.insert(cur);
        for (const auto & nxt : directed[cur])
            if (!visit.count(nxt))
            {
                if (isConnectedToCycleRecur(directed, nxt, visit, completion))
                    return true;
            }
            else
            {
                if (!completion.count(nxt))
                    return true;
            }
        //std::cout << "complete:" << cur << std::endl;
        completion.insert(cur);
        return false;
    }
};
/*
[rY][cX]
Row#0	= 1, 2
Row#1	= 2, 3
Row#2	= 5,
Row#3	= 0,
Row#4	= 5,
Row#5	=  ,
Row#6	=  ,

EventualSafeVerticesDirectedGraph FindCompletionVertices for above graph: 2, 4, 5, 6
 */
#endif
