#ifndef _DELETE_TGT_NODES_RETURN_REMAINING_SUBTREES_H
#define _DELETE_TGT_NODES_RETURN_REMAINING_SUBTREES_H
#include "Debug.h"
/*
Leetcode: Delete Nodes And Return Forest
Given the root of a binary tree, each node in the tree has a distinct value.
After deleting all nodes with a value in to_delete, we are left with a forest (a disjoint union of trees).
Return the roots of the trees in the remaining forest.  You may return the result in any order.
Example 1:
Input: root = [1,2,3,4,5,6,7], to_delete = [3,5]
Output: [[1,2,null,4],[6],[7]]
 */
class DeleteTgtNodesReturnRemainingSubtrees
{
public:
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL){}
        int val;
        TreeNode * left;
        TreeNode * right;
    };
    std::vector<TreeNode*> DFS(TreeNode* root, std::vector<int>& to_delete)
    {
        std::unordered_set<int> del;
        for (auto i : to_delete) del.insert(i);
        std::vector<TreeNode*> res;
        if (!del.count(root->val))
            res.push_back(root);
        recur(root, del, res);
        return res;
    }
private:
    TreeNode * recur(TreeNode * cur, std::unordered_set<int> & del, std::vector<TreeNode*> & res)
    {
        if (cur == NULL) return NULL;
        cur->left = recur(cur->left, del, res);
        cur->right = recur(cur->right, del, res);
        if (del.count(cur->val))
        {
            if (cur->left) res.push_back(cur->left);
            if (cur->right) res.push_back(cur->right);
            return NULL;
        }
        return cur;
    }
};
#endif
