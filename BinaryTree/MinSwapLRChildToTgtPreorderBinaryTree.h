#ifndef _MIN_SWAP_L_R_CHILD_TO_TGT_PREORDER_BINARY_TREE_H
#define _MIN_SWAP_L_R_CHILD_TO_TGT_PREORDER_BINARY_TREE_H
#include "Debug.h"
/*
Leetcode: Flip Binary Tree To Match Preorder Traversal
Given a binary tree with N nodes, each node has a different value from {1, ..., N}.
A node in this binary tree can be flipped by swapping the left child and the right child of that node.
Consider the sequence of N values reported by a preorder traversal starting from the root.  Call such a sequence of N values the voyage of the tree.
(Recall that a preorder traversal of a node means we report the current node's value, then preorder-traverse the left child, then preorder-traverse the right child.)
Our goal is to flip the least number of nodes in the tree so that the voyage of the tree matches the voyage we are given.
If we can do so, then return a list of the values of all nodes flipped.  You may return the answer in any order.
If we cannot do so, then return the list [-1].
Example 1:
Input: root = [1,2], voyage = [2,1]
Output: [-1]
Example 2:
Input: root = [1,2,3], voyage = [1,3,2]
Output: [1]
Example 3:
Input: root = [1,2,3], voyage = [1,2,3]
Output: []
 */
class MinSwapLRChildToTgtPreorderBinaryTree
{
public:
    MinSwapLRChildToTgtPreorderBinaryTree(){}
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };

    std::vector<int> Recur(TreeNode * root, std::vector<int> && voyage)
    {
        int cur = 0;
        std::vector<int> res;
        bool valid = recur(root, voyage, cur, res);
        if (valid) return res;
        return {-1};
    }
    bool recur(TreeNode * root, std::vector<int> & tgt, int & cur, std::vector<int> & res)
    {
        if (root == NULL) return true;
        if (root->val != tgt[cur++]) return false;
        //now root->val == tgt[cur-1] and cur points to next node
        if (root->left && root->left->val != tgt[cur])//try swap 2 children of root
        {
            res.push_back(root->val);
            return recur(root->right, tgt, cur, res) && recur(root->left, tgt, cur, res);
        }
        //don't swap 2 children of root
        return recur(root->left, tgt, cur, res) && recur(root->right, tgt, cur, res);
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
   1
   1
 /   \
 2   2
 2   3

MinSwapLRChildToTgtPreorderBinaryTree Recur: 1
 */
#endif
