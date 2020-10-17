#ifndef _DELETE_LEAVES_OF_BINARY_TREE_H
#define _DELETE_LEAVES_OF_BINARY_TREE_H
#include "Debug.h"
/*
Leetcode: Delete Leaves With a Given Value
Given a binary tree root and an integer target, delete all the leaf nodes with value target.
Note that once you delete a leaf node with value target, if it's parent node becomes a leaf node and has the value target, it should also be deleted (you need to continue doing that until you can't).
 */
class DeleteLeavesOfBinaryTree
{
public:
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };
    TreeNode* PostOrderRecur(TreeNode* root, int target)
    {
        return recur(root, target);
    }
    TreeNode * recur(TreeNode * cur, int tgt)
    {
        if (cur == NULL) return NULL;
        cur->left = recur(cur->left, tgt);
        cur->right = recur(cur->right, tgt);
        if (cur->left == NULL && cur->right == NULL && cur->val == tgt)
            return NULL;
        return cur;
    }
};
#endif
