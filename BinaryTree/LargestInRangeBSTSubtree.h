#ifndef LARGEST_IN_RANGE_BST_SUBTREE_H
#define LARGEST_IN_RANGE_BST_SUBTREE_H
#include "Debug.h"
/*
Google
Given a BST and a range [lower,upper], find a max sized subtree whose nodes all have values in the given range. Return the size.
see also LargestBSTSubtree.h
*/
class LargestInRangeBSTSubtree
{
public:
	LargestInRangeBSTSubtree() {}
	~LargestInRangeBSTSubtree() {}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};
	int PostorderRecur(TreeNode * root, int lower, int upper)
	{
		if (root == NULL) return 0;
		int maxSize = 0;
		auto res = this->recur(root, lower, upper, maxSize);
		std::cout << "LargestInRangeBSTSubtree for \"[" << lower << ", " << upper << "]\": " << maxSize << std::endl;
		return maxSize;
	}
private:
	std::pair<bool, int> recur(TreeNode * cur, int lower, int upper, int & maxSize)
	{
		if (cur == NULL)
			return{ true, 0 };

		auto left = this->recur(cur->left, lower, upper, maxSize);
		auto right = this->recur(cur->right, lower, upper, maxSize);
		if (left.first && right.first)//both left and right are in range
		{
			if (cur->val >= lower && cur->val <= upper)
			{
				maxSize = std::max(maxSize, left.second + right.second + 1);
				return{ true, left.second + right.second + 1 };//second is meaningful only when first is true
			}
			else return{ false, 0 };
		}
		else
			return{ false, 0 };
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
        ______ 9______
       /               \
       2               2
    __ 5__          __14__
   /       \       /       \
   3       3       3       3
   3       7      12      17
 /   \   /   \   /   \   /   \
 4   4   4   4   4   4   4   4
 1   4   6   8  11  13  16  18


LargestInRangeBSTSubtree for "[3, 11]": 3
LargestInRangeBSTSubtree for "[1, 14]": 7
LargestInRangeBSTSubtree for "[10, 16]": 3
LargestInRangeBSTSubtree for "[12, 17]": 1
LargestInRangeBSTSubtree for "[2, 2]": 0
LargestInRangeBSTSubtree for "[9, 10]": 0
LargestInRangeBSTSubtree for "[19, 21]": 0
*/
#endif
