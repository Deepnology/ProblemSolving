#ifndef _FLIP_EQUIVALENT_BINARY_TREES_H
#define _FLIP_EQUIVALENT_BINARY_TREES_H
#include "Debug.h"
/*
Leetcode: Flip Equivalent Binary Trees
For a binary tree T, we can define a flip operation as follows: choose any node, and swap the left and right child subtrees.
A binary tree X is flip equivalent to a binary tree Y if and only if we can make X equal to Y after some number of flip operations.
Write a function that determines whether two binary trees are flip equivalent.
The trees are given by root nodes root1 and root2.
Example 1:
Input: root1 = [1,2,3,4,5,6,null,null,null,7,8], root2 = [1,3,2,null,6,4,5,null,null,null,null,8,7]
Output: true
Explanation: We flipped at nodes with values 1, 3, and 5.
 */
class FlipEquivalentBinaryTrees
{
public:
    FlipEquivalentBinaryTrees(){}
    ~FlipEquivalentBinaryTrees(){}
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };

    bool Recur(TreeNode * root1, TreeNode * root2)
    {
        bool res = recur(root1, root2);
        std::cout << "FlipEquivalentBinaryTrees Recur: " << res << std::endl;
        return res;
    }
    bool recur(TreeNode * cur1, TreeNode * cur2)
    {
        if (!cur1 && !cur2) return true;
        if (!cur1 || !cur2) return false;
        return (cur1->val == cur2->val) && (
                recur(cur1->left, cur2->left)&&recur(cur1->right, cur2->right) || //without flip
                recur(cur1->left, cur2->right)&&recur(cur1->right, cur2->left)    //with flip
        );
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
        ______ 1______
       /               \
       2               2
    __ 2__          __ 3__
   /       \       /       \
   3       3       3       X
   4       5       6       N
 /   \   /   \   /   \   /   \
 X   X   4   4   X   X   X   X
 N   N   7   8   N   N   N   N


               1
        ______ 1______
       /               \
       2               2
    __ 3__          __ 2__
   /       \       /       \
   X       3       3       3
   N       6       4       5
 /   \   /   \   /   \   /   \
 X   X   X   X   X   X   4   4
 N   N   N   N   N   N   8   7


FlipEquivalentBinaryTrees Recur: 1
 */
#endif
