#ifndef _ALL_POSSIBLE_FULL_BINARY_TREE_H
#define _ALL_POSSIBLE_FULL_BINARY_TREE_H
#include "Debug.h"
/*
Leetcode: All Possible Full Binary Tree
A full binary tree is a binary tree where each node has exactly 0 or 2 children.
Return a list of all possible full binary trees with N nodes.  Each element of the answer is the root node of one possible tree.
Each node of each tree in the answer must have node.val = 0.
You may return the final list of trees in any order.
Example 1:
Input: 7
Output: [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]
 */
class AllPossibleFullBinaryTree
{
public:
    AllPossibleFullBinaryTree(){}

    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };

    std::vector<TreeNode*> Enumerate(int N)
    {
        std::unordered_map<int, std::vector<TreeNode*>> visit;
        return recur(N, visit);
    }
    std::vector<TreeNode *> recur(int N, std::unordered_map<int,std::vector<TreeNode*>> & visit)
    {
        std::vector<TreeNode*> res;
        if (N % 2 == 0) return res;
        if (visit.count(N)) return visit[N];
        if (N == 1)
        {
            res.push_back(new TreeNode(0));
            return res;
        }
        --N;
        for (int leftCount = 1; leftCount < N; leftCount += 2)
        {
            std::vector<TreeNode*> leftV = recur(leftCount, visit);
            std::vector<TreeNode*> rightV = recur(N-leftCount, visit);
            for (TreeNode*& left : leftV)
                for (TreeNode *& right : rightV)
                {
                    TreeNode * root = new TreeNode(0);
                    root->left = left;
                    root->right = right;
                    res.push_back(root);
                }
        }
        visit.insert({N, res});
        return res;
    }
};
/*
AllPossibleFullBinaryTree for nodeCount=7:

               1
        ______ 0______
       /               \
       2               2
    __ 0__          __ 0__
   /       \       /       \
   X       X       3       3
   N       N       0       0
 /   \   /   \   /   \   /   \
 X   X   X   X   X   X   4   4
 N   N   N   N   N   N   0   0


               1
        ______ 0______
       /               \
       2               2
    __ 0__          __ 0__
   /       \       /       \
   X       X       3       3
   N       N       0       0
 /   \   /   \   /   \   /   \
 X   X   X   X   4   4   X   X
 N   N   N   N   0   0   N   N


       1
    __ 0__
   /       \
   2       2
   0       0
 /   \   /   \
 3   3   3   3
 0   0   0   0


               1
        ______ 0______
       /               \
       2               2
    __ 0__          __ 0__
   /       \       /       \
   3       3       X       X
   0       0       N       N
 /   \   /   \   /   \   /   \
 X   X   4   4   X   X   X   X
 N   N   0   0   N   N   N   N


               1
        ______ 0______
       /               \
       2               2
    __ 0__          __ 0__
   /       \       /       \
   3       3       X       X
   0       0       N       N
 /   \   /   \   /   \   /   \
 4   4   X   X   X   X   X   X
 0   0   N   N   N   N   N   N


 */
#endif
