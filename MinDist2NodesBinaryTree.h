/*Facebook*/
#ifndef _MIN_DIST_2_NODES_BINARY_TREE_H
#define _MIN_DIST_2_NODES_BINARY_TREE_H
#include "Debug.h"
/*
Given a binary tree with its root node and two arbitrary nodes in the tree, find the min distance between the two nodes.
 */
class MinDist2NodesBinaryTree
{
public:
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };
    MinDist2NodesBinaryTree(){}

    int HashMap(TreeNode * root, TreeNode * p, TreeNode * q)
    {
        if (!root || !p || !q) return 0;

        std::unordered_map<TreeNode *, TreeNode *> chdToP;
        chdToP[root] = NULL;
        //perform preorder traversal w/ stack to construct chdToP map
        std::stack<TreeNode *> stk;
        stk.push(root);
        while (!stk.empty())
        {
            TreeNode * cur = stk.top(); stk.pop();
            if (cur->left) chdToP[cur->left] = cur;
            if (cur->right) chdToP[cur->right] = cur;
            if (cur->right) stk.push(cur->right);
            if (cur->left) stk.push(cur->left);
        }

        //Find LCA, BFS_BottomUp + HashSet
        std::unordered_set<TreeNode *> visit;
        TreeNode * curP = p;
        TreeNode * curQ = q;
        TreeNode * LCA = NULL;
        while (curP || curQ)
        {
            if (curP)
            {
                if (visit.count(curP))
                {
                    LCA = curP;
                    break;
                }
                visit.insert(curP);
                curP = chdToP[curP];
            }
            if (curQ)
            {
                if (visit.count(curQ))
                {
                    LCA = curQ;
                    break;
                }
                visit.insert(curQ);
                curQ = chdToP[curQ];
            }
        }

        int lenP = 0;
        int lenQ = 0;
        curP = p;
        curQ = q;
        while (curP != LCA)
        {
            ++lenP;
            curP = chdToP[curP];
        }
        while (curQ != LCA)
        {
            ++lenQ;
            curQ = chdToP[curQ];
        }

        std::cout << "MinDist2NodesBinaryTree HashMap for [" << p->val << "," << q->val << "]: " << lenP << "+" << lenQ << " (LCA=" << LCA->val << ")" << std::endl;
        return lenP + lenQ;
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
        ______ 0______
       /               \
       2               2
    __ 1__          __ 8__
   /       \       /       \
   3       3       3       3
   2       5       9      12
 /   \   /   \   /   \   /   \
 4   4   4   4   4   4   4   4
 3   4   6   7  10  11  13  14


MinDist2NodesBinaryTree HashMap for [2,13]: 2+3 (LCA=0)
MinDist2NodesBinaryTree HashMap for [4,11]: 3+3 (LCA=0)
MinDist2NodesBinaryTree HashMap for [4,4]: 0+0 (LCA=4)
MinDist2NodesBinaryTree HashMap for [4,2]: 1+0 (LCA=2)
MinDist2NodesBinaryTree HashMap for [0,10]: 0+3 (LCA=0)
MinDist2NodesBinaryTree HashMap for [8,12]: 0+1 (LCA=8)
MinDist2NodesBinaryTree HashMap for [9,11]: 0+1 (LCA=9)
 */
#endif
