#ifndef _FLATTEN_BINARY_TREE_IN_INORDER_H
#define _FLATTEN_BINARY_TREE_IN_INORDER_H
#include "Debug.h"
/*
Leetcode: Increasing Order Search Tree
Given a tree, rearrange the tree in in-order so that the leftmost node in the tree is now the root of the tree, and every node has no left child and only 1 right child.
Example 1:
Input: [5,3,6,2,4,null,8,1,null,null,null,7,9]

       5
      / \
    3    6
   / \    \
  2   4    8
 /        / \
1        7   9

Output: [1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]

 1
  \
   2
    \
     3
      \
       4
        \
         5
          \
           6
            \
             7
              \
               8
                \
                 9
 */
class FlattenBinaryTreeInInorder
{
public:
    FlattenBinaryTreeInInorder(){}
    ~FlattenBinaryTreeInInorder(){}
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL){}
        int val;
        TreeNode * left;
        TreeNode * right;
    };

    TreeNode * Iterate(TreeNode * root)
    {
        std::stack<TreeNode*> stk;
        TreeNode * cur = root;
        root = NULL;
        TreeNode * pre = NULL;
        for (;cur!=NULL;cur=cur->left)
            stk.push(cur);
        while(!stk.empty())
        {
            cur = stk.top(); stk.pop();
            cur->left = NULL; // !!!!! remember
            //inorder traversal, now visit cur node

            if (!root)
            {
                root = cur;
                pre = cur;
            }
            else
            {
                pre->right = cur;
                pre = pre->right;
            }
            for(cur=cur->right;cur!=NULL;cur=cur->left)
                stk.push(cur);
        }
        return root;
    }

    TreeNode * Recur(TreeNode * root)
    {
        TreeNode * resRoot = NULL;
        TreeNode * pre = NULL;
        recur(root, pre, resRoot);
        return resRoot;
    }
    void recur(TreeNode * cur, TreeNode *& pre, TreeNode *& resRoot)
    {
        if (cur == NULL) return;
        recur(cur->left, pre, resRoot);
        cur->left = NULL;
        if (!resRoot)
        {
            resRoot = cur;
            pre = cur;
        }
        else
        {
            pre->right = cur;
            pre = pre->right;
        }
        recur(cur->right, pre, resRoot);
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
FlattenBinaryTreeInInorder:

               1
        ______ 5______
       /               \
       2               2
    __ 3__          __ 6__
   /       \       /       \
   3       3       X       X
   2       4       N       N
 /   \   /   \   /   \   /   \
 4   X   X   X   X   X   X   X
 1   N   N   N   N   N   N   N


                                                               1
                                ______________________________ 1______________________________
                               /                                                               \
                               X                                                               2
                ______________ N______________                                  ______________ 2______________
               /                               \                               /                               \
               X                               X                               X                               3
        ______ N______                  ______ N______                  ______ N______                  ______ 3______
       /               \               /               \               /               \               /               \
       X               X               X               X               X               X               X               4
    __ N__          __ N__          __ N__          __ N__          __ N__          __ N__          __ N__          __ 4__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       X       X       X       X       X       X       X       X       X       X       X       5
   N       N       N       N       N       N       N       N       N       N       N       N       N       N       N       5
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   6
 N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   6
 */
#endif
