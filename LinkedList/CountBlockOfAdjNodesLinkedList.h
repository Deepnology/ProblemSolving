#ifndef COUNT_BLOCK_OF_ADJ_NODES_LINKED_LIST_H
#define COUNT_BLOCK_OF_ADJ_NODES_LINKED_LIST_H
#include <list>
#include <unordered_set>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include "Debug.h"
/*
Google
http://www.careercup.com/question?id=18880663
Given a doubly linked list and an array of references to nodes on the linked list.
Count the block of adjacent nodes from the array of references to nodes.
A "block" is defined as a group of nodes on the list that are adjacent to each other.

*/
class CountBlockOfAdjNodesLinkedList
{
public:
	CountBlockOfAdjNodesLinkedList(){}
	~CountBlockOfAdjNodesLinkedList(){}

	struct ListConstItorHash
	{
		size_t operator()(const std::list<int>::const_iterator & itor) const
		{
			return std::hash<const int*>()(&*itor);
		}
	};

	int Solve(const std::list<int> & L, const std::vector<std::list<int>::const_iterator> & V)
	{
		int N = V.size();
		int blockCount = 0;
		std::unordered_set<std::list<int>::const_iterator, ListConstItorHash> set;
		for (int i = 0; i < N; ++i)
		{
			std::list<int>::const_iterator cur = V[i];

			//skip cur if already present
			if (set.count(cur) != 0)
				continue;

			//1. increment block count
			++blockCount;

			//2. decrement block count if cur's prev node is already present
			if (cur != L.begin())
			{
				--cur;
				if (set.count(cur) != 0)
					--blockCount;
				++cur;
			}

			//3. decrement block count if cur's next node is already present
			std::list<int>::const_iterator last = L.end();
			--last;
			if (cur != last)
			{
				++cur;
				if (set.count(cur) != 0)
					--blockCount;
				--cur;
			}
			
			//4. insert cur
			set.insert(cur);
		}

		std::cout << "List: " << Debug::ToStr1D<int>()(L) << std::endl;
		std::cout << "ListConstItorVec: " << this->VecOfListConstItor_to_Str(V) << std::endl;
		std::cout << "CountBlockOfAdjNodesLinkedList for the above: " << blockCount << std::endl;
		return blockCount;
	}

	std::string VecOfListConstItor_to_Str(const std::vector<std::list<int>::const_iterator> & V)
	{
		std::ostringstream oss;
		int N = V.size();
		for (int i = 0; i < N; ++i)
		{
			oss << *V[i];
			if (i != N - 1)
				oss << ", ";
		}
		return oss.str();
	}
};
/*
List: 1, 2, 3, 4, 5, 6, 7, 8, 9
ListConstItorVec: 8, 9, 7, 3, 5, 2, 1
CountBlockOfAdjNodesLinkedList for the above: 3
List: 1, 2, 3, 4, 5, 6, 7, 8, 9
ListConstItorVec: 8, 9, 7, 3, 5, 2, 7, 4, 2, 1, 6
CountBlockOfAdjNodesLinkedList for the above: 1
*/
#endif