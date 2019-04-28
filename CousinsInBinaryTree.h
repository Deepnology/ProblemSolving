#ifndef _COUSINS_IN_BINARY_TREE_H
#define _COUSINS_IN_BINARY_TREE_H
#include "Debug.h"
/*
Leetcode: Cousins In Binary Tree
In a binary tree, the root node is at depth 0, and children of each depth k node are at depth k+1.
Two nodes of a binary tree are cousins if they have the same depth, but have different parents.
We are given the root of a binary tree with unique values, and the values x and y of two different nodes in the tree.
Return true if and only if the nodes corresponding to the values x and y are cousins.
 */
class CousinsInBinaryTree
{
public:
    CousinsInBinaryTree(){}
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };

    bool IsCousins(TreeNode * root, int x, int y)
    {
        int depth1 = -1, depth2 = -1;
        TreeNode * parent1 = NULL, * parent2 = NULL;
        recur(root, 0, NULL, x, depth1, parent1);
        recur(root, 0, NULL, y, depth2, parent2);
        return depth1 == depth2 && parent1 != parent2;
    }
    void recur(TreeNode * cur, int depth, TreeNode * p, int val, int & resDepth, TreeNode *& resP)
    {
        if (cur == NULL) return;
        if (cur->val == val)
        {
            resDepth = depth;
            resP = p;
            return;
        }
        recur(cur->left, depth+1, cur, val, resDepth, resP);
        recur(cur->right, depth+1, cur, val, resDepth, resP);
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
#endif
