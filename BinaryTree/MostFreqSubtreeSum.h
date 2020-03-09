#ifndef MOST_FREQ_SUBTREE_SUM_H
#define MOST_FREQ_SUBTREE_SUM_H
#include "Debug.h"
/*
Leetcode: Most Frequent Subtree Sum
Given the root of a tree, you are asked to find the most frequent subtree sum.
The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself).
So what is the most frequent subtree sum value?
If there is a tie, return all the values with the highest frequency in any order.
Examples 1
Input:

  5
 /  \
2   -3

return [2, -3, 4], since all the values happen only once, return all of them in any order.
Examples 2
Input:

  5
 /  \
2   -5

return [2], since 2 happens twice, however -5 only occur once.
Note: You may assume the sum of values in any subtree is in the range of 32-bit signed integer. 
*/
class MostFreqSubtreeSum
{
public:
	MostFreqSubtreeSum() {}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};
	std::vector<int> Recur(TreeNode* root)
	{
		if (root == NULL) return{};
		std::unordered_map<int, int> sumFreq;//<sum, count>
		recur(root, sumFreq);
		std::vector<int> res;
		int maxFreq = INT_MIN;
		for (auto & p : sumFreq)
			maxFreq = std::max(maxFreq, p.second);
		for (auto & p : sumFreq)
			if (p.second == maxFreq)
				res.push_back(p.first);
		return res;
	}
private:
	int recur(TreeNode * cur, std::unordered_map<int, int> & sumFreq)
	{
		if (cur == NULL) return 0;
		int sum = cur->val + recur(cur->left, sumFreq) + recur(cur->right, sumFreq);
		++sumFreq[sum];
		return sum;
	}
};
#endif
