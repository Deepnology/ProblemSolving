#ifndef _SUBTREE_CONTAINING_ALL_DEEPEST_NODES_H
#define _SUBTREE_CONTAINING_ALL_DEEPEST_NODES_H
#include "Debug.h"
/*
Leetcode: Smallest Subtree with all deepest nodes
Given a binary tree rooted at root, the depth of each node is the shortest distance to the root.
A node is deepest if it has the largest depth possible among any node in the entire tree.
The subtree of a node is that node, plus the set of all descendants of that node.
Return the node with the largest depth such that it contains all the deepest nodes in its subtree.
 */
class SubtreeContainingAllDeepestNodes
{
public:
    SubtreeContainingAllDeepestNodes(){}
    ~SubtreeContainingAllDeepestNodes(){}

    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL){}
        int val;
        TreeNode * left;
        TreeNode * right;
    };

    TreeNode * Recur(TreeNode * root)
    {
        auto res = recur(root);
        return res.second;
    }
    std::pair<int,TreeNode*> recur(TreeNode * cur) //<depth, root>
    {
        if (cur == nullptr) return {0,NULL};
        auto left = recur(cur->left);
        auto right = recur(cur->right);
        if (left.first == right.first)
        {
            return {left.first+1, cur};
        }
        //return left.first > right.first ? {left.first+1, left.second} : {right.first+1, right.second};

        if (left.first > right.first)
            return {left.first+1,left.second};
        return {right.first+1,right.second};
    }

    static void DeleteTree(TreeNode * root)
    {
        if (root == 0)
            return;

        DeleteTree(root->left);
        DeleteTree(root->right);

        //post order
        delete root;
        root = 0;
    }
};
/*
SubtreeContainingAllDeepestNodes:

               1
        ______ 3______
       /               \
       2               2
    __ 5__          __ 1__
   /       \       /       \
   3       3       3       3
   6       2       0       8
 /   \   /   \   /   \   /   \
 X   X   4   4   X   X   X   X
 N   N   7   4   N   N   N   N


   1
   2
 /   \
 2   2
 7   4

 */
#endif
