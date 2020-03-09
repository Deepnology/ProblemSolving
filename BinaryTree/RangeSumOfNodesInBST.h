#ifndef _RANGE_SUM_OF_NODES_IN_BST_H
#define _RANGE_SUM_OF_NODES_IN_BST_H
#include "Debug.h"
/*
Leetcode: Range Sum of BST
Given the root node of a binary search tree, return the sum of values of all nodes with value between L and R (inclusive).
The binary search tree is guaranteed to have unique values.
Example 1:
Input: root = [10,5,15,3,7,null,18], L = 7, R = 15
Output: 32
Example 2:
Input: root = [10,5,15,3,7,13,18,1,null,6], L = 6, R = 10
Output: 23
 */
class RangeSumOfNodesInBST
{
public:
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };
    RangeSumOfNodesInBST(){}
    ~RangeSumOfNodesInBST(){}

    void Recur(TreeNode * root, int L, int R)
    {
        int res = 0;
        recur(root, L, R, res);
        int res2 = recur2(root, L, R);
        std::cout << "RangeSumOfNodesInBST Recur: " << res << "," << res2 << std::endl;
    }

    void recur(TreeNode * cur, int L, int R, int & sum) //inorder
    {
        if (cur == NULL) return;
        if (L <= cur->val)
            recur(cur->left, L, R, sum);
        if (L <= cur->val && cur->val <= R)
            sum += cur->val;
        if (cur->val <= R)
            recur(cur->right, L, R, sum);
    }

    int recur2(TreeNode * cur, int L, int R)//faster
    {
        if (cur == NULL) return 0;
        if (cur->val < L) return recur2(cur->right, L, R);
        if (cur->val > R) return recur2(cur->left, L, R);
        return cur->val + recur2(cur->left, L, R) + recur2(cur->right, L, R);
    }
};
#endif
