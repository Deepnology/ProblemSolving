#ifndef _SPLIT_BST_H
#define _SPLIT_BST_H
#include "Debug.h"
/*
Leetcode: Split BST
Given a Binary Search Tree (BST) with root node root, and a target value V
, split the tree into two subtrees where one subtree has nodes that are all smaller or equal to the target value
, while the other subtree has all nodes that are greater than the target value.
It's not necessarily the case that the tree contains a node with value V.
Additionally, most of the structure of the original tree should remain.
Formally, for any child C with parent P in the original tree, if they are both in the same subtree after the split
, then node C should still have the parent P.
You should output the root TreeNode of both subtrees after splitting, in any order.
Example 1:
Input: root = [4,2,6,1,3,5,7], V = 2
Output: [[2,1],[4,3,6,null,null,5,7]]
Explanation:
Note that root, output[0], and output[1] are TreeNode objects, not arrays.
The given tree [4,2,6,1,3,5,7] is represented by the following diagram:

          4
        /   \
      2      6
     / \    / \
    1   3  5   7

while the diagrams for the outputs are:

          4
        /   \
      3      6      and    2
            / \           /
           5   7         1
 */
class SplitBST
{
public:
    SplitBST(){}
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };

    std::vector<TreeNode *> Recur(TreeNode * root, int V)
    {
        return recur(root, V);
    }
private:
    std::vector<TreeNode *> recur(TreeNode * cur, int V)
    {
        if (cur == NULL) return {NULL,NULL};
        if (cur->val <= V)//cur and cur->left will remain unchanged
        {
            auto roots = recur(cur->right, V);
            cur->right = roots[0];
            return {cur, roots[1]};
        }
        else//cur and cur->right will remain unchanged
        {
            auto roots = recur(cur->left, V);
            cur->left = roots[1];
            return {roots[0], cur};
        }
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
/*

       1
    __ 4__
   /       \
   2       2
   2       6
 /   \   /   \
 3   3   3   3
 1   3   5   7


SplitBST for above BST with value=2:

   1
   2
 /   \
 2   X
 1   N


       1
    __ 4__
   /       \
   2       2
   3       6
 /   \   /   \
 X   X   3   3
 N   N   5   7


 */
#endif
