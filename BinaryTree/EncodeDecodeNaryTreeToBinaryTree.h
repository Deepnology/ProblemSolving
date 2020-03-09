#ifndef _ENCODE_DECODE_NARY_TREE_TO_BINARY_TREE_H
#define _ENCODE_DECODE_NARY_TREE_TO_BINARY_TREE_H
#include "Debug.h"
/*
Leetcode: Encode N-ary Tree to Binary Tree
Design an algorithm to encode an N-ary tree into a binary tree and decode the binary tree to get the original N-ary tree.
An N-ary tree is a rooted tree in which each node has no more than N children.
Similarly, a binary tree is a rooted tree in which each node has no more than 2 children.
There is no restriction on how your encode/decode algorithm should work.
You just need to ensure that an N-ary tree can be encoded to a binary tree and this binary tree can be decoded to the original N-nary tree structure.

   1
 / | \
2  3  4

to:

 1
/
2
 \
  3
   \
    4
 */
class EncodeDecodeNaryTreeToBinaryTree
{
public:
    EncodeDecodeNaryTreeToBinaryTree(){}
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };
    struct Node
    {
        int val;
        std::vector<Node*> children;
        Node() {}
        Node(int _val, std::vector<Node*> _children)
        {
            val = _val;
            children = _children;
        }
    };

    // Encodes an n-ary tree to a binary tree.
    TreeNode* encode(Node * root)
    {
        if (root == NULL) return NULL;
        TreeNode * res = new TreeNode(root->val);
        if (!root->children.empty())
            res->left = encode(root->children[0]);
        TreeNode * cur = res->left;
        for (int i = 1; i < root->children.size(); ++i)
        {
            cur->right = encode(root->children[i]);
            cur = cur->right;
        }
        return res;
    }

    // Decodes your binary tree to an n-ary tree.
    Node* decode(TreeNode * root)
    {
        if (root == NULL) return NULL;
        Node * res = new Node(root->val, std::vector<Node*>());
        TreeNode * cur = root->left;
        while (cur)
        {
            res->children.push_back(decode(cur));
            cur = cur->right;
        }
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
#endif
