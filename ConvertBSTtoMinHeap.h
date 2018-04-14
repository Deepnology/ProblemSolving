/*Facebook*/
#ifndef _CONVERT_BST_TO_MIN_HEAP_H
#define _CONVERT_BST_TO_MIN_HEAP_H
#include "Debug.h"
/*
https://www.geeksforgeeks.org/convert-bst-min-heap/
https://www.geeksforgeeks.org/in-place-convert-bst-into-a-min-heap/
By definition of MinHeap:

I. MinHeap: all the values in the left subtree of a node should be less than all the values in the right subtree of the node.
Approach:
1. Record all values of BST nodes with inorder traversal in an array, then perform "preorder traversal" to update node values from the inorder array
2. In place: BST -> CDLL with inorder from head to tail -> MinHeap tree using "preorder traversal" on the inorder list

II. MinHeap: the value of a node is less than or equal to all its child nodes (this is more accurate !)
Approach:
1. Record all values of BST nodes with inorder traversal in an array, then perform "levelorder traversal (BFS)" to update node values from the inorder array
2. In place: BST -> CDLL with inorder from head to tail -> MinHeap tree using "levelorder traversal (BFS)" on the inorder list
 */
class ConvertBSTtoMinHeap
{
public:
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };
    ConvertBSTtoMinHeap(){}

    TreeNode * InorderArray(TreeNode * root)
    {
        //1. perform inorder traversal
        std::vector<int> inorder;
        inorderRecur(root, inorder);
        //2. perform levelorder traversal to update nodes' values
        std::queue<TreeNode *> que;
        que.push(root);
        int idx = -1;
        while (!que.empty())
        {
            ++idx;
            TreeNode * cur = que.front(); que.pop();
            cur->val = inorder[idx];
            if (cur->left) que.push(cur->left);
            if (cur->right) que.push(cur->right);
        }
        return root;
    }
private:
    void inorderRecur(TreeNode * cur, std::vector<int> & v)
    {
        if (cur == NULL) return;
        inorderRecur(cur->left, v);
        v.push_back(cur->val);
        inorderRecur(cur->right, v);
    }

public:
    TreeNode * InPlace(TreeNode * root)
    {
        //1. BST to CDLL with inorder from head to tail
        TreeNode * head = BSTtoCDLLRecur(root);

        //2. perform levelorder traversal on CDLL to convert to MinHeap

        //disconnect tail<->head
        head->left->right = NULL;
        head->left = NULL;

        TreeNode * cur = head;
        std::queue<TreeNode *> que;//a queue that saves parent only
        que.push(head);
        cur = cur->right;
        head->left = NULL;//in case root is leaf
        head->right = NULL;//in case root is leaf
        while (cur)//que saves parents, so finally que won't be empty
        {
            TreeNode * parent = que.front(); que.pop();

            TreeNode * left = cur;
            parent->left = left;
            que.push(left);
            cur = cur->right;//advance cur
            left->left = NULL;//in case left is leaf
            left->right = NULL;//in case left is leaf

            if (cur)
            {
                TreeNode * right = cur;
                parent->right = right;
                que.push(right);
                cur = cur->right;
                right->left = NULL;//in case right is leaf
                right->right = NULL;//in case right is leaf
            }
            else
                parent->right = NULL;
        }

        return head;
    }
private:
    TreeNode * BSTtoCDLLRecur(TreeNode * root)
    {
        if (root == NULL)
            return NULL;
        TreeNode * leftHead = BSTtoCDLLRecur(root->left);
        TreeNode * rightHead = BSTtoCDLLRecur(root->right);

        //post-order: now visit the node
        std::string lh = leftHead ? std::to_string(leftHead->val) : "N";
        std::string rh = rightHead ? std::to_string(rightHead->val) : "N";
        //std::cout << root->val << " [" << lh << "," << rh << "]" << std::endl;

        //1. make current node CDLL
        root->left = root;
        root->right = root;

        //2. connect left child CDLL with current node CDLL
        leftHead = this->join2CDLL(leftHead, root);

        //3. connect the result CDLL from 2. with right child CDLL
        leftHead = this->join2CDLL(leftHead, rightHead);

        return leftHead;
    }
    TreeNode * join2CDLL(TreeNode * leftHead, TreeNode * rightHead)
    {
        if (leftHead == NULL)
            return rightHead;
        if (rightHead == NULL)
            return leftHead;

        TreeNode * leftTail = leftHead->left;
        TreeNode * rightTail = rightHead->left;

        //leftHead->right->right->...->leftTail are in increasing order
        //leftTail->left->left->...->leftHead are in decreasing order
        //only leftHead<->leftTail is in reverse order
        //same for rightHead<->rightTail

        //1. connect leftTail to rightHead (in forward order)
        leftTail->right = rightHead;
        rightHead->left = leftTail;

        //2. connect rightTail to leftHead (in reverse order)
        rightTail->right = leftHead;
        leftHead->left = rightTail;

        //now only leftHead<->rightTail is in reverse order
        return leftHead;
    }

public:
    TreeNode * SortedArrayToMinHeap(const std::vector<int> & inorder)
    {
        int N = inorder.size();
        if (N == 0) return NULL;
        TreeNode * root = new TreeNode(inorder[0]);
        int cur = 1;
        std::queue<TreeNode *> que;//a queue that saves parent only
        que.push(root);
        while (cur < N)
        {
            TreeNode * parent = que.front(); que.pop();

            TreeNode * left = new TreeNode(inorder[cur]);
            parent->left = left;
            que.push(left);
            ++cur;

            if (cur < N)
            {
                TreeNode * right = new TreeNode(inorder[cur]);
                parent->right = right;
                que.push(right);
                ++cur;
            }
        }

        return root;
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
    __ 4__
   /       \
   2       2
   2       6
 /   \   /   \
 3   3   3   3
 1   3   5   7

ConvertBSTtoMinHeap UseInOrderArray for above BinaryTree:

       1
    __ 1__
   /       \
   2       2
   2       3
 /   \   /   \
 3   3   3   3
 4   5   6   7



       1
    __ 4__
   /       \
   2       2
   2       6
 /   \   /   \
 3   3   3   3
 1   3   5   7

ConvertBSTtoMinHeap InPlace for above BinaryTree:

       1
    __ 1__
   /       \
   2       2
   2       3
 /   \   /   \
 3   3   3   3
 4   5   6   7


ConvertBSTtoMinHeap SortedArrayToMinHeap:

       1
    __ 1__
   /       \
   2       2
   2       3
 /   \   /   \
 3   3   3   3
 4   5   6   7


 */
#endif
