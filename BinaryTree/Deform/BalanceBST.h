#ifndef _BALANCE_BST_H
#define _BALANCE_BST_H
#include "Debug.h"
/*
Leetcode: Balance a Binary Search Tree
Given a binary search tree, return a balanced binary search tree with the same node values.
A binary search tree is balanced if and only if the depth of the two subtrees of every node never differ by more than 1.
If there is more than one answer, return any of them.
 */
class BalanceBST
{
public:
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };
    //Approach 1: O(N) time, O(logN) space
    TreeNode* FlattenToInorderConstructBSTFromSortedList(TreeNode* root)
    {
        if (root == NULL) return NULL;
        root = FlattenToInorder(root);//1. flatten BST to inorder (sorted) list
        TreeNode * cur = root;
        int count = 1;
        while (NULL != (cur = cur->right))
            ++count;
        return inOrderRecur(root, 0, count - 1);//2. construct BST from sorted list
    }
private:
    TreeNode * FlattenToInorder(TreeNode * root)
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
    TreeNode * inOrderRecur(TreeNode *& cur, int start, int end)
    {
        if (start > end)
            return NULL;

        int middle = start + (end - start) / 2;
        TreeNode * tmp = this->inOrderRecur(cur, start, middle - 1);

        //inorder: cur has been advanced to the middle node
        TreeNode * root = new TreeNode(cur->val);
        root->left = tmp;
        cur = cur->right;//advance cur
        root->right = this->inOrderRecur(cur, middle + 1, end);

        return root;
    }

public:
    //Approach 2: flatten BST to preorder list, then construct BST from it.: O(N) time, O(1) space
};
#endif
