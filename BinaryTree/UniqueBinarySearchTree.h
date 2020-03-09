#ifndef UNIQUE_BINARY_SEARCH_TREE
#define UNIQUE_BINARY_SEARCH_TREE
#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <algorithm>
#include "PrintBinaryTree.h"
/*
Elements of programming interview, Recursion: Enumerate binary trees
Write a function which takes as input an integer n and returns all distinct binary trees with n nodes.
Leetcode: Unique Binary Search Trees
// Unique Binary Search Trees
// Given n, how many structurally unique BST's (binary search trees) that
// store values 1...n?
//
// For example,
// Given n = 3, there are a total of 5 unique BST's.
//
//   1         3     3      2      1
//    \       /     /      / \      \
//     3     2     1      1   3      2
//    /     /       \                 \
//   2     1         2                 3
//
// Complexity:
// Recursion, O(n^2) time, O(n) space
// DP, O(n^2) time, O(n) space
// Math, O(n) time, O(1) space
See also CatalanNumber.h

Leetcode: Unique Binary Search Trees II
// Unique Binary Search Trees II
// Given n, generate all structurally unique BST's (binary search trees) that
// store values 1...n.
//
// For example,
// Given n = 3, your program should return all 5 unique BST's shown below.
//
//   1         3     3      2      1
//    \       /     /      / \      \
//     3     2     1      1   3      2
//    /     /       \                 \
//   2     1         2                 3
//
// Complexity: (Cn*n) Cn is Catalan number
// DFS + Memoization
// DP
See also ParenthesesCombination.h

//   1    1        2        3     3
//    \    \      / \      /     /
//     3    2    1   3    2     1
//    /      \           /       \
//   2        3         1         2
//
*/
class UniqueBinarySearchTree
{
public:
	UniqueBinarySearchTree(){}
	~UniqueBinarySearchTree(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	//1 count
	//1.1 recur: time limit exceeded
	int count_Recur(int n)
	{
		int res = this->countRecur(n);

		std::cout << "UniqueBinarySearchTree count recur for 1..." << n << ": " << res << std::endl;
		return res;
	}
private:
	int countRecur(int n)
	{
		if (n <= 1)
			return 1;

		int res = 0;
		for (int leftCount = 0; leftCount < n; ++leftCount)
		{
			int rightCount = n - leftCount - 1;//rightCount must exclude root
			res += this->countRecur(leftCount) * this->countRecur(rightCount);
		}
		return res;
	}

public:
	//1.2 DP (See also CatalanNumber.h)
	int count_DP(int n)
	{
		std::vector<int> dp(n + 1, 0);
		dp[0] = 1;
		dp[1] = 1;
		/*
		2 numbers {1,2}:
		dp[2] = dp[0] * dp[1] (root = 1)
				+ dp[1] * dp[0] (root = 2)

		3 numbers {1,2,3}:
		dp[3] = dp[0] * dp[2] (root = 1)
				+ dp[1] * dp[1] (root = 2)
				+ dp[2] * dp[0] (root = 3)
		*/

		for (int count = 2; count <= n; ++count)
		{
			for (int leftCount = 0; leftCount < count; ++leftCount)//suppose leftCount includes root
			{
				int rightCount = count - leftCount - 1;//rightCount doesn't include root
				dp[count] += dp[leftCount] * dp[rightCount];
			}
		}

		std::cout << "UniqueBinarySearchTree count DP for 1..." << n << ": " << dp[n] << std::endl;
		return dp[n];
	}

	//2 generate
	//2.1 recur
	std::vector<TreeNode *> generate_Recur(int n)
	{
		return this->generateRecur(1, n);//root number is from 1 to n (1-based as required)
	}
private:
	std::vector<TreeNode *> generateRecur(int start, int end)
	{
		std::vector<TreeNode *> subTrees;

		if (start > end)//this is why corner case (start, end) should be: (1, 0) and (n+1, n)
		{	
			subTrees.push_back(NULL);
			return subTrees;
		}

		for (int i = start; i <= end; ++i)
		{
			//at current node
			auto leftSubs = this->generateRecur(start, i - 1);//generate all possible left subtrees from start to i-1
			auto rightSubs = this->generateRecur(i + 1, end);//generate all possible right subtrees from i+1 to end

			//post order: now visit current node. create new subtree rooted at i with all possible left and right subtree combinations
			for (auto lSub : leftSubs)
			{
				for (auto rSub : rightSubs)
				{
					//generate current node's subtree
					TreeNode * root = new TreeNode(i);
					//std::cout << "new " << i << std::endl;
					root->left = lSub;
					root->right = rSub;
					subTrees.push_back(root);
				}
			}
		}

		return subTrees;
	}

	//2.2 DP
public:
	std::vector<TreeNode *> generate_DP(int n)
	{
		std::vector<std::vector<std::vector<TreeNode *> > > dp(n + 2, std::vector<std::vector<TreeNode *> >(n + 2, std::vector<TreeNode *>()));

		//dp[x][y]: a list of subtrees whose roots' number range starting from x and ending in y
		//dp[start][start-1]: must be init with a NULL subtree
		for (int i = 1; i <= n + 1; ++i)
			dp[i][i - 1].push_back(NULL);//diagonal

		this->Print3D(dp);

		for (int count = 1; count <= n; ++count)
		{
			for (int start = 1; start <= n - count + 1; ++start)
			{
				int end = start + count - 1;
				/*
				count = 1: {(start,end)} = {(1,1),(2,2),(3,3)}
				count = 2: {(start,end)} = {(1,2),(2,3)}
				count = 3: {(start,end)} = {(1,3)}
				*/

				std::vector<TreeNode *> subTrees;
				for (int subRoot = start; subRoot <= end; ++subRoot)
				{
					for (auto lSub : dp[start][subRoot - 1])//upper grid
					{
						for (auto rSub : dp[subRoot + 1][end])//right grid
						{
							//a new substree rooted at subRoot with all possible left (in upper grid) and right (in right grid) subtrees' combinations
							TreeNode * rootNode = new TreeNode(subRoot);
							rootNode->left = this->clone(lSub);
							rootNode->right = this->clone(rSub);
							subTrees.push_back(rootNode);
						}
					}
				}
				dp[start][end] = subTrees;

				//std::ostringstream oss;
				//for (auto p : res)
				//{
				//	PrintBinaryTree<TreeNode, std::ostringstream>(p, oss);
				//}
				//std::cout << oss.str() << std::endl;
				std::cout << "count, start, end: " << count << ", " << start << ", " << end << ":" << std::endl;
				this->Print3D(dp);
			}
			
		}
		
		return dp[1][n];//a list of subtrees whose roots' number range from 1 to n
	}
private:
	TreeNode * clone(TreeNode * sub)
	{
		if (sub == NULL)
			return NULL;
			
		//perform preorder traversal of oldTree and preorder traversal of newTree
		std::stack<TreeNode *> oldStk;
		std::stack<TreeNode *> newStk;
		oldStk.push(sub);
		TreeNode * root = new TreeNode(sub->val);
		newStk.push(root);
		while (!oldStk.empty())
		{
			TreeNode * cur = oldStk.top(); oldStk.pop();
			TreeNode * copy = newStk.top(); newStk.pop();
			if (cur->right)
			{
				oldStk.push(cur->right);
				copy->right = new TreeNode(cur->right->val);
				newStk.push(copy->right);
			}
			if (cur->left)
			{
				oldStk.push(cur->left);
				copy->left = new TreeNode(cur->left->val);
				newStk.push(copy->left);
			}
		}
		return root;
	}

public:
	static void DeleteTree(TreeNode * root)
	{
		if (root == NULL)
			return;

		//std::cout << root->val << std::endl;
		DeleteTree(root->left);
		DeleteTree(root->right);

		//post order
		delete root;
		root = NULL;
	}
	static void Print3D(std::vector<std::vector<std::vector<TreeNode *> > > & vvv)//[colX][rowY][depthZ]
	{
		std::ostringstream oss;

		int maxColumnSize = vvv[0].size();//can vary
		int maxRowSize = vvv.size();//should be fixed
		int maxDepthSize = 0;
		for (int columnX = 0; columnX < maxRowSize; ++columnX)
		{
			int columnSize = vvv[columnX].size();

			if (maxColumnSize < columnSize)
				maxColumnSize = columnSize;

			for (int rowY = 0; rowY < columnSize; ++rowY)
			{
				int depthSize = vvv[columnX][rowY].size();

				if (maxDepthSize < depthSize)
					maxDepthSize = depthSize;
			}
		}

		for (int rowY = 0; rowY < maxColumnSize; ++rowY)//for each rowY (iterate vertically)
		{
			for (int columnX = 0; columnX < maxRowSize; ++columnX)//for each columnX (iterate horizontally)
			{
				int columnSize = vvv[columnX].size();
				if (columnX == 0)
				{
					oss << "Row_#" << rowY << "	= ";
				}

				if (rowY < columnSize)
				{
					int depthSize = vvv[columnX][rowY].size();
					for (int depthZ = 0; depthZ < depthSize; ++depthZ)
					{
						if (vvv[columnX][rowY][depthZ])
							oss << vvv[columnX][rowY][depthZ]->val;
						else
							oss << "N";
						if (depthZ != depthSize - 1)
							oss << ",";
					}
				}
				else//(rowY > 0 && rowY < maxColumnSize) || (rowY == 0 && columnSize == 0)
				{
					oss << "		";
				}

				if (columnX != maxRowSize - 1)
				{
					oss << ";		";
				}
			}
			oss << std::endl;
		}
		std::cout << oss.str() << std::endl;
	}
};

/*
UniqueBinarySearchTree count recur for 1...3: 5
UniqueBinarySearchTree count DP for 1...3: 5
UniqueBinarySearchTree generate recur (1...3):
      
       1
    __ 1__
   /       \
   X       2
   N       2
 /   \   /   \
 X   X   X   3
 N   N   N   3

      
       1
    __ 1__
   /       \
   X       2
   N       3
 /   \   /   \
 X   X   3   X
 N   N   2   N

  
   1
   2
 /   \
 2   2
 1   3

      
       1
    __ 3__
   /       \
   2       X
   1       N
 /   \   /   \
 X   3   X   X
 N   2   N   N

      
       1
    __ 3__
   /       \
   2       X
   2       N
 /   \   /   \
 3   X   X   X
 1   N   N   N


Row_#0	= ;		N;		;		;		
Row_#1	= ;		;		N;		;		
Row_#2	= ;		;		;		N;		
Row_#3	= ;		;		;		;		N
Row_#4	= ;		;		;		;		

count, start, end: 1, 1, 1:
Row_#0	= ;		N;		;		;		
Row_#1	= ;		1;		N;		;		
Row_#2	= ;		;		;		N;		
Row_#3	= ;		;		;		;		N
Row_#4	= ;		;		;		;		

count, start, end: 1, 2, 2:
Row_#0	= ;		N;		;		;		
Row_#1	= ;		1;		N;		;		
Row_#2	= ;		;		2;		N;		
Row_#3	= ;		;		;		;		N
Row_#4	= ;		;		;		;		

count, start, end: 1, 3, 3:
Row_#0	= ;		N;		;		;		
Row_#1	= ;		1;		N;		;		
Row_#2	= ;		;		2;		N;		
Row_#3	= ;		;		;		3;		N
Row_#4	= ;		;		;		;		

count, start, end: 2, 1, 2:
Row_#0	= ;		N;		;		;		
Row_#1	= ;		1;		N;		;		
Row_#2	= ;		1,2;		2;		N;		
Row_#3	= ;		;		;		3;		N
Row_#4	= ;		;		;		;		

count, start, end: 2, 2, 3:
Row_#0	= ;		N;		;		;		
Row_#1	= ;		1;		N;		;		
Row_#2	= ;		1,2;		2;		N;		
Row_#3	= ;		;		2,3;		3;		N
Row_#4	= ;		;		;		;		

count, start, end: 3, 1, 3:
Row_#0	= ;		N;		;		;		
Row_#1	= ;		1;		N;		;		
Row_#2	= ;		1,2;		2;		N;		
Row_#3	= ;		1,1,2,3,3;		2,3;		3;		N
Row_#4	= ;		;		;		;		

UniqueBinarySearchTree generate DP (1...3):
      
       1
    __ 1__
   /       \
   X       2
   N       2
 /   \   /   \
 X   X   X   3
 N   N   N   3

      
       1
    __ 1__
   /       \
   X       2
   N       3
 /   \   /   \
 X   X   3   X
 N   N   2   N

  
   1
   2
 /   \
 2   2
 1   3

      
       1
    __ 3__
   /       \
   2       X
   1       N
 /   \   /   \
 X   3   X   X
 N   2   N   N

      
       1
    __ 3__
   /       \
   2       X
   2       N
 /   \   /   \
 3   X   X   X
 1   N   N   N

*/



#endif