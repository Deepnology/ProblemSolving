#ifndef FLATTEN_NESTED_LIST_ITERATOR_H
#define FLATTEN_NESTED_LIST_ITERATOR_H
#include <iostream>
#include <string>
#include <vector>
#include "Debug.h"
/*
Leetcode: Flatten Nested List Iterator
Given a nested list of integers, implement an iterator to flatten it.
Each element is either an integer, or a list -- whose elements may also be integers or other lists.
Example 1:
Given the list [[1,1],2,[1,1]],
By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,1,2,1,1].
Example 2:
Given the list [1,[4,[6]]],
By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,4,6].
Example 3:
[[[6,7],4,5],2,[3,[[6],8,[4,[5,[[7,3],0]]],4],1],9]
=> [6,7,4,5,2,3,6,8,4,5,7,3,0,4,1,9]

The input array represents an in-order traversal.
Every pair of [] represents a child level.
Flatten the nested list iterator actually performs an in-order traversal.
Use a stack to store pointers to NestedInteger(can be either an integer or a list of NestedIntegers) from right to left in the given array.
hasNext(): if the top of the stack is an integer, return true, otherwise, pop the stack and push all elements in the popped list to stack, until the top element is an integer.
next(): pop out and return the top integer(must be an integer instead of a list) in the stack.

see also TreeFromParentChildPairs.h, BinaryTreePreOrderTraversal.h
*/
class FlattenNestedListIterator
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

	std::stack<const NestedInteger*> stk;
public:
	explicit FlattenNestedListIterator(std::vector<NestedInteger> & nestedList)
	{
		int N = nestedList.size();
		for (int i = N - 1; i >= 0; --i)
		{
			stk.emplace(&nestedList[i]);
		}
	}
	~FlattenNestedListIterator() {}

	int next()
	{
		int res = stk.top()->getInteger();
		stk.pop();
		return res;
	}

	bool hasNext()
	{
		while (!stk.empty())
		{
			const NestedInteger * cur = stk.top();
			if (cur->isInteger())
				return true;
			//now cur is a list: push all elements in the list to stk
			stk.pop();
			int N = cur->getList().size();
			for (int i = N - 1; i >= 0; --i)
			{
				stk.emplace(&cur->getList()[i]);
			}
		}
		//now stk is empty
		return false;
	}
};
#endif
