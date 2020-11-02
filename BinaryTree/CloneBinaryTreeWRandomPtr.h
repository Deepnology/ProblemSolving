#ifndef _CLONE_BINARY_TREE_W_RANDOM_PTR_H
#define _CLONE_BINARY_TREE_W_RANDOM_PTR_H
#include "Debug.h"
/*
Leetcode: Clone Binary Tree With Random Pointer
A binary tree is given such that each node contains an additional random pointer which could point to any node in the tree or null.
Return a deep copy of the tree.
The tree is represented in the same input/output way as normal binary trees where each node is represented as a pair of [val, random_index] where:
val: an integer representing Node.val
random_index: the index of the node (in the input) where the random pointer points to, or null if it does not point to any node.
You will be given the tree in class Node and you should return the cloned tree in class NodeCopy. NodeCopy class is just a clone of Node class with the same attributes and constructors.
 */
class CloneBinaryTreeWRandomPtr
{
public:
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL), random(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
        TreeNode * random;
    };
    //1. Use Hashmap
    //2. Inplace
    TreeNode* Inplace(TreeNode * root)
    {
        clone(root);
        connectRand(root);
        return split(root);
    }
private:
    void clone(TreeNode * cur)
    {
        if (cur == NULL) return;
        TreeNode * copy = new TreeNode(cur->val);
        copy->left = cur->left;
        copy->right = cur->right;
        cur->left = copy;//put the copy node in left child
        cur->right = NULL;
        clone(copy->left);
        clone(copy->right);
    }
    void connectRand(TreeNode * cur)
    {
        if (cur == NULL) return;
        TreeNode * copy = cur->left;
        if (cur->random)
            copy->random = cur->random->left;
        else
            copy->random = NULL;
        connectRand(copy->left);
        connectRand(copy->right);
    }
    TreeNode * split(TreeNode * cur)
    {
        if (cur == NULL) return NULL;
        TreeNode * copy = cur->left;
        cur->left = copy->left;
        cur->right = copy->right;
        if (cur->left)
            copy->left = split(cur->left);
        if (cur->right)
            copy->right = split(cur->right);
        return copy;
    }
};
#endif
