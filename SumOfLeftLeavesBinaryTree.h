#ifndef _SUM_OF_LEFT_LEAVES_BINARY_TREE_H
#define _SUM_OF_LEFT_LEAVES_BINARY_TREE_H
/*
Leetcode: Sum of left leaves
Find the sum of all left leaves in a given binary tree.

Example:

    3
   / \
  9  20
    /  \
   15   7

There are two left leaves in the binary tree, with values 9 and 15 respectively. Return 24.
 */
class SumOfLeftLeavesBinaryTree
{
public:
    SumOfLeftLeavesBinaryTree(){}
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };

    int Recur(TreeNode* root)
    {
        int res = 0;
        if (root == NULL) return res;
        recur(root->left, true, res);
        recur(root->right, false, res);

        return res;
    }

    void recur(TreeNode * cur, bool isLeft, int & res)
    {
        if (cur == NULL) return;
        if (!cur->left && !cur->right && isLeft)
        {
            res += cur->val;
            return;
        }
        recur(cur->left, true, res);
        recur(cur->right, false, res);
    }
public:
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
