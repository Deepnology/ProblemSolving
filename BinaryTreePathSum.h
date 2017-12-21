#ifndef BINARY_TREE_PATH_SUM_H
#define BINARY_TREE_PATH_SUM_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, BinaryTrees: Find a root to leaf path with specified sum
1.
Leetcode: Path Sum
//Given a binary tree and a sum, determine if the tree has a root-to-leaf path
// such that adding up all the values along the path equals the given sum.
//
// For example:
// Given the below binary tree and sum = 22,
//              5
//             / \
//            4   8
//           /   / \
//          11  13  4
//         /  \      \
//        7    2      1
// return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
// Complexity:
// O(n) time, O(h) space, h is the height of tree

2.
Leetcode: Path Sum II
// Given a binary tree and a sum, find all root-to-leaf paths where each
// path's sum equals the given sum.
//
// For example:
// Given the below binary tree and sum = 22,
//              5
//             / \
//            4   8
//           /   / \
//          11  13  4
//         /  \    / \
//        7    2  5   1
// return
// [
//   [5,4,11,2],
//   [5,8,4,5]
// ]
//
// Complexity:
// O(n*h) time, O(h) space, h is the height of the tree
(similar Leetcode: Given a binary tree, return all root-to-leaf paths.)

3.
Path Sum III
Cracking the coding interview 4.8
Now, what if the path can start anywhere?
On every node, we look "up" to see if we¡¦ve found the sum.
Time complexity:
There are 2^r nodes at level r.
1*2^1 + 2*2^2 + 3*2^3 + 4*2^4 + ... d * 2^d
= sum(r * 2^r, r from 0 to depth)
= 2 * (d-1) * 2^d + 2
n = 2^d ==> d = lg n
NOTE: 2^lg(x) = x
O(2 (lg n - 1) * 2^(lg n) + 2) = O(2 (lg n - 1) * n ) = O(n lg n)
Following similar logic, our space complexity is O(n lg n)

4.
Leetcode: Path Sum IV
If the depth of a tree is smaller than 5, then this tree can be represented by a list of three-digits integers.
For each integer in this list:
	1. The hundreds digit represents the depth D of this node, 1 <= D <= 4.
    2. The tens digit represents the position P of this node in the level it belongs to, 1 <= P <= 8.
	The position is the same as that in a full binary tree.
    3. The units digit represents the value V of this node, 0 <= V <= 9.
Given a list of ascending three-digits integers representing a binary with the depth smaller than 5.
You need to return the sum of all paths from the root towards the leaves.
Example 1:
Input: [113, 215, 221]
Output: 12
Explanation: 
The tree that the list represents is:
    3
   / \
  5   1
The path sum is (3 + 5) + (3 + 1) = 12.
Example 2:
Input: [113, 221]
Output: 4
Explanation: 
The tree that the list represents is: 
    3
     \
      1
The path sum is (3 + 1) = 4.
*/
class BinaryTreePathSum
{
public:
	BinaryTreePathSum(){}
	~BinaryTreePathSum(){}

	struct TreeNode
	{
		TreeNode(int x): val(x), left(0), right(0) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};
	//1.
	bool HasRootToLeafPathSumRecur(TreeNode * root, int sum)
	{
		bool res = this->hasRootToLeafPathSumRecur(root, sum);
		std::cout << "BinaryTreePathSum HasRootToLeafRecur for sum of \"" << sum << "\": " << res << std::endl;
		return res;
	}
private:
	bool hasRootToLeafPathSumRecur(TreeNode * root, int sum)
	{
		if (root == 0)
			return false;

		sum -= root->val;
		if (root->left == 0 && root->right == 0)//leaf node
			return (sum == 0);
		return this->hasRootToLeafPathSumRecur(root->left, sum) || this->hasRootToLeafPathSumRecur(root->right, sum);
	}
	//2.
public:
	std::vector<std::vector<int> > FindAllRootToLeafPath(TreeNode * root, int sum)
	{
		int accuSumFromRoot = 0;
		std::vector<int> path;
		std::vector<std::vector<int> > res;
		this->findAllRootToLeafPathRecur(root, sum, accuSumFromRoot, path, res);

		std::cout << "BinaryTreePathSum FindAllRootToLeafPath for sum of \"" << sum << "\":" << std::endl;
		Debug::Print2D<int>()(res);
		return res;
	}
private:
	void findAllRootToLeafPathRecur(TreeNode * cur, const int & targetSum, int & accuSumFromRoot, std::vector<int> & path, std::vector<std::vector<int> > & res)
	{
		if (cur == NULL)
			return;

		accuSumFromRoot += cur->val;
		path.push_back(cur->val);

		if (cur->left == NULL && cur->right == NULL)//reach a leaf node
		{
			if (accuSumFromRoot == targetSum)
				res.push_back(path);
		}
		else
		{
			this->findAllRootToLeafPathRecur(cur->left, targetSum, accuSumFromRoot, path, res);
			this->findAllRootToLeafPathRecur(cur->right, targetSum, accuSumFromRoot, path, res);
		}
		
		path.pop_back();
		accuSumFromRoot -= cur->val;
	}
	
	//3.
public:
	std::vector<std::vector<int> > FindAllArbitraryPath(TreeNode * root, int sum)
	{
		std::vector<int> path;
		std::vector<std::vector<int> > res;
		this->findAllArbitraryPathRecur(root, sum, path, res);

		std::cout << "BinaryTreePathSum FindAllArbitraryPath for sum of \"" << sum << "\":" << std::endl;
		Debug::Print2D<int>()(res);
		return res;
	}
private:
	void findAllArbitraryPathRecur(TreeNode * cur, int targetSum, std::vector<int> & path, std::vector<std::vector<int> > & res)
	{
		if (cur == NULL)
			return;
		path.push_back(cur->val);

		/*
		this part was from Cracking the coding interview 4.8
		find the path from current node up to some other parent node that sum to targetSum
		*/
		std::vector<int> sumPathUp = this->sumPathUpFromCur(path, targetSum);
		if (sumPathUp.size() > 0)
			res.push_back(sumPathUp);

		this->findAllArbitraryPathRecur(cur->left, targetSum, path, res);
		this->findAllArbitraryPathRecur(cur->right, targetSum, path, res);
		path.pop_back();
	}
	std::vector<int> sumPathUpFromCur(const std::vector<int> & path, int targetSum)
	{
		int N = path.size();
		if (N == 0)
			return std::vector<int>();
		int sum = 0;
		for (int i = N - 1; i >= 0; --i)
		{
			sum += path[i];//accumulated sum from path's end
			if (sum == targetSum)
			{
				//found, stop and return path with nodes from end to cur
				return std::vector<int>(path.begin() + i, path.end());
			}
		}
		//not found
		return std::vector<int>();
	}
public:
	//Similar to Leetcode: Path Sum III
	int CountNumOfPathSum(TreeNode* root, int sum)
	{
		std::vector<int> path;
		int res = 0;
		this->findAllArbitraryPathRecur(root, sum, path, res);
		return res;
	}
private:
	void findAllArbitraryPathRecur(TreeNode * cur, int targetSum, std::vector<int> & path, int & res)
	{
		if (cur == NULL)
			return;
		path.push_back(cur->val);
		int countSumPathUp = this->countNumOfPathUpFromCur(path, targetSum);
		res += countSumPathUp;

		this->findAllArbitraryPathRecur(cur->left, targetSum, path, res);
		this->findAllArbitraryPathRecur(cur->right, targetSum, path, res);
		path.pop_back();
	}
	int countNumOfPathUpFromCur(const std::vector<int> & path, int targetSum)
	{
		int N = path.size();
		if (N == 0)
			return 0;
		int count = 0;
		int sum = 0;
		for (int i = N - 1; i >= 0; --i)
		{
			sum += path[i];
			if (sum == targetSum)
				++count;
		}
		return count;
	}

public:
	//4. Path Sum IV
	struct Hash
	{
		size_t operator()(const std::pair<int, int> & a) const
		{
			return a.first ^ a.second;
		}
	};
	int SumAllPaths(std::vector<int> & nums)//[depth|position|value, depth|position|value, ...]
	{
		std::unordered_map<std::pair<int, int>, int, Hash> map;//<<depth,position>,value>
		for (auto num : nums)
		{
			map.insert({ { (num / 100) % 10,(num / 10) % 10 },num % 10 });
		}
		int resSum = 0;
		if (map.count({ 1,1 }))
			recur(map, 1, 1, 0, resSum);
		return resSum;
	}
private:
	void recur(std::unordered_map<std::pair<int, int>, int, Hash> & map, int curDepth, int curPos, int curSum, int & resSum)
	{
		std::pair<int, int> leftChild = { curDepth + 1, curPos * 2 - 1 };
		std::pair<int, int> rightChild = { curDepth + 1, curPos * 2 };
		curSum += map[{curDepth, curPos}];
		if (!map.count(leftChild) && !map.count(rightChild))//this is a leaf node
		{
			resSum += curSum;
			return;
		}
		if (map.count(leftChild))
			recur(map, leftChild.first, leftChild.second, curSum, resSum);
		if (map.count(rightChild))
			recur(map, rightChild.first, rightChild.second, curSum, resSum);
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
        ______ 5______
       /               \
       2               2
    __ 4__          __ 8__
   /       \       /       \
   3       3       3       3
  11      18       9       6
 /   \   /   \   /   \   /   \
 4   4   4   4   4   4   4   4
 7   2  10   1   5   7   3  16


BinaryTreePathSum HasRootToLeafRecur for sum of "22": 1
BinaryTreePathSum FindAllRootToLeafPath for sum of "22":
[cX][rY]
Row#0	= 5, 5
Row#1	= 4, 8
Row#2	= 11, 6
Row#3	= 2, 3

BinaryTreePathSum FindAllArbitraryPath for sum of "22":
[cX][rY]
Row#0	= 4, 5, 4, 5, 8, 5, 6
Row#1	= 11, 4, 18, 8, 9, 8, 16
Row#2	= 7, 11,  , 9, 5, 6,  
Row#3	=  , 2,  ,  ,  , 3,  

*/
#endif