#ifndef _PARTITION_BINARY_TREE_MAX_PRODUCT_OF_2_SUM_H
#define _PARTITION_BINARY_TREE_MAX_PRODUCT_OF_2_SUM_H
#include "Debug.h"
/*
Leetcode: Maximum Product of Splitted Binary Tree
Given a binary tree root.
Split the binary tree into two subtrees by removing 1 edge such that the product of the sums of the subtrees are maximized.
Since the answer may be too large, return it modulo 10^9 + 7.
 */
class PartitionBinaryTreeMaxProductOf2Sum
{
public:
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };
    int MOD = 1e9+7;
    int Recur(TreeNode* root)
    {
        int sum = totalSum(root);
        long long maxProd = 0;
        recur(root, sum, maxProd);
        return maxProd % MOD;
    }
private:
    int totalSum(TreeNode * cur)
    {
        if (cur == NULL) return 0;
        return cur->val + totalSum(cur->left) + totalSum(cur->right);
    }
    int recur(TreeNode * cur, int totalSum, long long & maxProd)
    {
        if (cur == NULL) return 0;
        int sum = cur->val + recur(cur->left, totalSum, maxProd) + recur(cur->right, totalSum, maxProd);
        maxProd = std::max(maxProd, (long long)sum * (long long)(totalSum-sum));
        return sum;
    }
};
#endif
