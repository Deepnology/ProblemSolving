#ifndef PRINT_BINARY_TREE_IN_2D_ARRAY_H
#define PRINT_BINARY_TREE_IN_2D_ARRAY_H
#include "Debug.h"
/*
Leetcode: Print Binary Tree
Print a binary tree in an m*n 2D string array following these rules:
1. The row number m should be equal to the height of the given binary tree.
2. The column number n should always be an odd number.
3. The root node's value (in string format) should be put in the exactly middle of the first row it can be put. The column and the row where the root node belongs will separate the rest space into two parts (left-bottom part and right-bottom part). You should print the left subtree in the left-bottom part and print the right subtree in the right-bottom part. The left-bottom part and the right-bottom part should have the same size. Even if one subtree is none while the other is not, you don't need to print anything for the none subtree but still need to leave the space as large as that for the other subtree. However, if two subtrees are none, then you don't need to leave space for both of them.
4. Each unused space should contain an empty string "".
5. Print the subtrees following the same rules.
Example 1:
Input:
     1
    /
   2
Output:
[["", "1", ""],
 ["2", "", ""]]
Example 2:
Input:
     1
    / \
   2   3
    \
     4
Output:
[["", "", "", "1", "", "", ""],
 ["", "2", "", "", "", "3", ""],
 ["", "", "4", "", "", "", ""]]
Example 3:
Input:
      1
     / \
    2   5
   / 
  3 
 / 
4 
Output:
[["",  "",  "", "",  "", "", "", "1", "",  "",  "",  "",  "", "", ""]
 ["",  "",  "", "2", "", "", "", "",  "",  "",  "",  "5", "", "", ""]
 ["",  "3", "", "",  "", "", "", "",  "",  "",  "",  "",  "", "", ""]
 ["4", "",  "", "",  "", "", "", "",  "",  "",  "",  "",  "", "", ""]]

Note: The height of binary tree is in the range of [1, 10]. 
*/
class PrintBinaryTreeIn2DArray
{
public:
	PrintBinaryTreeIn2DArray() {}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};
	std::vector<std::vector<std::string>> Recur(TreeNode * root)
	{
		int h = heightRecur(root);
		int w = widthRecur(root);
		std::vector<std::vector<std::string>> res(h, std::vector<std::string>(w, " "));
		recur(root, 0, 0, w - 1, res);
        std::cout << "PrintBinaryTreeIn2DArray Recur: " << std::endl;
        Debug::Print2D<std::string>()(res, false);
		return res;
	}
private:
	void recur(TreeNode * cur, int depth, int left, int right, std::vector<std::vector<std::string>> & res)
	{
		if (cur == NULL) return;
		int mid = (left + right) / 2;
		res[depth][mid] = std::to_string(cur->val);
		recur(cur->left, depth + 1, left, mid - 1, res);
		recur(cur->right, depth + 1, mid + 1, right, res);
	}
	int heightRecur(TreeNode * cur)
	{
		if (cur == NULL) return 0;
		return std::max(heightRecur(cur->left), heightRecur(cur->right)) + 1;
	}
	int widthRecur(TreeNode * cur)
	{
		if (cur == NULL) return 0;
		return std::max(widthRecur(cur->left), widthRecur(cur->right)) * 2 + 1;
	}
public:
	std::vector<std::vector<std::string>> BFS(TreeNode * root)
	{
		int h = heightRecur(root);
		int w = widthRecur(root);
		std::vector<std::vector<std::string>> res(h, std::vector<std::string>(w, " "));
		std::queue<std::tuple<TreeNode *, int, int>> que;
		que.push({root, 0, w-1});
		int depth = 0;
		while (!que.empty())
		{
			int levelCount = que.size();
			while (levelCount-->0)
			{
				auto cur = que.front();
				que.pop();
				TreeNode *n = std::get<0>(cur);
				int left = std::get<1>(cur);
				int right = std::get<2>(cur);
				int mid = (left + right) / 2;
				res[depth][mid] = std::to_string(n->val);
				if (n->left)
					que.push({n->left,left,mid-1});
				if (n->right)
					que.push({n->right,mid+1,right});
			}
			++depth;
		}
		std::cout << "PrintBinaryTreeIn2DArray BFS: " << std::endl;
		Debug::Print2D<std::string>()(res, false);
		return res;
	}

public:
	std::vector<std::string> ToStrRecur(TreeNode * root)
	{
		int h = heightRecur(root);
		int w = widthRecur(root);
        std::vector<std::string> res(h, std::string(w, ' '));
		recur(root, 0, 0, w-1, res);

		std::cout << "PrintBinaryTreeIn2DArray ToStrRecur: " << std::endl;
        Debug::Print2D<std::string>()(res, false);
		return res;
	}
private:
	void recur(TreeNode * cur, int curDepth, int left, int right, std::vector<std::string> & res)
	{
        if (cur == NULL) return;
        int mid = (left + right) / 2;
        res[curDepth][mid] = (cur->val+'0');
        recur(cur->left, curDepth + 1, left, mid - 1, res);
        recur(cur->right, curDepth + 1, mid + 1, right, res);
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
        ______ 0______
       /               \
       2               2
    __ 1__          __ 8__
   /       \       /       \
   3       3       3       3
   2       5       9       2
 /   \   /   \   /   \   /   \
 4   4   4   4   4   4   4   4
 3   4   6   7   0   1   3   4


PrintBinaryTreeIn2DArray Recur:
[rY][cX]
Row#0	=  ,  ,  ,  ,  ,  ,  , 0,  ,  ,  ,  ,  ,  ,
Row#1	=  ,  ,  , 1,  ,  ,  ,  ,  ,  ,  , 8,  ,  ,
Row#2	=  , 2,  ,  ,  , 5,  ,  ,  , 9,  ,  ,  , 2,
Row#3	= 3,  , 4,  , 6,  , 7,  , 0,  , 1,  , 3,  , 4

PrintBinaryTreeIn2DArray BFS:
[rY][cX]
Row#0	=  ,  ,  ,  ,  ,  ,  , 0,  ,  ,  ,  ,  ,  ,
Row#1	=  ,  ,  , 1,  ,  ,  ,  ,  ,  ,  , 8,  ,  ,
Row#2	=  , 2,  ,  ,  , 5,  ,  ,  , 9,  ,  ,  , 2,
Row#3	= 3,  , 4,  , 6,  , 7,  , 0,  , 1,  , 3,  , 4

PrintBinaryTreeIn2DArray ToStrRecur:
[rY][cX]
Row#0	=  ,  ,  ,  ,  ,  ,  , 0,  ,  ,  ,  ,  ,  ,
Row#1	=  ,  ,  , 1,  ,  ,  ,  ,  ,  ,  , 8,  ,  ,
Row#2	=  , 2,  ,  ,  , 5,  ,  ,  , 9,  ,  ,  , 2,
Row#3	= 3,  , 4,  , 6,  , 7,  , 0,  , 1,  , 3,  , 4

 */
/*
//Amazon
class BinaryTreeBottomView
{
public:
	BinaryTreeBottomView(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};
	std::vector<std::string> BFS(TreeNode * root)
	{
		int width = widthRecur(root);
		std::vector<std::string> res(width, "");
		std::queue<std::pair<TreeNode *,int>> que;
		que.push({root,0});
		while (!que.empty())
		{
			auto cur = que.front(); que.pop();
			res[cur.second] = std::to_string(cur.first->val);
			if (cur.first->left)
				que.push({cur.first->left, 2*cur.second+1});
		}
		return res;
	}
	int widthRecur(TreeNode * cur)
	{
		if (cur == NULL) return 0;
		return std::max(widthRecur(cur->left), widthRecur(cur->right)) * 2 + 1;
	}
};
*/
#endif
