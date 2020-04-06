#ifndef COUNT_UNIVALUE_SUBTREES_H
#define COUNT_UNIVALUE_SUBTREES_H
#include <string>
#include <sstream>
#include <iostream>
#include "Debug.h"
/*
Leetcode: Count Univalue Subtrees
Given a binary tree, count the number of uni-value subtrees.
A Uni-value subtree means all nodes of the subtree have the same value.
(A uni-value subtree is a node and all its descendant nodes have same value.)
(All leaves are uni-value subtrees.)
For example:
Given binary tree,
              5
             / \
            1   5
           / \   \
          5   5   5
return 4.

Postorder recur: O(n) time
*/
class CountUnivalueSubtrees
{
public:
	CountUnivalueSubtrees() {}
	~CountUnivalueSubtrees() {}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	int Recur(TreeNode * root)
	{
		int count = 0;
		this->recur(root, count);
		std::cout << "CountUnivalueSubtrees PostorderRecur: " << count << std::endl;
		return count;
	}
private:
	bool recur(TreeNode * cur, int & count)
	{
		if (cur == nullptr)
			return true;

		bool left = this->recur(cur->left, count);
		bool right = this->recur(cur->right, count);

		//postorder
		if ((cur->left == nullptr || (left && cur->val == cur->left->val)) &&//determine if left subtree is same as cur node
			(cur->right == nullptr || (right && cur->val == cur->right->val)))//determine if right subtree is same as cur node
		{
			++count;
			return true;
		}
		return false;
	}

public:
	int IteratePostorderStack_HashMap(TreeNode * root)
	{
		if (root == NULL) return 0;
		int count = 0;
		std::unordered_map<TreeNode *, bool> map;//<node, isUniValueSubtree>
		std::stack<TreeNode *> stk;
		TreeNode * cur = root;
		while (cur)
		{
			stk.push(cur);
			if (cur->left) cur = cur->left;
			else cur = cur->right;
		}
		while (!stk.empty())
		{
			cur = stk.top(); stk.pop();
			if ((cur->left == NULL || (map[cur->left] && cur->val == cur->left->val)) &&
				(cur->right == NULL || (map[cur->right] && cur->val == cur->right->val)))//cur and all cur's descendant nodes is a uni-value subtree
			{
				map[cur] = true;
				++count;
			}
			else
				map[cur] = false;

			if (!stk.empty() && stk.top()->left == cur)
			{
				cur = stk.top()->right;
				while (cur)
				{
					stk.push(cur);
					if (cur->left) cur = cur->left;
					else cur = cur->right;
				}
			}
		}

		std::cout << "CountUnivalueSubtrees IteratePostorderStack_HashMap: " << count << std::endl;
		return count;
	}

	int IteratePostorderStack_LeftSibStk(TreeNode * root)
	{
		if (root == NULL) return 0;
		int count = 0;
		std::stack<TreeNode *> stk;
		std::stack<bool> leftSibStk;
		bool curUniVal = false;
		bool leftUniVal;
		bool rightUniVal;
		TreeNode * cur = root;
		while (cur)
		{
			stk.push(cur);
			if (cur->left) cur = cur->left;
			else cur = cur->right;
		}
		while (!stk.empty())
		{
			cur = stk.top(); stk.pop();
			TreeNode * top = cur;
			if ((cur->left == NULL || (leftUniVal && cur->val == cur->left->val)) &&
				(cur->right == NULL || (rightUniVal && cur->val == cur->right->val)))//cur and all cur's descendant nodes is a uni-value subtree
			{
				curUniVal = true;
				++count;
			}
			else
				curUniVal = false;

			if (!stk.empty() && stk.top()->left == cur)
			{
				cur = stk.top()->right;
				if (cur) leftSibStk.push(curUniVal);
				while (cur)
				{
					stk.push(cur);
					if (cur->left) cur = cur->left;
					else cur = cur->right;
				}
			}

			cur = top;
			if (!stk.empty() && stk.top()->left == cur)//going up from left subtree w/o right sibling
			{
				leftUniVal = curUniVal;
			}
			else if (!stk.empty() && stk.top()->right == cur)//going up from right subtree
			{
				rightUniVal = curUniVal;
				if (stk.top()->left) leftUniVal = leftSibStk.top(), leftSibStk.pop();
			}
			else//going (down) to right sibling leaf
			{

			}
		}

		std::cout << "CountUnivalueSubtrees IteratePostorderStack_LeftSibStk: " << count << std::endl;
		return count;
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
    __ 5__
   /       \
   2       2
   1       5
 /   \   /   \
 3   3   X   3
 5   5   N   5


CountUnivalueSubtrees PostorderRecur: 4
CountUnivalueSubtrees IteratePostorderStack_HashMap: 4
CountUnivalueSubtrees IteratePostorderStack_LeftSibStk: 4
                              
                               1
                ______________ 7______________
               /                               \
               2                               2
        ______ 5______                  ______ 9______
       /               \               /               \
       3               3               3               3
    __ 1__          __ 5__          __ 9__          __13__
   /       \       /       \       /       \       /       \
   X       4       X       4       X       X       4       X
   N       1       N       5       N       N      13       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   5   5   X   X
 N   N   N   N   N   N   N   N   N   N   N   N  13  13   N   N


CountUnivalueSubtrees PostorderRecur: 9
CountUnivalueSubtrees IteratePostorderStack_HashMap: 9
CountUnivalueSubtrees IteratePostorderStack_LeftSibStk: 9
*/
#endif
