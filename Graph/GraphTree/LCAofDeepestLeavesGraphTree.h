/*Facebook*/
#ifndef _LCA_OF_DEEPEST_LEAVES_GRAPH_TREE_H
#define _LCA_OF_DEEPEST_LEAVES_GRAPH_TREE_H
#include "Debug.h"
/*
Given a tree(not binary), find the LCA of all deepest leaves.
 */
class LCAofDeepestLeavesGraphTree
{
public:
    struct TreeNode
    {
        TreeNode(int x) : val(x) {}
        int val;
        std::vector<TreeNode *> children;
    };
    LCAofDeepestLeavesGraphTree(){}

    TreeNode * BottomUp_BFS(TreeNode * root)
    {
        std::unordered_map<TreeNode *, TreeNode *> chdToP;
        chdToP[root] = NULL;
        //BFS top down to construct chdToP and find deepestLeaves
        std::vector<TreeNode *> deepestL;
        std::queue<TreeNode *> que;
        que.push(root);
        while (!que.empty())
        {
            int levelCount = que.size();
            std::vector<TreeNode *> curLevel;
            std::vector<TreeNode *> nxtLevel;
            for (int i = 0; i < levelCount; ++i)
            {
                TreeNode * cur = que.front();
                que.pop();
                curLevel.push_back(cur);
                for (auto & chd : cur->children)
                {
                    chdToP[chd] = cur;
                    nxtLevel.push_back(chd);
                }
            }
            if (nxtLevel.empty())//deepest leaves
            {
                deepestL.swap(curLevel);
            }
            else//non deepest leaves
            {
                for (auto & n : nxtLevel)
                    que.push(n);
            }
        }

        //BFS_BottomUp and HashSet to find LCA of deepestLeaves
        //note: for this method, if there is only 1 deepest leaf, its LCA will become the root
        for (auto & n : deepestL)
            que.push(n);
        std::unordered_set<TreeNode *> visit;
        TreeNode * LCA = root;
        while (!que.empty())
        {
            TreeNode * cur = que.front(); que.pop();
            if (visit.count(cur))
            {
                LCA = cur;
                break;
            }
            visit.insert(cur);
            TreeNode * curP = chdToP[cur];
            if (curP)
                que.push(curP);
        }


        std::cout << "LCAofDeepestLeavesGraphTree BottomUp_BFS: " << LCA->val << std::endl;
        return LCA;
    }


    static void DeleteTree(TreeNode * node)
    {
        std::vector<TreeNode *> tmp;

        std::unordered_set<TreeNode *> visited;
        std::queue<TreeNode *> queue;
        queue.push(node);
        visited.insert(node);
        while (!queue.empty())
        {
            node = queue.front();
            queue.pop();

            tmp.push_back(node);//now visit the node

            for (auto nebr : node->children)
            {
                if (visited.count(nebr) == 0)
                {
                    visited.insert(nebr);
                    queue.push(nebr);
                }
            }
        }

        //now delete tmp
        for (std::vector<TreeNode *>::iterator i = tmp.begin(); i != tmp.end(); ++i)
        {
            delete *i;
            *i = 0;
        }
    }
};
/*

     _______0________
    /       |        \
   1       _2_        3
  /       / | \        \
12       4  5  6       13
        /   |   \       \
       7   11    8      14
      /           \
     9            10

LCAofDeepestLeavesGraphTree BottomUp_BFS: 2
 */
#endif
