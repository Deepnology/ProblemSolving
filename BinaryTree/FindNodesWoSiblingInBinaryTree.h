#ifndef _FIND_NODES_WO_SIBLING_IN_BINARY_TREE_H
#define _FIND_NODES_WO_SIBLING_IN_BINARY_TREE_H
#include "Debug.h"
/*
Leetcode: Find All The Lonely Nodes
In a binary tree, a lonely node is a node that is the only child of its parent node.
The root of the tree is not lonely because it does not have a parent node.
Given the root of a binary tree, return an array containing the values of all lonely nodes in the tree.
Return the list in any order.
 */
class FindNodesWoSiblingInBinaryTree
{
public:
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };
    std::vector<int> DFS(TreeNode* root)
    {
        std::vector<int> res;
        recur(root, res);
        return res;
    }
private:
    void recur(TreeNode * cur, std::vector<int> & res)
    {
        if (cur == NULL) return;
        if (!cur->left && cur->right)
            res.push_back(cur->right->val);
        if (cur->left && !cur->right)
            res.push_back(cur->left->val);
        recur(cur->left, res);
        recur(cur->right, res);
    }
};
#endif
