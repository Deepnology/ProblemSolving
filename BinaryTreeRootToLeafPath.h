#ifndef _BINARY_TREE_ROOT_TO_LEAF_PATH_H
#define _BINARY_TREE_ROOT_TO_LEAF_PATH_H
#include "Debug.h"
/*
Leetcode: Sum of Root To Leaf Binary Numbers
Given a binary tree, each node has value 0 or 1.
Each root-to-leaf path represents a binary number starting with the most significant bit.
For example, if the path is 0 -> 1 -> 1 -> 0 -> 1, then this could represent 01101 in binary, which is 13.
For all leaves in the tree, consider the numbers represented by the path from the root to that leaf.
Return the sum of these numbers.
Example 1:
Input: [1,0,1,0,1,0,1]
Output: 22
Explanation: (100) + (101) + (110) + (111) = 4 + 5 + 6 + 7 = 22

Leetcode: Smallest String Starting From Leaf
Given the root of a binary tree, each node has a value from 0 to 25 representing the letters 'a' to 'z': a value of 0 represents 'a', a value of 1 represents 'b', and so on.
Find the lexicographically smallest string that starts at a leaf of this tree and ends at the root.
(As a reminder, any shorter prefix of a string is lexicographically smaller: for example, "ab" is lexicographically smaller than "aba".
A leaf of a node is a node that has no children.)
Example 1:
Input: [0,1,2,3,4,3,4]
Output: "dba"
Example 2:
Input: [25,1,3,1,3,0,2]
Output: "adz"
Example 3:
Input: [2,2,1,null,1,0,null,0]
Output: "abc"
 */
class BinaryTreeRootToLeafPath
{
public:
    BinaryTreeRootToLeafPath(){}
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };
    int SumRootToLeafBinaryNums(TreeNode * root)
    {
        int res = 0;
        std::vector<int> path;
        recur(root, path, res);
        return res;
    }
    void recur(TreeNode * cur, std::vector<int> & path, int & res)
    {
        if (cur == NULL) return;
        path.push_back(cur->val);
        if (!cur->left && !cur->right)
        {
            int num = 0;
            int N = path.size();
            for (int i = 0; i < N; ++i)
                num = (num << 1) | path[i];
            res += num;
            path.pop_back();
            return;
        }
        recur(cur->left, path, res);
        recur(cur->right, path, res);
        path.pop_back();
    }

    std::string SmallestStrLeafToRoot(TreeNode * root)
    {
        std::string path;
        std::string res;
        recur(root, path, res);
        return res;
    }
    void recur(TreeNode * cur, std::string & path, std::string & res)
    {
        if (cur == NULL) return;
        char c = cur->val + 'a';
        path.insert(0, 1, c);
        if (!cur->left && !cur->right)
        {
            if (res.empty() || path.compare(res) < 0)
                res = path;
            path.erase(0, 1);
            return;
        }
        recur(cur->left, path, res);
        recur(cur->right, path, res);
        path.erase(0, 1);
    }
};
#endif
