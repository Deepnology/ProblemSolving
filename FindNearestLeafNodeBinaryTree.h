/*BinaryTree*/
#ifndef _FIND_NEAREST_LEAF_NODE_BINARY_TREE_H
#define _FIND_NEAREST_LEAF_NODE_BINARY_TREE_H
#include "Debug.h"
/*
Given a binary tree where every node has a unique value, and a target key k, find the value of the nearest leaf node to target k in the tree.
Here, nearest to a leaf means the least number of edges travelled on the binary tree to reach any leaf of the tree.
Also, a node is called a leaf if it has no children.
In the following examples, the input tree is represented in flattened form row by row.
The actual root tree given will be a TreeNode object.
Example 1:
Input:
root = [1, 3, 2], k = 1
Diagram of binary tree:
          1
         / \
        3   2

Output: 2 (or 3)
Explanation: Either 2 or 3 is the nearest leaf node to the target of 1.
Example 2:
Input:
root = [1], k = 1
Output: 1
Explanation: The nearest leaf node is the root node itself.
Example 3:
Input:
root = [1,2,3,4,null,null,null,5,null,6], k = 2
Diagram of binary tree:
             1
            / \
           2   3
          /
         4
        /
       5
      /
     6

Output: 3
Explanation: The leaf node with value 3 (and not the leaf node with value 6) is nearest to the node with value 2.
Note:
root represents a binary tree with at least 1 node and at most 1000 nodes.
Every node has a unique node.val in range [1, 1000].
There exists some node in the given binary tree for which node.val == k.
 */
class FindNearestLeafNodeBinaryTree
{
public:
    struct TreeNode
    {
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
        int val;
        TreeNode * left;
        TreeNode * right;
    };
    FindNearestLeafNodeBinaryTree(){}

    int Recur(TreeNode * root, int k)
    {
        auto res = recur(root, k);
        std::cout << "FindNearestLeafNodeBinaryTree Recur for \"" << k << "\": " << res[3] << " (min dist = " << res[2] << ")" << std::endl;
        return res[3];
    }
private:
    //{found, dist from curNode to leaf if not found OR dist from foundNode to curNode if found, global min dist that may include a turn, leaf}
    std::vector<int> recur(TreeNode * cur, int k)
    {
        if (cur == NULL)
            return {0, -1, INT_MAX, -1};

        std::vector<int> left = recur(cur->left, k);
        std::vector<int> right = recur(cur->right, k);
        int foundCur = cur->val == k ? 1:0;
        int found = left[0]||right[0]||foundCur ? 1:0;
        int minHeight = foundCur?0:left[0]?left[1]+1:right[0]?right[1]+1:!cur->left?right[1]+1:!cur->right?left[1]+1:std::min(left[1],right[1])+1;
        int minDiameter = foundCur?!cur->left?right[1]+1:!cur->right?left[1]+1:std::min(left[1],right[1])+1:left[0]?std::min(left[2],left[1]+right[1]+2):right[0]?std::min(right[2],left[1]+right[1]+2):INT_MAX;
        int leaf = !cur->left&&!cur->right?cur->val:!cur->left?right[3]:!cur->right?left[3]:!found||foundCur?(left[1]<right[1]?left[3]:right[3]):left[0]?(left[1]+right[1]+2<left[2]?right[3]:left[3]):(left[1]+right[1]+2<right[2]?left[3]:right[3]);

        //std::cout << cur->val << ":" << found << "," << minHeight << "," << minDiameter << "," << leaf << "(" << left[0] << "," << left[1] << "," << left[2] << "," << left[3] << ")(" << right[0] << "," << right[1] << "," << right[2] << "," << right[3] << ")" << std::endl;
        return {found, minHeight, minDiameter, leaf};
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
                ______________ 1______________
               /                               \
               2                               2
        ______ 2______                  ______ 3______
       /               \               /               \
       3               X               X               X
    __ 4__          __ N__          __ N__          __ N__
   /       \       /       \       /       \       /       \
   4       X       X       X       X       X       X       X
   5       N       N       N       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 5   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X
 6   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N


FindNearestLeafNodeBinaryTree Recur for "2": 3 (min dist = 2)

                               1
                ______________ 1______________
               /                               \
               2                               2
        ______ 2______                  ______ 3______
       /               \               /               \
       X               X               3               3
    __ N__          __ N__          __ 4__          __ 5__
   /       \       /       \       /       \       /       \
   X       X       X       X       4       X       X       4
   N       N       N       N       6       N       N       7
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   5   5   X   X   X   X   5   X
 N   N   N   N   N   N   N   N   8   9   N   N   N   N  10   N


FindNearestLeafNodeBinaryTree Recur for "3": 2 (min dist = 2)
FindNearestLeafNodeBinaryTree Recur for "7": 10 (min dist = 1)
FindNearestLeafNodeBinaryTree Recur for "4": 9 (min dist = 2)
 */
#endif
