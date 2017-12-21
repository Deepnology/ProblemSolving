#ifndef SET_OF_STACKS_H
#define SET_OF_STACKS_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>
#include "Debug.h"
/*
Cracking the coding interview 3.3
Implement a stack class that is composed of a list of small stacks with fixed capacity.
*/
class SetOfStacks
{
	std::vector<std::stack<int> *> m_stacks;
	int m_capacity;
public:
	SetOfStacks(int capacity) : m_stacks(), m_capacity(capacity)
	{}
	~SetOfStacks()
	{
		for (auto p : m_stacks)
		{
			delete p;
		}
	}
	
	std::stack<int> * GetLastStack() const
	{
		if (m_stacks.size() == 0)
			return NULL;
		return m_stacks.back();
	}
	void Push(int v)
	{
		std::stack<int> * last = this->GetLastStack();
		if (last != NULL && (int)last->size() < m_capacity)
			last->push(v);
		else
		{
			std::stack<int> * stk = new std::stack<int>();
			stk->push(v);
			m_stacks.push_back(stk);
		}
	}
	int Top() const
	{
		std::stack<int> * last = this->GetLastStack();
		if (last == NULL || last->size() == 0)
			throw std::exception("SetOfStacks Null Stack");
		return last->top();
	}
	void Pop()
	{
		std::stack<int> * last = this->GetLastStack();
		if (last == NULL)
			return;
		else
		{
			last->pop();
			if (last->size() == 0)
			{
				m_stacks.pop_back();
				delete last;
				last = 0;
			}
		}
	}
	int TopAt(int index)
	{
		int count = m_stacks.size();
		if (index >= 0 && index < count)
		{
			return m_stacks[index]->top();
		}
		throw std::exception("SetOfStacks NULL Stack");
	}

	int Size() const
	{
		int count = 0;
		for (auto p : m_stacks)
			count += p->size();
		return count;
	}
	bool Empty() const
	{
		return this->Size() == 0;
	}

	void Print()
	{
		std::ostringstream oss;
		for (std::vector<std::stack<int> *>::const_reverse_iterator ritr = m_stacks.rbegin(); ritr != m_stacks.rend(); ++ritr)
		{
			oss << "[" << Debug::ToStr1D<int>()(*(*ritr)) << "]";
			if (ritr != m_stacks.rend() - 1)
				oss << ",";
		}
		std::cout << "SetOfStacks: " << oss.str() << " (" << this->Size() << ")" << std::endl;
	}
};
/*
SetOfStacks: [8, 7, 6],[5, 4, 3],[2, 1, 0] (9)
SetOfStacks: [7, 6],[5, 4, 3],[2, 1, 0] (8)
SetOfStacks: [6],[5, 4, 3],[2, 1, 0] (7)
SetOfStacks: [5, 4, 3],[2, 1, 0] (6)
SetOfStacks: [4, 3],[2, 1, 0] (5)
*/
#endif