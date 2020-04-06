#ifndef _SAME_LEAF_VAL_SEQ_BINARY_TREES_H
#define _SAME_LEAF_VAL_SEQ_BINARY_TREES_H
#include "Debug.h"
/*
Leetcode: Leaf-similar binary trees
Consider all the leaves of a binary tree.  From left to right order, the values of those leaves form a leaf value sequence.
For example, in the given tree above, the leaf value sequence is (6, 7, 4, 9, 8).
Two binary trees are considered leaf-similar if their leaf value sequence is the same.
Return true if and only if the two given trees with head nodes root1 and root2 are leaf-similar.
 */
class SameLeafValSeqBinaryTrees
{
public:
    SameLeafValSeqBinaryTrees(){}
    ~SameLeafValSeqBinaryTrees(){}
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };

    struct BTIterator
    {
        std::stack<TreeNode *> m_LmostStk;
        BTIterator(TreeNode * root)
        {
            TreeNode * cur = root;
            while (cur)
            {
                m_LmostStk.push(cur);
                cur = cur->left;
            }
        }
        TreeNode * Next()
        {
            if (m_LmostStk.empty()) return NULL;
            TreeNode * res = m_LmostStk.top();
            m_LmostStk.pop();
            TreeNode * RSubLmost = res->right;
            while (RSubLmost)
            {
                m_LmostStk.push(RSubLmost);
                RSubLmost = RSubLmost->left;
            }
            return res;
        }
        TreeNode * NextLeaf()
        {
            TreeNode * res = Next();
            while (res && (res->left || res->right))
                res = Next();
            return res;
        }
    };

    bool UseBTIterator(TreeNode * root1, TreeNode * root2)
    {
        BTIterator itr1(root1);
        BTIterator itr2(root2);
        for (root1 = itr1.NextLeaf(), root2 = itr2.NextLeaf(); root1 || root2; root1 = itr1.NextLeaf(), root2 = itr2.NextLeaf())
        {
            if (root1 == NULL || root2 == NULL) return false;
            if (root1->val != root2->val) return false;
        }
        return true;
    }
};
#endif
