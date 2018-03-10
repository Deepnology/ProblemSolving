#ifndef CARTESIAN_TREE_H
#define CARTESIAN_TREE_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include "Debug.h"
#include "PrintBinaryTree.h"
/*
Leetcode: Maximum Binary Tree
Elements of programming interview, BinaryTrees: Reconstruct a binary tree from traversal data, variant
Let A be an array of n distinct integers.
Let the index of the maximum element of A be m.
Define the max-tree on A to be the binary tree on the entries of A in which the root contains the maximum element of A
, the left child is the max-tree on A[0:m-1] and the right child is the max-tree on A[m+1:n-1].
Design an O(n) algorithm for building the max-tree of A.
http://web.stanford.edu/class/cs166/
http://www.sanfoundry.com/cpp-program-implement-cartesian-tree/
Convert an array to a binary tree (Cartesian Tree),
where the in-order traversal of the tree represents the original array, and
where a parent of a non-root node always has a smaller value than the node itself (Heap Property).
Based on the heap property, the root of the tree must be the smallest number in the sequence.

Construct with sorted stack: O(n) time
Construct with brute force recursion: O(nlogn) time in average, O(n^2) time in worst case

To query the range minimum of any two points in a given segment, we can build the Cartesian Tree for the given segment
, and the lowest common ancestor node of the two nodes in the Cartesian Tree is the answer.

see also LargestRectHistogram.h, AllStockSpans.h
see also MinFirstBST.h, Treap.h, LowestCommonAncestorBinaryTree.h
see also ConvertSortedArrayToBinarySearchTree.h, ConvertSortedListToBinarySearchTree.h
see also ConstructBSTFromTraversal.h
*/
class CartesianTree
{
public:
	CartesianTree(){}
	~CartesianTree(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	//O(n) time
	//inorder traversal of the tree is original array and min heap property is kept
	TreeNode * Construct_SortedStack(const std::vector<int> & inorder)//inorder is not necessarily sorted
	{
		int N = inorder.size();
		std::stack<TreeNode *> stk;//nodes' vals sorted in increasing order
								   //this sorted stack (from left to right, bottom to top) actually keeps track of the rightmost path nodes starting from root
		
		TreeNode * root = new TreeNode(inorder[0]);
		stk.push(root);
		for (int i = 1; i < N; ++i)
		{
			TreeNode * cur = new TreeNode(inorder[i]);
			
			//insert cur to the rightmost path nodes in stk
			TreeNode * highestLeftChild = NULL;
			while (!stk.empty() && stk.top()->val > cur->val)
			{
				highestLeftChild = stk.top();
				stk.pop();
			}
			cur->left = highestLeftChild;
			if (!stk.empty())
				stk.top()->right = cur;

			stk.push(cur);
			
			root = cur->val < root->val ? cur : root;

			//std::ostringstream oss;
			//oss << "Inserting " << inorder[i] << ": ";
			//std::stack<TreeNode *> copy(stk);
			//std::stack<TreeNode *> copy2;
			//while (!copy.empty())
			//	copy2.push(copy.top()), copy.pop();
			//while (!copy2.empty())
			//	oss << copy2.top()->val << ",", copy2.pop();
			//oss << std::endl;
			//PrintBinaryTree<TreeNode, std::ostringstream>(root, oss);
			//std::cout << oss.str() << std::endl;
		}
		return root;
	}

	//O(nlogn) time in average, O(n^2) time in worst case
	TreeNode * Construct_BruteForceRecur(const std::vector<int> & inorder)
	{
		int N = inorder.size();
		return this->construct_Recur(inorder, 0, N - 1);
	}
private:
	TreeNode * construct_Recur(const std::vector<int> & inorder, int start, int end)
	{
		if (start > end)
			return NULL;
		int minVal = inorder[start];
		int minIdx = start;
		for (int i = start + 1; i <= end; ++i)
			if (inorder[i] < minVal)
			{
				minVal = inorder[i];
				minIdx = i;
			}
		TreeNode * root = new TreeNode(minVal);
		if (start == end)
			return root;
		root->left = this->construct_Recur(inorder, start, minIdx - 1);
		root->right = this->construct_Recur(inorder, minIdx + 1, end);
		return root;
	}

public:
	TreeNode * RangeMin_LCA(TreeNode * root, TreeNode * a, TreeNode * b)
	{
		std::pair<int, TreeNode *> res = this->LCARecur(root, a, b);
		std::string node = res.second == nullptr ? "N" : std::to_string(res.second->val);
		std::cout << "CartesianTree RangeMin_LCA for \"" << a->val << "," << b->val << "\": " << node << std::endl;
		return res.second;
	}
private:
	std::pair<int, TreeNode *> LCARecur(TreeNode * root, TreeNode * a, TreeNode * b)
	{
		if (root == nullptr)
			return{ 0, nullptr };

		std::pair<int, TreeNode *> left = this->LCARecur(root->left, a, b);
		if (left.first == 2)//found both nodes in left subtree
			return left;

		std::pair<int, TreeNode *> right = this->LCARecur(root->right, a, b);
		if (right.first == 2)//found both nodes in right subtree
			return right;

		int foundCount = left.first + right.first + (root == a || root == b);

		return{ foundCount, foundCount == 2 ? root : nullptr };
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
Inserting 41: 31,41,
  
   1
  31
 /   \
 X   2
 N  41


Inserting 59: 31,41,59,
      
       1
    __31__
   /       \
   X       2
   N      41
 /   \   /   \
 X   X   X   3
 N   N   N  59


Inserting 26: 26,
              
               1
        ______26______
       /               \
       2               X
    __31__          __ N__
   /       \       /       \
   X       3       X       X
   N      41       N       N
 /   \   /   \   /   \   /   \
 X   X   X   4   X   X   X   X
 N   N   N  59   N   N   N   N


Inserting 53: 26,53,
              
               1
        ______26______
       /               \
       2               2
    __31__          __53__
   /       \       /       \
   X       3       X       X
   N      41       N       N
 /   \   /   \   /   \   /   \
 X   X   X   4   X   X   X   X
 N   N   N  59   N   N   N   N


Inserting 58: 26,53,58,
              
               1
        ______26______
       /               \
       2               2
    __31__          __53__
   /       \       /       \
   X       3       X       3
   N      41       N      58
 /   \   /   \   /   \   /   \
 X   X   X   4   X   X   X   X
 N   N   N  59   N   N   N   N


Inserting 97: 26,53,58,97,
              
               1
        ______26______
       /               \
       2               2
    __31__          __53__
   /       \       /       \
   X       3       X       3
   N      41       N      58
 /   \   /   \   /   \   /   \
 X   X   X   4   X   X   X   4
 N   N   N  59   N   N   N  97


Inserting 23: 23,
                              
                               1
                ______________23______________
               /                               \
               2                               X
        ______26______                  ______ N______
       /               \               /               \
       3               3               X               X
    __31__          __53__          __ N__          __ N__
   /       \       /       \       /       \       /       \
   X       4       X       4       X       X       X       X
   N      41       N      58       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   5   X   X   X   5   X   X   X   X   X   X   X   X
 N   N   N  59   N   N   N  97   N   N   N   N   N   N   N   N


Inserting 93: 23,93,
                              
                               1
                ______________23______________
               /                               \
               2                               2
        ______26______                  ______93______
       /               \               /               \
       3               3               X               X
    __31__          __53__          __ N__          __ N__
   /       \       /       \       /       \       /       \
   X       4       X       4       X       X       X       X
   N      41       N      58       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   5   X   X   X   5   X   X   X   X   X   X   X   X
 N   N   N  59   N   N   N  97   N   N   N   N   N   N   N   N


Inserting 84: 23,84,
                              
                               1
                ______________23______________
               /                               \
               2                               2
        ______26______                  ______84______
       /               \               /               \
       3               3               3               X
    __31__          __53__          __93__          __ N__
   /       \       /       \       /       \       /       \
   X       4       X       4       X       X       X       X
   N      41       N      58       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   5   X   X   X   5   X   X   X   X   X   X   X   X
 N   N   N  59   N   N   N  97   N   N   N   N   N   N   N   N


Inserting 33: 23,33,
                              
                               1
                ______________23______________
               /                               \
               2                               2
        ______26______                  ______33______
       /               \               /               \
       3               3               3               X
    __31__          __53__          __84__          __ N__
   /       \       /       \       /       \       /       \
   X       4       X       4       4       X       X       X
   N      41       N      58      93       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   5   X   X   X   5   X   X   X   X   X   X   X   X
 N   N   N  59   N   N   N  97   N   N   N   N   N   N   N   N


Inserting 64: 23,33,64,
                              
                               1
                ______________23______________
               /                               \
               2                               2
        ______26______                  ______33______
       /               \               /               \
       3               3               3               3
    __31__          __53__          __84__          __64__
   /       \       /       \       /       \       /       \
   X       4       X       4       4       X       X       X
   N      41       N      58      93       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   5   X   X   X   5   X   X   X   X   X   X   X   X
 N   N   N  59   N   N   N  97   N   N   N   N   N   N   N   N


Inserting 62: 23,33,62,
                              
                               1
                ______________23______________
               /                               \
               2                               2
        ______26______                  ______33______
       /               \               /               \
       3               3               3               3
    __31__          __53__          __84__          __62__
   /       \       /       \       /       \       /       \
   X       4       X       4       4       X       4       X
   N      41       N      58      93       N      64       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   5   X   X   X   5   X   X   X   X   X   X   X   X
 N   N   N  59   N   N   N  97   N   N   N   N   N   N   N   N


Inserting 83: 23,33,62,83,
                              
                               1
                ______________23______________
               /                               \
               2                               2
        ______26______                  ______33______
       /               \               /               \
       3               3               3               3
    __31__          __53__          __84__          __62__
   /       \       /       \       /       \       /       \
   X       4       X       4       4       X       4       4
   N      41       N      58      93       N      64      83
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   5   X   X   X   5   X   X   X   X   X   X   X   X
 N   N   N  59   N   N   N  97   N   N   N   N   N   N   N   N


Inserting 27: 23,27,
                              
                               1
                ______________23______________
               /                               \
               2                               2
        ______26______                  ______27______
       /               \               /               \
       3               3               3               X
    __31__          __53__          __33__          __ N__
   /       \       /       \       /       \       /       \
   X       4       X       4       4       4       X       X
   N      41       N      58      84      62       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   5   X   X   X   5   5   X   5   5   X   X   X   X
 N   N   N  59   N   N   N  97  93   N  64  83   N   N   N   N


CartesianTree SortedStack and BruteForceRecur for "31, 41, 59, 26, 53, 58, 97, 23, 93, 84, 33, 64, 62, 83, 27":
                              
                               1
                ______________23______________
               /                               \
               2                               2
        ______26______                  ______27______
       /               \               /               \
       3               3               3               X
    __31__          __53__          __33__          __ N__
   /       \       /       \       /       \       /       \
   X       4       X       4       4       4       X       X
   N      41       N      58      84      62       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   5   X   X   X   5   5   X   5   5   X   X   X   X
 N   N   N  59   N   N   N  97  93   N  64  83   N   N   N   N

                              
                               1
                ______________23______________
               /                               \
               2                               2
        ______26______                  ______27______
       /               \               /               \
       3               3               3               X
    __31__          __53__          __33__          __ N__
   /       \       /       \       /       \       /       \
   X       4       X       4       4       4       X       X
   N      41       N      58      84      62       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   5   X   X   X   5   5   X   5   5   X   X   X   X
 N   N   N  59   N   N   N  97  93   N  64  83   N   N   N   N


CartesianTree RangeMin_LCA for "31,62": 23
CartesianTree RangeMin_LCA for "31,62": 23
Inserting 45: 32,45,
  
   1
  32
 /   \
 X   2
 N  45


Inserting 16: 16,
      
       1
    __16__
   /       \
   2       X
  32       N
 /   \   /   \
 X   3   X   X
 N  45   N   N


Inserting 18: 16,18,
      
       1
    __16__
   /       \
   2       2
  32      18
 /   \   /   \
 X   3   X   X
 N  45   N   N


Inserting 9: 9,
              
               1
        ______ 9______
       /               \
       2               X
    __16__          __ N__
   /       \       /       \
   3       3       X       X
  32      18       N       N
 /   \   /   \   /   \   /   \
 X   4   X   X   X   X   X   X
 N  45   N   N   N   N   N   N


Inserting 33: 9,33,
              
               1
        ______ 9______
       /               \
       2               2
    __16__          __33__
   /       \       /       \
   3       3       X       X
  32      18       N       N
 /   \   /   \   /   \   /   \
 X   4   X   X   X   X   X   X
 N  45   N   N   N   N   N   N


CartesianTree SortedStack and BruteForceRecur for "32, 45, 16, 18, 9, 33":
              
               1
        ______ 9______
       /               \
       2               2
    __16__          __33__
   /       \       /       \
   3       3       X       X
  32      18       N       N
 /   \   /   \   /   \   /   \
 X   4   X   X   X   X   X   X
 N  45   N   N   N   N   N   N

              
               1
        ______ 9______
       /               \
       2               2
    __16__          __33__
   /       \       /       \
   3       3       X       X
  32      18       N       N
 /   \   /   \   /   \   /   \
 X   4   X   X   X   X   X   X
 N  45   N   N   N   N   N   N


CartesianTree RangeMin_LCA for "45,18": 16
CartesianTree RangeMin_LCA for "45,18": 16
Inserting 3: 3,
  
   1
   3
 /   \
 2   X
 9   N


Inserting 7: 3,7,
  
   1
   3
 /   \
 2   2
 9   7


Inserting 1: 1,
      
       1
    __ 1__
   /       \
   2       X
   3       N
 /   \   /   \
 3   3   X   X
 9   7   N   N


Inserting 8: 1,8,
      
       1
    __ 1__
   /       \
   2       2
   3       8
 /   \   /   \
 3   3   X   X
 9   7   N   N


Inserting 12: 1,8,12,
      
       1
    __ 1__
   /       \
   2       2
   3       8
 /   \   /   \
 3   3   X   3
 9   7   N  12


Inserting 10: 1,8,10,
              
               1
        ______ 1______
       /               \
       2               2
    __ 3__          __ 8__
   /       \       /       \
   3       3       X       3
   9       7       N      10
 /   \   /   \   /   \   /   \
 X   X   X   X   X   X   4   X
 N   N   N   N   N   N  12   N


Inserting 20: 1,8,10,20,
              
               1
        ______ 1______
       /               \
       2               2
    __ 3__          __ 8__
   /       \       /       \
   3       3       X       3
   9       7       N      10
 /   \   /   \   /   \   /   \
 X   X   X   X   X   X   4   4
 N   N   N   N   N   N  12  20


Inserting 15: 1,8,10,15,
                              
                               1
                ______________ 1______________
               /                               \
               2                               2
        ______ 3______                  ______ 8______
       /               \               /               \
       3               3               X               3
    __ 9__          __ 7__          __ N__          __10__
   /       \       /       \       /       \       /       \
   X       X       X       X       X       X       4       4
   N       N       N       N       N       N      12      15
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   X   X   5   X
 N   N   N   N   N   N   N   N   N   N   N   N   N   N  20   N


Inserting 18: 1,8,10,15,18,
                              
                               1
                ______________ 1______________
               /                               \
               2                               2
        ______ 3______                  ______ 8______
       /               \               /               \
       3               3               X               3
    __ 9__          __ 7__          __ N__          __10__
   /       \       /       \       /       \       /       \
   X       X       X       X       X       X       4       4
   N       N       N       N       N       N      12      15
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   X   X   5   5
 N   N   N   N   N   N   N   N   N   N   N   N   N   N  20  18


Inserting 5: 1,5,
                                                              
                                                               1
                                ______________________________ 1______________________________
                               /                                                               \
                               2                                                               2
                ______________ 3______________                                  ______________ 5______________
               /                               \                               /                               \
               3                               3                               3                               X
        ______ 9______                  ______ 7______                  ______ 8______                  ______ N______
       /               \               /               \               /               \               /               \
       X               X               X               X               X               4               X               X
    __ N__          __ N__          __ N__          __ N__          __ N__          __10__          __ N__          __ N__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       X       X       X       X       X       X       5       5       X       X       X       X
   N       N       N       N       N       N       N       N       N       N      12      15       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   6   6   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N  20  18   N   N   N   N   N   N   N   N


CartesianTree SortedStack and BruteForceRecur for "9, 3, 7, 1, 8, 12, 10, 20, 15, 18, 5":
                                                              
                                                               1
                                ______________________________ 1______________________________
                               /                                                               \
                               2                                                               2
                ______________ 3______________                                  ______________ 5______________
               /                               \                               /                               \
               3                               3                               3                               X
        ______ 9______                  ______ 7______                  ______ 8______                  ______ N______
       /               \               /               \               /               \               /               \
       X               X               X               X               X               4               X               X
    __ N__          __ N__          __ N__          __ N__          __ N__          __10__          __ N__          __ N__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       X       X       X       X       X       X       5       5       X       X       X       X
   N       N       N       N       N       N       N       N       N       N      12      15       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   6   6   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N  20  18   N   N   N   N   N   N   N   N

                                                              
                                                               1
                                ______________________________ 1______________________________
                               /                                                               \
                               2                                                               2
                ______________ 3______________                                  ______________ 5______________
               /                               \                               /                               \
               3                               3                               3                               X
        ______ 9______                  ______ 7______                  ______ 8______                  ______ N______
       /               \               /               \               /               \               /               \
       X               X               X               X               X               4               X               X
    __ N__          __ N__          __ N__          __ N__          __ N__          __10__          __ N__          __ N__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       X       X       X       X       X       X       5       5       X       X       X       X
   N       N       N       N       N       N       N       N       N       N      12      15       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   6   6   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N  20  18   N   N   N   N   N   N   N   N


CartesianTree RangeMin_LCA for "9,10": 1
CartesianTree RangeMin_LCA for "9,10": 1
*/
#endif