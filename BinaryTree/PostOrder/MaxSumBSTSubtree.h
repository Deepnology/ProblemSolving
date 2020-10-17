#ifndef _MAX_SUM_BST_SUBTREE_H
#define _MAX_SUM_BST_SUBTREE_H
#include "Debug.h"
/*
Leetcode: Maximum Sum BST in Binary Tree
Given a binary tree root, the task is to return the maximum sum of all keys of any sub-tree which is also a Binary Search Tree (BST).
Assume a BST is defined as follows:
The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.
 */
class MaxSumBSTSubtree
{
public:
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };
    int PostOrderRecur(TreeNode* root)
    {
        int maxSum = 0;
        recur(root, maxSum);
        return maxSum;
    }
    std::vector<int> recur(TreeNode * cur, int & maxSum)
    {
        if (cur == NULL) return {1, INT_MAX, INT_MIN, 0};//<isBST,min,max,sum>
        auto left = recur(cur->left, maxSum);
        auto right = recur(cur->right, maxSum);
        std::vector<int> res(4,0);
        res[1] = std::min(cur->val, left[1]);
        res[2] = std::max(cur->val, right[2]);
        if (left[0] && cur->val > left[2] &&
            right[0] && cur->val < right[1])
        {
            res[0] = 1;
            res[3] = cur->val + left[3] + right[3];
            maxSum = std::max(maxSum, res[3]);
        }
        return res;
    }
};
#endif
