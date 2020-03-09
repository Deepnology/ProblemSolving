#ifndef PARTITION_BINARY_TREE_2_EQUAL_SUM_H
#define PARTITION_BINARY_TREE_2_EQUAL_SUM_H
#include "Debug.h"
/*
Leetcode: Equal Tree Partition
Given a binary tree with n nodes, your task is to check if it's possible to
partition the tree to two trees which have the equal sum of values after removing exactly one edge on the original tree.
Example 1:
Input:     
    5
   / \
  10 10
    /  \
   2   3

Output: True
Explanation: 
    5
   / 
  10
      
Sum: 15

   10
  /  \
 2    3

Sum: 15
Example 2:
Input:     
    1
   / \
  2  10
    /  \
   2   20

Output: False
Explanation: You can't split the tree into two trees with equal sum after removing exactly one edge on the tree.
*/
class PartitionBinaryTree2EqualSum
{
public:
	PartitionBinaryTree2EqualSum() {}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	bool UseHashMap(TreeNode * root)
	{
		std::unordered_map<int, int> sumCount;
		int sum = recur(root, sumCount);
		if (sum % 2 != 0) return false;
		if (sum == 0) return sumCount[0] >= 2;
		return sumCount.count(sum / 2);
	}
	int recur(TreeNode * cur, std::unordered_map<int, int> & sumCount)
	{
		if (cur == NULL) return 0;
		int left = recur(cur->left, sumCount);
		int right = recur(cur->right, sumCount);
		int curSum = left + right + cur->val;
		++sumCount[curSum];
		return curSum;
	}
};
#endif
