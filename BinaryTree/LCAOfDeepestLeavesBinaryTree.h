#ifndef _LCA_OF_DEEPEST_LEAVES_BINARY_TREE_H
#define _LCA_OF_DEEPEST_LEAVES_BINARY_TREE_H
#include "Debug.h"
/*
Leetcode: Lowest Common Ancestor of Deepest Leaves
Given a rooted binary tree, return the lowest common ancestor of its deepest leaves.
Recall that:
The node of a binary tree is a leaf if and only if it has no children
The depth of the root of the tree is 0, and if the depth of a node is d, the depth of each of its children is d+1.
The lowest common ancestor of a set S of nodes is the node A with the largest depth such that every node in S is in the subtree with root A.
Example 1:
Input: root = [1,2,3]
Output: [1,2,3]
Explanation:
The deepest leaves are the nodes with values 2 and 3.
The lowest common ancestor of these leaves is the node with value 1.
The answer returned is a TreeNode object (not an array) with serialization "[1,2,3]".
Example 2:
Input: root = [1,2,3,4]
Output: [4]
Example 3:
Input: root = [1,2,3,4,5]
Output: [2,4,5]
 */
class LCAOfDeepestLeavesBinaryTree
{
public:
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL), parent(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
        TreeNode * parent;
    };
    TreeNode * Recur(TreeNode * root)
    {
        return recur(root).first;
    }
private:
    std::pair<TreeNode*,int> recur(TreeNode * cur)//<LCA,cur height>
    {
        if (cur==NULL) return {NULL,0};
        auto left = recur(cur->left);
        auto right = recur(cur->right);
        if (left.second == right.second)
            return {cur, left.second+1};
        else if (left.second > right.second)
            return {left.first, left.second+1};
        else
            return {right.first, right.second+1};
    }
};
/*
       1
    __ 1__
   /       \
   2       2
   2       3
 /   \   /   \
 3   X   X   X
 4   N   N   N

LCAOfDeepestLeavesBinaryTree:

 1
 4
 */
#endif
