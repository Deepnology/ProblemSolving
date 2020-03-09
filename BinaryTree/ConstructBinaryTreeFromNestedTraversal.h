#ifndef CONSTRUCT_BINARY_TREE_FROM_NESTED_TRAVERSAL_H
#define CONSTRUCT_BINARY_TREE_FROM_NESTED_TRAVERSAL_H
#include "Debug.h"
/*
Leetcode: Construct Binary Tree From String
You need to construct a binary tree from a string consisting of parenthesis and integers.
The whole input represents a binary tree.
It contains an integer followed by zero, one or two pairs of parenthesis.
The integer represents the root's value and a pair of parenthesis contains a child binary tree with the same structure.
You always start to construct the left child node of the parent first if it exists.

Example:
Input: "4(2(3)(1))(6(5))"
Output: return the tree root node representing the following tree:

       4
     /   \
    2     6
   / \   / 
  3   1 5   
Note:
There will only be '(', ')', '-' and '0' ~ '9' in the input string.
An empty tree is represented by "" instead of "()".

Leetcode: Construct String from Binary Tree
You need to construct a string consists of parenthesis and integers from a binary tree with the preorder traversing way.
The null node needs to be represented by empty parenthesis pair "()".
And you need to omit all the empty parenthesis pairs that don't affect the one-to-one mapping relationship between the string and the original binary tree.
Example 1:
Input: Binary tree: [1,2,3,4]
       1
     /   \
    2     3
   /    
  4     

Output: "1(2(4))(3)"
Explanation: Originallay it needs to be "1(2(4)())(3()())", 
but you need to omit all the unnecessary empty parenthesis pairs. 
And it will be "1(2(4))(3)".
Example 2:
Input: Binary tree: [1,2,3,null,4]
       1
     /   \
    2     3
     \  
      4 

Output: "1(2()(4))(3)"
Explanation: Almost the same as the first example, 
except we can't omit the first parenthesis pair to break the one-to-one mapping relationship between the input and the output.
*/
class ConstructBinaryTreeFromNestedTraversal
{
public:
	ConstructBinaryTreeFromNestedTraversal() {}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};
	TreeNode * Recur(const std::string & s)//better
	{
		int i = 0;
		return recur(s, i);
	}
private:
	TreeNode * recur(const std::string & s, int & i)
	{
		int N = s.size();
		TreeNode * cur = NULL;
		while (i < N)
		{
			if (s[i] == ')')
			{
				++i;
				return cur;
			}
			else if (s[i] == '(')
			{
				if (cur->left == NULL)
					cur->left = recur(s, ++i);
				else
					cur->right = recur(s, ++i);
			}
			else
			{
				int begin = i;
				while (s[i] != '(' && s[i] != ')')
					++i;
				cur = new TreeNode(stoi(s.substr(begin, i - begin)));
			}
		}
		return cur;
	}

public:
	TreeNode * Stack(const std::string & s)
	{
		if (s.empty()) return NULL;
		std::stack<TreeNode *> stk;
		int N = s.size();
		TreeNode * root = NULL;
		for (int i = 0; i < N;)
		{
			if (s[i] == ')')
			{
				stk.pop();
				++i;
			}
			else if (s[i] == '(')
			{
				++i;
			}
			else
			{
				int begin = i;
				while (s[i] != '(' && s[i] != ')')
					++i;
				TreeNode * cur = new TreeNode(stoi(s.substr(begin, i - begin)));
				if (root == NULL) root = cur;
				if (!stk.empty())
				{
					if (stk.top()->left == NULL)
						stk.top()->left = cur;
					else
						stk.top()->right = cur;
				}
				stk.push(cur);
			}
		}
		return root;
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


	//construct string from binary tree
	std::string ToNestedStringRecur(TreeNode* t)
	{
		return recur(t);
	}
private:
	std::string recur(TreeNode * cur)
	{
		if (cur == NULL)
			return "";
		if (cur->left == NULL && cur->right == NULL)
			return std::to_string(cur->val);

		return std::to_string(cur->val) + "(" + recur(cur->left) + ")"
			+ (cur->right ? ("(" + recur(cur->right) + ")") : "");
	}
};
/*
ConstructBinaryTreeFromNestedTraversal for "4(2(3)(1))(6(5))":
      
       1
    __ 4__
   /       \
   2       2
   2       6
 /   \   /   \
 3   3   3   X
 3   1   5   N

      
       1
    __ 4__
   /       \
   2       2
   2       6
 /   \   /   \
 3   3   3   X
 3   1   5   N


*/

/*
Leetcode: Construct string from binary tree
You need to construct a string consists of parenthesis and integers from a binary tree with the preorder traversing way.
The null node needs to be represented by empty parenthesis pair "()".
And you need to omit all the empty parenthesis pairs that don't affect the one-to-one mapping relationship between the string and the original binary tree.
Example 1:
Input: Binary tree: [1,2,3,4]
       1
     /   \
    2     3
   /    
  4     

Output: "1(2(4))(3)"
Explanation: Originallay it needs to be "1(2(4)())(3()())", 
but you need to omit all the unnecessary empty parenthesis pairs. 
And it will be "1(2(4))(3)".
Example 2:
Input: Binary tree: [1,2,3,null,4]
       1
     /   \
    2     3
     \  
      4 

Output: "1(2()(4))(3)"
Explanation: Almost the same as the first example, 
except we can't omit the first parenthesis pair to break the one-to-one mapping relationship between the input and the output
*/
class ConstructNestedTraversalFromBinaryTree
{
public:
	ConstructNestedTraversalFromBinaryTree() {}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	std::string Recur(TreeNode* t)
	{
		return recur(t);
	}
	std::string recur(TreeNode * cur)
	{
		if (cur == NULL)
			return "";
		if (cur->left == NULL && cur->right == NULL)
			return std::to_string(cur->val);

		return std::to_string(cur->val)
			+ "(" + recur(cur->left) + ")"
			+ (cur->right ? ("(" + recur(cur->right) + ")") : "");
	}
};
/*
Leetcode: Find Duplicate Subtrees
Given a binary tree, return all duplicate subtrees.
For each kind of duplicate subtrees, you only need to return the root node of any one of them.
Two trees are duplicate if they have the same structure with same node values.
Example 1:

        1
       / \
      2   3
     /   / \
    4   2   4
       /
      4

The following are two duplicate subtrees:

      2
     /
    4

and

    4

Therefore, you need to return above trees' root in the form of a list.
*/
class FindDuplicateSubtrees
{
public:
	FindDuplicateSubtrees() {}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	std::vector<TreeNode*> RecordNestedTraversal(TreeNode* root)
	{
		std::unordered_map<std::string, std::vector<TreeNode *>> map;
		recur(root, map);
		std::vector<TreeNode*> res;
		for (auto & p : map)
		{
			if (p.second.size() >= 2)
				res.push_back(p.second.front());
		}
		return res;
	}

	std::string recur(TreeNode * root, std::unordered_map<std::string, std::vector<TreeNode *>> & map)
	{
		if (root == NULL) return "";
		if (root->left == NULL && root->right == NULL)
		{
			map[std::to_string(root->val)].push_back(root);
			return std::to_string(root->val);
		}
		std::string cur = std::to_string(root->val)
			+ "(" + recur(root->left, map) + ")"
			+ (root->right ? "(" + recur(root->right, map) + ")" : "");
		map[cur].push_back(root);
		return cur;
	}
};
/*

*/
#endif
