#ifndef _MAX_AVG_SUBTREE_H
#define _MAX_AVG_SUBTREE_H
#include "Debug.h"
/*
Leetcode: Maximum Average Subtree
Given the root of a binary tree, find the maximum average value of any subtree of that tree.
(A subtree of a tree is any node of that tree plus all its descendants.
The average value of a tree is the sum of its values, divided by the number of nodes.)
Example 1:
Input: [5,6,1]
Output: 6.00000
Explanation:
For the node with value = 5 we have an average of (5 + 6 + 1) / 3 = 4.
For the node with value = 6 we have an average of 6 / 1 = 6.
For the node with value = 1 we have an average of 1 / 1 = 1.
So the answer is 6 which is the maximum.
 */
class MaxAvgSubtreeBinaryTree
{
public:
    MaxAvgSubtreeBinaryTree(){}

    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };

    double Recur(TreeNode * root)
    {
        double res = recur(root)[2];
        std::cout << "MaxAvgSubtree Recur: " << res << std::endl;
        return res;
    }
private:
    std::vector<double> recur(TreeNode * cur)
    {
        if (cur == NULL)
            return {0,0,0};//<sum of nodes, num of nodes, max average of a subtree>
        auto left = recur(cur->left);
        auto right = recur(cur->right);
        double sum = cur->val + left[0] + right[0];
        double numNodes = left[1] + right[1] + 1;
        double maxAvg = std::max(left[2], std::max(right[2], sum/numNodes));
        return {sum, numNodes, maxAvg};
    }
};
class MaxAvgSubtree //Amazon OA
{
public:
    MaxAvgSubtree(){}

    struct TreeNode
    {
        TreeNode(int x) : val(x), children() {}
        int val;
        std::vector<TreeNode*> children;
    };
    double Recur(TreeNode * root)
    {
        double res = recur(root)[2];
        std::cout << "MaxAvgSubtree Recur: " << res << std::endl;
        return res;
    }
private:
    std::vector<double> recur(TreeNode * cur)
    {
        if (cur == NULL)
            return {0, 0, 0};
        double sum = cur->val;
        double numNodes = 1;
        double maxAvg = 0;
        int N = cur->children.size();
        for (int i = 0; i < N; ++i)
        {
            auto v = recur(cur->children[i]);
            sum += v[0];
            numNodes += v[1];
            maxAvg = std::max(maxAvg, v[2]);
        }
        maxAvg = std::max(maxAvg, sum / numNodes);
        return {sum, numNodes, maxAvg};
    }

public:
    double Recur2(TreeNode * root) //now a subtree must contain at least 1 child
    {
        double res = recur2(root)[2];
        std::cout << "MaxAvgSubtree Recur2: " << res << std::endl;
        return res;
    }
private:
    std::vector<double> recur2(TreeNode * cur)
    {
        if (cur == NULL)
            return {0, 0, 0};
        double sum = cur->val;
        double numNodes = 1;
        double maxAvg = 0;
        int N = cur->children.size();
        for (int i = 0; i < N; ++i)
        {
            auto v = recur2(cur->children[i]);
            sum += v[0];
            numNodes += v[1];
            maxAvg = std::max(maxAvg, v[2]);
        }
        if (N > 0)
            maxAvg = std::max(maxAvg, sum / numNodes);
        return {sum, numNodes, maxAvg};
    }
};
#endif
