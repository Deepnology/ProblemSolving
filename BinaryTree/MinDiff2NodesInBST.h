#ifndef _MIN_DIFF_TWO_NODES_IN_BST_H
#define _MIN_DIFF_TWO_NODES_IN_BST_H
#include "Debug.h"
/*
Leetcode: Minimum distance between BST nodes
Given a Binary Search Tree (BST) with the root node root, return the minimum difference between the values of any two different nodes in the tree.
Example :
Input: root = [4,2,6,1,3,null,null]
Output: 1
Explanation:
Note that root is a TreeNode object, not an array.
The given tree [4,2,6,1,3,null,null] is represented by the following diagram:

          4
        /   \
      2      6
     / \
    1   3

while the minimum difference in this tree is 1, it occurs between node 1 and node 2, also between node 3 and node 2.
 */
class MinDiff2NodesInBST
{
public:
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };
    MinDiff2NodesInBST(){}
    ~MinDiff2NodesInBST(){}

    int Inorder(TreeNode * root)
    {
        TreeNode * pre = NULL;
        int res = INT_MAX;
        recur(root, pre, res);
        std::cout << "MinDiff2NodesInBST Inorder: " << res << std::endl;
        return res;
    }
    void recur(TreeNode * cur, TreeNode *& pre, int & res)
    {
        if (cur == NULL) return;
        recur(cur->left, pre, res);

        if (!pre)
            pre = cur;
        else
        {
            res = std::min(res, cur->val-pre->val);
            pre = cur;
        }
        recur(cur->right, pre, res);
    }
};
#endif
