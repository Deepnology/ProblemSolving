#ifndef _BST_ITERATOR_BIDIRECTIONAL_H
#define _BST_ITERATOR_BIDIRECTIONAL_H
#include "Debug.h"
/*
Leetcode: Binary Search Tree Iterator II
Implement the BSTIterator class that represents an iterator over the in-order traversal of a binary search tree (BST):
BSTIterator(TreeNode root) Initializes an object of the BSTIterator class. The root of the BST is given as part of the constructor. The pointer should be initialized to a non-existent number smaller than any element in the BST.
boolean hasNext() Returns true if there exists a number in the traversal to the right of the pointer, otherwise returns false.
int next() Moves the pointer to the right, then returns the number at the pointer.
boolean hasPrev() Returns true if there exists a number in the traversal to the left of the pointer, otherwise returns false.
int prev() Moves the pointer to the left, then returns the number at the pointer.
Notice that by initializing the pointer to a non-existent smallest number, the first call to next() will return the smallest element in the BST.
You may assume that next() and prev() calls will always be valid. That is, there will be at least a next/previous number in the in-order traversal when next()/prev() is called.
Follow up: Could you solve the problem without precalculating the values of the tree?
 */
class BSTIteratorBidirectional
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
    std::stack<TreeNode*> nxtStk;
    std::stack<TreeNode*> preStk;//preStk.top() refers to the node that is currently being traversed
    std::unordered_set<TreeNode*> visit;
public:
    BSTIteratorBidirectional(TreeNode* root)
    {
        while (root)
        {
            nxtStk.push(root);
            root = root->left;
        }
    }

    bool hasNext()
    {
        return !nxtStk.empty();
    }

    int next()
    {
        TreeNode * cur = nxtStk.top(); nxtStk.pop();
        if (!visit.count(cur))
        {
            visit.insert(cur);
            TreeNode * RSubLmost = cur->right;
            while (RSubLmost)
            {
                nxtStk.push(RSubLmost);
                RSubLmost = RSubLmost->left;
            }
        }

        preStk.push(cur);//preStk.top() refers to the node that is currently being traversed
        return cur->val;
    }

    bool hasPrev()
    {
        return preStk.size()>=2; //preStk.top() refers to the node that is currently being traversed
    }

    int prev()
    {
        TreeNode * cur = preStk.top(); preStk.pop();
        nxtStk.push(cur);//move the node that is currently being traversed to nxtStk
        return preStk.top()->val;
    }
};
#endif
