#ifndef FIND_LEAVES_OF_BINARY_TREE_H
#define FIND_LEAVES_OF_BINARY_TREE_H
#include "Debug.h"
/*
Leetcode: Find Leaves Of Binary Tree
Given a binary tree, find all leaves and then remove those leaves.
Then repeat the previous steps until the tree is empty.

Example:
Given binary tree 
          1
         / \
        2   3
       / \     
      4   5    
Returns [4, 5, 3], [2], [1].

Explanation:
1. Remove the leaves [4, 5, 3] from the tree

          1
         / 
        2          
2. Remove the leaf [2] from the tree

          1          
3. Remove the leaf [1] from the tree

          []         
Returns [4, 5, 3], [2], [1].

(This problem is to identify it is a postorder traversal and node's level is "max height from leaf")
DFS find curNode's max depth of its both children from leaf, then insert curNode's val to res[depth] (postorder)
*/
class FindLeavesOfBinaryTree
{
public:
	FindLeavesOfBinaryTree() {}
	~FindLeavesOfBinaryTree() {}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	std::vector<std::vector<int>> DFS_Recur(TreeNode * root)
	{
		std::vector<std::vector<int>> res;
		this->recur(root, res);

		std::cout << "FindLeavesOfBinaryTree DFS_Recur: " << std::endl;
		Debug::Print2D<int>()(res, false);
		return res;
	}
private:
	int recur(TreeNode * root, std::vector<std::vector<int>> & res)
	{
		if (root == NULL)
			return -1;

		int ldepth = this->recur(root->left, res);
		int rdepth = this->recur(root->right, res);
		int depth = 1 + std::max(ldepth, rdepth);
		if (depth + 1 > (int)res.size())
			res.resize(depth + 1);
		res[depth].push_back(root->val);
		return depth;
	}
public:
	std::vector<std::vector<int>> IteratePostorderStack_HashMap(TreeNode * root)
	{
		std::vector<std::vector<int>> res;
		std::stack<TreeNode *> stk;
		std::unordered_map<TreeNode *, int> map;//<node, maxHeightFromLeaf>

		//postorder traversal w/ stack while keeping track of maxHeightFromLeaf for each node
		TreeNode * cur = root;
		while (cur)
		{
			stk.push(cur);
			if (cur->left) cur = cur->left;
			else cur = cur->right;
		}
		int height = 0;//maxHeightFromLeaf
		while (!stk.empty())
		{
			cur = stk.top(); stk.pop();
			TreeNode * top = cur;
			if (height + 1 > (int)res.size())
				res.resize(height + 1);
			res[height].push_back(cur->val);//now visit the node in postorder
			map[cur] = height;
			if (!stk.empty() && cur == stk.top()->left)//going up from left subtree
			{
				cur = stk.top()->right;
				while (cur)
				{
					stk.push(cur);
					if (cur->left) cur = cur->left;
					else cur = cur->right;
				}
			}

			//3 cases to update maxHeightFromLeaf:
			cur = top;
			if (!stk.empty() && cur == stk.top()->left)//1. going up from left subtree w/o right sibling
				++height;
			else if (!stk.empty() && cur == stk.top()->right)//2. going up from right subtree
			{
				if (stk.top()->left)//parent has left subtree
					height = std::max(height, map[stk.top()->left]) + 1;
				else
					++height;
			}
			else//3. going (down) to right sibling leaf
				height = 0;
		}
		//now res is bottomLevel->topLevel

		std::cout << "FindLeavesOfBinaryTree IteratePostorderStack_HashMap: " << std::endl;
		Debug::Print2D<int>()(res, false);
		return res;
	}

	std::vector<std::vector<int>> IteratePostorderStack_LeftSibStk(TreeNode * root)
	{
		std::vector<std::vector<int>> res;
		std::stack<TreeNode *> stk;
		std::stack<int> leftSibStk;

		//postorder traversal w/ stack while keeping track of maxHeightFromLeaf for each node
		TreeNode * cur = root;
		while (cur)
		{
			stk.push(cur);
			if (cur->left) cur = cur->left;
			else cur = cur->right;
		}
		int height = 0;//maxHeightFromLeaf
		while (!stk.empty())
		{
			cur = stk.top(); stk.pop();
			TreeNode * top = cur;
			if (height + 1 > (int)res.size())
				res.resize(height + 1);
			res[height].push_back(cur->val);//now visit the node in postorder

			if (!stk.empty() && cur == stk.top()->left)//going up from left subtree
			{
				cur = stk.top()->right;
				if (cur) leftSibStk.push(height);//save cur height if cur is a left child and cur has a right sibling
				while (cur)
				{
					stk.push(cur);
					if (cur->left) cur = cur->left;
					else cur = cur->right;
				}
			}

			//3 cases to update maxHeightFromLeaf:
			cur = top;
			if (!stk.empty() && cur == stk.top()->left)//1. going up from left subtree w/o right sibling
				++height;
			else if (!stk.empty() && cur == stk.top()->right)//2. going up from right subtree
			{
				if (stk.top()->left)//parent has left subtree
					height = std::max(height, leftSibStk.top()) + 1, leftSibStk.pop();
				else
					++height;
			}
			else//3. going (down) to right sibling leaf
				height = 0;
		}
		//now res is bottomLevel->topLevel

		std::cout << "FindLeavesOfBinaryTree IteratePostorderStack_LeftSibStk: " << std::endl;
		Debug::Print2D<int>()(res, false);
		return res;
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
    __ 1__
   /       \
   2       2
   2       3
 /   \   /   \
 3   3   X   X
 4   5   N   N


FindLeavesOfBinaryTree DFS_Recur: 
[rY][cX]
Row#0	= 4, 5, 3
Row#1	= 2,  ,  
Row#2	= 1,  ,  

FindLeavesOfBinaryTree IteratePostorderStack_HashMap:
[rY][cX]
Row#0	= 4, 5, 3
Row#1	= 2,  ,
Row#2	= 1,  ,

FindLeavesOfBinaryTree IteratePostorderStack_LeftSibStk:
[rY][cX]
Row#0	= 4, 5, 3
Row#1	= 2,  ,
Row#2	= 1,  ,
                              
                               1
                ______________ 7______________
               /                               \
               2                               2
        ______ 3______                  ______11______
       /               \               /               \
       3               3               3               3
    __ 1__          __ 5__          __ 9__          __15__
   /       \       /       \       /       \       /       \
   X       4       X       4       X       X       4       X
   N       2       N       6       N       N      13       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   5   5   X   X
 N   N   N   N   N   N   N   N   N   N   N   N  12  14   N   N


FindLeavesOfBinaryTree DFS_Recur: 
[rY][cX]
Row#0	= 2, 6, 9, 12, 14
Row#1	= 1, 5, 13,  ,  
Row#2	= 3, 15,  ,  ,  
Row#3	= 11,  ,  ,  ,  
Row#4	= 7,  ,  ,  ,  

FindLeavesOfBinaryTree IteratePostorderStack_HashMap:
[rY][cX]
Row#0	= 2, 6, 9, 12, 14
Row#1	= 1, 5, 13,  ,
Row#2	= 3, 15,  ,  ,
Row#3	= 11,  ,  ,  ,
Row#4	= 7,  ,  ,  ,

FindLeavesOfBinaryTree IteratePostorderStack_LeftSibStk:
[rY][cX]
Row#0	= 2, 6, 9, 12, 14
Row#1	= 1, 5, 13,  ,
Row#2	= 3, 15,  ,  ,
Row#3	= 11,  ,  ,  ,
Row#4	= 7,  ,  ,  ,
*/
#endif
