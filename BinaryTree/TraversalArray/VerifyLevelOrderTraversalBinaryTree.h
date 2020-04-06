#ifndef _VERIFY_LEVELORDER_TRAVERSAL_BINARY_TREE_H
#define _VERIFY_LEVELORDER_TRAVERSAL_BINARY_TREE_H
#include "Debug.h"
/*

*/
class VerifyLevelOrderTraversalBinaryTree
{
public:
	VerifyLevelOrderTraversalBinaryTree() {}
	~VerifyLevelOrderTraversalBinaryTree() {}
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
	bool Iterate(const std::string & levelorder)
	{
		std::vector<std::string> res = SplitComma(levelorder);
		int N = res.size();
		int leaf = 1;
		bool result = true;
		for (int i = 0; i < N; ++i)
		{
			if (res[i] != "#")
			{
				if (leaf == N) { result = false; break; }
				++leaf;
				if (leaf == N) { result = false; break; }
				++leaf;
			}
		}
		result = result && (leaf == N);

		std::cout << "VerifyLevelOrderTraversalBinaryTree Iterate for \"" << levelorder << "\": " << result << std::endl;
		return result;
	}
};
/*
      _5_
	 /   \
	1     4
  /  \   /  \
  #  2   3  #
    / \ / \
    # # # #

VerifyLevelOrderTraversalBinaryTree Iterate for "5,1,4,#,2,3,#,#,#,#,#": 1
VerifyLevelOrderTraversalBinaryTree Iterate for "5,1,4,#,2,3,#,6,#,#,#": 0
VerifyLevelOrderTraversalBinaryTree Iterate for "5,1,#,#,2,3,#,#,#,#,#": 0
*/
#endif
