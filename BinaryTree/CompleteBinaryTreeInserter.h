#ifndef _COMPLETE_BINARY_TREE_INSERTER_H
#define _COMPLETE_BINARY_TREE_INSERTER_H
#include "Debug.h"
/*
Leetcode: Complete Binary Tree Inserter
A complete binary tree is a binary tree in which every level, except possibly the last, is completely filled, and all nodes are as far left as possible.
Write a data structure CBTInserter that is initialized with a complete binary tree and supports the following operations:
CBTInserter(TreeNode root) initializes the data structure on a given tree with head node root;
CBTInserter.insert(int v) will insert a TreeNode into the tree with value node.val = v so that the tree remains complete, and returns the value of the parent of the inserted TreeNode;
CBTInserter.get_root() will return the head node of the tree.
Example 1:
Input: inputs = ["CBTInserter","insert","get_root"], inputs = [[[1]],[2],[]]
Output: [null,1,[1,2]]
Example 2:
Input: inputs = ["CBTInserter","insert","insert","get_root"], inputs = [[[1,2,3,4,5,6]],[7],[8],[]]
Output: [null,3,4,[1,2,3,4,5,6,7,8]]
 */
class CompleteBinaryTreeInserter
{
public:
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };
private:
    std::vector<TreeNode*> levelOrder;
public:
    CompleteBinaryTreeInserter(TreeNode * root)
    {
        std::queue<TreeNode*> que;
        que.push(root);
        while (!que.empty())
        {
            root = que.front();
            que.pop();
            levelOrder.push_back(root);
            if (root->left) que.push(root->left);
            if (root->right) que.push(root->right);
        }
    }

    int Insert(int v)
    {
        TreeNode * cur = new TreeNode(v);
        int N = levelOrder.size();
        levelOrder.push_back(cur);
        if (N % 2 == 1)//cur will be a left child
            levelOrder[(N-1)/2]->left = cur;
        else
            levelOrder[(N-1)/2]->right = cur;

        std::cout << "Insert " << v << ", parent: " << levelOrder[(N-1)/2]->val << std::endl;
        return levelOrder[(N-1)/2]->val;
    }

    TreeNode* GetRoot()
    {
        return levelOrder[0];
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
Insert 1, parent: 0
Insert 2, parent: 0
Insert 3, parent: 1
Insert 4, parent: 1
Insert 5, parent: 2
Insert 6, parent: 2
Insert 7, parent: 3
Insert 8, parent: 3
Insert 9, parent: 4

               1
        ______ 0______
       /               \
       2               2
    __ 1__          __ 2__
   /       \       /       \
   3       3       3       3
   3       4       5       6
 /   \   /   \   /   \   /   \
 4   4   4   X   X   X   X   X
 7   8   9   N   N   N   N   N

 */
#endif
