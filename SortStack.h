#ifndef SORT_STACK_H
#define SORT_STACK_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, StacksAndQueues: Sort a stack
Cracking the coding interview 3.6
Write a program to sort a stack in ascending order from bottom to top.
THe following are the only functions that should be used to write in this program:
push, pop, peek, isEmpty.
O(n^2)
*/
class SortStack
{
public:
	SortStack(){}
	~SortStack(){}

	std::stack<int> Iterate(std::stack<int> s)
	{
		std::string before = Debug::ToStr1D<int>()(s);
		std::stack<int> res;
		while (!s.empty())
		{
			int tmp = s.top();
			s.pop();
			while (!res.empty() && res.top() > tmp)
			{
				s.push(res.top());
				res.pop();
			}
			res.push(tmp);
		}
		std::cout << "SortStack Iterate for \"" << before << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	void InPlace_Recur(std::stack<int> & s)
	{
		std::string before = Debug::ToStr1D<int>()(s);
		this->sortRecur(s);
		std::cout << "SortStack InPlace_Recur for \"" << before << "\": " << Debug::ToStr1D<int>()(s) << std::endl;
	}
private:
	void sortRecur(std::stack<int> & s)
	{
		if (s.empty())
			return;
		int tmp = s.top();
		s.pop();
		this->sortRecur(s);
		//in the deepest recursion here, all entries in s were popped out and saved in the recursion stack
		//s is empty now, then insert all entries back to s from recursion stack
		this->insertRecur(s, tmp);
	}
	void insertRecur(std::stack<int> & s, int val)
	{
		if (s.empty() || s.top() <= val)
		{
			s.push(val);
			return;
		}
		int tmp = s.top();
		s.pop();
		this->insertRecur(s, val);
		s.push(tmp);
	}
};
/*
SortStack Iterate for "7, 1, 4, 5, 6, 8, 2, 3": 8, 7, 6, 5, 4, 3, 2, 1
SortStack InPlace_Recur for "7, 1, 4, 5, 6, 8, 2, 3": 8, 7, 6, 5, 4, 3, 2, 1
*/
#endif