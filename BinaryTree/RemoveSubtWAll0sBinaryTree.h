#ifndef _REMOVE_SUBT_W_ALL_0S_BINARY_TREE_H
#define _REMOVE_SUBT_W_ALL_0S_BINARY_TREE_H
#include "Debug.h"
/*
Leetcode: Binary Tree Pruning
We are given the head node root of a binary tree, where additionally every node's value is either a 0 or a 1.
Return the same tree where every subtree (of the given tree) not containing a 1 has been removed.
(Recall that the subtree of a node X is X, plus every node that is a descendant of X.)
Example 1:
Input: [1,null,0,0,1]
Output: [1,null,0,null,1]
Explanation:
Only the red nodes satisfy the property "every subtree not containing a 1".
The diagram on the right represents the answer.
Example 2:
Input: [1,0,1,0,0,0,1]
Output: [1,null,1,null,1]
Example 3:
Input: [1,1,0,1,1,0,1,0]
Output: [1,1,0,1,1,null,1]
 */
class RemoveSubtWAll0sBinaryTree
{
public:
    RemoveSubtWAll0sBinaryTree(){}
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };

    TreeNode* Recur(TreeNode* root)
    {
        return recur(root);
    }
    TreeNode * recur(TreeNode * root)
    {
        if (root == NULL) return NULL;
        root->left = recur(root->left);
        root->right = recur(root->right);
        if (!root->left && !root->right && root->val == 0)
            return NULL;
        return root;
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
RemoveSubtWAll0sBinaryTree:

       1
    __ 1__
   /       \
   X       2
   N       0
 /   \   /   \
 X   X   3   3
 N   N   0   1


       1
    __ 1__
   /       \
   X       2
   N       0
 /   \   /   \
 X   X   X   3
 N   N   N   1

 */
#endif
