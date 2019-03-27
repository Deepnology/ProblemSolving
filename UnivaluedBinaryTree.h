#ifndef _UNIVALUED_BINARY_TREE_H
#define _UNIVALUED_BINARY_TREE_H
#include "Debug.h"
/*
Leetcode: Univalued Binary Tree
A binary tree is univalued if every node in the tree has the same value.
Return true if and only if the given tree is univalued.
see also CountUnivalueSubtrees.h
 */
class UnivaluedBinaryTree
{
public:
    UnivaluedBinaryTree(){}
    ~UnivaluedBinaryTree(){}
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };

    bool recur(TreeNode * cur)
    {
        return (!cur->left || cur->val == cur->left->val && recur(cur->left)) &&
               (!cur->right || cur->val == cur->right->val && recur(cur->right));
    }
    bool Recur(TreeNode * root)
    {
        if (root == NULL) return true;
        return recur(root);
    }
};
#endif
