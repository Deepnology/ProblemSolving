#ifndef _MIN_CAMERAS_BINARY_TREE_H
#define _MIN_CAMERAS_BINARY_TREE_H
#include "Debug.h"
/*
Leetcode: Binary Tree Cameras
Given a binary tree, we install cameras on the nodes of the tree.
Each camera at a node can monitor its parent, itself, and its immediate children.
Calculate the minimum number of cameras needed to monitor all nodes of the tree.
Input: [0,0,null,0,0]
Output: 1
Explanation: One camera is enough to monitor all nodes if placed as shown.
Input: [0,0,null,0,null,0,null,null,0]
Output: 2
Explanation: At least two cameras are needed to monitor all nodes of the tree.
 */
class MinCamerasBinaryTree
{
public:
    MinCamerasBinaryTree(){}
    ~MinCamerasBinaryTree(){}
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };
    enum Status
    {
        NOT_MONITORED = 0,
        MONITORED_NOCAM = 1,
        MONITORED_WITHCAM = 2
    };
    Status recur(TreeNode * cur, int & sum)
    {
        if (cur == NULL) return MONITORED_NOCAM;//null node is considered monitored with no cam
        Status left = recur(cur->left, sum);
        Status right = recur(cur->right, sum);
        //the most efficient way is to put a cam on a parent node so that it can monitors two children
        //do post-order bottom-up to decide if put a cam on cur node based on its two children
        if (left == NOT_MONITORED || right == NOT_MONITORED)
        {
            ++sum;//add a camera at cur node
            return MONITORED_WITHCAM;//cur is monitored with cam
        }
            //now both left and right are monitored
        else if (left == MONITORED_NOCAM && right == MONITORED_NOCAM)//both left and right are monitored by their child
            return NOT_MONITORED;//cur is not monitored
        else//at least on child contains a cam
            return MONITORED_NOCAM;//cur is monitored with no cam
    }

    int Recur(TreeNode * root)
    {
        int res = 0;
        Status rootStatus = recur(root, res);
        if (rootStatus == NOT_MONITORED)
            ++res;
        std::cout << "MinCamerasBinaryTree Recur: " << res << std::endl;
        return res;
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
    __ 0__
   /       \
   2       X
   0       N
 /   \   /   \
 3   3   X   X
 0   0   N   N


MinCamerasBinaryTree Recur: 1

                               1
                ______________ 0______________
               /                               \
               2                               X
        ______ 0______                  ______ N______
       /               \               /               \
       3               X               X               X
    __ 0__          __ N__          __ N__          __ N__
   /       \       /       \       /       \       /       \
   4       X       X       X       X       X       X       X
   0       N       N       N       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   5   X   X   X   X   X   X   X   X   X   X   X   X   X   X
 N   0   N   N   N   N   N   N   N   N   N   N   N   N   N   N


MinCamerasBinaryTree Recur: 2
 */
#endif
