#ifndef _CLONE_NARY_TREE_H
#define _CLONE_NARY_TREE_H
#include "Debug.h"
/*
Leetcode: Clone N-ary Tree
 */
class CloneNaryTree
{
public:
    struct TreeNode
    {
        TreeNode(int x) : val(x), children() {}
        int val;
        std::vector<TreeNode *> children;
    };

    TreeNode * Recur(TreeNode* root)
    {
        std::unordered_map<TreeNode*,TreeNode*> m;
        return recur(root, m);
    }
    TreeNode * recur(TreeNode * cur)
    {
        if (cur == NULL) return NULL;
        TreeNode * copy = new TreeNode(cur->val);
        for (auto chd : cur->children)
            copy->children.push_back(recur(chd));
        return copy;
    }
    TreeNode * recur(TreeNode * cur, std::unordered_map<TreeNode*,TreeNode*> & m)
    {
        if (cur == NULL) return NULL;
        if (m.count(cur)) return m[cur];
        m[cur] = new TreeNode(cur->val);
        for (auto chd : cur->children)
            m[cur]->children.push_back(recur(chd, m));
        return m[cur];
    }
};
#endif
