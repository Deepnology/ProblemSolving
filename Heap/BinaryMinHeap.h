#ifndef BINARY_MIN_HEAP_H
#define BINARY_MIN_HEAP_H
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
#include "Debug.h"
/*
Chapter 6.3
http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/BinaryHeap.h
Elements of programming interview, Heaps: Compute the K largest elements in a max heap, Test if x is bigger than the k-th largest element
find K smallest elements in binary heap represented as an array
GetKMin: O(klogk) time, O(k) space

compare the Kth smallest element in binary heap represented as an array with a number
Recur: O(k) time, O(k) space

http://www.ashishsharma.me/2011/09/binary-heap-implementation-java.html

Insert: O(height) = O(logn) time
Delete Min: O(height) = O(logn) time
Find Min: O(1) time
Decrease Key: O(height) = O(logn) time
Union: O(n) time

see also HeapSort.h, YoungTableau.h
*/
class BinaryMinHeap
{
public:
	BinaryMinHeap(int size) : m_curNodeCount(0), m_levelOrder(size)
	{

	}
	BinaryMinHeap(const std::vector<int> & A) : m_curNodeCount(0), m_levelOrder(A.size())
	{
		//make heap: O(nlogn)
		int N = A.size();
		for (int i = 0; i < N; ++i)
			this->Insert(A[i]);
		std::cout << "BinaryMinHeap for \"" << Debug::ToStr1D<int>()(A) << "\": " << Debug::ToStr1D<int>()(m_levelOrder) << std::endl;
	}
	~BinaryMinHeap(){}

	int GetLeftChildIndex(int nodeIndex) const
	{
		return 2 * nodeIndex + 1;
	}
	int GetRightChildIndex(int nodeIndex) const
	{
		return 2 * nodeIndex + 2;
	}
	int GetParentIndex(int nodeIndex) const
	{
		return (int)(nodeIndex - 1) / 2;
	}
	void Insert(int value)
	{
		if (m_curNodeCount == m_levelOrder.size())
			throw std::runtime_error("Heap Overflow");
		++m_curNodeCount;//1. increase the size
		m_levelOrder[m_curNodeCount - 1] = value;//2. place the new value in the back of the level order array
		this->bubbleUp_Iterate(m_curNodeCount - 1);//3. bubble up the new value
		std::cout << "BinaryMinHeap Insert for \"" << value << "\": " << Debug::ToStr1D<int>()(m_levelOrder) << std::endl;
	}
private:
	void bubbleUp_Recur(int nodeIndex)//preorder
	{
		if (nodeIndex == 0)//1. check if current node indx is root and return accordingly
			return;
		int parentIdx = this->GetParentIndex(nodeIndex);//2. find the parent index of current node index
		if (parentIdx >= 0 && 
			m_levelOrder[parentIdx] > m_levelOrder[nodeIndex])//3. compare parent with current node. swap and bubble up recur accordingly
		{
			std::swap(m_levelOrder[parentIdx], m_levelOrder[nodeIndex]);
			this->bubbleUp_Recur(parentIdx);
		}
	}
	void bubbleUp_Iterate(int nodeIndex)
	{
		int parentIdx = this->GetParentIndex(nodeIndex);
		while (parentIdx >= 0 && m_levelOrder[parentIdx] > m_levelOrder[nodeIndex])
		{
			std::swap(m_levelOrder[parentIdx], m_levelOrder[nodeIndex]);
			nodeIndex = parentIdx;
			parentIdx = this->GetParentIndex(nodeIndex);
		}
	}
public:
	int GetMin()
	{
		int min = m_levelOrder[0];
		return min;
	}
	void RemoveMin()
	{
		if (m_curNodeCount == 0)
			return;
		int min = m_levelOrder[0];//1. get min from root
		m_levelOrder[0] = m_levelOrder[m_curNodeCount - 1];//2. copy the last value in the level order array to root
		--m_curNodeCount;//3. shrink the size
		if (m_curNodeCount > 0)
			this->bubbleDown_Iterate(0);//4. bubble down recur the root value

		std::cout << "BinaryMinHeap RemoveMin: " << "\"" << min << "\", " << Debug::ToStr1D<int>()(&m_levelOrder[0], m_curNodeCount) << std::endl;
	}
private:
	void bubbleDown_Recur(int nodeIndex)
	{
		//1. find which child node that has a smaller value than current node
		int leftChildIdx = this->GetLeftChildIndex(nodeIndex);
		int rightChildIdx = this->GetRightChildIndex(nodeIndex);
		int minChildIdx = -1;
		if (rightChildIdx < m_curNodeCount)
		{
			minChildIdx = m_levelOrder[leftChildIdx] - m_levelOrder[rightChildIdx] < 0 ? leftChildIdx : rightChildIdx;
		}
		else if (leftChildIdx < m_curNodeCount)
		{
			minChildIdx = leftChildIdx;
		}
		else
			return;

		//2. swap current node value with smaller child value, and recur down
		if (m_levelOrder[minChildIdx] < m_levelOrder[nodeIndex])
		{
			std::swap(m_levelOrder[minChildIdx], m_levelOrder[nodeIndex]);
			this->bubbleDown_Recur(minChildIdx);
		}
	}
	void bubbleDown_Iterate(int nodeIndex)
	{
		while (true)
		{
			int leftChildIdx = this->GetLeftChildIndex(nodeIndex);
			int rightChildIdx = this->GetRightChildIndex(nodeIndex);
			int minChildIdx;
			if (rightChildIdx < m_curNodeCount)
			{
				minChildIdx = m_levelOrder[leftChildIdx] - m_levelOrder[rightChildIdx] < 0 ? leftChildIdx : rightChildIdx;
			}
			else if (leftChildIdx < m_curNodeCount)
			{
				minChildIdx = leftChildIdx;
			}
			else
				break;
			if (m_levelOrder[minChildIdx] < m_levelOrder[nodeIndex])
			{
				std::swap(m_levelOrder[minChildIdx], m_levelOrder[nodeIndex]);
				nodeIndex = minChildIdx;
			}
			else
				break;
		}
	}
public:
	std::vector<int> GetLevelOrderArray() const
	{
		return m_levelOrder;
	}
private:
	int m_curNodeCount;
	std::vector<int> m_levelOrder;

	struct GreaterThanComp
	{
		bool operator()(const std::pair<int, int> & a, const std::pair<int, int> & b)
		{
			return a.first > b.first;
		}
	};
public:
	std::vector<int> GetKMin(int K)
	{
		std::vector<int> res;
		if (K > m_curNodeCount)
			return res;
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >, GreaterThanComp> minHeap;//first: val, second: idx
		minHeap.push(std::make_pair(m_levelOrder[0], 0));
		
		//BFS for first K elements
		for (int i = 0; i < K; ++i)
		{
			int idx = minHeap.top().second;
			res.push_back(minHeap.top().first);
			minHeap.pop();

			if ((idx * 2) + 1 < m_curNodeCount)
				minHeap.push(std::make_pair(m_levelOrder[(idx * 2) + 1], (idx * 2) + 1));//push left child to minHeap
			if ((idx * 2) + 2 < m_curNodeCount)
				minHeap.push(std::make_pair(m_levelOrder[(idx * 2) + 2], (idx * 2) + 2));//push right child to minHeap
		}

		std::cout << "BinaryMinHeap GetKMin for \"" << K << "\" in \"" << Debug::ToStr1D<int>()(m_levelOrder) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	//-1 means smaller, 0 means equal, 1 means larger
	//if smallerCount >= K: larger
	//else if smallerCount+equalCount >= K: equal
	//else: smaller
	int CompareKthElement(int K, int val)
	{
		int smallerCount = 0;//the count of elements that are smaller than val in heap toward the Kth smallest element
		int equalCount = 0;//the count of elements that are equal to val in heap toward the Kth smallest element
		this->compareKthElement_Recur(K, val, 0, smallerCount, equalCount);
		int res = smallerCount >= K ? 1 : (smallerCount + equalCount >= K ? 0 : -1);
		std::cout << "BinaryMinHeap CompareKthElement for \"" << K << "\"-th with \"" << val << "\": " << res << std::endl;
		return res;
	}
private:
	//DFS accumulate smallerCount and equalCount
	void compareKthElement_Recur(int K, int val, int idx, int & smallerCount, int & equalCount)
	{
		if (smallerCount >= K || idx >= m_curNodeCount || m_levelOrder[idx] > val)
			return;
		else if (m_levelOrder[idx] == val)
		{
			++equalCount;
			if (equalCount >= K)
				return;
		}
		else//m_levelOrder[idx] < val
		{
			++smallerCount;
		}

		this->compareKthElement_Recur(K, val, 2 * idx + 1, smallerCount, equalCount);//recur down to left child
		this->compareKthElement_Recur(K, val, 2 * idx + 2, smallerCount, equalCount);//recur down to right child
	}
};
/*
BinaryMinHeap Insert for "41": 41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
BinaryMinHeap Insert for "67": 41, 67, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
BinaryMinHeap Insert for "34": 34, 67, 41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
BinaryMinHeap Insert for "0": 0, 34, 41, 67, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
BinaryMinHeap Insert for "69": 0, 34, 41, 67, 69, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
BinaryMinHeap Insert for "24": 0, 34, 24, 67, 69, 41, 0, 0, 0, 0, 0, 0, 0, 0, 0
BinaryMinHeap Insert for "78": 0, 34, 24, 67, 69, 41, 78, 0, 0, 0, 0, 0, 0, 0, 0
BinaryMinHeap Insert for "58": 0, 34, 24, 58, 69, 41, 78, 67, 0, 0, 0, 0, 0, 0, 0
BinaryMinHeap Insert for "62": 0, 34, 24, 58, 69, 41, 78, 67, 62, 0, 0, 0, 0, 0, 0
BinaryMinHeap Insert for "64": 0, 34, 24, 58, 64, 41, 78, 67, 62, 69, 0, 0, 0, 0, 0
BinaryMinHeap Insert for "5": 0, 5, 24, 58, 34, 41, 78, 67, 62, 69, 64, 0, 0, 0, 0
BinaryMinHeap Insert for "45": 0, 5, 24, 58, 34, 41, 78, 67, 62, 69, 64, 45, 0, 0, 0
BinaryMinHeap Insert for "81": 0, 5, 24, 58, 34, 41, 78, 67, 62, 69, 64, 45, 81, 0, 0
BinaryMinHeap Insert for "27": 0, 5, 24, 58, 34, 41, 27, 67, 62, 69, 64, 45, 81, 78, 0
BinaryMinHeap Insert for "61": 0, 5, 24, 58, 34, 41, 27, 67, 62, 69, 64, 45, 81, 78, 61
BinaryMinHeap for "41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61": 0, 5, 24, 58, 34, 41, 27, 67, 62, 69, 64, 45, 81, 78, 61
BinaryMinHeap GetKMin for "15" in "0, 5, 24, 58, 34, 41, 27, 67, 62, 69, 64, 45, 81, 78, 61": 0, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 81
BinaryMinHeap CompareKthElement for "15"-th with "80": -1
BinaryMinHeap CompareKthElement for "15"-th with "81": 0
BinaryMinHeap CompareKthElement for "15"-th with "82": 1
BinaryMinHeap RemoveMin: "0", 5, 34, 24, 58, 61, 41, 27, 67, 62, 69, 64, 45, 81, 78
BinaryMinHeap RemoveMin: "5", 24, 34, 27, 58, 61, 41, 78, 67, 62, 69, 64, 45, 81
BinaryMinHeap RemoveMin: "24", 27, 34, 41, 58, 61, 45, 78, 67, 62, 69, 64, 81
BinaryMinHeap RemoveMin: "27", 34, 58, 41, 62, 61, 45, 78, 67, 81, 69, 64
BinaryMinHeap Insert for "3": 3, 58, 34, 62, 61, 41, 78, 67, 81, 69, 64, 45, 81, 78, 61
BinaryMinHeap Insert for "2": 2, 58, 3, 62, 61, 34, 78, 67, 81, 69, 64, 45, 41, 78, 61
BinaryMinHeap Insert for "1": 1, 58, 2, 62, 61, 34, 3, 67, 81, 69, 64, 45, 41, 78, 61
BinaryMinHeap Insert for "0": 0, 58, 1, 62, 61, 34, 2, 67, 81, 69, 64, 45, 41, 78, 3
*/
#endif