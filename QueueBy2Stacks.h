#ifndef QUEUE_BY_2_STACKS_H
#define QUEUE_BY_2_STACKS_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, StacksAndQueues: Implement a queue using stacks
Cracking the coding interview 3.5
http://www.geeksforgeeks.org/queue-using-stacks/
See also StackBy2Queues.h
*/
template<class T>
class QueueBy2Stacks_A
{
	std::stack<T> reversed;
	std::stack<T> nonReversed;
public:
	QueueBy2Stacks_A() :reversed(), nonReversed()
	{}
	~QueueBy2Stacks_A(){}
	int Size() const
	{
		return reversed.size() + nonReversed.size();
	}
	void Push(const T & val)//efficient push
	{
		reversed.push(val);
	}
	T Pop()
	{
		if (this->Size() == 0)
			throw std::runtime_error("");

		if (nonReversed.empty())
		{
			while (!reversed.empty())
			{
				nonReversed.push(reversed.top());
				reversed.pop();
			}
		}
		
		T res = nonReversed.top();
		nonReversed.pop();
		return res;
	}
};

template<class T>
class QueueBy2Stacks_B
{
	std::stack<T> nonReversed;
	std::stack<T> tmp;
public:
	QueueBy2Stacks_B() : nonReversed(), tmp()
	{}
	~QueueBy2Stacks_B(){}
	int Size() const
	{
		return nonReversed.size();
	}
	void Push(const T & val)
	{
		//1. move all vals to tmp
		while (!nonReversed.empty())
		{
			tmp.push(nonReversed.top());
			nonReversed.pop();
		}

		//2. push the new val
		nonReversed.push(val);

		//3. move all vals back
		while (!tmp.empty())
		{
			nonReversed.push(tmp.top());
			tmp.pop();
		}
	}
	T Pop()//efficient pop and front
	{
		if (this->Size() == 0)
			throw std::runtime_error("");

		T res = nonReversed.top();
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
QueueBy2Stacks_A: 6,5,4
QueueBy2Stacks_B: 6,5,4
*/
#endif