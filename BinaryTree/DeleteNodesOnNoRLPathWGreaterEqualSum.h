#ifndef _DELETE_NODES_ON_NO_RL_PATH_W_GREATER_EQUAL_SUM_H
#define _DELETE_NODES_ON_NO_RL_PATH_W_GREATER_EQUAL_SUM_H
#include "Debug.h"
/*
Leetcode: Insufficient Nodes in Root to Leaf Paths
Given the root of a binary tree, consider all root to leaf paths: paths from the root to any leaf.
 (A leaf is a node with no children.)
A node is insufficient if every such root to leaf path intersecting this node has sum strictly less than limit.
Delete all insufficient nodes simultaneously, and return the root of the resulting binary tree.

(for each node, as long as it is on a root to leaf path sum greater equal than K, don't delete it.
 otherwise, delete it)
 */
class DeleteNodesOnNoRLPathWGreaterEqualSum //DeleteNodesOnAllRLPathsWLessSum
{
public:
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };
    TreeNode * GetSufficientSubset(TreeNode * root, int limit)
    {
        return recur(root, limit);
    }
    TreeNode * recur(TreeNode * root, int limit)
    {
        if(!root)
            return NULL;
        if(!root->left && !root->right)
            return (limit - root->val > 0) ? NULL : root;
        root->left = recur(root->left, limit - root->val);
        root->right = recur(root->right, limit - root->val);
        return (!root->left && !root->right) ? NULL : root;
    }
};
/*
DeleteNodesOnNoRLPathWGreaterEqualSum for limit=12:

               1
        ______ 5______
       /               \
       2               2
    __ 4__          __ 8__
   /       \       /       \
   3       X       3       3
  11       N      17       4
 /   \   /   \   /   \   /   \
 4   4   X   X   X   X   4   4
 7   1   N   N   N   N   5   3


               1
        ______ 5______
       /               \
       2               2
    __ 4__          __ 8__
   /       \       /       \
   3       X       3       3
  11       N      17       4
 /   \   /   \   /   \   /   \
 4   X   X   X   X   X   4   X
 7   N   N   N   N   N   5   N


 */
#endif
