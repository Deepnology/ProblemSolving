#ifndef _DIST_K_NODES_OF_TGT_NODE_BINARY_TREE_H
#define _DIST_K_NODES_OF_TGT_NODE_BINARY_TREE_H
#include "Debug.h"
/*
Leetcode: All Nodes Distance K in Binary Tree
We are given a binary tree (with root node root), a target node, and an integer value K.
Return a list of the values of all nodes that have a distance K from the target node.
The answer can be returned in any order.
Example 1:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, K = 2
Output: [7,4,1]
Explanation:
The nodes that are a distance 2 from the target node (with value 5)
have values 7, 4, and 1.
Note that the inputs "root" and "target" are actually TreeNodes.
The descriptions of the inputs above are just serializations of these objects.
 */
class DistKNodesOfTgtNodeBinaryTree
{
public:
    DistKNodesOfTgtNodeBinaryTree(){}

    std::vector<int> BFS(TreeNode* root, TreeNode* target, int K)
    {
        std::vector<int> res;
        if (root == NULL || target == NULL) return res;
        std::unordered_map<TreeNode*,TreeNode*> toP;
        recur(root, toP);
        int dist = 0;
        std::queue<TreeNode*> que;
        que.push(target);
        std::unordered_set<TreeNode*> visit;
        visit.insert(target);
        while (!que.empty())
        {
            int levelCount = que.size();
            while (levelCount-->0)
            {
                TreeNode * cur = que.front(); que.pop();
                if (dist == K)
                {
                    res.push_back(cur->val);
                    continue;
                }
                if (cur->left && !visit.count(cur->left))
                {
                    visit.insert(cur->left);
                    que.push(cur->left);
                }
                if (cur->right && !visit.count(cur->right))
                {
                    visit.insert(cur->right);
                    que.push(cur->right);
                }
                if (toP.count(cur) && !visit.count(toP[cur]))
                {
                    visit.insert(toP[cur]);
                    que.push(toP[cur]);
                }
            }
            ++dist;
        }
        return res;
    }
    void recur(TreeNode * cur, std::unordered_map<TreeNode*,TreeNode*> & toP)
    {
        if (cur->left)
        {
            toP[cur->left] = cur;
            recur(cur->left, toP);
        }
        if (cur->right)
        {
            toP[cur->right] = cur;
            recur(cur->right, toP);
        }
    }
};
#endif
