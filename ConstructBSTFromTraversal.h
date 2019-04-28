#ifndef CONSTRUCT_BST_FROM_TRAVERSAL_H
#define CONSTRUCT_BST_FROM_TRAVERSAL_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
/*
Leetcode: Construct Binary Search Tree from Preorder Traversal
http://www.geeksforgeeks.org/construct-bst-from-given-preorder-traversal-set-2/
Elements of programming interview, BST: Reconstruct a BST from traversal data
Inorder traversal sequence is insufficient to reconstruct the BST.
For example, the sequence {1,2,3} corresponds to 5 distinct BSTs:

1          1                             3                 3
 \          \                           /                 /
  2          3           2             1                 2
   \        /           / \             \               /
    3      2           1   3             2             1
				(height balanced)
				(see also
				ConvertSortedArrayToBinarySearchTree.h)

But there exists a unique BST for a sequence of preorder and postorder traversal.
It is critical that the elements stored in the tree be unique.
If there are duplicates existing in the preorder or postorder sequence, we cannot identify whether some subsequent elements are in the left subtree or in the right subtree.

PreorderBruteForceRecur: O(n^2) time in worst case of completely left-skewed tree, O(n) time in best case of completely right-skewed tree, O(nlogn) time in the case of balanced BST
PreorderLinearRecur: O(n) time in worst case
Same for postorder

See also ConstructBinaryTreeFrom2Traversals.h
see also VerifyPreOrderTraversalBST.h, VerifyPostOrderTraversalBST.h
see also CartesianTree.h
*/
class ConstructBSTFromTraversal
{
public:
	ConstructBSTFromTraversal(){}
	~ConstructBSTFromTraversal(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};
public:
	TreeNode * Preorder_BruteForce_Recur(const std::vector<int> & preorder)
	{
		return this->preorderBruteForceRecur(preorder, 0, preorder.size() - 1);
	}
private:
	TreeNode * preorderBruteForceRecur(const std::vector<int> & preorder, int start, int end)
	{
		if (start > end)
			return nullptr;
		int middle = start + 1;
		while (middle <= end && preorder[middle] < preorder[start])
			++middle;
		//middle now points to current new node's right child node
		TreeNode * root = new TreeNode(preorder[start]);
		root->left = this->preorderBruteForceRecur(preorder, start + 1, middle - 1);
		root->right = this->preorderBruteForceRecur(preorder, middle, end);
		return root;
	}
public:
	TreeNode * Preorder_Linear_Recur(const std::vector<int> & preorder)
	{
		int cur = 0;
		return this->preorderLinearRecur(preorder, INT_MIN, INT_MAX, cur);
	}
private:
	TreeNode * preorderLinearRecur(const std::vector<int> & preorder, int min, int max, int & cur)
	{
		if (cur == (int)preorder.size())
			return nullptr;

		int curVal = preorder[cur];
		if (curVal < min || curVal > max)
			return nullptr;
		
		TreeNode * root = new TreeNode(curVal);
		++cur;
		root->left = this->preorderLinearRecur(preorder, min, curVal, cur);//traverse left child subtree first!
		root->right = this->preorderLinearRecur(preorder, curVal, max, cur);
		return root;
	}
public:
	TreeNode * IteratePreorderSortedStack(const std::vector<int> & preorder)
	{
		int N = preorder.size();
		std::vector<TreeNode *> sortedStk;//in descending order (keep a path of greater nodes in left subtree from top to cur excluding lesser ancestor nodes)
		TreeNode * root = new TreeNode(preorder[0]);
		sortedStk.push_back(root);

		for (int i = 1; i < N; ++i)
		{
			TreeNode * cur = new TreeNode(preorder[i]);
			TreeNode * lowestA = NULL;//lowest ancestor for cur node as a right child

			//pop out cur node's left siblings and parent (which are all less than cur)
			//the last one popped will be the "lowest ancestor for cur node as a right child" (cur > lowestA)
			while (!sortedStk.empty() && cur->val > sortedStk.back()->val)
			{
				lowestA = sortedStk.back();//lowestA is the leftmost one
				sortedStk.pop_back();
			}

			if (lowestA)
				lowestA->right = cur;
			else
				sortedStk.back()->left = cur;

			sortedStk.push_back(cur);

			//std::ostringstream oss;
			//oss << "Inserting " << preorder[i] << ": ";
			//for (const auto & t : sortedStk)
			//	oss << t->val << ",";
			//oss << std::endl;
			//PrintBinaryTree<TreeNode, std::ostringstream>(root, oss);
			//std::cout << oss.str() << std::endl;
		}
		return root;
	}

public:
	TreeNode * Postorder_BruteForce_Recur(const std::vector<int> & postorder)
	{
		return this->postorderBruteForceRecur(postorder, 0, postorder.size() - 1);
	}
private:
	TreeNode * postorderBruteForceRecur(const std::vector<int> & postorder, int start, int end)
	{
		if (start > end)
			return nullptr;
		int middle = end - 1;
		while (middle >= start && postorder[middle] > postorder[end])
			--middle;
		//middle now points to current new node's left child node
		TreeNode * root = new TreeNode(postorder[end]);
		root->left = this->postorderBruteForceRecur(postorder, start, middle);
		root->right = this->postorderBruteForceRecur(postorder, middle + 1, end - 1);
		return root;
	}
public:
	TreeNode * Postorder_Linear_Recur(const std::vector<int> & postorder)
	{
		int cur = postorder.size() - 1;
		return this->postorderLinearRecur(postorder, INT_MIN, INT_MAX, cur);
	}
private:
	TreeNode * postorderLinearRecur(const std::vector<int> & postorder, int min, int max, int & cur)
	{
		if (cur == -1)
			return nullptr;

		int curVal = postorder[cur];
		if (curVal < min || curVal > max)
			return nullptr;

		TreeNode * root = new TreeNode(curVal);
		--cur;
		root->right = this->postorderLinearRecur(postorder, curVal, max, cur);//traverse right child subtree first!
		root->left = this->postorderLinearRecur(postorder, min, curVal, cur);
		return root;
	}
public:
	TreeNode * IteratePostorderSortedStack(const std::vector<int> & postorder)//reverse preorder, then perform mirror-preorder
	{
		int N = postorder.size();
		std::vector<int> rev(postorder);
		std::reverse(rev.begin(), rev.end());
		std::vector<TreeNode *> sortedStk;//in increasing order (keep a path of lesser nodes in right subtree from top to cur excluding greater ancestor nodes)
		TreeNode * root = new TreeNode(rev[0]);
		sortedStk.push_back(root);

		for (int i = 1; i < N; ++i)
		{
			TreeNode * cur = new TreeNode(rev[i]);
			TreeNode * lowestA = NULL;//lowest ancestor for cur node as a left child

			//pop out cur node's right siblings and parent (which are all greater than cur)
			//the last one popped will be the "lowest ancestor for cur node as a left child" (cur < lowestA)
			while (!sortedStk.empty() && cur->val < sortedStk.back()->val)
			{
				lowestA = sortedStk.back();//lowestA is the leftmost one
				sortedStk.pop_back();
			}

			if (lowestA)
				lowestA->left = cur;
			else
				sortedStk.back()->right = cur;

			sortedStk.push_back(cur);

			//std::ostringstream oss;
			//oss << "Inserting " << rev[i] << ": ";
			//for (const auto & t : sortedStk)
			//	oss << t->val << ",";
			//oss << std::endl;
			//PrintBinaryTree<TreeNode, std::ostringstream>(root, oss);
			//std::cout << oss.str() << std::endl;
		}
		return root;
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
ConstructBSTFromTraversal Preorder BruteForce Recur:
7, 1, 0, 3, 2, 5, 4, 6, 9, 8, 10
                              
                               1
                ______________ 7______________
               /                               \
               2                               2
        ______ 1______                  ______ 9______
       /               \               /               \
       3               3               3               3
    __ 0__          __ 3__          __ 8__          __10__
   /       \       /       \       /       \       /       \
   X       X       4       4       X       X       X       X
   N       N       2       5       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   5   5   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   4   6   N   N   N   N   N   N   N   N


ConstructBSTFromTraversal Preorder Linear Recur:
7, 1, 0, 3, 2, 5, 4, 6, 9, 8, 10
                              
                               1
                ______________ 7______________
               /                               \
               2                               2
        ______ 1______                  ______ 9______
       /               \               /               \
       3               3               3               3
    __ 0__          __ 3__          __ 8__          __10__
   /       \       /       \       /       \       /       \
   X       X       4       4       X       X       X       X
   N       N       2       5       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   5   5   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   4   6   N   N   N   N   N   N   N   N


Inserting 1: 7,1,
  
   1
   7
 /   \
 2   X
 1   N


Inserting 0: 7,1,0,
      
       1
    __ 7__
   /       \
   2       X
   1       N
 /   \   /   \
 3   X   X   X
 0   N   N   N


Inserting 3: 7,3,
      
       1
    __ 7__
   /       \
   2       X
   1       N
 /   \   /   \
 3   3   X   X
 0   3   N   N


Inserting 2: 7,3,2,
              
               1
        ______ 7______
       /               \
       2               X
    __ 1__          __ N__
   /       \       /       \
   3       3       X       X
   0       3       N       N
 /   \   /   \   /   \   /   \
 X   X   4   X   X   X   X   X
 N   N   2   N   N   N   N   N


Inserting 5: 7,5,
              
               1
        ______ 7______
       /               \
       2               X
    __ 1__          __ N__
   /       \       /       \
   3       3       X       X
   0       3       N       N
 /   \   /   \   /   \   /   \
 X   X   4   4   X   X   X   X
 N   N   2   5   N   N   N   N


Inserting 4: 7,5,4,
                              
                               1
                ______________ 7______________
               /                               \
               2                               X
        ______ 1______                  ______ N______
       /               \               /               \
       3               3               X               X
    __ 0__          __ 3__          __ N__          __ N__
   /       \       /       \       /       \       /       \
   X       X       4       4       X       X       X       X
   N       N       2       5       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   5   X   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   4   N   N   N   N   N   N   N   N   N


Inserting 6: 7,6,
                              
                               1
                ______________ 7______________
               /                               \
               2                               X
        ______ 1______                  ______ N______
       /               \               /               \
       3               3               X               X
    __ 0__          __ 3__          __ N__          __ N__
   /       \       /       \       /       \       /       \
   X       X       4       4       X       X       X       X
   N       N       2       5       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   5   5   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   4   6   N   N   N   N   N   N   N   N


Inserting 9: 9,
                              
                               1
                ______________ 7______________
               /                               \
               2                               2
        ______ 1______                  ______ 9______
       /               \               /               \
       3               3               X               X
    __ 0__          __ 3__          __ N__          __ N__
   /       \       /       \       /       \       /       \
   X       X       4       4       X       X       X       X
   N       N       2       5       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   5   5   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   4   6   N   N   N   N   N   N   N   N


Inserting 8: 9,8,
                              
                               1
                ______________ 7______________
               /                               \
               2                               2
        ______ 1______                  ______ 9______
       /               \               /               \
       3               3               3               X
    __ 0__          __ 3__          __ 8__          __ N__
   /       \       /       \       /       \       /       \
   X       X       4       4       X       X       X       X
   N       N       2       5       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   5   5   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   4   6   N   N   N   N   N   N   N   N


Inserting 10: 10,
                              
                               1
                ______________ 7______________
               /                               \
               2                               2
        ______ 1______                  ______ 9______
       /               \               /               \
       3               3               3               3
    __ 0__          __ 3__          __ 8__          __10__
   /       \       /       \       /       \       /       \
   X       X       4       4       X       X       X       X
   N       N       2       5       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   5   5   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   4   6   N   N   N   N   N   N   N   N


ConstructBSTFromTraversal IteratePreorderSortedStack:
7, 1, 0, 3, 2, 5, 4, 6, 9, 8, 10
                              
                               1
                ______________ 7______________
               /                               \
               2                               2
        ______ 1______                  ______ 9______
       /               \               /               \
       3               3               3               3
    __ 0__          __ 3__          __ 8__          __10__
   /       \       /       \       /       \       /       \
   X       X       4       4       X       X       X       X
   N       N       2       5       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   5   5   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   4   6   N   N   N   N   N   N   N   N


ConstructBSTFromTraversal Postorder BruteForce Recur:
0, 2, 4, 6, 5, 3, 1, 8, 10, 9, 7
                              
                               1
                ______________ 7______________
               /                               \
               2                               2
        ______ 1______                  ______ 9______
       /               \               /               \
       3               3               3               3
    __ 0__          __ 3__          __ 8__          __10__
   /       \       /       \       /       \       /       \
   X       X       4       4       X       X       X       X
   N       N       2       5       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   5   5   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   4   6   N   N   N   N   N   N   N   N


ConstructBSTFromTraversal Postorder Linear Recur:
0, 2, 4, 6, 5, 3, 1, 8, 10, 9, 7
                              
                               1
                ______________ 7______________
               /                               \
               2                               2
        ______ 1______                  ______ 9______
       /               \               /               \
       3               3               3               3
    __ 0__          __ 3__          __ 8__          __10__
   /       \       /       \       /       \       /       \
   X       X       4       4       X       X       X       X
   N       N       2       5       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   5   5   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   4   6   N   N   N   N   N   N   N   N


Inserting 9: 7,9,
  
   1
   7
 /   \
 X   2
 N   9


Inserting 10: 7,9,10,
      
       1
    __ 7__
   /       \
   X       2
   N       9
 /   \   /   \
 X   X   X   3
 N   N   N  10


Inserting 8: 7,8,
      
       1
    __ 7__
   /       \
   X       2
   N       9
 /   \   /   \
 X   X   3   3
 N   N   8  10


Inserting 1: 1,
      
       1
    __ 7__
   /       \
   2       2
   1       9
 /   \   /   \
 X   X   3   3
 N   N   8  10


Inserting 3: 1,3,
      
       1
    __ 7__
   /       \
   2       2
   1       9
 /   \   /   \
 X   3   3   3
 N   3   8  10


Inserting 5: 1,3,5,
              
               1
        ______ 7______
       /               \
       2               2
    __ 1__          __ 9__
   /       \       /       \
   X       3       3       3
   N       3       8      10
 /   \   /   \   /   \   /   \
 X   X   X   4   X   X   X   X
 N   N   N   5   N   N   N   N


Inserting 6: 1,3,5,6,
                              
                               1
                ______________ 7______________
               /                               \
               2                               2
        ______ 1______                  ______ 9______
       /               \               /               \
       X               3               3               3
    __ N__          __ 3__          __ 8__          __10__
   /       \       /       \       /       \       /       \
   X       X       X       4       X       X       X       X
   N       N       N       5       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   5   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   N   6   N   N   N   N   N   N   N   N


Inserting 4: 1,3,4,
                              
                               1
                ______________ 7______________
               /                               \
               2                               2
        ______ 1______                  ______ 9______
       /               \               /               \
       X               3               3               3
    __ N__          __ 3__          __ 8__          __10__
   /       \       /       \       /       \       /       \
   X       X       X       4       X       X       X       X
   N       N       N       5       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   5   5   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   4   6   N   N   N   N   N   N   N   N


Inserting 2: 1,2,
                              
                               1
                ______________ 7______________
               /                               \
               2                               2
        ______ 1______                  ______ 9______
       /               \               /               \
       X               3               3               3
    __ N__          __ 3__          __ 8__          __10__
   /       \       /       \       /       \       /       \
   X       X       4       4       X       X       X       X
   N       N       2       5       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   5   5   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   4   6   N   N   N   N   N   N   N   N


Inserting 0: 0,
                              
                               1
                ______________ 7______________
               /                               \
               2                               2
        ______ 1______                  ______ 9______
       /               \               /               \
       3               3               3               3
    __ 0__          __ 3__          __ 8__          __10__
   /       \       /       \       /       \       /       \
   X       X       4       4       X       X       X       X
   N       N       2       5       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   5   5   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   4   6   N   N   N   N   N   N   N   N


ConstructBSTFromTraversal IteratePostorderSortedStack:
0, 2, 4, 6, 5, 3, 1, 8, 10, 9, 7
                              
                               1
                ______________ 7______________
               /                               \
               2                               2
        ______ 1______                  ______ 9______
       /               \               /               \
       3               3               3               3
    __ 0__          __ 3__          __ 8__          __10__
   /       \       /       \       /       \       /       \
   X       X       4       4       X       X       X       X
   N       N       2       5       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   5   5   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   4   6   N   N   N   N   N   N   N   N

*/
#endif