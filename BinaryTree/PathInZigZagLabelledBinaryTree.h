#ifndef _PATH_IN_ZIGZAG_LABELLED_BINARY_TREE_H
#define _PATH_IN_ZIGZAG_LABELLED_BINARY_TREE_H
#include "Debug.h"
/*
Leetcode: Path in Zigzag Labelled Binary Tree
In an infinite binary tree where every node has two children, the nodes are labelled in row order.
In the odd numbered rows (ie., the first, third, fifth,...), the labelling is left to right, while in the even numbered rows (second, fourth, sixth,...), the labelling is right to left.
Given the label of a node in this tree, return the labels in the path from the root of the tree to the node with that label.

               1
        ______ 1______
       /               \
       2               2
    __ 3__          __ 2__
   /       \       /       \
   3       3       3       3
   4       5       6       7
 /   \   /   \   /   \   /   \
 4   4   4   4   4   4   4   4
15  14  13  12  11  10   9   8
Example 1:
Input: label = 14
Output: [1,3,4,14]
Example 2:
Input: label = 26
Output: [1,2,6,10,26]
 */
class PathInZigZagLabelledBinaryTree
{
public:
    PathInZigZagLabelledBinaryTree(){}

    std::vector<int> Solve(int label)
    {
        int labelBefore = label;
        int height = log2(label) + 1;
        //std::cout << height << std::endl;
        int right = pow(2, height);
        right /= 2;//starting from prev level of cur label
        std::vector<int> res;
        while (label)
        {
            res.push_back(label);
            //the parent of label is label/2
            label = (right-1) + (right/2) - (label/2); //head+tail-label
            right /= 2;
        }
        std::reverse(res.begin(), res.end());

        std::cout << "PathInZigZagLabelledBinaryTree for " << labelBefore << ": " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }
};
/*
PathInZigZagLabelledBinaryTree for 14: 1, 3, 4, 14
 */
#endif
