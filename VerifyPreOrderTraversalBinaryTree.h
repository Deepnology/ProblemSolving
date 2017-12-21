#ifndef _VERIFY_PREORDER_TRAVERSAL_BINARY_TREE_H
#define _VERIFY_PREORDER_TRAVERSAL_BINARY_TREE_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "Debug.h"
/*
Leetcode: Verify Preorder Serialization of a Binary Tree

One way to serialize a binary tree is to use pre-order traversal.
When we encounter a non-null node, we record the node's value.
If it is a null node, we record using a sentinel value such as #.

     _9_
    /   \
   3     2
  / \   / \
 4   1  #  6
/ \ / \   / \
# # # #   # #

For example, the above binary tree can be serialized to the string "9,3,4,#,#,1,#,#,2,#,6,#,#", where # represents a null node.

Given a string of comma separated values, verify whether it is a correct preorder traversal serialization of a binary tree.
Find an algorithm without reconstructing the tree.
Each comma separated value in the string must be either an integer or a character '#' representing null pointer.

1. Iterate w/ Stack
Iterate over the preorder sequence. Push current node onto the stack.
If the top 3 nodes on the stack is "num,#,#" (a leaf node), replace them with a "#" (null node) by popping them out and push a "#".
Keep doing this until the top 3 nodes on the stack is not "num,#,#".
After iteration, the root and its two null leaves must be replaced with a "#".
So for a valid preorder traversal, the final stack must contain a single "#".

2. Const Space
Keep track of depth.
From 2 observations:
a. the count of nums is always 1 less than the count of #.
b. the last one must be a #.

see also ConstructBinaryTreeFromTraversal.h
*/
class VerifyPreOrderTraversalBinaryTree
{
public:
	VerifyPreOrderTraversalBinaryTree() {}
	~VerifyPreOrderTraversalBinaryTree() {}
private:
	std::vector<std::string> SplitComma(const std::string & s)
	{
		std::vector<std::string> res;
		std::istringstream iss(s);
		std::string buf;
		while (getline(iss, buf, ','))
			res.push_back(buf);
		return res;
	}
public:
	bool IterateWStack(const std::string & preorder)
	{
		//split comma
		std::vector<std::string> res = SplitComma(preorder);

		//iterate w/ stack
		int N = res.size();
		std::vector<std::string> stk;
		bool result = true;
		for (int i = N - 1; i >= 0; --i)
		{
			std::string cur = res[i];
			if (cur != "#")
			{
				if (stk.empty()) { result = false; break; }
				std::string left = stk.back();
				stk.pop_back();
				if (stk.empty()) { result = false; break; }
				std::string right = stk.back();
				stk.pop_back();
			}
			stk.push_back(cur);
		}
		result = result && (stk.size() == 1);

		std::cout << "VerifyPreOrderTraversalBinaryTree IterateWStack for \"" << preorder << "\": " << result << std::endl;
		return result;
	}
	bool ConstSpace(const std::string & preorder)
	{
		//split comma
		std::vector<std::string> res = SplitComma(preorder);

		//iterate w/ stack
		int N = res.size();
		int stk = 0;
		bool result = true;
		for (int i = N - 1; i >= 0; --i)
		{
			if (res[i] != "#")
			{
				if (stk == 0) { result = false; break; }
				--stk;
				if (stk == 0) { result = false; break; }
				--stk;
			}
			++stk;
		}
		result = result && (stk == 1);

		std::cout << "VerifyPreOrderTraversalBinaryTree ConstSpace for \"" << preorder << "\": " << result << std::endl;
		return result;
	}




	bool IterateWStack2(const std::string & preorder)
	{
		//split comma
		std::vector<std::string> res = SplitComma(preorder);

		//iterate w/ stack
		int N = res.size();
		std::vector<std::string> stk;
		for (int i = 0; i < N; ++i)
		{
			stk.push_back(res[i]);
			while (stk.size() >= 3 && stk[stk.size() - 1] == "#" && stk[stk.size() - 2] == "#" && stk[stk.size() - 3] != "#")
			{
				stk.pop_back();
				stk.pop_back();
				stk.pop_back();
				stk.push_back("#");
			}
		}
		bool result = (stk.size() == 1 && stk[0] == "#");
		std::cout << "VerifyPreOrderTraversalBinaryTree IterateWStack2 for \"" << preorder << "\": " << result << std::endl;
		return result;
	}

	bool ConstSpace2(const std::string & preorder)
	{
		//split comma
		std::vector<std::string> res = SplitComma(preorder);

		//keep track of depth
		int N = res.size();
		if (N == 0)
			return false;
		int depth = 0;
		for (int i = 0; i < N - 1; ++i)
		{
			if (res[i] == "#")
			{
				if (depth == 0)
				{
					std::cout << "VerifyPreOrderTraversalBinaryTree ConstSpace2 for \"" << preorder << "\": False." << std::endl;
					return false;
				}
				--depth;
			}
			else
			{
				++depth;
			}
		}

		if (depth != 0 || res.back() != "#")
		{
			std::cout << "VerifyPreOrderTraversalBinaryTree ConstSpace2 for \"" << preorder << "\": False." << std::endl;
			return false;
		}
		std::cout << "VerifyPreOrderTraversalBinaryTree ConstSpace2 for \"" << preorder << "\": True." << std::endl;
		return true;
	}
};
/*
VerifyPreOrderTraversalBinaryTree IterateWStack for "1,#,#,#,#": 0
VerifyPreOrderTraversalBinaryTree ConstSpace for "1,#,#,#,#": 0
VerifyPreOrderTraversalBinaryTree IterateWStack2 for "1,#,#,#,#": 0
VerifyPreOrderTraversalBinaryTree ConstSpace2 for "1,#,#,#,#": False.
VerifyPreOrderTraversalBinaryTree IterateWStack for "196,233,345,#,#,11,#,#,22,#,565,#,#": 1
VerifyPreOrderTraversalBinaryTree ConstSpace for "196,233,345,#,#,11,#,#,22,#,565,#,#": 1
VerifyPreOrderTraversalBinaryTree IterateWStack2 for "196,233,345,#,#,11,#,#,22,#,565,#,#": 1
VerifyPreOrderTraversalBinaryTree ConstSpace2 for "196,233,345,#,#,11,#,#,22,#,565,#,#": True.
*/
#endif