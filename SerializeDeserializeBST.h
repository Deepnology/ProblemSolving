#ifndef SERIALIZE_DESERIALIZE_BST_H
#define SERIALIZE_DESERIALIZE_BST_H
#include "Debug.h"
/*
Leetcode: Serialize and Deserialize BST
Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer
, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.
Design an algorithm to serialize and deserialize a binary search tree.
There is no restriction on how your serialization/deserialization algorithm should work.
You just need to ensure that a binary search tree can be serialized to a string and this string can be deserialized to the original tree structure.
The encoded string should be as compact as possible.
Note: Do not use class member/global/static variables to store states.
Your serialize and deserialize algorithms should be stateless.
*/
class SerializeDeserializeBST
{
public:
	SerializeDeserializeBST() {}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	std::string Serialize(TreeNode* root)
	{
		std::vector<TreeNode *> preorder;
		recur(root, preorder);
		std::ostringstream oss;
		int N = preorder.size();
		for (int i = 0; i < N; ++i)
		{
			oss << preorder[i]->val;
			if (i != N - 1)
				oss << ",";
		}
		return oss.str();
	}
	void recur(TreeNode * cur, std::vector<TreeNode*> & preorder)
	{
		if (cur == NULL) return;
		preorder.push_back(cur);
		recur(cur->left, preorder);
		recur(cur->right, preorder);
	}


	// Decodes your encoded data to tree.
	TreeNode* Deserialize(std::string data)
	{
		std::vector<int> preorder;
		int begin = 0;
		int N = data.size();
		for (int i = 0; i < N; ++i)
		{
			if (data[i] == ',')
			{
				preorder.push_back(stoi(data.substr(begin, i - begin)));
				begin = i + 1;
			}
			else if (i == N - 1)
				preorder.push_back(stoi(data.substr(begin, i - begin + 1)));
		}
		int cur = 0;
		return recur(preorder, INT_MIN, INT_MAX, cur);
	}
	TreeNode * recur(std::vector<int> & preorder, int min, int max, int & cur)
	{
		int N = preorder.size();
		if (cur == N) return NULL;
		int curVal = preorder[cur];
		if (curVal < min || curVal > max) return NULL;
		TreeNode * root = new TreeNode(curVal);
		++cur;
		root->left = recur(preorder, min, curVal, cur);
		root->right = recur(preorder, curVal, max, cur);
		return root;
	}
};
#endif
