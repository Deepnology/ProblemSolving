/*Facebook*/
#ifndef _FIRST_PAIR_NON_MATCHING_LEAF_BST_H
#define _FIRST_PAIR_NON_MATCHING_LEAF_BST_H
#include "Debug.h"
/*
https://gist.github.com/gcrfelix/0ea6b38e0ae7e45f7bce7e3777186884
Given 2 preorder arrays of 2 BSTs.
Find first pair of non-matching leaves.
Follow-up: what if it is general binary tree, not BST?

    2        2      2    2         3         3      1         1
   / \      / \    /      \       /         /        \         \
  1  3     1  4   1       3      1         2          3         2
                                  \       /          /           \
                                   2     1          2             3

 2,1,3     2,1,4  2,1   2,3     3,1,2  3,2,1     1,3,2       1,2,3
 */
class FirstPairNonMatchingLeafBST
{
public:
    FirstPairNonMatchingLeafBST(){}

    std::vector<int> BST_UseStack(const std::vector<int> & preorder1, const std::vector<int> & preorder2)
    {
        int N = preorder1.size();
        int M = preorder2.size();
        std::stack<int> stk1;
        std::stack<int> stk2;
        int i = 0;
        int j = 0;
        int leaf1 = -1;
        int leaf2 = -1;
        while (true)
        {
            while (i < N)
            {
                int cur = preorder1[i];
                int countPop = 0;
                while (!stk1.empty() && cur > stk1.top())
                {
                    stk1.pop();
                    ++countPop;
                }
                if (countPop >= 2) break;
                stk1.push(cur);
                leaf1 = cur;
                ++i;
            }
            while (j < M)
            {
                int cur = preorder2[j];
                int countPop = 0;
                while (!stk2.empty() && cur > stk2.top())
                {
                    stk2.pop();
                    ++countPop;
                }
                if (countPop >= 2) break;
                stk2.push(cur);
                leaf2 = cur;
                ++j;
            }

            if (leaf1 != leaf2)
                return {leaf1, leaf2};

            if (i >= N || j >= M)
                return {-1, -1};
        }
    }

    //leaf: [val, -1, -1, ...] or [..., val]
    std::vector<int> NonBST(const std::vector<int> & preorder1, const std::vector<int> & preorder2)
    {
        int N = preorder1.size();
        int M = preorder2.size();
        int i = 0;
        int j = 0;

        while (true)
        {
            while (i < N)
            {
                if (i+2 < N && preorder1[i+1] == -1 && preorder1[i+2] == -1)//[val, -1, -1, ...]
                    break;
                if (i+2 == N && preorder1[i+1] == -1)//[..., val, -1] ??
                    break;
                if (i+1 == N)
                    break;
                ++i;
            }
            while (j < M)
            {
                if (j+2 < M && preorder2[j+1] == -1 && preorder2[j+2] == -1)//[val, -1, -1, ...]
                    break;
                if (j+2 == M && preorder2[j+1] == -1)//[..., val, -1] ??
                    break;
                if (j+1 == M)
                    break;
                ++j;
            }
            if (i >= N || j >= M)
                return {-1, -1};
            if (preorder1[i] != preorder2[j])
                return {preorder1[i], preorder2[j]};
            ++i;
            ++j;
        }

    }
};
#endif
