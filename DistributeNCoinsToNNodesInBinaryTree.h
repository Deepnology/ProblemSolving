#ifndef _DISTRIBUTE_N_COINS_TO_N_NODES_IN_BINARY_TREE_H
#define _DISTRIBUTE_N_COINS_TO_N_NODES_IN_BINARY_TREE_H
#include "Debug.h"
/*
Leetcode: Distribute Coins in binary tree
Given the root of a binary tree with N nodes, each node in the tree has node.val coins, and there are N coins total.
In one move, we may choose two adjacent nodes and move one coin from one node to another.
(The move may be from parent to child, or from child to parent.)
Return the number of moves required to make every node have exactly one coin.
 */
class DistributeNCoinsToNNodesInBinaryTree
{
public:
    DistributeNCoinsToNNodesInBinaryTree(){}
    ~DistributeNCoinsToNNodesInBinaryTree(){}
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };
    int recur(TreeNode * cur, int & move)
    {
        if (cur == NULL) return 0;
        int left = recur(cur->left, move);
        int right = recur(cur->right, move);
        //post-order bottom-up:
        //left and right:
        //positive num: extra coins needed to move from child to cur
        //negative num: extra coins needed to move from cur to child
        move += abs(left) + abs(right);
        return cur->val + left + right - 1;//sum of total coins and leave one at cur node
    }
    int Recur(TreeNode * root)
    {
        int move = 0;
        recur(root, move);
        return move;
    }
};
#endif
