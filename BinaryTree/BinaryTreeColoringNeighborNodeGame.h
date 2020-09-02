#ifndef _BINARY_TREE_COLORING_NEIGHBOR_NODE_GAME_H
#define _BINARY_TREE_COLORING_NEIGHBOR_NODE_GAME_H
#include "Debug.h"
/*
Leetcode: Binary Tree Coloring Game
Two players play a turn based game on a binary tree.
We are given the root of this binary tree, and the number of nodes n in the tree.
n is odd, and each node has a distinct value from 1 to n.
Initially, the first player names a value x with 1 <= x <= n, and the second player names a value y with 1 <= y <= n and y != x.
The first player colors the node with value x red, and the second player colors the node with value y blue.
Then, the players take turns starting with the first player.
In each turn, that player chooses a node of their color (red if player 1, blue if player 2) and colors an uncolored neighbor of the chosen node (either the left child, right child, or parent of the chosen node.)
If (and only if) a player cannot choose such a node in this way, they must pass their turn.  If both players pass their turn, the game ends, and the winner is the player that colored more nodes.
You are the second player.
If it is possible to choose such a y to ensure you win the game, return true.  If it is not possible, return false.
 */
class BinaryTreeColoringNeighborNodeGame
{
public:
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };
    //total n (odd) nodes in the tree with distinct node values
    //x is the node value that 1st player chose
    bool Can2ndPlayerWin(TreeNode * root, int n, int x)
    {
        int leftCount = 0;
        int rightCount = 0;
        int totalCount = countRecur(root, x, leftCount, rightCount);
        //when player2 choose left child or right child of x
        if (leftCount > totalCount/2 || rightCount > totalCount/2) return true;
        //when player2 choose parent node of x
        if (totalCount-(leftCount+rightCount+1) > totalCount/2) return true;
        return false;
    }
private:
    int countRecur(TreeNode * cur, int val, int & leftCount, int & rightCount)
    {
        if (cur == NULL) return 0;
        int left = countRecur(cur->left, val, leftCount, rightCount);
        int right = countRecur(cur->right, val, leftCount, rightCount);
        if (cur->val == val)
        {
            leftCount = left;
            rightCount = right;
        }
        return left + right + 1;
    }
};
#endif
