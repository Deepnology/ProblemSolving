#ifndef IN_BETWEEN_ANCESTOR_DESCENDANT_BST_H
#define IN_BETWEEN_ANCESTOR_DESCENDANT_BST_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
/*
Elements of programming interview, BST: Test if three BST nodes are totally ordered
Given a BST and three nodes.
Test if the middle node is in between an ancestor node and a descendant node.

O(d) time, where d is the difference between the depths of the ancestor and the descendant.
*/
class InBetweenAncestorDescendantBST
{
public:
	InBetweenAncestorDescendantBST(){}
	~InBetweenAncestorDescendantBST(){}

	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	bool Valid_Iterate(TreeNode * mid, TreeNode * a, TreeNode * b)
	{
		bool res;
		TreeNode * curA = a;
		TreeNode * curB = b;

		//1. test if ancestor is valid: move a and b down based on mid's val to see if a or b is valid as an ancestor
		while (curA && curA != b && curA != mid)
			curA = mid->val < curA->val ? curA->left : curA->right;
		while (curB && curB != a && curB != mid)
			curB = mid->val < curB->val ? curB->left : curB->right;

		if ((curA == b && b != mid) || ( curB == a && a != mid) || (curA != mid && curB != mid))
		{
			std::string foundA = curA == nullptr ? "N" : std::to_string(curA->val);
			std::string foundB = curB == nullptr ? "N" : std::to_string(curB->val);
			std::cout << foundA << "," << foundB << std::endl;
			res = false;
		}
		else
		{
			//2. test if descendant is valid: move mid down based on a or b's val to see if a or b is valid as an descendant
			TreeNode * curMid = mid;
			while (curMid && curMid != a)
				curMid = a->val < curMid->val ? curMid->left : curMid->right;
			if (curMid == a)
				res = true;
			else
			{
				curMid = mid;
				while (curMid && curMid != b)
					curMid = b->val < curMid->val ? curMid->left : curMid->right;
				if (curMid == b)
					res = true;
				else
					res = false;
			}
		}

		std::cout << "InBetweenAncestorDescendantBST Valid_Iterate for \"" << mid->val << " in [" << a->val << "," << b->val << "]\": " << res << std::endl;
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
                                ______________________________19______________________________
                               /                                                               \
                               2                                                               2
                ______________ 7______________                                  ______________43______________
               /                               \                               /                               \
               3                               3                               3                               3
        ______ 3______                  ______11______                  ______23______                  ______47______
       /               \               /               \               /               \               /               \
       4               4               X               4               X               4               X               4
    __ 2__          __ 5__          __ N__          __17__          __ N__          __37__          __ N__          __53__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       X       X       5       X       X       X       5       5       X       X       X       X
   N       N       N       N       N       N      13       N       N       N      29      41       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   6   X   X   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N  31   N   N   N   N   N   N   N   N   N   N


InBetweenAncestorDescendantBST Valid_Iterate for "23 in [19,37]": 1
InBetweenAncestorDescendantBST Valid_Iterate for "23 in [19,31]": 1
InBetweenAncestorDescendantBST Valid_Iterate for "29 in [31,23]": 1
N,N
InBetweenAncestorDescendantBST Valid_Iterate for "23 in [7,47]": 0
InBetweenAncestorDescendantBST Valid_Iterate for "7 in [7,13]": 1
InBetweenAncestorDescendantBST Valid_Iterate for "13 in [13,19]": 1
N,N
InBetweenAncestorDescendantBST Valid_Iterate for "7 in [3,13]": 0
InBetweenAncestorDescendantBST Valid_Iterate for "29 in [23,11]": 0
InBetweenAncestorDescendantBST Valid_Iterate for "47 in [53,19]": 1
*/
#endif