#ifndef GENERIC_DFS_W_STACK_H
#define GENERIC_DFS_W_STACK_H
#include "Debug.h"
/*

*/
class GenericDFSWStack
{
public:
	struct TreeNode
	{
		int val;
		std::vector<TreeNode *> children;
		explicit TreeNode(int v) : val(v) {}
		~TreeNode() {}
	};
	GenericDFSWStack() {}
	~GenericDFSWStack() {}

	std::vector<int> Preorder(TreeNode * root)
	{
		std::vector<int> res;
		std::stack<TreeNode *> stk;
		std::unordered_set<TreeNode *> visit;
		if (root)
			stk.push(root), visit.insert(root);
		while (!stk.empty())
		{
			//push all nodes in the rightmost child path to stk
			TreeNode * chd;
			while ((chd = GetNextNonVisitedChild(stk.top(), visit, false)) != nullptr)//Children: Right to Left
			{
				stk.push(chd);
				visit.insert(chd);
			}
			//now visit cur node in reversed preorder
			TreeNode * cur = stk.top();
			stk.pop();
			res.push_back(cur->val);
		}
		std::reverse(res.begin(), res.end());
		std::cout << "GenericDFSWStack Preorder: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
	std::vector<int> Postorder(TreeNode * root)
	{
		std::vector<int> res;
		std::stack<TreeNode *> stk;
		std::unordered_set<TreeNode *> visit;
		if (root)
			stk.push(root), visit.insert(root);
		while (!stk.empty())
		{
			//push all nodes in the leftmost child path to stk
			TreeNode * chd;
			while ((chd = GetNextNonVisitedChild(stk.top(), visit, true)) != nullptr)//Children: Left to Right
			{
				stk.push(chd);
				visit.insert(chd);
			}
			//now visit cur node in postorder
			TreeNode * cur = stk.top();
			stk.pop();
			res.push_back(cur->val);
		}
		std::cout << "GenericDFSWStack Postorder: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	TreeNode * GetNextNonVisitedChild(TreeNode * cur, std::unordered_set<TreeNode *> & visit, bool LToR)
	{
		if (LToR)
		{
			for (auto itr = cur->children.cbegin(); itr != cur->children.cend(); ++itr)
			{
				if (visit.count(*itr) == 0)
					return *itr;
			}
		}
		else
		{
			for (auto itr = cur->children.crbegin(); itr != cur->children.crend(); ++itr)
			{
				if (visit.count(*itr) == 0)
					return *itr;
			}
		}
		return nullptr;
	}

public:
	static void DeleteTree(TreeNode * root)
	{
		if (root == 0)
			return;

		int N = root->children.size();
		for (int i = 0; i < N; ++i)
			DeleteTree(root->children[i]);

		//post order
		delete root;
		root = 0;
	}
};
/*
     _______0________
    /       |        \
  _1_      _5_      __9__
 / | \    / | \    /  |  \
2  3  4  6  7  8  10  11  12

GenericDFSWStack Preorder: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
GenericDFSWStack Postorder: 2, 3, 4, 1, 6, 7, 8, 5, 10, 11, 12, 9, 0

					    _________________________0_____________________________
				       /                |                  |                   \
				  ____1____         ____5____          ____9_____           ____13____
				 /    |    \       /    |    \        /    |     \         /    |     \
				2     3    _4_    6   __7__   8   __10_   _11    _12_    14    _15    _16____
			   / \    |   / | \   |  /  |  \  |  /  |  \ /   \  /  | \  /  \  /   \  /  |  | \
			  17 18  19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43

GenericDFSWStack Preorder: 0, 1, 2, 17, 18, 3, 19, 4, 20, 21, 22, 5, 6, 23, 7, 24, 25, 26, 8, 27, 9, 10, 28, 29, 30, 11, 31, 32, 12, 33, 34, 35, 13, 14, 36, 37, 15, 38, 39, 16, 40, 41, 42, 43
GenericDFSWStack Postorder: 17, 18, 2, 19, 3, 20, 21, 22, 4, 1, 23, 6, 24, 25, 26, 7, 27, 8, 5, 28, 29, 30, 10, 31, 32, 11, 33, 34, 35, 12, 9, 36, 37, 14, 38, 39, 15, 40, 41, 42, 43, 16, 13, 0
*/
#endif
