#ifndef _BINARY_TREE_PREORDER_SUCC_H
#define _BINARY_TREE_PREORDER_SUCC_H
#include "Debug.h"
/*

 */
class BinaryTreePreOrderSucc
{
public:
    BinaryTreePreOrderSucc(){}
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL), parent(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
        TreeNode * parent;
    };
    TreeNode * Find_BST_Only(TreeNode * root, TreeNode * aNode)
    {
        if (root == NULL || aNode == NULL)
            return NULL;
        TreeNode * res = NULL;

        if (aNode->left)
            res = aNode->left;
        else if (aNode->right)
            res = aNode->right;
        else//aNode is a leaf: similar to InOrderSucc
        {
            TreeNode * parent = NULL;
            while (root)
            {
                if (aNode->val < root->val)
                {
                    parent = root;
                    root = root->left;
                }
                else if (aNode->val > root->val)
                    root = root->right;
                else
                    break;
            }
            res = parent->right;
        }


        std::cout << "BinaryTreePreOrderSucc Find_BST_Only for \"" << aNode->val << "\": " << (res == NULL ? std::string("NULL") : std::to_string(res->val)) << std::endl;
        return res;
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

template<>
std::string PrintBinaryTree<BinaryTreePreOrderSucc::TreeNode, std::ostringstream>::selectVal2(int depthY, BinaryTreePreOrderSucc::TreeNode * n)
{
    std::ostringstream oss;
    if (n->parent)
        oss << n->parent->val;
    else
        oss << "N";
    return oss.str();
};
/*
BinaryTreePreOrderSucc Find_BST_Only for "3": 8
BinaryTreePreOrderSucc Find_BST_Only for "8": 7
BinaryTreePreOrderSucc Find_BST_Only for "7": NULL

       N
    __ 6__
   /       \
   6       6
   2       8
 /   \   /   \
 X   2   8   X
 N   3   7   N

 */
#endif
