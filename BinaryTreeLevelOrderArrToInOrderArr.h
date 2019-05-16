#ifndef _BINARY_TREE_LEVEL_ORDER_ARR_TO_IN_ORDER_ARR_H
#define _BINARY_TREE_LEVEL_ORDER_ARR_TO_IN_ORDER_ARR_H
#include "Debug.h"
/*
http://code.cloudkaksha.org/binary-search-tree/print-inorder-traversal-of-an-array-representing-bst
Complete Binary Tree
Input:
              4
           /     \
          2       6
        /  \     /  \
       1    3    5   7
This BST is stored in array as
arr[] = {4, 2, 6, 1, 3, 5, 7}

The Output should be:
1 2 3 4 5 6 7
 */
class BinaryTreeLevelOrderArrToInOrderArr
{
public:
    BinaryTreeLevelOrderArrToInOrderArr(){}
    ~BinaryTreeLevelOrderArrToInOrderArr(){}

    std::vector<int> Recur(std::vector<int> && levelOrder)
    {
        std::vector<int> res;
        recur(levelOrder, 0, levelOrder.size()-1, res);
        std::cout << "BinaryTreeLevelOrderArrToInOrderArr for [" << Debug::ToStr1D<int>()(levelOrder) << "]: " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }
    void recur(const std::vector<int> & levelOrder, int begin, int end, std::vector<int> & inOrder)
    {
        if (begin > end) return;
        recur(levelOrder, begin*2+1, end, inOrder);
        inOrder.push_back(levelOrder[begin]);
        recur(levelOrder, begin*2+2, end, inOrder);
    }
};
/*
BinaryTreeLevelOrderArrToInOrderArr for [4, 2, 6, 1, 3, 5, 7]: 1, 2, 3, 4, 5, 6, 7
 */
#endif
