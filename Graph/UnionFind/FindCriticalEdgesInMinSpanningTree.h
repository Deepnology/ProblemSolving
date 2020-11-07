#ifndef _FIND_CRITICAL_EDGES_IN_MIN_SPANNING_TREE_H
#define _FIND_CRITICAL_EDGES_IN_MIN_SPANNING_TREE_H
#include "Debug.h"
/*
Leetcode: Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree
Given a weighted undirected connected graph with n vertices numbered from 0 to n-1, and an array edges where edges[i] = [fromi, toi, weighti] represents a bidirectional and weighted edge between nodes fromi and toi.
A minimum spanning tree (MST) is a subset of the edges of the graph that connects all vertices without cycles and with the minimum possible total edge weight.
Find all the critical and pseudo-critical edges in the minimum spanning tree (MST) of the given graph.
An MST edge whose deletion from the graph would cause the MST weight to increase is called a critical edge.
A pseudo-critical edge, on the other hand, is that which can appear in some MSTs but not all.
Note that you can return the indices of the edges in any order.
 */
class FindCriticalEdgesInMinSpanningTree
{
public:
    std::vector<std::vector<int>> UseUnionFind(int n, std::vector<std::vector<int>> & edges)
    {
        for (auto i = 0; i < edges.size(); ++i)
            edges[i].push_back(i);//now edges[i]: [from,to,weight,index]
        std::sort(edges.begin(), edges.end(), [](const std::vector<int> & a, const std::vector<int> & b)
        {
            return a[2] < b[2];
        });
        int mstWeights = MSTweights(n, edges);
        std::vector<int> critical;
        std::vector<int> pseudoCritical;
        for (auto i = 0; i < edges.size(); ++i)
        {
            if (mstWeights < MSTweights(n, edges, i, -1))
                critical.push_back(edges[i][3]);//remove edge will increase total weights or not able to form MST
            else if (mstWeights == MSTweights(n, edges, -1, i))
                pseudoCritical.push_back(edges[i][3]);//force include edge in MST will not increase total weights
        }
        return {critical, pseudoCritical};
    }
private:
    int MSTweights(int n, std::vector<std::vector<int>> & edges, int excludeEdgeIdx = -1, int includeEdgeIdx = -1)
    {
        //edges:[from,to,weight,index], sorted by weights in incr order
        std::vector<int> chdToP;
        for (int i = 0; i < n; ++i)
            chdToP.push_back(i);
        int weights = 0;
        if (includeEdgeIdx != -1)
        {
            int root1 = edges[includeEdgeIdx][0];
            int root2 = edges[includeEdgeIdx][1];
            weights += edges[includeEdgeIdx][2];
            chdToP[root2] = root1;
        }
        for (auto i = 0; i < edges.size(); ++i)
        {
            if (i == includeEdgeIdx || i == excludeEdgeIdx) continue;
            int root1 = Find(chdToP, edges[i][0]);
            int root2 = Find(chdToP, edges[i][1]);
            if (root1 != root2)
            {
                weights += edges[i][2];
                chdToP[root2] = root1;
            }
        }
        int root = Find(chdToP, 0);
        for (auto i = 1; i < n; ++i)
            if (Find(chdToP, i) != root)
                return INT_MAX; //at least 2 connected components
        return weights;
    }
    int Find(std::vector<int> & chdToP, int cur)
    {
        while (chdToP[cur] != cur)
        {
            chdToP[cur] = chdToP[chdToP[cur]];
            cur = chdToP[cur];
        }
        return cur;
    }
};
#endif
