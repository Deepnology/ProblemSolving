#ifndef _MIN_TRIO_OUT_DEGREE_IN_GRAPH_H
#define _MIN_TRIO_OUT_DEGREE_IN_GRAPH_H
#include "Debug.h"
/*
Amazon OA
Amazon is trying to understand customer shopping patterns and offer items that are regularly bought together to new customers.
Each item that has been bought together can be represented as an undirected graph where edges join often bundled products.
A group of n products is uniquely numbered from 1 of product_nodes. A trio is defined as a group of three related products that all connected by an edge.
Trios are scored by counting the number of related products outside of the trio, this is referred as a product sum.
Given product relation data, determine the minimum product sum for all trios of related products in the group.
If no such trio exists, return -1.
Example
products_nodes = 6
products_edges = 6
products_from = [1,2,2,3,4,5]
products_to = [2,4,5,5,5,6]
Product,	Related Products
1	2
2	1, 4, 5
3	5
4	2, 5
5	2, 3, 4, 6
6	5
A graph of n = 6 products where the only trio of related products is (2, 4, 5).
The product scores based on the graph above are:
Product,	Outside Products,	Which Products Are Outside
2	1	1
4	0
5	2	3, 6
In the diagram above, the total product score is 1 + 0 + 2 = 3 for the trio (2, 4, 5).

Function Description
Complete the function getMinScore in the editor below.
getMinScore has the following parameter(s):
   int products_nodes: the total number of products
   int products_edges the total number of edges representing related products
   int products_from[products_nodes]: each element is a node of one side of an edge.
   int products_to[products edges]: each products_to[i] is a node connected to products_from[i]
Returns:
int: the minimum product sum for all trios of related products in the group. If no such trio exists, return -1.

Constraints
1 <= products_nodes <= 500
1 <= products_edges <= min(500, (products_nodes * (products_nodes - 1)) / 2)
1 <= products_from[i], products to[i] <= products_nodes
products_from[i] != products_to[i]

Sample Case 0
STDIN        Funtion
-------        ------------------------------------------------
5   6     ->  products_nodes = 5    products_edges = 6
1   2     ->  products_from[0] = 1   products_to[0] = 2
1   3     ->  products_from[1] = 1   products_to[1] = 3
2   3     ->  products_from[2] = 2   products_to[2] = 3
2   4     ->  products_from[3] = 2   products_to[3] = 4
3   4     ->  products_from[4] = 3   products_to[4] = 4
4   5     ->  products_from[5] = 4   products_to[5] = 5

Sample Output
2

Explanation
There are two possible trios: {1,2,3} and {2,3,4}
The score for {1,2,3} is 0 + 1 + 1 = 2.
The score for {2,3,4} is 1 + 1 + 1 = 3.
Return 2.
 */
class MinTrioOutDegreeInGraph
{
public:
    int BFS(int numNodes, int numEdges, const std::vector<int> & from, const std::vector<int> & to)
    {
        std::unordered_map<int, std::unordered_set<int>> graph;
        for (auto i = 0; i < numEdges; ++i)
        {
            graph[from[i]].insert(to[i]);
            graph[to[i]].insert(from[i]);
        }
        std::unordered_set<int> visit;
        std::queue<int> que;
        que.push(from[0]);
        visit.insert(from[0]);
        std::unordered_map<std::string,std::vector<int>> trios;
        while (!que.empty())
        {
            int cur = que.front();
            que.pop();
            for (auto itr1 = graph[cur].begin(); itr1 != graph[cur].end(); ++itr1)
            {
                int adj1 = *itr1;
                for (auto itr2 = std::next(itr1); itr2 != graph[cur].end(); ++itr2)
                {
                    int adj2 = *itr2;
                    bool isTrio = graph[adj1].count(adj2);
                    if (isTrio)
                    {
                        std::vector<int> v({cur, adj1, adj2});
                        std::sort(v.begin(), v.end());
                        std::string trioStr = std::to_string(v[0]) + "," + std::to_string(v[1]) + "," + std::to_string(v[2]);
                        trios.insert({trioStr, v});
                    }
                }
            }
            for (auto & adj : graph[cur])
            {
                if (!visit.count(adj))
                {
                    visit.insert(adj);
                    que.push(adj);
                }
            }
        }
        int res = numEdges;
        for (auto & t : trios)
        {
            int trioEdges = graph[t.second[0]].size() + graph[t.second[1]].size() + graph[t.second[2]].size() - 3*2;
            std::cout << t.first << ": " << trioEdges << std::endl;
            res = std::min(res, trioEdges);
        }

        std::cout << "MinTrioOutDegreeInGraph BFS for from=[" << Debug::ToStr1D<int>()(from) << "], to=[" << Debug::ToStr1D<int>()(to) << "]: " << res << std::endl;
        return res;
    }
};
/*
2,4,5: 3
MinTrioOutDegreeInGraph BFS for from=[1, 2, 2, 3, 4, 5], to=[2, 4, 5, 5, 5, 6]: 3
2,3,4: 3
1,2,3: 2
MinTrioOutDegreeInGraph BFS for from=[1, 1, 2, 2, 3, 4], to=[2, 3, 3, 4, 4, 5]: 2
 */
#endif
