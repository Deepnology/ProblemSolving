#ifndef _SUM_OF_DIST_BTW_CUR_AND_ALL_OTHER_NODES_IN_TREE_H
#define _SUM_OF_DIST_BTW_CUR_AND_ALL_OTHER_NODES_IN_TREE_H
#include "Debug.h"
/*
Leetcode: Sum of distances in tree
An undirected, connected tree with N nodes labelled 0...N-1 and N-1 edges are given.
The ith edge connects nodes edges[i][0] and edges[i][1] together.
Return a list ans, where ans[i] is the sum of the distances between node i and all other nodes.
Example 1:
Input: N = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
Output: [8,12,6,10,10,10]
Explanation:
Here is a diagram of the given tree:
  0
 / \
1   2
   /|\
  3 4 5
We can see that dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
equals 1 + 1 + 2 + 2 + 2 = 8.  Hence, answer[0] = 8, and so on.
 */
class SumOfDistBtwCurAndAllOtherNodesInTree
{
public:
    SumOfDistBtwCurAndAllOtherNodesInTree(){}
    ~SumOfDistBtwCurAndAllOtherNodesInTree(){}

    std::vector<int> TwoPassDFS(int N, std::vector<std::vector<int>> && edges)
    {
        //bruteforce: O(N^2) time
        //2 pass DFS: O(N) time
        std::vector<std::unordered_set<int>> adjSet(N);
        std::vector<int> res(N, 0);
        std::vector<int> count(N, 0);//count[i]: children node count at node i (include i)
        if (N == 1) return res;
        for (auto e : edges) //construct adjSet
        {
            adjSet[e[0]].insert(e[1]);
            adjSet[e[1]].insert(e[0]);
        }
        std::unordered_set<int> visit1, visit2;
        dfs(adjSet, 0, visit1, count, res);
        //now:
        //count[i]: children node count at node i (include i)
        //res[i]: edge count for all pairs "starting from i to all its children"
        std::cout << "count[] = " << Debug::ToStr1D<int>()(count) << std::endl;
        std::cout << "res[] = " << Debug::ToStr1D<int>()(res) << std::endl;

        dfs2(adjSet, 0, visit2, count, res, N);

        std::cout << "SumOfDistBtwCurAndAllOtherNodesInTree TwoPassDFS for [" << Debug::ToStr1D<int>()(edges) << "]: " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;

    }

    void dfs(std::vector<std::unordered_set<int>> & adjSet, int root, std::unordered_set<int> & visit, std::vector<int> & count, std::vector<int> & res)
    {
        visit.insert(root);
        for (auto i : adjSet[root])
            if (!visit.count(i))
            {
                dfs(adjSet, i, visit, count, res);
                //post-order
                count[root] += count[i];//accumulate children node count for each child i
                res[root] += res[i] + count[i];//accumulate edge count
            }
        count[root] += 1;//include cur node
    }

    void dfs2(std::vector<std::unordered_set<int>>& adjSet, int root, std::unordered_set<int>& visit, std::vector<int>& count, std::vector<int> & res, int N)
    {
        visit.insert(root);
        for (auto i : adjSet[root])
            if (!visit.count(i))
            {
                //pre-order
                //when moving from root to i:
                //count[i] nodes get 1 closer to the new root i
                //N-count[i] nodes get 1 further to the new root i
                res[i] = res[root] - count[i] + (N - count[i]);
                dfs2(adjSet, i, visit, count, res, N);
            }
    }
};
/*
count[] = 6, 1, 4, 1, 1, 1
res[] = 8, 0, 3, 0, 0, 0
SumOfDistBtwCurAndAllOtherNodesInTree TwoPassDFS for [[0,1], [0,2], [2,3], [2,4], [2,5]]: 8, 12, 6, 10, 10, 10

now use 1 instead of 0:
count[] = 5, 6, 4, 1, 1, 1
res[] = 7, 12, 3, 0, 0, 0
SumOfDistBtwCurAndAllOtherNodesInTree TwoPassDFS for [[0,1], [0,2], [2,3], [2,4], [2,5]]: 8, 12, 6, 10, 10, 10
 */
#endif
