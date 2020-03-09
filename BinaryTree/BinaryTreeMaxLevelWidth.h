#ifndef BINARY_TREE_MAX_LEVEL_WIDTH_H
#define BINARY_TREE_MAX_LEVEL_WIDTH_H
#include "Debug.h"
/*
Leetcode: Maximum Width Of Binary Tree
Given a binary tree, write a function to get the maximum width of the given tree.
The width of a tree is the maximum width among all levels.
The binary tree has the same structure as a full binary tree, but some nodes are null.
The width of one level is defined as the length between the end-nodes (the leftmost and right most non-null nodes in the level
, where the null nodes between the end-nodes are also counted into the length calculation.
Example 1:
Input: 

           1
         /   \
        3     2
       / \     \  
      5   3     9 

Output: 4
Explanation: The maximum width existing in the third level with the length 4 (5,3,null,9).
Example 2:
Input: 

          1
         /  
        3    
       / \       
      5   3     

Output: 2
Explanation: The maximum width existing in the third level with the length 2 (5,3).
Example 3:
Input: 

          1
         / \
        3   2 
       /        
      5      

Output: 2
Explanation: The maximum width existing in the second level with the length 2 (3,2).
Example 4:
Input: 

          1
         / \
        3   2
       /     \  
      5       9 
     /         \
    6           7
Output: 8
Explanation:The maximum width existing in the fourth level with the length 8 (6,null,null,null,null,null,null,7).
*/
class BinaryTreeMaxLevelWidth
{
public:
	BinaryTreeMaxLevelWidth() {}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	int BFS(TreeNode* root)
	{
		int res = 0;
		std::queue<std::pair<TreeNode*, int>> que;
		if (root)
			que.push({ root,0 });
		while (!que.empty())
		{
			int count = que.size();
			int leftmostIdx, rightmostIdx;
			for (int i = 0; i < count; ++i)
			{
				auto cur = que.front();
				que.pop();
				if (i == 0) leftmostIdx = cur.second;
				if (i == count - 1) rightmostIdx = cur.second;
				if (cur.first->left)
					que.push({ cur.first->left,cur.second * 2 + 1 });
				if (cur.first->right)
					que.push({ cur.first->right,cur.second * 2 + 2 });
			}
			res = std::max(res, rightmostIdx - leftmostIdx + 1);
		}
		return res;
	}

	int DFS(TreeNode * root)
	{
		std::vector<int> leftmostNodeIdx;//store the idx of the leftmost nodes from root to leaf
		int res = 0;
		recur(root, 0, 0, leftmostNodeIdx, res);
		return res;
	}
	void recur(TreeNode * cur, int idx, int depth, std::vector<int> & leftmostNodeIdx, int & res)
	{
		if (cur == NULL) return;
		if (depth >= leftmostNodeIdx.size())
			leftmostNodeIdx.push_back(idx);//cur node is a leftmost node
		res = std::max(res, idx - leftmostNodeIdx[depth] + 1);//width = idx - leftmostNodeIdx[depth] + 1
		recur(cur->left, idx * 2 + 1, depth + 1, leftmostNodeIdx, res);
		recur(cur->right, idx * 2 + 2, depth + 1, leftmostNodeIdx, res);
	}
};
#endif
