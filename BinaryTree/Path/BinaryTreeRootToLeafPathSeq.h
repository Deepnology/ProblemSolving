#ifndef _BINARY_TREE_ROOT_TO_LEAF_PATH_SEQ_H
#define _BINARY_TREE_ROOT_TO_LEAF_PATH_SEQ_H
#include "Debug.h"
/*
Leetcode: Check If a String Is a Valid Sequence from Root to Leaves Path in a Binary Tree
Given a binary tree where each path going from the root to any leaf form a valid sequence, check if a given string is a valid sequence in such binary tree.
We get the given string from the concatenation of an array of integers arr and the concatenation of all values of the nodes along a path results in a sequence in the given binary tree.
 */
class BinaryTreeRootToLeafPathSeq
{
public:
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };
    bool isValidSequence(TreeNode* root, std::vector<int> & arr)
    {
        return recur(root, arr, 0);
    }
    bool recur(TreeNode * cur, std::vector<int> & v, int i)
    {
        /*
        //this is incorrect bc it requires the path reaches a "leaf"
        int N = v.size();
        if (i == N && cur == NULL) return true;
        if (i == N || cur == NULL) return false;
        if (cur->val != v[i]) return false;
        return recur(cur->left, v, i+1) || recur(cur->right, v, i+1);
        */
        int N = v.size();
        if (i == N || cur == NULL || cur->val != v[i]) return false;
        if (cur->left == NULL && cur->right == NULL && i == N-1)
            return true;
        return recur(cur->left, v, i+1) || recur(cur->right, v, i+1);
    }
};
#endif
