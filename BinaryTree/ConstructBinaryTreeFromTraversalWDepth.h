#ifndef _CONSTRUCT_BINARY_TREE_FROM_TRAVERSAL_W_DEPTH_H
#define _CONSTRUCT_BINARY_TREE_FROM_TRAVERSAL_W_DEPTH_H
#include "Debug.h"
/*
Leetcode: Recover a Tree From Preorder Traversal
We run a preorder depth first search on the root of a binary tree.
At each node in this traversal, we output D dashes (where D is the depth of this node), then we output the value of this node.
(If the depth of a node is D, the depth of its immediate child is D+1.  The depth of the root node is 0.)
If a node has only one child, that child is guaranteed to be the left child.
Given the output S of this traversal, recover the tree and return its root.
Example 1:
Input: "1-2--3--4-5--6--7"
Output: [1,2,5,3,4,6,7]
Example 2:
Input: "1-2--3---4-5--6---7"
Output: [1,2,5,3,null,6,null,4,null,7]
Example 3:
Input: "1-401--349---90--88"
Output: [1,401,null,349,88,90]
 */
class ConstructBinaryTreeFromTraversalWDepth
{
public:
    ConstructBinaryTreeFromTraversalWDepth(){}

    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };

    TreeNode * FromPreorder(std::string S)
    {
        int cur = 0;
        return recur(S, cur, 0);
    }
    TreeNode * recur(std::string & preorder, int & cur, int depth)
    {
        int N = preorder.size();
        int begin = cur;
        while (cur < N && preorder[cur] == '-')
            ++cur;
        int countDash = cur-begin;
        if (countDash != depth)
        {
            cur = begin;//restore
            return NULL;
        }
        begin = cur;
        while (cur < N && isdigit(preorder[cur]))
            ++cur;
        int curVal = stoi(preorder.substr(begin,cur-begin));

        TreeNode * root = new TreeNode(curVal);
        root->left = recur(preorder, cur, depth+1);
        root->right = recur(preorder, cur, depth+1);
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
ConstructBinaryTreeFromTraversalWDepth from 1-2--3--4-5--6--7:

       1
    __ 1__
   /       \
   2       2
   2       5
 /   \   /   \
 3   3   3   3
 3   4   6   7

 */
#endif
