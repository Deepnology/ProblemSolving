#ifndef _SUM_OF_NODES_W_GRANDPARENT_VAL_EVEN_H
#define _SUM_OF_NODES_W_GRANDPARENT_VAL_EVEN_H
#include "Debug.h"
/*
Leetcode: Sum of Nodes with Even-Valued Grandparent
Given a binary tree, return the sum of values of nodes with even-valued grandparent.
(A grandparent of a node is the parent of its parent, if it exists.)
If there are no nodes with an even-valued grandparent, return 0.
 */
class SumOfNodesWGrandParentValEven
{
public:
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(0), right(0) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };
    int Recur(TreeNode * root)
    {
        return recur(root, NULL, NULL);
    }
private:
    int recur(TreeNode * cur, TreeNode * parent, TreeNode * gParent)
    {
        if (cur == NULL) return 0;
        int sum = 0;
        if (gParent != NULL && gParent->val % 2 == 0)
            sum += cur->val;
        sum += recur(cur->left, cur, parent);
        sum += recur(cur->right, cur, parent);
        return sum;
    }
};
#endif
