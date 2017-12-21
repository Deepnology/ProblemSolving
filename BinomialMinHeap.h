#ifndef BINOMIAL_MIN_HEAP_H
#define BINOMIAL_MIN_HEAP_H
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
#include "PrintBinaryTree.h"
/*
http://www.cs.toronto.edu/~krueger/cscB63h/assignments/p1/THeap.java
http://mytestpjt.googlecode.com/svn/trunk/ASAssembly/src/com/mhhe/clrs2e/BinomialHeap.java
main:
http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/BinomialQueue.h
BinomialHeap:
An array of Binomial Trees with node count: 1, 2, 4, 8, 16, 32, ...
The min element is the min node among all tree roots

n: number of all nodes of all binomial trees
logn: number of all binomial trees

Insert (Merge): O(1) amortized time, O(logn) time in worst case
Insert n nodes to an empty heap: O(n) time in worst case
DeleteMin (FindMin + Merge): O(logn) time
FindMin: O(logn) time
Merge: O(logn) time

Non-standard operations:
DecreaseKey (PercolateUp/BubbleUp): O(logn) time
Remove (DecreaseKey + DeleteMin): O(logn) time
*/
class BinomialMinHeap
{
public:
	struct HeapNode
	{
		HeapNode(const int & val) : val(val), leftChild(NULL), nextSibling(NULL) {}
		HeapNode(int && val) : val(std::move(val)), leftChild(NULL), nextSibling(NULL) {}
		~HeapNode(){}
		int val;
		HeapNode * leftChild;
		HeapNode * nextSibling;
	};
private:
	std::vector<HeapNode *> m_theTrees;
	int m_curNodeCount;
public:
	//ctor
	BinomialMinHeap() : m_theTrees(1), m_curNodeCount(0)
	{
		m_theTrees[0] = nullptr;
	}
	BinomialMinHeap(const std::vector<int> & v) : m_theTrees(1), m_curNodeCount(0)
	{
		int N = v.size();
		for (int i = 0; i < N; ++i)
			this->Insert(v[i]);
	}
	BinomialMinHeap(const int & item) : m_theTrees(1), m_curNodeCount(1)
	{
		m_theTrees[0] = new HeapNode(item);
	}
	//copy ctor: deep copy
	BinomialMinHeap(const BinomialMinHeap & rhs) : m_theTrees(rhs.m_theTrees), m_curNodeCount(rhs.m_curNodeCount)
	{
		for (int i = 0; i < (int)rhs.m_theTrees.size(); ++i)
			m_theTrees[i] = this->cloneRecur(rhs.m_theTrees[i]);//deep copy
	}
	//copy ctor: move
	BinomialMinHeap(BinomialMinHeap && rhs) : m_theTrees(std::move(rhs.m_theTrees)), m_curNodeCount(rhs.m_curNodeCount)
	{

	}
	//dtor
	~BinomialMinHeap()
	{
		this->MakeEmpty();
	}
	//assignment: deep copy
	BinomialMinHeap & operator=(const BinomialMinHeap & rhs)
	{
		BinomialMinHeap copy = rhs;//use copy ctor
		std::swap(*this, copy);
		return *this;
	}
	//assignment: move
	BinomialMinHeap & operator=(BinomialMinHeap && rhs)
	{
		std::swap(m_curNodeCount, rhs.m_curNodeCount);
		std::swap(m_theTrees, rhs.m_theTrees);
		return *this;
	}

	void MakeEmpty()
	{
		m_curNodeCount = 0;
		for (auto & root : m_theTrees)
			this->deleteTreeRecur(root);
	}
	bool IsEmpty() const
	{
		return m_curNodeCount == 0;
	}
	const int & FindMin() const
	{
		if (this->IsEmpty())
			throw std::exception("Empty Heap");
		int minIdx = this->findMinIndex();
		std::cout << "BinomialMinHeap FindMin: " << m_theTrees[minIdx]->val << std::endl;
		return m_theTrees[minIdx]->val;
	}
	/*
	allow duplicates
	implemented in terms of Merge()
	*/
	void Insert(const int & val)
	{
		BinomialMinHeap aHeap(val);
		this->Merge(aHeap);
		std::cout << "BinomialMinHeap Insert: " << val << std::endl;
	}
	/*
	allow duplicates
	implemented in terms of Merge()
	*/
	void Insert(int && val)
	{
		BinomialMinHeap aHeap(std::move(val));
		this->Merge(aHeap);
	}
	void DeleteMin()
	{
		int min;
		this->DeleteMin(min);
	}
	/*
	remove the min item and place it in minItem
	implemented in terms of findMinIndex() and Merge()
	*/
	void DeleteMin(int & minItem)
	{
		if (this->IsEmpty())
			throw std::exception("DeleteMinFromEmptyHeap");
		//1. find min index
		int minIdx = this->findMinIndex();
		minItem = m_theTrees[minIdx]->val;
		//2. delete min root (m_theTrees[minIdx)
		HeapNode * deletedTree = m_theTrees[minIdx]->leftChild;
		delete m_theTrees[minIdx];
		m_theTrees[minIdx] = nullptr;
		//3. construct deletedHeap from deletedTree
		BinomialMinHeap deletedHeap;
		deletedHeap.m_theTrees.resize(minIdx);
		deletedHeap.m_curNodeCount = (1 << minIdx) - 1;//2^minIdx - 1
		//the deletedTree can be decomposed into smaller binomial trees
		//starting from index (minIdx-1) to 0
		for (int i = minIdx - 1; i >= 0; --i)
		{
			deletedHeap.m_theTrees[i] = deletedTree;
			deletedTree = deletedTree->nextSibling;//nextSibling will be the next smaller binomial tree
			deletedHeap.m_theTrees[i]->nextSibling = nullptr;
		}
		//4. remove deletedTree and merge deletedHeap
		m_curNodeCount -= deletedHeap.m_curNodeCount + 1;
		this->Merge(deletedHeap);

		std::cout << "BinomialMinHeap DeleteMin: " << minItem << std::endl;
	}

	/*Merge is called in DeleteMin, Insert*/
	void Merge(BinomialMinHeap & rhs)
	{
		if (this == &rhs)
			return;

		//1. resize m_theTrees if necessary
		m_curNodeCount += rhs.m_curNodeCount;
		if (m_curNodeCount > this->capacity())//current m_theTrees' size isn't big enough
		{
			int curTreeCount = m_theTrees.size();
			int newTreeCount = std::max(m_theTrees.size(), rhs.m_theTrees.size()) + 1;
			m_theTrees.resize(newTreeCount);
			for (int i = curTreeCount; i < newTreeCount; ++i)
				m_theTrees[i] = nullptr;
		}

		//2. combine each equal sized binomial tree pairs to m_theTrees
		//empty rhs.m_theTrees
		HeapNode * carry = nullptr;
		//i: index of binomial tree
		//j: max node count (capacity) of a binomial tree m_theTrees[i]
		for (int i = 0, j = 1; j <= m_curNodeCount; ++i, j *= 2)
		{
			HeapNode * t1 = m_theTrees[i];
			HeapNode * t2 = i < (int)rhs.m_theTrees.size() ? rhs.m_theTrees[i] : nullptr;

			int whichCase = t1 == nullptr ? 0 : 1;
			whichCase += t2 == nullptr ? 0 : 2;
			whichCase += carry == nullptr ? 0 : 4;

			switch (whichCase)
			{
			case 0:/*no trees*/
				break;
			case 1:/*only this*/
				break;
			case 2:/*only rhs*/
				m_theTrees[i] = t2;
				rhs.m_theTrees[i] = nullptr;
				break;
			case 3:/*this and rhs*/
				carry = this->combineTreesRecur(t1, t2);
				m_theTrees[i] = rhs.m_theTrees[i] = nullptr;
				break;
			case 4:/*only carry*/
				m_theTrees[i] = carry;
				carry = nullptr;
				break;
			case 5:/*this and carry*/
				carry = this->combineTreesRecur(t1, carry);
				m_theTrees[i] = nullptr;
				break;
			case 6:/*rhs and carry*/
				carry = this->combineTreesRecur(t2, carry);
				rhs.m_theTrees[i] = nullptr;
				break;
			case 7:/*this, rhs, and carry*/
				m_theTrees[i] = carry;
				carry = this->combineTreesRecur(t1, t2);
				rhs.m_theTrees[i] = nullptr;
				break;
			default:
				break;
			}
		}

		//3. empty rhs.m_theTrees and rhs.m_curNodeCount
		for (auto & root : rhs.m_theTrees)
			root = nullptr;
		rhs.m_curNodeCount = 0;
	}

private:
	/*scan from first tree root to the last tree root*/
	int findMinIndex() const
	{
		int N = m_theTrees.size();
		int minIdx = -1;
		for (int i = 0; i < N; ++i)
		{
			if (m_theTrees[i] != nullptr)
			{
				if (minIdx == -1)
					minIdx = i;//first time init
				else if (m_theTrees[i]->val < m_theTrees[minIdx]->val)
					minIdx = i;
			}
		}
		return minIdx;
	}
	/*capacity is the max number of all tree nodes in the forest*/
	int capacity() const
	{
		return (1 << m_theTrees.size()) - 1;//2^(number of binomial trees) - 1
	}
	/*return the result of merging equal-sized t1 and t2*/
	HeapNode * combineTreesRecur(HeapNode * t1, HeapNode * t2)
	{
		if (t2->val < t1->val)
			return this->combineTreesRecur(t2, t1);
		t2->nextSibling = t1->leftChild;
		t1->leftChild = t2;
		return t1;
	}
	void deleteTreeRecur(HeapNode * & t)
	{
		if (t != nullptr)
		{
			this->deleteTreeRecur(t->leftChild);
			this->deleteTreeRecur(t->nextSibling);
			delete t;//post order visiting the node
			t = nullptr;
		}
	}
	HeapNode * cloneRecur(HeapNode * t) const
	{
		if (t == nullptr)
			return nullptr;
		else
		{
			HeapNode * c = new HeapNode(t->val);
			c->leftChild = this->cloneRecur(t->leftChild);
			c->nextSibling = this->cloneRecur(t->nextSibling);
			return c;
		}
	}

public:
	void Print()
	{
		std::ostringstream oss;
		int N = m_theTrees.size();
		for (int i = 0; i < N; ++i)
		{
			oss << i << "-th BinomialTree (leftChild, nextSibling):";
			PrintBinaryTree<HeapNode, std::ostringstream>(m_theTrees[i], oss);
		}
		std::cout << oss.str() << std::endl;
	}
	
};

template<>
BinomialMinHeap::HeapNode * PrintBinaryTree<BinomialMinHeap::HeapNode, std::ostringstream>::getLeft(BinomialMinHeap::HeapNode * n)
{
	return n->leftChild;
};
template<>
BinomialMinHeap::HeapNode * PrintBinaryTree<BinomialMinHeap::HeapNode, std::ostringstream>::getRight(BinomialMinHeap::HeapNode * n)
{
	return n->nextSibling;
};
template<>
std::string PrintBinaryTree<BinomialMinHeap::HeapNode, std::ostringstream>::getVal(BinomialMinHeap::HeapNode * n)
{
	std::ostringstream oss;
	oss << n->val;
	return oss.str();
};
/*
BinomialMinHeap Insert: 41
BinomialMinHeap Insert: 67
BinomialMinHeap Insert: 34
BinomialMinHeap Insert: 0
BinomialMinHeap Insert: 69
BinomialMinHeap Insert: 24
BinomialMinHeap Insert: 78
BinomialMinHeap Insert: 58
BinomialMinHeap Insert: 62
BinomialMinHeap Insert: 64
BinomialMinHeap Insert: 5
BinomialMinHeap Insert: 45
BinomialMinHeap Insert: 81
BinomialMinHeap Insert: 27
BinomialMinHeap Insert: 61
0-th BinomialTree (leftChild, nextSibling):
 1
61

1-th BinomialTree (leftChild, nextSibling):  
   1
  27
 /   \
 2   X
81   N

2-th BinomialTree (leftChild, nextSibling):      
       1
    __ 5__
   /       \
   2       X
  62       N
 /   \   /   \
 3   3   X   X
64  45   N   N

3-th BinomialTree (leftChild, nextSibling):              
               1
        ______ 0______
       /               \
       2               X
    __24__          __ N__
   /       \       /       \
   3       3       X       X
  58      41       N       N
 /   \   /   \   /   \   /   \
 4   4   4   4   X   X   X   X
78  69  67  34   N   N   N   N


BinomialMinHeap DeleteMin: 0
0-th BinomialTree (leftChild, nextSibling):

1-th BinomialTree (leftChild, nextSibling):  
   1
  34
 /   \
 2   X
61   N

2-th BinomialTree (leftChild, nextSibling):      
       1
    __27__
   /       \
   2       X
  41       N
 /   \   /   \
 3   3   X   X
67  81   N   N

3-th BinomialTree (leftChild, nextSibling):              
               1
        ______ 5______
       /               \
       2               X
    __24__          __ N__
   /       \       /       \
   3       3       X       X
  58      62       N       N
 /   \   /   \   /   \   /   \
 4   4   4   4   X   X   X   X
78  69  64  45   N   N   N   N


BinomialMinHeap DeleteMin: 5
0-th BinomialTree (leftChild, nextSibling):
 1
45

1-th BinomialTree (leftChild, nextSibling):

2-th BinomialTree (leftChild, nextSibling):      
       1
    __34__
   /       \
   2       X
  62       N
 /   \   /   \
 3   3   X   X
64  61   N   N

3-th BinomialTree (leftChild, nextSibling):              
               1
        ______24______
       /               \
       2               X
    __27__          __ N__
   /       \       /       \
   3       3       X       X
  41      58       N       N
 /   \   /   \   /   \   /   \
 4   4   4   4   X   X   X   X
67  81  78  69   N   N   N   N


BinomialMinHeap DeleteMin: 24
0-th BinomialTree (leftChild, nextSibling):

1-th BinomialTree (leftChild, nextSibling):

2-th BinomialTree (leftChild, nextSibling):      
       1
    __45__
   /       \
   2       X
  58       N
 /   \   /   \
 3   3   X   X
78  69   N   N

3-th BinomialTree (leftChild, nextSibling):              
               1
        ______27______
       /               \
       2               X
    __34__          __ N__
   /       \       /       \
   3       3       X       X
  62      41       N       N
 /   \   /   \   /   \   /   \
 4   4   4   4   X   X   X   X
64  61  67  81   N   N   N   N

*/
#endif