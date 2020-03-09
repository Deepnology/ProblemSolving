#ifndef _MAX_DIFF_BTW_NODE_ANCESTOR_BINARY_TREE_H
#define _MAX_DIFF_BTW_NODE_ANCESTOR_BINARY_TREE_H
/*
Leetcode: Maximum Difference Between Node and Ancestor
Given the root of a binary tree, find the maximum value V for which there exists different nodes A and B where V = |A.val - B.val| and A is an ancestor of B.
(A node A is an ancestor of B if either: any child of A is equal to B, or any child of A is an ancestor of B.)
Example 1:
Input: [8,3,10,1,6,null,14,null,null,4,7,13]
Output: 7
Explanation:
We have various ancestor-node differences, some of which are given below :
|8 - 3| = 5
|3 - 7| = 4
|8 - 1| = 7
|10 - 13| = 3
Among all possible differences, the maximum value of 7 is obtained by |8 - 1| = 7.
 */
class MaxDiffBtwNodeAncestorBinaryTree
{
public:
    MaxDiffBtwNodeAncestorBinaryTree(){}
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };

    int Recur(TreeNode* root)
    {
        int Max = root->val;
        int Min = root->val;
        int res = 0;
        recur(root, Max, Min, res);
        std::cout << "MaxDiffBtwNodeAncestorBinaryTree Recur: " << res << std::endl;
        return res;
    }
    void recur(TreeNode * cur, int Max, int Min, int & res)
    {
        if (cur == NULL) return;
        res = std::max(res, std::max(std::abs(cur->val-Max),std::abs(cur->val-Min)));
        int nxtMax = std::max(Max, cur->val);
        int nxtMin = std::min(Min, cur->val);
        recur(cur->left, nxtMax, nxtMin, res);
        recur(cur->right, nxtMax, nxtMin, res);
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
        ______ 8______
       /               \
       2               2
    __ 3__          __10__
   /       \       /       \
   3       3       X       3
   1       6       N      14
 /   \   /   \   /   \   /   \
 X   X   4   4   X   X   4   X
 N   N   4   7   N   N  13   N


MaxDiffBtwNodeAncestorBinaryTree Recur: 7
 */
#endif
