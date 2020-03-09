#ifndef NESTED_LIST_WEIGHT_SUM_H
#define NESTED_LIST_WEIGHT_SUM_H
#include "Debug.h"
/*
Leetcode: Nested List Weight Sum
Given a nested list of integers, return the sum of all integers in the list weighted by their depth.
Each element is either an integer, or a list -- whose elements may also be integers or other lists.
Example 1:
Given the list [[1,1],2,[1,1]], return 10. (four 1's at depth 2, one 2 at depth 1)
Example 2:
Given the list [1,[4,[6]]], return 27. (one 1 at depth 1, one 4 at depth 2, and one 6 at depth 3; 1 + 4*2 + 6*3 = 27)

Leetcode: Nested List Weight Sum II (Definition: deepest leaves have weights 1, other non-deepest leaves' have weights greater than 1)
Different from the previous question where weight is increasing from root to leaf, 
now the weight is defined from bottom up. i.e., the leaf level integers have weight 1, and the root level integers have the largest weight.
Example 1:
Given the list [[1,1],2,[1,1]], return 8. (four 1¡¦s at depth 1, one 2 at depth 2)
Example 2:
Given the list [1,[4,[6]]], return 17. (one 1 at depth 3, one 4 at depth 2, and one 6 at depth 1; 1*3 + 4*2 + 6*1 = 17)

The input array represents an in-order traversal.
Every pair of [] represents a child level.
See also FlattenNestedListIterator.h, TreeFromParentChildPairs.h
*/
class NestedListWeightSum
{
public:
	class NestedInteger
	{
		std::vector<NestedInteger> buf;
	public:
		NestedInteger() {}
		~NestedInteger() {}
		// Return true if this NestedInteger holds a single integer, rather than a nested list.
		bool isInteger() const
		{
			return false;
		}

		// Return the single integer that this NestedInteger holds, if it holds a single integer
		// The result is undefined if this NestedInteger holds a nested list
		int getInteger() const
		{
			return 0;
		}

		// Return the nested list that this NestedInteger holds, if it holds a nested list
		// The result is undefined if this NestedInteger holds a single integer
		const std::vector<NestedInteger> & getList() const
		{
			return buf;
		}
	};

	NestedListWeightSum() {}
	~NestedListWeightSum() {}

	//I. DFS
	int DepthSum_RootToLeaf(const std::vector<NestedInteger> & nestedList)
	{
		int res = this->recur(nestedList, 1);
		return res;
	}
private:
	int recur(const std::vector<NestedInteger> & list, int depth)//DFS
	{
		int sum = 0;
		int N = list.size();
		for (int i = 0; i < N; ++i)
			if (list[i].isInteger())
				sum += list[i].getInteger() * depth;
			else
				sum += this->recur(list[i].getList(), depth + 1);

		return sum;
	}
public:
	//I. BFS
	int BFS_DepthSum_RootToLeaf(const std::vector<NestedInteger> & nestedList)
	{
		int sum = 0;
		int level = 0;
		std::queue<NestedInteger> que;
		for (const auto & ni : nestedList)
			que.push(ni);
		while (!que.empty())
		{
			++level;
			int levelCount = que.size();
			int levelSum = 0;
			for (int i = 0; i < levelCount; ++i)
			{
				NestedInteger cur = que.front(); que.pop();
				if (cur.isInteger())
					levelSum += cur.getInteger();
				else
				{
					for (const auto & ni : cur.getList())
						que.push(ni);
				}
			}
			levelSum *= level;
			sum += levelSum;
		}

		return sum;
	}

	//II. DFS
public:
	int DepthSum_LeafToRoot(const std::vector<NestedInteger> & nestedList)
	{
		int maxDepth = this->MaxDepth(nestedList, 1);
		int res = this->recur2(nestedList, maxDepth);
		return res;
	}
private:
	int MaxDepth(const std::vector<NestedInteger> & list, int depth)
	{
		int N = list.size();
		int maxDepth = depth;
		for (int i = 0; i < N; ++i)
			if (!list[i].isInteger())
				maxDepth = std::max(maxDepth, this->MaxDepth(list[i].getList(), depth + 1));

		return maxDepth;
	}
	int recur2(const std::vector<NestedInteger> & list, int depth)//DFS
	{
		int sum = 0;
		int N = list.size();
		for (int i = 0; i < N; ++i)
			if (list[i].isInteger())
				sum += list[i].getInteger() * depth;
			else
				sum += this->recur2(list[i].getList(), depth - 1);

		return sum;
	}
public:
	//II. BFS
	int BFS_DepthSum_LeafToRoot(const std::vector<NestedInteger> & nestedList)
	{
		int prev = 0;
		int sum = 0;
		std::queue<NestedInteger> que;
		for (const auto & ni : nestedList)
			que.push(ni);
		while (!que.empty())
		{
			int levelCount = que.size();
			int levelSum = 0;
			for (int i = 0; i < levelCount; ++i)
			{
				NestedInteger cur = que.front(); que.pop();
				if (cur.isInteger())
					levelSum += cur.getInteger();
				else
				{
					for (const auto & ni : cur.getList())
						que.push(ni);
				}
			}
			prev += levelSum;
			sum += prev;
		}

		return sum;
	}
};
#endif
