#ifndef VERIFY_POST_ORDER_TRAVERSAL_BST_H
#define VERIFY_POST_ORDER_TRAVERSAL_BST_H
#include "Debug.h"
/*
https://discuss.leetcode.com/topic/21217/java-o-n-and-o-1-extra-space/39
see also ConstructBSTFromTraversal.h
*/
class VerifyPostOrderTraversalBST
{
public:
	VerifyPostOrderTraversalBST() {}
	~VerifyPostOrderTraversalBST() {}
	
	bool LinearRecur(const std::vector<int> & postorder)
	{
		int N = postorder.size();
		//postorder can be obtained by mirror-preorder traversal (go right first) then reverse the result
		int cur = N - 1;//start from right, perform mirror-preorder (go right first)
		recur(postorder, INT_MIN, INT_MAX, cur);

		std::cout << "VerifyPostOrderTraversalBST Linear for \"" << Debug::ToStr1D<int>()(postorder) << "\": " << (cur == -1) << " (cur=" << cur << ")" << std::endl;
		return cur == -1;
	}
private:
	void recur(const std::vector<int> & postorder, int min, int max, int & cur)
	{
		if (cur == -1)
			return;
		int curVal = postorder[cur];
		if (curVal < min || curVal > max)
			return;
		--cur;
		recur(postorder, curVal, max, cur);//go right first
		recur(postorder, min, curVal, cur);
	}

public:
	//postorder can be obtained by mirror-preorder traversal (go right first) then reverse the result
	//so 1. reverse postorder array 2. use sortedStack sorted in increasing order
	bool UsingSortedStack(const std::vector<int> & postorder)
	{
		int N = postorder.size();
		if (N <= 1) return true;

		std::vector<int> rev(postorder);
		std::reverse(rev.begin(), rev.end());
		std::vector<int> stk;
		int lowestA = INT_MAX;
		bool res = true;
		for (int i = 0; i < N; ++i)
		{
			if (rev[i] > lowestA)
			{
				res = false;
				break;
			}

			while (!stk.empty() && rev[i] < stk.back())
			{
				lowestA = stk.back();
				stk.pop_back();
			}
			stk.push_back(rev[i]);
		}

		std::cout << "VerifyPostOrderTraversalBST UseSortedStack for \"" << Debug::ToStr1D<int>()(postorder) << "\": " << res << std::endl;
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

VerifyPostOrderTraversalBST Linear for "0, 2, 1, 4, 6, 5, 3, 8, 10, 9, 12, 14, 13, 11, 7": 1 (cur=-1)
VerifyPostOrderTraversalBST UseSortedStack for "0, 2, 1, 4, 6, 5, 3, 8, 10, 9, 12, 14, 13, 11, 7": 1
VerifyPostOrderTraversalBST Linear for "0, 2, 1, 4, 6, 8, 3, 5, 10, 9, 12, 14, 13, 11, 7": 0 (cur=5)
VerifyPostOrderTraversalBST UseSortedStack for "0, 2, 1, 4, 6, 8, 3, 5, 10, 9, 12, 14, 13, 11, 7": 0
VerifyPostOrderTraversalBST Linear for "0, 11, 1, 4, 6, 5, 3, 8, 10, 9, 12, 14, 13, 2, 7": 0 (cur=12)
VerifyPostOrderTraversalBST UseSortedStack for "0, 11, 1, 4, 6, 5, 3, 8, 10, 9, 12, 14, 13, 2, 7": 0
VerifyPostOrderTraversalBST Linear for "0, 2, 1, 4, 6, 5, 3, 8, 10, 14, 12, 9, 13, 11, 7": 0 (cur=10)
VerifyPostOrderTraversalBST UseSortedStack for "0, 2, 1, 4, 6, 5, 3, 8, 10, 14, 12, 9, 13, 11, 7": 0
*/
#endif
