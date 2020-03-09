#ifndef STACK_WITH_MIN_H
#define STACK_WITH_MIN_H
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
Elements of programming interview, StacksAndQueues: Implement a stack with max API
Cracking the coding interview 3.2
*/

/*keep track of all sorted values*/
class StackWithMin1
{
	std::stack<int> m_stk;
	std::stack<int> m_sortedStk;
public:
	StackWithMin1() : m_stk(), m_sortedStk()
	{}
	~StackWithMin1(){}

	void Push(int v)
	{
		if (v <= this->Min())
			m_sortedStk.push(v);
		m_stk.push(v);
	}
	void Pop()
	{
		int v = m_stk.top();
		if (v == this->Min())
			m_sortedStk.pop();
		m_stk.pop();
	}
	int Top() const
	{
		return m_stk.top();
	}
	int Min() const
	{
		if (m_sortedStk.empty())
			return INT_MAX;
		else
			return m_sortedStk.top();
	}
	int Size() const
	{
		return m_stk.size();
	}
	bool Empty() const
	{
		return m_stk.empty();
	}

	void Print()
	{
		std::cout << "StackWithMin1: \"" << Debug::ToStr1D<int>()(m_stk) << "\", Min: \"" << this->Min() << "\"" << std::endl;
	}
};

/*keep track of the count of different sorted values (this is the most efficient way)*/
class StackWithMin2
{
	std::stack<int> m_stk;
	std::stack<std::pair<int, int> > m_sortedStk;//first: min value (in descending order from bottom), second: count
public:
	StackWithMin2() : m_stk(), m_sortedStk()
	{}
	~StackWithMin2(){}

	void Push(int v)
	{
		if (this->Empty())
			m_sortedStk.push(std::make_pair(v, 1));
		else
		{
			if (v == m_sortedStk.top().first)
				++m_sortedStk.top().second;
			else if (v < m_sortedStk.top().first)
				m_sortedStk.push(std::make_pair(v, 1));
		}
		m_stk.push(v);
	}
	void Pop()
	{
		int v = m_stk.top();
		if (v == m_sortedStk.top().first)
		{
			--m_sortedStk.top().second;
			if (m_sortedStk.top().second == 0)
				m_sortedStk.pop();
		}
		m_stk.pop();
	}
	int Top() const
	{
		return m_stk.top();
	}
	int Min() const
	{
		return m_sortedStk.top().first;
	}
	int Size() const
	{
		return m_stk.size();
	}
	bool Empty() const
	{
		return m_stk.empty();
	}

	void Print()
	{
		std::cout << "StackWithMin2: \"" << Debug::ToStr1D<int>()(m_stk) << "\", Min: \"" << this->Min() << "\"" << std::endl;
	}
};

/*keep track of current min value for each value*/
class StackWithMin3
{
	std::stack<std::pair<int, int> > m_stk;//first: value, second: min value
public:
	StackWithMin3() : m_stk()
	{}
	~StackWithMin3(){}

	void Push(int v)
	{
		m_stk.push(std::make_pair(v, (m_stk.empty() ? v : std::min(v, m_stk.top().second))));
	}
	void Pop()
	{
		m_stk.pop();
	}
	int Top() const
	{
		return m_stk.top().first;
	}
	int Min() const
	{
		return m_stk.top().second;
	}
	int Size() const
	{
		return m_stk.size();
	}
	bool Empty() const
	{
		return m_stk.empty();
	}

	void Print()
	{
		std::cout << "StackWithMin3: \"" << Debug::ToStr1D<int>()(m_stk) << "\", Min: \"" << this->Min() << "\"" << std::endl;
	}
};
/*
StackWithMin1: "1, 2, 3, 4, 5, 6, 7, 8, 9, 10", Min: "1"
StackWithMin1: "2, 3, 4, 5, 6, 7, 8, 9, 10", Min: "2"
StackWithMin1: "3, 4, 5, 6, 7, 8, 9, 10", Min: "3"
StackWithMin1: "4, 5, 6, 7, 8, 9, 10", Min: "4"
StackWithMin2: "1, 2, 3, 4, 5, 6, 7, 8, 9, 10", Min: "1"
StackWithMin2: "2, 3, 4, 5, 6, 7, 8, 9, 10", Min: "2"
StackWithMin2: "3, 4, 5, 6, 7, 8, 9, 10", Min: "3"
StackWithMin2: "4, 5, 6, 7, 8, 9, 10", Min: "4"
StackWithMin3: "[1,1], [2,2], [3,3], [4,4], [5,5], [6,6], [7,7], [8,8], [9,9], [10,10]", Min: "1"
StackWithMin3: "[2,2], [3,3], [4,4], [5,5], [6,6], [7,7], [8,8], [9,9], [10,10]", Min: "2"
StackWithMin3: "[3,3], [4,4], [5,5], [6,6], [7,7], [8,8], [9,9], [10,10]", Min: "3"
StackWithMin3: "[4,4], [5,5], [6,6], [7,7], [8,8], [9,9], [10,10]", Min: "4"
*/

#endif