#ifndef _VERIFY_POSTORDER_TRAVERSAL_BINARY_TREE_H
#define _VERIFY_POSTORDER_TRAVERSAL_BINARY_TREE_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "Debug.h"
/*
see also ConstructBinaryTreeFromTraversal.h
*/
class VerifyPostOrderTraversalBinaryTree
{
public:
	VerifyPostOrderTraversalBinaryTree() {}
	~VerifyPostOrderTraversalBinaryTree() {}
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
	bool IterateWStack(const std::string & postorder)
	{
		//split comma
		std::vector<std::string> res = SplitComma(postorder);

		//iterate w/ stack
		int N = res.size();
		std::vector<std::string> stk;
		bool result = true;
		for (int i = 0; i < N; ++i)
		{
			std::string cur = res[i];
			if (cur != "#")
			{
				if (stk.empty()) { result = false; break; }
				std::string right = stk.back();
				stk.pop_back();
				if (stk.empty()) { result = false; break; }
				std::string left = stk.back();
				stk.pop_back();
			}
			stk.push_back(cur);
		}
		result = result && (stk.size() == 1);

		std::cout << "VerifyPostOrderTraversalBinaryTree IterateWStack for \"" << postorder << "\": " << result << std::endl;
		return result;
	}
	bool ConstSpace(const std::string & postorder)
	{
		//split comma
		std::vector<std::string> res = SplitComma(postorder);

		//iterate w/ stack
		int N = res.size();
		int stk = 0;
		bool result = true;
		for (int i = 0; i < N; ++i)
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

		std::cout << "VerifyPostOrderTraversalBinaryTree ConstSpace for \"" << postorder << "\": " << result << std::endl;
		return result;
	}
};
/*
	1
  /  \
  #  2
    / \
    # #
VerifyPostOrderTraversalBinaryTree IterateWStack for "#,#,#,2,1": 1
VerifyPostOrderTraversalBinaryTree ConstSpace for "#,#,#,2,1": 1

      _1_
	 /   \
	5     4
  /  \   /  \
  #  2   3  #
    / \ / \
    # # # #
VerifyPostOrderTraversalBinaryTree IterateWStack for "#,#,#,2,#,#,3,#,4,1": 0
VerifyPostOrderTraversalBinaryTree ConstSpace for "#,#,#,2,#,#,3,#,4,1": 0

      _1_
	 /   \
	5     4
  /  \   /  \
  #  2   3  #
    / \ / \
    # # # #
VerifyPostOrderTraversalBinaryTree IterateWStack for "#,#,#,2,5,#,#,3,#,4,1": 1
VerifyPostOrderTraversalBinaryTree ConstSpace for "#,#,#,2,5,#,#,3,#,4,1": 1
*/
#endif
