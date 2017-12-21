#ifndef STACK_BY_2_QUEUES_H
#define STACK_BY_2_QUEUES_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>
#include <math.h>
#include "Debug.h"
/*
Leetcode: Implement Stack using Queues
Implement the following operations of a stack using queues.
push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
empty() -- Return whether the stack is empty.
http://stackoverflow.com/questions/688276/implement-stack-using-two-queues
http://www.geeksforgeeks.org/implement-stack-using-queue/
See also QueueBy2Stacks.h
*/
template<class T>
class StackBy2Queues_A
{
	std::queue<T> reversed;
	std::queue<T> tmp;
public:
	StackBy2Queues_A(): reversed(), tmp()
	{}
	~StackBy2Queues_A(){}
	int Size() const
	{
		return reversed.size();
	}
	void Push(const T & val)//efficient push
	{
		reversed.push(val);
	}
	T Pop()
	{
		if (this->Size() == 0)
			throw std::exception("");

		//1. find the last one in reversed
		while (reversed.size() > 1)
		{
			tmp.push(reversed.front());
			reversed.pop();
		}
		T res = reversed.front();
		reversed.pop();

		//2. now reversed is empty, and all vals are in tmp => swap
		while (!tmp.empty())
		{
			reversed.push(tmp.front());
			tmp.pop();
		}

		return res;
	}
};

template<class T>
class StackBy2Queues_B
{
	std::queue<T> tmp;
	std::queue<T> nonReversed;
public:
	StackBy2Queues_B() : tmp(), nonReversed()
	{}
	~StackBy2Queues_B(){}
	int Size() const
	{
		return nonReversed.size();
	}
	void Push(const T & val)
	{
		//1. push the new in tmp, and move all vals from nonReversed to tmp
		tmp.push(val);
		while (!nonReversed.empty())
		{
			tmp.push(nonReversed.front());
			nonReversed.pop();
		}

		//2. now nonReversed is empty, and all vals are in tmp => swap
		while (!tmp.empty())
		{
			nonReversed.push(tmp.front());
			tmp.pop();
		}
	}
	T Pop()//efficient pop and top
	{
		if (this->Size() == 0)
			throw std::exception("");

		T res = nonReversed.front();
		nonReversed.pop();
		return res;
	}
};
/*
QueueBy2StacksB
              pop push
               v   v
stk: bottom<->top
nR:  6 5 4 3 2 1
tmp:
Push(7): move, add, move
nR:
tmp: 1 2 3 4 5 6

nR:  7
tmp: 1 2 3 4 5 6

nR:  7 6 5 4 3 2 1
tmp:

StackBy2QueuesB
    pop           push
     v             v
que: front<->back
nR:  6 5 4 3 2 1
tmp:
Push(7): add, move, move
nR:  6 5 4 3 2 1
tmp: 7

nR:
tmp: 7 6 5 4 3 2 1

nR:  7 6 5 4 3 2 1
tmp:
*/
/*
StackBy2Queues_A: 4,1,0
StackBy2Queues_B: 9,6,5
*/
#endif