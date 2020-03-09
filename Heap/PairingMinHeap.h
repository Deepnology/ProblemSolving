#ifndef PAIRING_MIN_HEAP_H
#define PAIRING_MIN_HEAP_H
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
http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/PairingHeap.h


Insert			O(1), O(logn) amortized
FindMin			O(1)
DeleteMin		O(n), O(logn) amortized
Union			O(1), O(logn) amortized

DecreaseKey		O(1), O(logn) amortized
DeleteNode		O(n), O(logn) amortized
*/
class PairingMinHeap
{
public:
	struct HeapNode
	{
		HeapNode(const int & val) : val(val), leftChild(nullptr), nextSibling(nullptr), prev(nullptr){}
		HeapNode(int && val) : val(std::move(val)), leftChild(nullptr), nextSibling(nullptr), prev(nullptr){}
		~HeapNode(){}
		int val;
		HeapNode * leftChild;
		HeapNode * nextSibling;
		HeapNode * prev;//mainly used in DecreaseKey()
	};
private:
	HeapNode * m_root;
public:
	PairingMinHeap() : m_root(nullptr)
	{}
	PairingMinHeap(const std::vector<int> & v) : m_root(nullptr)
	{
		int N = v.size();
		for (int i = 0; i < N; ++i)
			this->Insert(v[i]);
	}
	~PairingMinHeap()
	{
		this->MakeEmpty();
	}
	//copy ctor: deep copy
	PairingMinHeap(const PairingMinHeap & rhs) : m_root(nullptr)
	{
		m_root = this->cloneRecur(rhs.m_root);
	}
	//copy ctor: move
	PairingMinHeap(PairingMinHeap && rhs) : m_root(rhs.m_root)
	{
		rhs.m_root = nullptr;
	}
	//assignment: deep copy
	PairingMinHeap & operator=(const PairingMinHeap & rhs)
	{
		PairingMinHeap copy = rhs;//copy ctor: deep copy
		std::swap(*this, copy);
		return *this;
	}
	//assignment: move
	PairingMinHeap & operator=(PairingMinHeap && rhs)
	{
		std::swap(m_root, rhs.m_root);
		return *this;
	}


	bool IsEmpty() const
	{
		return m_root == nullptr;
	}
	void MakeEmpty()
	{
		this->deleteTreeRecur(m_root);
		m_root = nullptr;
	}
	const int & FindMin() const
	{
		if (this->IsEmpty())
			throw std::runtime_error("");
		std::cout << "PairingMinHeap FindMin: " << m_root->val << std::endl;
		return m_root->val;
	}
	/*
	insert item val into the priority queue, maintaining heap order.
	return a pointer to the node containing the new item.
	*/
	HeapNode * Insert(const int & val)
	{
		HeapNode * node = new HeapNode(val);
		if (m_root == nullptr)
			m_root = node;
		else
			this->compareAndLink(m_root, node);
		std::cout << "PairingMinHeap Insert: " << val << std::endl;
		return node;
	}
	void DeleteMin(int & val)
	{
		if (this->IsEmpty())
			throw std::runtime_error("");
		val = m_root->val;
		HeapNode * oldRoot = m_root;
		if (m_root->leftChild == nullptr)
			m_root = nullptr;
		else
			m_root = this->combineSiblings_2Pass(m_root->leftChild);
		delete oldRoot;
		oldRoot = nullptr;
		std::cout << "PairingMinHeap DeleteMin: " << val << std::endl;
	}
	void DeleteMin()
	{
		int val;
		this->DeleteMin(val);
	}
	void DecreaseKey(HeapNode * p, const int & val)
	{
		if (p->val < val)
			throw std::runtime_error("new val too large");
		std::cout << "PairingMinHeap DecreaseKey for \"" << p->val << "\": " << val << std::endl;
		p->val = val;
		if (p != m_root)
		{
			if (p->nextSibling != nullptr)
				p->nextSibling->prev = p->prev;
			if (p->prev->leftChild == p)
				p->prev->leftChild = p->nextSibling;
			else
				p->prev->nextSibling = p->nextSibling;

			p->nextSibling = nullptr;
			this->compareAndLink(m_root, p);
		}
	}
private:
	/*
	Links first and second together to satisfy heap order.
	first is root of tree1, which may not be nullptr.
	first->nextSibling MUST be nullptr on entry.
	second is root of tree2, which may be nullptr.
	first becomes the result of the tree merge.
	Called in combineSiblings_2Pass(), DecreaseKey(), Insert()
	*/
	void compareAndLink(HeapNode *& first, HeapNode * second)
	{
		if (second == nullptr)
			return;
		if (second->val < first->val)
		{
			//attach first as leftmost child of second
			second->prev = first->prev;
			first->prev = second;
			first->nextSibling = second->leftChild;
			if (first->nextSibling != nullptr)
				first->nextSibling->prev = first;
			second->leftChild = first;
			first = second;
		}
		else
		{
			//attach second as leftmost child of first
			second->prev = first;
			first->nextSibling = second->nextSibling;
			if (first->nextSibling != nullptr)
				first->nextSibling->prev = first;
			second->nextSibling = first->leftChild;
			if (second->nextSibling != nullptr)
				second->nextSibling->prev = second;
			first->leftChild = second;
		}
	}
	/*
	internal method that implements 2 pass merging.
	firstSibling the root of the conglomerate and is assumed not nullptr.
	called in DeleteMin()
	*/
	HeapNode * combineSiblings_2Pass(HeapNode * firstSibling)
	{
		if (firstSibling->nextSibling == nullptr)
			return firstSibling;
		static std::vector<HeapNode *> treeArray(5);
		int siblingCount = 0;
		for (; firstSibling != nullptr; ++siblingCount)
		{
			if (siblingCount == (int)treeArray.size())
				treeArray.resize(siblingCount * 2);
			treeArray[siblingCount] = firstSibling;
			firstSibling->prev->nextSibling = nullptr;//break links
			firstSibling = firstSibling->nextSibling;
		}
		if (siblingCount == (int)treeArray.size())
			treeArray.resize(siblingCount + 1);
		treeArray[siblingCount] = nullptr;

		//1. from left to right
		int i = 0;
		for (; i + 1 < siblingCount; i += 2)
			this->compareAndLink(treeArray[i], treeArray[i + 1]);

		int j = i - 2;
		if (j == siblingCount - 3)
			this->compareAndLink(treeArray[j], treeArray[j + 2]);

		//2. from right to left
		for (; j >= 2; j -= 2)
			this->compareAndLink(treeArray[j - 2], treeArray[j]);

		return treeArray[0];
	}
	HeapNode * cloneRecur(HeapNode * t)
	{
		if (t == nullptr)
			return nullptr;
		else
		{
			HeapNode * c = new HeapNode(t->val);
			if ((c->leftChild = this->cloneRecur(t->leftChild)) != nullptr)
				c->leftChild->prev = c;
			if ((c->nextSibling = this->cloneRecur(t->nextSibling)) != nullptr)
				c->nextSibling->prev = c;
			return c;
		}
	}
	void deleteTreeRecur(HeapNode * t)
	{
		if (t != nullptr)
		{
			this->deleteTreeRecur(t->leftChild);
			this->deleteTreeRecur(t->nextSibling);
			delete t;
			t = nullptr;
		}
	}

public:
	void Print()
	{
		std::ostringstream oss;
		oss << "PairingMinHeap (leftChild, nextSibling, val, prev):" << std::endl;
		PrintBinaryTree<HeapNode, std::ostringstream>(m_root, oss);
		std::cout << oss.str() << std::endl;
	}
};

template<>
PairingMinHeap::HeapNode * PrintBinaryTree<PairingMinHeap::HeapNode, std::ostringstream>::getLeft(PairingMinHeap::HeapNode * n)
{
	return n->leftChild;
};
template<>
PairingMinHeap::HeapNode * PrintBinaryTree<PairingMinHeap::HeapNode, std::ostringstream>::getRight(PairingMinHeap::HeapNode * n)
{
	return n->nextSibling;
};
template<>
std::string PrintBinaryTree<PairingMinHeap::HeapNode, std::ostringstream>::getVal(PairingMinHeap::HeapNode * n)
{
	return std::to_string(n->val);
};
template<>
std::string PrintBinaryTree<PairingMinHeap::HeapNode, std::ostringstream>::selectVal2(int depth, PairingMinHeap::HeapNode * n)
{
	std::ostringstream oss;
	if (n->prev != nullptr)
		oss << n->prev->val;
	else
		oss << "N";
	return oss.str();
}
/*
PairingMinHeap Insert: 9
PairingMinHeap Insert: 4
PairingMinHeap Insert: 3
PairingMinHeap Insert: 5
PairingMinHeap Insert: 8
PairingMinHeap Insert: 7
PairingMinHeap (leftChild, nextSibling, val, prev):
                                                              
                                                               N
                                ______________________________ 3______________________________
                               /                                                               \
                               3                                                               X
                ______________ 7______________                                  ______________ N______________
               /                               \                               /                               \
               X                               7                               X                               X
        ______ N______                  ______ 8______                  ______ N______                  ______ N______
       /               \               /               \               /               \               /               \
       X               X               X               8               X               X               X               X
    __ N__          __ N__          __ N__          __ 5__          __ N__          __ N__          __ N__          __ N__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       X       X       X       5       X       X       X       X       X       X       X       X
   N       N       N       N       N       N       N       4       N       N       N       N       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   X   X   4   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   N   N   N   N   N   N   N   N   9   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N


PairingMinHeap DeleteMin: 3
PairingMinHeap (leftChild, nextSibling, val, prev):
              
              -572662307
        ______ 4______
       /               \
       4               X
    __ 7__          __ N__
   /       \       /       \
   7       7       X       X
   8       5       N       N
 /   \   /   \   /   \   /   \
 X   X   X   5   X   X   X   X
 N   N   N   9   N   N   N   N


PairingMinHeap DeleteMin: 4
PairingMinHeap (leftChild, nextSibling, val, prev):
              
              -572662307
        ______ 5______
       /               \
       5               X
    __ 9__          __ N__
   /       \       /       \
   X       9       X       X
   N       7       N       N
 /   \   /   \   /   \   /   \
 X   X   7   X   X   X   X   X
 N   N   8   N   N   N   N   N


PairingMinHeap Insert: 6
PairingMinHeap (leftChild, nextSibling, val, prev):
                              
                              -572662307
                ______________ 5______________
               /                               \
               5                               X
        ______ 6______                  ______ N______
       /               \               /               \
       X               6               X               X
    __ N__          __ 9__          __ N__          __ N__
   /       \       /       \       /       \       /       \
   X       X       X       9       X       X       X       X
   N       N       N       7       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   7   X   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   8   N   N   N   N   N   N   N   N   N


PairingMinHeap Insert: 10
PairingMinHeap (leftChild, nextSibling, val, prev):
                                                              
                                                              -572662307
                                ______________________________ 5______________________________
                               /                                                               \
                               5                                                               X
                ______________10______________                                  ______________ N______________
               /                               \                               /                               \
               X                              10                               X                               X
        ______ N______                  ______ 6______                  ______ N______                  ______ N______
       /               \               /               \               /               \               /               \
       X               X               X               6               X               X               X               X
    __ N__          __ N__          __ N__          __ 9__          __ N__          __ N__          __ N__          __ N__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       X       X       X       9       X       X       X       X       X       X       X       X
   N       N       N       N       N       N       N       7       N       N       N       N       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   X   X   7   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   N   N   N   N   N   N   N   N   8   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N


PairingMinHeap DecreaseKey for "6": 3
PairingMinHeap (leftChild, nextSibling, val, prev):
                                                              
                                                              -572662307
                                ______________________________ 3______________________________
                               /                                                               \
                               3                                                               X
                ______________ 5______________                                  ______________ N______________
               /                               \                               /                               \
               5                               X                               X                               X
        ______10______                  ______ N______                  ______ N______                  ______ N______
       /               \               /               \               /               \               /               \
       X              10               X               X               X               X               X               X
    __ N__          __ 9__          __ N__          __ N__          __ N__          __ N__          __ N__          __ N__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       9       X       X       X       X       X       X       X       X       X       X       X       X
   N       N       N       7       N       N       N       N       N       N       N       N       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   7   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   8   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N


PairingMinHeap DecreaseKey for "10": 4
PairingMinHeap (leftChild, nextSibling, val, prev):
                                                              
                                                              -572662307
                                ______________________________ 3______________________________
                               /                                                               \
                               3                                                               X
                ______________ 4______________                                  ______________ N______________
               /                               \                               /                               \
               X                               4                               X                               X
        ______ N______                  ______ 5______                  ______ N______                  ______ N______
       /               \               /               \               /               \               /               \
       X               X               5               X               X               X               X               X
    __ N__          __ N__          __ 9__          __ N__          __ N__          __ N__          __ N__          __ N__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       X       9       X       X       X       X       X       X       X       X       X       X
   N       N       N       N       N       7       N       N       N       N       N       N       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   7   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   N   N   N   N   8   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N

*/
#endif