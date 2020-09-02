#ifndef _FIND_CORRESPONDING_NODE_IN_CLONED_BT_H
#define _FIND_CORRESPONDING_NODE_IN_CLONED_BT_H
#include "Debug.h"
/*
Leetcode: Find a Corresponding Node of a Binary Tree in a Clone of That Tree
Given two binary trees original and cloned and given a reference to a node target in the original tree.
The cloned tree is a copy of the original tree.
Return a reference to the same node in the cloned tree.
Note that you are not allowed to change any of the two trees or the target node and the answer must be a reference to a node in the cloned tree.
Follow up: Solve the problem if repeated values on the tree are allowed.
 */
class FindCorrespondingNodeInClonedBT
{
public:
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };
    TreeNode * GetTargetCopy(TreeNode * original, TreeNode * cloned, TreeNode * target)
    {
        TreeNode * res = NULL;
        preorderRecur(original, cloned, target, res);
        return res;
    }
private:
    void preorderRecur(TreeNode * original, TreeNode * cloned, TreeNode * tgt, TreeNode *& res)
    {
        if (original == NULL) return;
        if (original == tgt)
        {
            res = cloned;
            return;
        }
        preorderRecur(original->left, cloned->left, tgt, res);
        if (res == NULL)
            preorderRecur(original->right, cloned->right, tgt, res);
    }
};
#endif
