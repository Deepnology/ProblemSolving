#ifndef _VERIFY_PREORDER_TRAVERSAL_BST_H
#define _VERIFY_PREORDER_TRAVERSAL_BST_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "Debug.h"
/*
https://discuss.leetcode.com/topic/21217/java-o-n-and-o-1-extra-space/2
Leetcode: Verify Preorder Sequence in Binary Search Tree

Given an array of numbers, verify whether it is the correct preorder traversal sequence of a binary search tree.
You may assume each number in the sequence is unique.
Follow up:
Could you do it using only constant space complexity?

Recur: O(n^2) time, O(1) space
UseSortedStack: O(n) time, O(n) space
InPlace: O(n) time, O(1) space
see also ConstructBSTFromTraversal.h
*/
class VerifyPreOrderTraversalBST
{
public:
	VerifyPreOrderTraversalBST() {}
	~VerifyPreOrderTraversalBST() {}

	bool BruteForceRecur(const std::vector<int> & preorder)
	{
		int N = preorder.size();
		if (N <= 1)
			return true;
		bool res = this->recur(preorder, 0, N - 1);
		std::cout << "VerifyPreOrderTraversalBST BruteForceRecur for \"" << Debug::ToStr1D<int>()(preorder) << "\": " << res << std::endl;
		return res;
	}
private:
	bool recur(const std::vector<int> & preorder, int start, int end)
	{
		if (start >= end)//all nodes in [start,end] are valid
			return true;

		int root = preorder[start];
		int mid = start + 1;
		//1. go over left subtree
		while (mid <= end && preorder[mid] < root)
			++mid;
		//now mid is the first node of right subtree
		//2. go over right subtree to verify all nodes in the right subtree
		int rightSub = mid;
		while (rightSub <= end && preorder[rightSub] > root)
			++rightSub;

		if (rightSub <= end)//some node in [start, end] doesn't satisfy leftSubNodes < root && rightSubNodes > root
			return false;

		return recur(preorder, start + 1, mid - 1) && recur(preorder, mid, end);
	}

public:
	bool LinearRecur(const std::vector<int> & preorder)
	{
		int N = preorder.size();
		int cur = 0;
		recur(preorder, INT_MIN, INT_MAX, cur);

		std::cout << "VerifyPreOrderTraversalBST LinearRecur for \"" << Debug::ToStr1D<int>()(preorder) << "\": " << (cur == N) << " (cur=" << cur << ")" << std::endl;
		return cur == N;
	}
private:
	void recur(const std::vector<int> & preorder, int min, int max, int & cur)
	{
		int N = preorder.size();
		if (cur == N)
			return;
		int curVal = preorder[cur];
		if (curVal < min || curVal > max)
			return;
		++cur;
		recur(preorder, min, curVal, cur);
		recur(preorder, curVal, max, cur);
	}

public:
	bool UseSortedStack(const std::vector<int> & preorder)
	{
		int N = preorder.size();
		if (N <= 1)
			return true;

		std::vector<int> sortedStk;//in descending order (keep a path of greater nodes in left subtree from top to cur excluding lesser ancestor nodes)
		int lowestA = INT_MIN;//lowest ancestor for cur node as a right child
		bool res = true;
		for (int i = 0; i < N; ++i)
		{
			if (preorder[i] < lowestA)//now lowestA becomes either a "left sibling of preorder[i]" OR a "lowest ancestor of preorder[i] as a right grand child" ==> lowestA must < preorder[i]
			{
				res = false;
				break;
			}

			//pop out cur node's left siblings and parent (which are all less than cur)
			//the last one popped will be the "lowest ancestor for cur node as a right child" (cur > lowestA)
			while (!sortedStk.empty() && preorder[i] > sortedStk.back())
			{
				lowestA = sortedStk.back();//lowestA is the leftmost one
				sortedStk.pop_back();
			}

			sortedStk.push_back(preorder[i]);

			std::cout << Debug::ToStr1D<int>()(sortedStk) << ". cur: " << preorder[i] << ", lowestA: " << lowestA << std::endl;
		}

		std::cout << "VerifyPreOrderTraversalBST UseSortedStack for \"" << Debug::ToStr1D<int>()(preorder) << "\": " << res << std::endl;
		return res;
	}

	bool InPlace(std::vector<int> && preorder)
	{
		std::vector<int> copy(preorder);
		int N = preorder.size();
		if (N <= 1)
			return true;

		int top = -1;//the top index of stack
		int lowestA = INT_MIN;
		bool res = true;
		for (int i = 0; i < N; ++i)
		{
			if (preorder[i] < lowestA)
			{
				res = false;
				break;
			}

			while (top >= 0 && preorder[i] > preorder[top])
			{
				lowestA = preorder[top];
				--top;
			}

			++top;
			preorder[top] = preorder[i];

			std::cout << Debug::ToStr1D<int>()(preorder) << ". cur: " << preorder[i] << ", lowestA: " << lowestA << std::endl;
		}

		std::cout << "VerifyPreOrderTraversalBST InPlace for \"" << Debug::ToStr1D<int>()(copy) << "\": " << res << std::endl;
		return res;
	}
};
/*
               N
        ______ 7______
       /               \
       7               7
    __ 3__          __11__
   /       \       /       \
   3       3      11      11
   1       5       9      13
 /   \   /   \   /   \   /   \
 1   1   5   5   9   9  13  13
 0   2   4   6   8  10  12  14

VerifyPreOrderTraversalBST BruteForceRecur for "7, 3, 1, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14": 1
VerifyPreOrderTraversalBST LinearRecur for "7, 3, 1, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14": 1 (cur=15)
7. cur: 7, lowestA: -2147483648
7, 3. cur: 3, lowestA: -2147483648
7, 3, 1. cur: 1, lowestA: -2147483648
7, 3, 1, 0. cur: 0, lowestA: -2147483648
7, 3, 2. cur: 2, lowestA: 1
7, 5. cur: 5, lowestA: 3
7, 5, 4. cur: 4, lowestA: 3
7, 6. cur: 6, lowestA: 5
11. cur: 11, lowestA: 7
11, 9. cur: 9, lowestA: 7
11, 9, 8. cur: 8, lowestA: 7
11, 10. cur: 10, lowestA: 9
13. cur: 13, lowestA: 11
13, 12. cur: 12, lowestA: 11
14. cur: 14, lowestA: 13
VerifyPreOrderTraversalBST UseSortedStack for "7, 3, 1, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14": 1
7, 3, 1, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14. cur: 7, lowestA: -2147483648
7, 3, 1, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14. cur: 3, lowestA: -2147483648
7, 3, 1, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14. cur: 1, lowestA: -2147483648
7, 3, 1, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14. cur: 0, lowestA: -2147483648
7, 3, 2, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14. cur: 2, lowestA: 1
7, 5, 2, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14. cur: 5, lowestA: 3
7, 5, 4, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14. cur: 4, lowestA: 3
7, 6, 4, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14. cur: 6, lowestA: 5
11, 6, 4, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14. cur: 11, lowestA: 7
11, 9, 4, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14. cur: 9, lowestA: 7
11, 9, 8, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14. cur: 8, lowestA: 7
11, 10, 8, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14. cur: 10, lowestA: 9
13, 10, 8, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14. cur: 13, lowestA: 11
13, 12, 8, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14. cur: 12, lowestA: 11
14, 12, 8, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14. cur: 14, lowestA: 13
VerifyPreOrderTraversalBST InPlace for "7, 3, 1, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14": 1
VerifyPreOrderTraversalBST BruteForceRecur for "7, 3, 1, 0, 2, 8, 4, 6, 11, 9, 5, 10, 13, 12, 14": 0
VerifyPreOrderTraversalBST LinearRecur for "7, 3, 1, 0, 2, 8, 4, 6, 11, 9, 5, 10, 13, 12, 14": 0 (cur=6)
7. cur: 7, lowestA: -2147483648
7, 3. cur: 3, lowestA: -2147483648
7, 3, 1. cur: 1, lowestA: -2147483648
7, 3, 1, 0. cur: 0, lowestA: -2147483648
7, 3, 2. cur: 2, lowestA: 1
8. cur: 8, lowestA: 7
VerifyPreOrderTraversalBST UseSortedStack for "7, 3, 1, 0, 2, 8, 4, 6, 11, 9, 5, 10, 13, 12, 14": 0
7, 3, 1, 0, 2, 8, 4, 6, 11, 9, 5, 10, 13, 12, 14. cur: 7, lowestA: -2147483648
7, 3, 1, 0, 2, 8, 4, 6, 11, 9, 5, 10, 13, 12, 14. cur: 3, lowestA: -2147483648
7, 3, 1, 0, 2, 8, 4, 6, 11, 9, 5, 10, 13, 12, 14. cur: 1, lowestA: -2147483648
7, 3, 1, 0, 2, 8, 4, 6, 11, 9, 5, 10, 13, 12, 14. cur: 0, lowestA: -2147483648
7, 3, 2, 0, 2, 8, 4, 6, 11, 9, 5, 10, 13, 12, 14. cur: 2, lowestA: 1
8, 3, 2, 0, 2, 8, 4, 6, 11, 9, 5, 10, 13, 12, 14. cur: 8, lowestA: 7
VerifyPreOrderTraversalBST InPlace for "7, 3, 1, 0, 2, 8, 4, 6, 11, 9, 5, 10, 13, 12, 14": 0
VerifyPreOrderTraversalBST BruteForceRecur for "7, 3, 1, 0, 11, 5, 4, 6, 2, 9, 8, 10, 13, 12, 14": 0
VerifyPreOrderTraversalBST LinearRecur for "7, 3, 1, 0, 11, 5, 4, 6, 2, 9, 8, 10, 13, 12, 14": 0 (cur=5)
7. cur: 7, lowestA: -2147483648
7, 3. cur: 3, lowestA: -2147483648
7, 3, 1. cur: 1, lowestA: -2147483648
7, 3, 1, 0. cur: 0, lowestA: -2147483648
11. cur: 11, lowestA: 7
VerifyPreOrderTraversalBST UseSortedStack for "7, 3, 1, 0, 11, 5, 4, 6, 2, 9, 8, 10, 13, 12, 14": 0
7, 3, 1, 0, 11, 5, 4, 6, 2, 9, 8, 10, 13, 12, 14. cur: 7, lowestA: -2147483648
7, 3, 1, 0, 11, 5, 4, 6, 2, 9, 8, 10, 13, 12, 14. cur: 3, lowestA: -2147483648
7, 3, 1, 0, 11, 5, 4, 6, 2, 9, 8, 10, 13, 12, 14. cur: 1, lowestA: -2147483648
7, 3, 1, 0, 11, 5, 4, 6, 2, 9, 8, 10, 13, 12, 14. cur: 0, lowestA: -2147483648
11, 3, 1, 0, 11, 5, 4, 6, 2, 9, 8, 10, 13, 12, 14. cur: 11, lowestA: 7
VerifyPreOrderTraversalBST InPlace for "7, 3, 1, 0, 11, 5, 4, 6, 2, 9, 8, 10, 13, 12, 14": 0
VerifyPreOrderTraversalBST BruteForceRecur for "7, 3, 1, 0, 2, 5, 4, 6, 11, 14, 8, 10, 13, 12, 9": 0
VerifyPreOrderTraversalBST LinearRecur for "7, 3, 1, 0, 2, 5, 4, 6, 11, 14, 8, 10, 13, 12, 9": 0 (cur=10)
7. cur: 7, lowestA: -2147483648
7, 3. cur: 3, lowestA: -2147483648
7, 3, 1. cur: 1, lowestA: -2147483648
7, 3, 1, 0. cur: 0, lowestA: -2147483648
7, 3, 2. cur: 2, lowestA: 1
7, 5. cur: 5, lowestA: 3
7, 5, 4. cur: 4, lowestA: 3
7, 6. cur: 6, lowestA: 5
11. cur: 11, lowestA: 7
14. cur: 14, lowestA: 11
VerifyPreOrderTraversalBST UseSortedStack for "7, 3, 1, 0, 2, 5, 4, 6, 11, 14, 8, 10, 13, 12, 9": 0
7, 3, 1, 0, 2, 5, 4, 6, 11, 14, 8, 10, 13, 12, 9. cur: 7, lowestA: -2147483648
7, 3, 1, 0, 2, 5, 4, 6, 11, 14, 8, 10, 13, 12, 9. cur: 3, lowestA: -2147483648
7, 3, 1, 0, 2, 5, 4, 6, 11, 14, 8, 10, 13, 12, 9. cur: 1, lowestA: -2147483648
7, 3, 1, 0, 2, 5, 4, 6, 11, 14, 8, 10, 13, 12, 9. cur: 0, lowestA: -2147483648
7, 3, 2, 0, 2, 5, 4, 6, 11, 14, 8, 10, 13, 12, 9. cur: 2, lowestA: 1
7, 5, 2, 0, 2, 5, 4, 6, 11, 14, 8, 10, 13, 12, 9. cur: 5, lowestA: 3
7, 5, 4, 0, 2, 5, 4, 6, 11, 14, 8, 10, 13, 12, 9. cur: 4, lowestA: 3
7, 6, 4, 0, 2, 5, 4, 6, 11, 14, 8, 10, 13, 12, 9. cur: 6, lowestA: 5
11, 6, 4, 0, 2, 5, 4, 6, 11, 14, 8, 10, 13, 12, 9. cur: 11, lowestA: 7
14, 6, 4, 0, 2, 5, 4, 6, 11, 14, 8, 10, 13, 12, 9. cur: 14, lowestA: 11
VerifyPreOrderTraversalBST InPlace for "7, 3, 1, 0, 2, 5, 4, 6, 11, 14, 8, 10, 13, 12, 9": 0
*/
#endif
