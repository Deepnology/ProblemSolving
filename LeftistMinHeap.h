#ifndef LEFTIST_MIN_HEAP_H
#define LEFTIST_MIN_HEAP_H
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
Chapter 6.6
http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/LeftistHeap.h
Leftist heap is a binary tree that maintains heap property.
Heap property:
For every node X in the heap, its val is smaller or equal to both of its left and right child.
Leftist heap property:
For every node X in the heap, the "null path length" of the left child is at least as large as that of the right child.
(null path length: the shortest length from the node to a leaf node)

Both Insert() and DeleteMin() are implemented in terms of Merge().
Insert/DeleteMin/Merge: O(logn) time

See also SkewMinHeap.h
LeftistMinHeap and SkewMinHeap differ only in Merge()
*/
class LeftistMinHeap
{
public:
	struct HeapNode
	{
		/*npl=0 means it is a leaf node*/
		HeapNode(const int & val, int npl = 0) : val(val), npl(npl), left(nullptr), right(nullptr){ }
		HeapNode(int && val, int npl = 0) : val(std::move(val)), npl(npl), left(nullptr), right(nullptr){ }
		~HeapNode(){}
		int val;
		HeapNode * left;
		HeapNode * right;
		int npl;//null path length: the length of the shortest path from it to a leaf node
	};
private:
	HeapNode * m_root;
public:
	//ctor
	LeftistMinHeap() : m_root(nullptr)
	{}
	LeftistMinHeap(const std::vector<int> & v) : m_root(nullptr)
	{
		int N = v.size();
		for (int i = 0; i < N; ++i)
			this->Insert(v[i]);
	}
	//copy ctor: deep copy
	LeftistMinHeap(const LeftistMinHeap & rhs) : m_root(nullptr)
	{
		std::cout << "LeftistMinHeap CopyCtor DeepCopy" << std::endl;
		m_root = this->cloneRecur(rhs.m_root);//only different from ctor
	}
	//copy ctor: move
	LeftistMinHeap(LeftistMinHeap && rhs) : m_root(rhs.m_root)
	{
		std::cout << "LeftistMinHeap CopyCtor Move" << std::endl;
		rhs.m_root = nullptr;
	}
	//assignment: deep copy
	LeftistMinHeap & operator=(const LeftistMinHeap & rhs)
	{
		std::cout << "LeftistMinHeap Assignment DeepCopy" << std::endl;
		LeftistMinHeap copy = rhs;//copy ctor deep copy
		//because LeftistMinHeap has defined ctor move and assignment move,
		//std::swap will use move semantics and call copy ctor move, assignment move, assignment move
		std::swap(*this, copy);
		return *this;
	}
	//assignment: move
	LeftistMinHeap & operator=(LeftistMinHeap && rhs)
	{
		std::cout << "LeftistMinHeap Assignment Move" << std::endl;
		//because HeapNode hasn't defined ctor move and assignment move,
		//std::swap will use move semantics
		std::swap(m_root, rhs.m_root);
		return *this;
	}
	//dtor
	~LeftistMinHeap()
	{
		this->MakeEmpty();
	}

	void MakeEmpty()
	{
		this->deleteTreeRecur(m_root);
	}
	bool IsEmpty() const
	{
		return m_root == nullptr;
	}
	const int & FindMin() const
	{
		if (this->IsEmpty())
			throw std::exception("");
		std::cout << "LeftistMinHeap FindMin: " << m_root->val << std::endl;
		return m_root->val;
	}
	void Insert(const int & val)
	{
		//merge a new node with root
		m_root = this->mergeRecur(new HeapNode(val), m_root);
		std::cout << "LeftistMinHeap Insert: " << val << std::endl;
	}
	void Insert(int && val)
	{
		//merge a new node with root
		m_root = this->mergeRecur(new HeapNode(std::move(val)), m_root);
	}
	void DeleteMin(int & minItem)
	{
		if (this->IsEmpty())
			throw std::exception("");
		minItem = m_root->val;
		HeapNode * oldRoot = m_root;

		//1. merge root's left and right child
		m_root = this->mergeRecur(m_root->left, m_root->right);

		//2. delete old root
		delete oldRoot;
		oldRoot = nullptr;

		std::cout << "LeftistMinHeap DeleteMin: " << minItem << std::endl;
	}
	void DeleteMin()
	{
		int min;
		this->DeleteMin(min);
	}
	void Merge(LeftistMinHeap & rhs)
	{
		if (this == &rhs)
			return;
		m_root = this->mergeRecur(m_root, rhs.m_root);
		rhs.m_root = nullptr;
	}
private:
	HeapNode * mergeRecur(HeapNode * h1, HeapNode * h2)
	{
		if (h1 == nullptr)
			return h2;
		if (h2 == nullptr)
			return h1;
		//now both h1 and h2 are not nullptr
		HeapNode * smaller;
		HeapNode * bigger;
		if (h1->val < h2->val)
		{
			smaller = h1;
			bigger = h2;
		}
		else
		{
			smaller = h2;
			bigger = h1;
		}

		//1. if smaller's left child is empty, assign bigger as smaller's left child
		if (smaller->left == nullptr)
			smaller->left = bigger;

		//2. if smaller already has a left child
		else
		{
			//2.1. merge recursively smaller's right child with bigger
			smaller->right = this->mergeRecur(smaller->right, bigger);

			//2.2. after merge, compare smaller's left and right child's npl, swap the bigger one to smaller's left
			if (smaller->left->npl < smaller->right->npl)
				std::swap(smaller->left, smaller->right);

			//2.3 update smaller's npl
			smaller->npl = smaller->right->npl + 1;
		}
		return smaller;
	}
	HeapNode * cloneRecur(HeapNode * t) const
	{
		if (t == nullptr)
			return nullptr;
		else
		{
			HeapNode * c = new HeapNode(t->val, t->npl);
			c->left = this->cloneRecur(t->left);
			c->right = this->cloneRecur(t->right);
			return c;
		}
	}
	void deleteTreeRecur(HeapNode * t)
	{
		if (t != nullptr)
		{
			this->deleteTreeRecur(t->left);
			this->deleteTreeRecur(t->right);
			delete t;
			t = nullptr;
		}
	}

public:
	void Print()
	{
		std::ostringstream oss;
		oss << "LeftistMinHeap (val2: npl, shortest length to a leaf node):" << std::endl;
		PrintBinaryTree<HeapNode, std::ostringstream>(m_root, oss);
		std::cout << oss.str() << std::endl;
	}
};

template<>
std::string PrintBinaryTree<LeftistMinHeap::HeapNode, std::ostringstream>::selectVal2(int depth, LeftistMinHeap::HeapNode * n)
{
	return std::to_string(n->npl);
}
/*
1.
LeftistMinHeap CopyCtor DeepCopy
2.
LeftistMinHeap CopyCtor DeepCopy
3.
LeftistMinHeap CopyCtor Move
4.
LeftistMinHeap CopyCtor Move
5.
LeftistMinHeap Assignment DeepCopy
LeftistMinHeap CopyCtor DeepCopy
LeftistMinHeap CopyCtor Move
LeftistMinHeap Assignment Move
LeftistMinHeap Assignment Move
6.
LeftistMinHeap Assignment Move
LeftistMinHeap Insert: 41
LeftistMinHeap Insert: 67
LeftistMinHeap Insert: 34
LeftistMinHeap Insert: 0
LeftistMinHeap Insert: 69
LeftistMinHeap Insert: 24
LeftistMinHeap Insert: 78
LeftistMinHeap Insert: 58
LeftistMinHeap Insert: 62
LeftistMinHeap Insert: 64
LeftistMinHeap Insert: 5
LeftistMinHeap Insert: 45
LeftistMinHeap Insert: 81
LeftistMinHeap Insert: 27
LeftistMinHeap Insert: 61
LeftistMinHeap (val2: npl, shortest length to a leaf node):
                              
                               2
                ______________ 0______________
               /                               \
               2                               1
        ______ 5______                  ______24______
       /               \               /               \
       1               1               0               0
    __34__          __27__          __69__          __78__
   /       \       /       \       /       \       /       \
   1       0       0       0       X       X       X       X
  58      41      45      61       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 0   0   0   X   0   X   X   X   X   X   X   X   X   X   X   X
62  64  67   N  81   N   N   N   N   N   N   N   N   N   N   N


LeftistMinHeap DeleteMin: 0
LeftistMinHeap (val2: npl, shortest length to a leaf node):
                              
                               2
                ______________ 5______________
               /                               \
               1                               1
        ______34______                  ______24______
       /               \               /               \
       1               0               1               0
    __58__          __41__          __27__          __69__
   /       \       /       \       /       \       /       \
   0       0       0       X       0       0       X       X
  62      64      67       N      45      61       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   0   X   0   X   X   X   X   X
 N   N   N   N   N   N   N   N  81   N  78   N   N   N   N   N


LeftistMinHeap DeleteMin: 5
LeftistMinHeap (val2: npl, shortest length to a leaf node):
              
               2
        ______24______
       /               \
       2               1
    __34__          __27__
   /       \       /       \
   1       1       0       0
  58      41      45      61
 /   \   /   \   /   \   /   \
 0   0   0   0   0   X   0   X
62  64  67  69  81   N  78   N


LeftistMinHeap DeleteMin: 24
LeftistMinHeap (val2: npl, shortest length to a leaf node):
                              
                               1
                ______________27______________
               /                               \
               2                               0
        ______34______                  ______45______
       /               \               /               \
       1               1               0               X
    __58__          __41__          __81__          __ N__
   /       \       /       \       /       \       /       \
   0       0       1       0       X       X       X       X
  62      64      61      67       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   0   0   X   X   X   X   X   X   X   X   X   X
 N   N   N   N  78  69   N   N   N   N   N   N   N   N   N   N

*/
#endif