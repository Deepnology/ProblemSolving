#ifndef _REMOVE_1_MAL_NODE_MINIMIZE_INFECTED_NODES_H
#define _REMOVE_1_MAL_NODE_MINIMIZE_INFECTED_NODES_H
#include "Debug.h"
/*
Leetcode: Minimize Malware Spread
In a network of nodes, each node i is directly connected to another node j if and only if graph[i][j] = 1.
Some nodes initial are initially infected by malware.
Whenever two nodes are directly connected and at least one of those two nodes is infected by malware, both nodes will be infected by malware.
This spread of malware will continue until no more nodes can be infected in this manner.
Suppose M(initial) is the final number of nodes infected with malware in the entire network, after the spread of malware stops.
We will remove one node from the initial list.
Return the node that if removed, would minimize M(initial).
If multiple nodes could be removed to minimize M(initial), return such a node with the smallest index.
Note that if a node was removed from the initial list of infected nodes, it may still be infected later as a result of the malware spread.
Example 1:
Input: graph = [[1,1,0],[1,1,0],[0,0,1]], initial = [0,1]
Output: 0
Example 2:
Input: graph = [[1,0,0],[0,1,0],[0,0,1]], initial = [0,2]
Output: 0
Example 3:
Input: graph = [[1,1,1],[1,1,1],[1,1,1]], initial = [1,2]
Output: 1

Leetcode: Minimize Malware Spread II
(This problem is the same as Minimize Malware Spread, with the differences bolded.)
In a network of nodes, each node i is directly connected to another node j if and only if graph[i][j] = 1.
Some nodes initial are initially infected by malware.
Whenever two nodes are directly connected and at least one of those two nodes is infected by malware, both nodes will be infected by malware.
This spread of malware will continue until no more nodes can be infected in this manner.
Suppose M(initial) is the final number of nodes infected with malware in the entire network, after the spread of malware stops.
We will remove one node from the initial list, completely removing it and any connections from this node to any other node.
Return the node that if removed, would minimize M(initial).
If multiple nodes could be removed to minimize M(initial), return such a node with the smallest index.
Example 1:
Input: graph = [[1,1,0],[1,1,0],[0,0,1]], initial = [0,1]
Output: 0
Example 2:
Input: graph = [[1,1,0],[1,1,1],[0,1,1]], initial = [0,1]
Output: 1
Example 3:
Input: graph = [[1,1,0,0],[1,1,1,0],[0,1,1,1],[0,0,1,1]], initial = [0,1]
Output: 1
 */
class Remove1MalNodeMinimizeInfectedNodes
{
public:
    Remove1MalNodeMinimizeInfectedNodes(){}

    int DFS(std::vector<std::vector<int>> && graph, std::vector<int> && initial)
    {
        //DFS: O(N^3) time
        std::sort(initial.begin(), initial.end());
        int N = graph.size();
        int res = 0;
        int minInfected = INT_MAX;
        for (int & i : initial)
        {
            //now exclude i, collect num of nodes infected
            std::unordered_set<int> visit;
            for (int & j : initial)
            {
                if (i == j) continue;
                if (!visit.count(j))
                {
                    visit.insert(j);
                    DFS(graph, j, visit);
                }
            }
            if (visit.size() < minInfected)
            {
                minInfected = visit.size();
                res = i;
            }
        }

        Debug::Print2D<int>()(graph, false);
        std::cout << "Remove1MalNodeMinimizeInfectedNodes DFS for MalNodes=[" << Debug::ToStr1D<int>()(initial) << "]: " << res << std::endl;
        return res;
    }

    int UnionFind(std::vector<std::vector<int>> && graph, std::vector<int> && initial)
    {
        //union find: O(N^2) time
        int N = graph.size();
        std::vector<int> chdToP(N);
        for (int i = 0; i < N; ++i)
            chdToP[i] = i;
        std::vector<int> nodeCount(N, 1);//node count in each connected component
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
            {
                if (graph[i][j] == 1)
                {
                    int root1 = Find(chdToP, i);
                    int root2 = Find(chdToP, j);
                    if (root2 != root1)
                    {
                        chdToP[root2] = root1;
                        nodeCount[root1] += nodeCount[root2];
                    }
                }
            }
        std::vector<int> malNodeCount(N, 0);//malware node count in each connected component
        for (auto & i : initial)
            ++malNodeCount[Find(chdToP, i)];
        std::sort(initial.begin(), initial.end());
        int res;
        int maxNonInfected = 0;
        for (auto & i : initial)
        {
            int root = Find(chdToP, i);
            if (malNodeCount[root] == 1)//candidate malware node whose component has only 1 maleware node
            {
                if (maxNonInfected < nodeCount[root])
                {
                    maxNonInfected = nodeCount[root];
                    res = i;
                }
            }
        }
        res = maxNonInfected == 0 ? initial[0] : res;
        //maxNonInfected==0: no such candidate malware node whose component has only 1 maleware node, just return the malware node with min idx
        //in this case, all components will have 0 or at least 2 malware nodes
        //so there is no difference to remove just 1 malware node


        Debug::Print2D<int>()(graph, false);
        std::cout << "Remove1MalNodeMinimizeInfectedNodes UnionFind for MalNodes=[" << Debug::ToStr1D<int>()(initial) << "]: " << res << std::endl;
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
    void DFS(std::vector<std::vector<int>> & graph, int cur, std::unordered_set<int> & visit)
    {
        int N = graph.size();
        for (int nxt = 0; nxt < N; ++nxt)
            if (graph[cur][nxt] == 1)
            {
                if (!visit.count(nxt))
                {
                    visit.insert(nxt);
                    DFS(graph, nxt, visit);
                }
            }
    }
};
class Remove1MalNodeMinimizeInfectedNodes_RemoveEdges
{
public:
    Remove1MalNodeMinimizeInfectedNodes_RemoveEdges(){}

    int DFS(std::vector<std::vector<int>> && graph, std::vector<int> && initial)
    {
        //DFS: O(N^3) time
        int N = graph.size();
        std::sort(initial.begin(), initial.end());
        int res = 0;
        int minInfected = INT_MAX;
        for (int & i : initial)
        {
            //disconnect node i
            std::vector<std::vector<int>> graph2(graph);
            for (int col = 0; col < N; ++col)
                graph2[i][col] = 0;
            for (int row = 0; row < N; ++row)
                graph2[row][i] = 0;
            //visit all infected nodes
            std::unordered_set<int> visit;
            for (int & j : initial)
            {
                if (j == i) continue;
                if (!visit.count(j))
                {
                    visit.insert(j);
                    DFS(graph2, j, visit);
                }
            }
            if (visit.size() < minInfected)
            {
                minInfected = visit.size();
                res = i;
            }
        }

        Debug::Print2D<int>()(graph, false);
        std::cout << "Remove1MalNodeMinimizeInfectedNodes_RemoveEdges DFS for MalNodes=[" << Debug::ToStr1D<int>()(initial) << "]: " << res << std::endl;
        return res;
    }

    int UnionFind(std::vector<std::vector<int>> && graph, std::vector<int> && initial)
    {
        //union find: O(N^2) time
        int N = graph.size();
        std::sort(initial.begin(), initial.end());
        //disconnect all malware nodes and build chdToP[] / nodeCount[]
        std::unordered_set<int> malNodes(initial.begin(), initial.end());
        std::vector<int> chdToP(N);
        for (int i = 0; i < N; ++i)
            chdToP[i] = i;
        std::vector<int> nodeCount(N, 1);//node count in each connected component
        for (int i = 0; i < N; ++i)
        {
            if (malNodes.count(i)) continue;
            for (int j = 0; j < N; ++j)
            {
                if (malNodes.count(j)) continue;
                if (graph[i][j] == 1)
                {
                    int root1 = Find(chdToP, i);
                    int root2 = Find(chdToP, j);
                    if (root2 != root1)
                    {
                        chdToP[root2] = root1;
                        nodeCount[root1] += nodeCount[root2];
                    }
                }
            }
        }
        //build malNodeCount[] separately
        std::vector<int> malNodeCount(N, 0);
        for (auto & i : initial)
        {
            for (int col = 0; col < N; ++col)
            {
                if (malNodes.count(col)) continue;
                if (graph[i][col] == 1)
                {
                    int root = Find(chdToP, col);
                    ++malNodeCount[root];
                }
            }
        }

        int res;
        int maxInfected = 0;//the largest infected connected component when connecting 1 malware node
        for (auto & i : initial)
        {
            for (int col = 0; col < N; ++col)
            {
                if (malNodes.count(col)) continue;
                if (graph[i][col] == 1)
                {
                    int root = Find(chdToP, col);
                    if (malNodeCount[root] == 1)
                    {
                        if (maxInfected < nodeCount[root])
                        {
                            maxInfected = nodeCount[root];
                            res = i;
                        }
                    }
                }
            }
        }
        res = maxInfected == 0 ? initial[0] : res;

        Debug::Print2D<int>()(graph, false);
        std::cout << "Remove1MalNodeMinimizeInfectedNodes_RemoveEdges UnionFind for MalNodes=[" << Debug::ToStr1D<int>()(initial) << "]: " << res << std::endl;
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
    void DFS(std::vector<std::vector<int>> & graph, int cur, std::unordered_set<int> & visit)
    {
        int N = graph.size();
        for (int nxt = 0; nxt < N; ++nxt)
        {
            if (graph[cur][nxt] == 1 && !visit.count(nxt))
            {
                visit.insert(nxt);
                DFS(graph, nxt, visit);
            }
        }
    }
};
/*
[rY][cX]
Row#0	= 1, 1, 0
Row#1	= 1, 1, 0
Row#2	= 0, 0, 1

Remove1MalNodeMinimizeInfectedNodes DFS for MalNodes=[0, 1]: 0
[rY][cX]
Row#0	= 1, 1, 0
Row#1	= 1, 1, 0
Row#2	= 0, 0, 1

Remove1MalNodeMinimizeInfectedNodes UnionFind for MalNodes=[0, 1]: 0
[rY][cX]
Row#0	= 1, 1, 0
Row#1	= 1, 1, 0
Row#2	= 0, 0, 1

Remove1MalNodeMinimizeInfectedNodes_RemoveEdges DFS for MalNodes=[0, 1]: 0
[rY][cX]
Row#0	= 1, 1, 0
Row#1	= 1, 1, 0
Row#2	= 0, 0, 1

Remove1MalNodeMinimizeInfectedNodes_RemoveEdges UnionFind for MalNodes=[0, 1]: 0
 */
#endif
