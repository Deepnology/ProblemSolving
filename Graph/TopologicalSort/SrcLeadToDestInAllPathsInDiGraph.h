#ifndef _SRC_LEAD_TO_DEST_IN_ALL_PATHS_IN_DIGRAPH_H
#define _SRC_LEAD_TO_DEST_IN_ALL_PATHS_IN_DIGRAPH_H
#include "Debug.h"
/*
Leetcode: All Paths from Source Lead to Destination
Given the edges of a directed graph where edges[i] = [ai, bi] indicates there is an edge between nodes ai and bi
 , and two nodes source and destination of this graph
 , determine whether or not all paths starting from source eventually, end at destination, that is:
At least one path exists from the source node to the destination node
If a path exists from the source node to a node with no outgoing edges, then that node is equal to destination.
The number of possible paths from source to destination is a finite number.
Return true if and only if all roads from source lead to destination.
 */
class SrcLeadToDestInAllPathsInDiGraph
{
public:
    bool ReversedTopologicalSort(int n, std::vector<std::vector<int>>& edges, int source, int dest)
    {
        //Approach 2: Reversed Topological Sort
        std::vector<std::vector<int>> rdgraph(n, std::vector<int>());
        std::vector<int> outDegree(n, 0);
        for (auto & e : edges)
        {
            rdgraph[e[1]].push_back(e[0]);
            ++outDegree[e[0]];
        }
        if (outDegree[dest] > 0) return false;
        std::queue<int> que;
        que.push(dest);
        while (!que.empty())
        {
            int cur = que.front();
            que.pop();
            if (cur == source) return true;
            for (int nxt : rdgraph[cur])
            {
                --outDegree[nxt];
                if (outDegree[nxt] == 0)
                    que.push(nxt);
            }
        }
        return false;
        //note: if the graph contains a cycle, or a node that has an edge that doesn't lead to dest eventually, the reversed topo sort iteration will stop at that node
        //note: forward topo sort iteration can reach all leaf nodes where the paths don't contain a cycle, and can reach all first nodes that are on a cycle and stop there
    }

    bool DFS(int n, std::vector<std::vector<int>>& edges, int source, int dest)
    {
        //UnionFind cycle detection works for Undirected graph only
        //Approach 1: DFS
        //1. must have no cycle (otherwise there will be infinite num of paths)
        //2. source must be able to lead to dest in all paths
        std::vector<std::vector<int>> dgraph(n, std::vector<int>());
        for (auto & e : edges)
            dgraph[e[0]].push_back(e[1]);
        std::vector<int> visit(n, -1);//-1: nonVisited, 0: visited, 1: completed
        return !hasCycle(dgraph, source, visit) && canReach(dgraph, source, dest);
    }
private:
    bool hasCycle(std::vector<std::vector<int>> & dgraph, int cur, std::vector<int> & visit)
    {
        visit[cur] = 0;//mark visited
        for (auto nxt : dgraph[cur])
        {
            if (visit[nxt] == -1)//non-visited
            {
                if (hasCycle(dgraph, nxt, visit))
                    return true;
            }
            else if (visit[nxt] == 0)//non-completed
                return true;
        }
        visit[cur] = 1;//mark completed
        return false;
    }
    bool canReach(std::vector<std::vector<int>> & dgraph, int cur, int dest)
    {
        if (dgraph[cur].size() == 0)
        {
            if (cur == dest) return true;
            else return false;
        }
        for (auto nxt : dgraph[cur])
            if (!canReach(dgraph, nxt, dest))
                return false;
        return true;
    }
};
#endif
