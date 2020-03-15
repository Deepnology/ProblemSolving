#ifndef _MIN_COST_CONNECT_ALL_NODES_IN_GRAPH_H
#define _MIN_COST_CONNECT_ALL_NODES_IN_GRAPH_H
#include "Debug.h"
/*
Leetcode: Connecting Cities with Minimum Cost
There are N cities numbered from 1 to N.
You are given connections, where each connections[i] = [city1, city2, cost] represents the cost to connect city1 and city2 together.
(A connection is bidirectional: connecting city1 and city2 is the same as connecting city2 and city1.)
Return the minimum cost so that for every pair of cities, there exists a path of connections (possibly of length 1) that connects those two cities together.
The cost is the sum of the connection costs used. If the task is impossible, return -1.
Example 1:
Input: N = 3, connections = [[1,2,5],[1,3,6],[2,3,1]]
Output: 6
Explanation:
Choosing any 2 edges will connect all cities so we choose the minimum 2.
Example 2:
Input: N = 4, connections = [[1,2,3],[3,4,4]]
Output: -1
Explanation:
There is no way to connect all cities even if all edges are used.
 */
class MinCostConnectAllNodesInGraph
{
public:
    MinCostConnectAllNodesInGraph(){}

    int UnionFind(int N, std::vector<std::vector<int>> && connections)
    {
        std::sort(connections.begin(), connections.end(), [](std::vector<int> & a, std::vector<int> & b)->bool
        {
            return a[2] < b[2];
        });
        int cost = 0;
        std::vector<int> chdToP(N+1, 0);//ignore index of 0
        for (int i = 1; i <= N; ++i)
            chdToP[i] = i;
        int numComponents = N;
        for (auto & v : connections) //construct a min spanning tree
        {
            int root1 = Find(chdToP, v[0]);
            int root2 = Find(chdToP, v[1]);
            if (root1 != root2)
            {
                chdToP[root2] = root1;
                --numComponents; //decrement num connected components
                cost += v[2];
            }
        }
        int res = numComponents == 1 ? cost : -1;

        std::cout << "MinCostConnectAllNodesInGraph UnionFind for " << N << ", [" << Debug::ToStr1D<int>()(connections) << "]: " << res << std::endl;
        return res;
    }
private:
    int Find(std::vector<int> & chdToP, int chd)
    {
        int cur = chd;
        while (chdToP[cur] != cur)
        {
            chdToP[cur] = chdToP[chdToP[cur]];
            cur = chdToP[cur];
        }
        return cur;
    }
};
/*
Amazon OA
Given an undirected graph with n nodes labeled 1..n.
Some of the nodes are already connected.
The i-th edge connects nodes edges[i][0] and edges[i][1] together.
Your task is to augment this set of edges with additional edges to connect all the nodes.
Find the minimum cost to add new edges between the nodes such that all the nodes are accessible from each other.
Input:
n, an int representing the total number of nodes.
edges, a list of integer pair representing the nodes already connected by an edge.
newEdges, a list where each element is a triplet representing the pair of nodes between which an edge can be added and the cost of addition, respectively
 (e.g. [1, 2, 5] means to add an edge between node 1 and 2, the cost would be 5).
Example 1:
Input: n = 6, edges = [[1, 4], [4, 5], [2, 3]], newEdges = [[1, 2, 5], [1, 3, 10], [1, 6, 2], [5, 6, 5]]
Output: 7
Explanation:
There are 3 connected components [1, 4, 5], [2, 3] and [6].
We can connect these components into a single component by connecting node 1 to node 2 and node 1 to node 6 at a minimum cost of 5 + 2 = 7.
 */
class MinCostConnectAllNodesInGraph2
{
public:
    MinCostConnectAllNodesInGraph2(){}

    struct CmpGreater
    {
        bool operator()(const std::vector<int> & a, const std::vector<int> & b) const
        {
            return a[2] > b[2];
        }
    };

    int UnionFind(int N, std::vector<std::vector<int>> && edges, std::vector<std::vector<int>> && newEdges)
    {
        //1. Union all edges
        std::vector<int> chdToP(N+1, 0);
        for (int i = 1; i <= N; ++i)
            chdToP[i] = i;
        int numComponents = N;
        for (auto & v : edges)
        {
            int root1 = Find(chdToP, v[0]);
            int root2 = Find(chdToP, v[1]);
            if (root1 != root2)
            {
                chdToP[root2] = root1;
                --numComponents; //decrement num connected components
            }
        }
        std::cout << numComponents << std::endl;
        //2. add new edges to connect until only 1 connected component left
        int cost = 0;
        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, CmpGreater> minHeap(newEdges.begin(), newEdges.end());
        while (numComponents > 1 && !minHeap.empty())
        {
            auto v = minHeap.top();
            minHeap.pop();
            int root1 = Find(chdToP, v[0]);
            int root2 = Find(chdToP, v[1]);
            if (root1 != root2)
            {
                chdToP[root2] = root1;
                --numComponents;
                cost += v[2];
            }
        }
        int res = numComponents == 1 ? cost : -1;

        std::cout << "MinCostConnectAllNodesInGraph2 UnionFind for " << N << ", [" << Debug::ToStr1D<int>()(edges) << "], [" << Debug::ToStr1D<int>()(newEdges) << "]: " << res << std::endl;
        return res;
    }

private:
    int Find(std::vector<int> & chdToP, int chd)
    {
        int cur = chd;
        while (chdToP[cur] != cur)
        {
            chdToP[cur] = chdToP[chdToP[cur]];
            cur = chdToP[cur];
        }
        return cur;
    }
};
/*
MinCostConnectAllNodesInGraph UnionFind for 3, [[2,3,1], [1,2,5], [1,3,6]]: 6
3
MinCostConnectAllNodesInGraph2 UnionFind for 6, [[1,4], [4,5], [2,3]], [[1,2,5], [1,3,10], [1,6,2], [5,6,5]]: 7
 */
/*
Amazon OA
There's an undirected connected graph with n nodes labeled 1..n.
But some of the edges has been broken disconnecting the graph.
Find the minimum cost to repair the edges so that all the nodes are once again accessible from each other.
Input:
n, an int representing the total number of nodes.
edges, a list of integer pair representing the nodes connected by an edge.
edgesToRepair, a list where each element is a triplet representing the pair of nodes between which an edge is currently broken and the cost of repearing that edge, respectively
 (e.g. [1, 2, 12] means to repear an edge between nodes 1 and 2, the cost would be 12).
Example 1:
Input: n = 5, edges = [[1, 2], [2, 3], [3, 4], [4, 5], [1, 5]], edgesToRepair = [[1, 2, 12], [3, 4, 30], [1, 5, 8]]
Output: 20
Explanation:
There are 3 connected components due to broken edges: [1], [2, 3] and [4, 5].
We can connect these components into a single component by repearing the edges between nodes 1 and 2, and nodes 1 and 5 at a minimum cost 12 + 8 = 20.
Example 2:
Input: n = 6, edges = [[1, 2], [2, 3], [4, 5], [3, 5], [1, 6], [2, 4]], edgesToRepair = [[1, 6, 410], [2, 4, 800]]
Output: 410
Example 3:
Input: n = 6, edges = [[1, 2], [2, 3], [4, 5], [5, 6], [1, 5], [2, 4], [3, 4]], edgesToRepair = [[1, 5, 110], [2, 4, 84], [3, 4, 79]]
Output: 79
 */
class MinCostRepairAllEdgesInGraph
{
public:
    MinCostRepairAllEdgesInGraph(){}
    struct CmpGreater
    {
        bool operator()(const std::vector<int> & a, const std::vector<int> & b) const
        {
            return a[2] > b[2];
        }
    };
    int UnionFind(int N, std::vector<std::vector<int>> && edges, std::vector<std::vector<int>> && edgesToRepair)
    {
        //1. filter out all good edges
        std::unordered_map<std::string, std::vector<int>> goodEdges;
        for (auto & v : edges)
        {
            if (v[0] > v[1]) std::swap(v[0], v[1]);
            goodEdges.insert({std::to_string(v[0])+","+std::to_string(v[1]), v});
        }
        for (auto & v : edgesToRepair)
        {
            if (v[0] > v[1]) std::swap(v[0], v[1]);
            goodEdges.erase(std::to_string(v[0])+","+std::to_string(v[1]));
        }
        //2. union all good edges
        std::vector<int> chdToP(N+1, 0);
        for (int i = 0; i <= N; ++i)
            chdToP[i] = i;
        int numComponents = N;
        for (auto & p : goodEdges)
        {
            int root1 = Find(chdToP, p.second[0]);
            int root2 = Find(chdToP, p.second[1]);
            if (root1 != root2)
            {
                chdToP[root2] = root1;
                --numComponents;
            }
        }
        std::cout << numComponents << std::endl;
        //3. add repaired edges to connect until only 1 connected component left
        int cost = 0;
        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, CmpGreater> minHeap(edgesToRepair.begin(), edgesToRepair.end());
        while (numComponents > 1 && !minHeap.empty())
        {
            auto v = minHeap.top();
            minHeap.pop();
            int root1 = Find(chdToP, v[0]);
            int root2 = Find(chdToP, v[1]);
            if (root1 != root2)
            {
                chdToP[root2] = root1;
                --numComponents;
                cost += v[2];
            }
        }

        int res = numComponents == 1 ? cost : -1;

        std::cout << "MinCostRepairAllEdgesInGraph UnionFind for " << N << ", [" << Debug::ToStr1D<int>()(edges) << "], [" << Debug::ToStr1D<int>()(edgesToRepair) << "]: " << res << std::endl;
        return res;
    }

private:
    int Find(std::vector<int> & chdToP, int chd)
    {
        int cur = chd;
        while (chdToP[cur] != cur)
        {
            chdToP[cur] = chdToP[chdToP[cur]];
            cur = chdToP[cur];
        }
        return cur;
    }
};
/*
3
MinCostRepairAllEdgesInGraph UnionFind for 5, [[1,2], [2,3], [3,4], [4,5], [1,5]], [[1,2,12], [3,4,30], [1,5,8]]: 20
2
MinCostRepairAllEdgesInGraph UnionFind for 6, [[1,2], [2,3], [4,5], [3,5], [1,6], [2,4]], [[1,6,410], [2,4,800]]: 410
2
MinCostRepairAllEdgesInGraph UnionFind for 6, [[1,2], [2,3], [4,5], [5,6], [1,5], [2,4], [3,4]], [[1,5,110], [2,4,84], [3,4,79]]: 79
 */
#endif
