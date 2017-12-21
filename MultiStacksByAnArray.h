#ifndef MULTI_STACKS_BY_AN_ARRAY_H
#define MULTI_STACKS_BY_AN_ARRAY_H
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
Cracking the coding interview 3.1
Implement K stacks with size S using an array.

Algorithm
1. Use both an integer (curMaxNext) and a minHeap to keep track of available positions in array to push new element.
=> curMaxNext points to the current rightmost position that has been used (and may also be released) of the array.
=> minHeap stores all available positions that were released on the left side of curMaxNext.
2. Use a vector (stkPtr) to store the positions of top elements of all stacks.
3. Use a vector (buffer) to store pairs of "element values" and "its prev element's position from its own stack".
*/
class MultiStacksByAnArray
{
	std::vector<std::pair<int, int> > m_buffer;//first: previous element's index in m_buffer of underlying stack, second: current value
	std::vector<int> m_stkPtr;//stores the index of the top element in m_buffer of a particular stk
	int m_curMaxNext;//points to the next free space in m_buffer
	std::priority_queue<int, std::vector<int>, std::greater<int> > m_minHeap;//stores the free spaces in m_buffer before m_curMaxNext
public:
	MultiStacksByAnArray(int stkCount, int stkSize) : m_stkPtr(stkCount, -1), m_buffer(stkCount * stkSize, std::make_pair(0, 0)), m_curMaxNext(0), m_minHeap()
	{}
	~MultiStacksByAnArray(){}
private:
	int GetNextFreeSpaceIdx()//return the leftmost available position
	{
		if (!m_minHeap.empty())
		{
			int r = m_minHeap.top();
			m_minHeap.pop();
			return r;
		}
		return m_curMaxNext++;
	}
	void SaveFreeSpaceIdx(int i)//release the target position
	{
		if (i == -1)
			return;
		if (i == m_curMaxNext - 1)
			--m_curMaxNext;
		else
			m_minHeap.push(i);
	}
public:
	void Push(int stkIdx, int val)
	{
		int preStkTopIdx = m_stkPtr[stkIdx];
		m_stkPtr[stkIdx] = this->GetNextFreeSpaceIdx();
		m_buffer[m_stkPtr[stkIdx]].first = preStkTopIdx;
		m_buffer[m_stkPtr[stkIdx]].second = val;
	}
	void Pop(int stkIdx)
	{
		int curStkTopIdx = m_stkPtr[stkIdx];
		this->SaveFreeSpaceIdx(curStkTopIdx);
		m_stkPtr[stkIdx] = m_buffer[m_stkPtr[stkIdx]].first;
	}
	int Top(int stkIdx) const
	{
		return m_buffer[m_stkPtr[stkIdx]].second;
	}
	bool Empty(int stkIdx) const
	{
		return m_stkPtr[stkIdx] == -1;
	}

	void Print()
	{
		std::string buffer = Debug::ToStr1D<int>()(m_buffer);
		std::string ptrs = Debug::ToStr1D<int>()(m_stkPtr);
		std::string curMinNext = m_minHeap.empty() ? "null" : std::to_string(m_minHeap.top());
		std::cout << "MultiStacksByAnArray Buffer: \"" << buffer << "\", StkPtrs: \"" << ptrs << "\", CurMaxNext: \"" << m_curMaxNext << "\", CurMinNext: \"" << curMinNext << "\"" << std::endl;
	}

};
/*
MultiStacksByAnArray Buffer: "[-1,1], [0,2], [1,3], [-1,11], [3,12], [4,13], [-1,101], [6,102], [7,103], [0,0], [0,0], [0,0], [0,0], [0,0], [0,0]", StkPtrs: "2, 5, 8", CurMaxNext: "9", CurMinNext: "null"
MultiStacksByAnArray Buffer: "[-1,1], [0,2], [1,3], [-1,11], [3,12], [4,13], [-1,101], [6,102], [7,103], [0,0], [0,0], [0,0], [0,0], [0,0], [0,0]", StkPtrs: "2, 5, 7", CurMaxNext: "8", CurMinNext: "null"
MultiStacksByAnArray Buffer: "[-1,1], [0,2], [1,3], [-1,11], [3,12], [4,13], [-1,101], [6,102], [7,103], [0,0], [0,0], [0,0], [0,0], [0,0], [0,0]", StkPtrs: "2, 4, 7", CurMaxNext: "8", CurMinNext: "5"
MultiStacksByAnArray Buffer: "[-1,1], [0,2], [1,3], [-1,11], [3,12], [4,13], [-1,101], [6,102], [7,103], [0,0], [0,0], [0,0], [0,0], [0,0], [0,0]", StkPtrs: "1, 4, 7", CurMaxNext: "8", CurMinNext: "2"
MultiStacksByAnArray Buffer: "[-1,1], [0,2], [7,104], [-1,11], [3,12], [4,13], [-1,101], [6,102], [7,103], [0,0], [0,0], [0,0], [0,0], [0,0], [0,0]", StkPtrs: "1, 4, 2", CurMaxNext: "8", CurMinNext: "5"
MultiStacksByAnArray Buffer: "[-1,1], [0,2], [7,104], [-1,11], [3,12], [4,14], [-1,101], [6,102], [7,103], [0,0], [0,0], [0,0], [0,0], [0,0], [0,0]", StkPtrs: "1, 5, 2", CurMaxNext: "8", CurMinNext: "null"
MultiStacksByAnArray Buffer: "[-1,1], [0,2], [7,104], [-1,11], [3,12], [4,14], [-1,101], [6,102], [1,4], [0,0], [0,0], [0,0], [0,0], [0,0], [0,0]", StkPtrs: "8, 5, 2", CurMaxNext: "9", CurMinNext: "null"
*/
#endif