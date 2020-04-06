#ifndef SERIALIZE_DESERIALIZE_BINARY_TREE_H
#define SERIALIZE_DESERIALIZE_BINARY_TREE_H
#include "Debug.h"
/*
Leetcode: Serialize Deserialize Binary Tree, Serialize Deserialize BST
Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer,
or transmitted across a network connection link to be reconstructed later in the same or another computer environment.
Design an algorithm to serialize and deserialize a binary tree.
There is no restriction on how your serialization/deserialization algorithm should work.
You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.
For example, you may serialize the following tree
    1
   / \
  2   3
     / \
    4   5
as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a binary tree.
You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

Serialize: use N to indicate null node, can be done using preorder, postorder, or levelorder traversal.
Deserialize: construct binary tree from a preorder, postorder, or levelorder traversal. see also ConstructBinaryTreeFromTraversal.h

Follow Up:
1. what if TreeNode class val is (string instead of int) which may contain newline, space, comma?
2. what if a tree node may contain multiple chidren?
=> when serializing, need to record numOfChildren#lenOfVal#val for each node
*/
class SerializeDeserializeBinaryTree
{
public:
	SerializeDeserializeBinaryTree() {}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	std::string Serialize(TreeNode * root)
	{
		std::vector<TreeNode *> res;
		LevelOrderTraverse(root, res);
		std::ostringstream oss;
		int N = res.size();
		for (int i = 0; i < N; ++i)
		{
			if (res[i] == NULL)
				oss << "N";
			else
				oss << res[i]->val;
			if (i != N - 1)
				oss << ",";
		}
		return oss.str();
	}
private:
	void LevelOrderTraverse(TreeNode * cur, std::vector<TreeNode *> & res)
	{
		std::queue<TreeNode *> que;
		que.push(cur);
		while (!que.empty())
		{
			TreeNode * front = que.front();
			que.pop();
			res.push_back(front);
			if (front)
			{
				que.push(front->left);
				que.push(front->right);
			}
		}
	}

public:
	TreeNode * Deserialize(std::string data)
	{
		std::vector<TreeNode *> res;
		int begin = 0;
		int N = data.size();
        int i = 0;
        while (i < N)
        {
            while (i < N && data[i] != ',')
                ++i;
            if (i-begin==1 && data[begin] == 'N')
                res.push_back(NULL);
            else
                res.push_back(new TreeNode(stoi(data.substr(begin,i-begin))));
            ++i;
            begin = i;
        }
		return LevelOrderConstructBT(res);
	}
private:
	TreeNode * LevelOrderConstructBT(std::vector<TreeNode *> & levelorder)
	{
		int N = levelorder.size();
		int leaf = 1;
		for (int i = 0; i < N; ++i)
		{
			if (levelorder[i])
			{
				levelorder[i]->left = levelorder[leaf++];
				levelorder[i]->right = levelorder[leaf++];
			}
		}
		return levelorder[0];
	}
};
#endif
