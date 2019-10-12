#ifndef _MIN_COST_BINARY_TREE_FROM_LEAF_VALUES_H
#define _MIN_COST_BINARY_TREE_FROM_LEAF_VALUES_H
#include "Debug.h"
/*
Leetcode: Minimum Cost Tree From Leaf Values
Given an array arr of positive integers, consider all binary trees such that:
Each node has either 0 or 2 children;
The values of arr correspond to the values of each leaf in an in-order traversal of the tree.  (Recall that a node is a leaf if and only if it has 0 children.)
The value of each non-leaf node is equal to the product of the largest leaf value in its left and right subtree respectively.
Among all possible binary trees considered, return the smallest possible sum of the values of each non-leaf node.
It is guaranteed this sum fits into a 32-bit integer.
Example 1:
Input: arr = [6,2,4]
Output: 32
Explanation:
There are two possible trees.  The first has non-leaf node sum 36, and the second has non-leaf node sum 32.

    24            24
   /  \          /  \
  12   4        6    8
 /  \               / \
6    2             2   4

 */
class MinCostBinaryTreeFromLeafValues
{
public:
    int Greedy(std::vector<int> && arr)
    {
        //greedy: O(N^2) time
        int sum = 0;
        while(arr.size() > 1)
        {
            int del = 0;
            int minProduct = INT_MAX;
            for(int i = 0; i < arr.size()-1; ++i)
            {
                if(arr[i]*arr[i+1] < minProduct)
                {
                    del = i;
                    minProduct = arr[i]*arr[i+1];
                }
            }
            sum += minProduct;
            if(arr[del] > arr[del+1])
                del = del+1;
            arr.erase(arr.begin() + del);
        }

        std::cout << "MinCostBinaryTreeFromLeafValues Greedy for [" << Debug::ToStr1D<int>()(arr) << "]: " << sum << std::endl;
        return sum;
    }
    int Stack(std::vector<int> && arr)
    {
        //stack: O(N) time
        arr.insert(arr.begin(), INT_MAX);
        arr.push_back(INT_MAX);
        //insert two INT_MAX at boundaries in order to find min
        std::stack<int> stk;//sorted in desc order
        int res = 0;
        for (int i = 0; i < arr.size(); ++i)
        {
            while (!stk.empty() && arr[stk.top()] < arr[i])
            {
                int curMin = stk.top();//left smaller nodes than cur node i
                stk.pop();
                int minLeftRight = std::min(arr[stk.top()], arr[i]);
                if (minLeftRight != INT_MAX)
                    res += minLeftRight * arr[curMin];
            }
            stk.push(i);
        }

        std::cout << "MinCostBinaryTreeFromLeafValues Stack for [" << Debug::ToStr1D<int>()(arr) << "]: " << res << std::endl;
        return res;
    }
};
/*
MinCostBinaryTreeFromLeafValues Greedy for [6]: 32
MinCostBinaryTreeFromLeafValues Stack for [2147483647, 6, 2, 4, 2147483647]: 32
 */
#endif
