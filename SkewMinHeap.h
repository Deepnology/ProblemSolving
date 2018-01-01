#ifndef SKEW_MIN_HEAP_H
#define SKEW_MIN_HEAP_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <deque>
#include <algorithm>
#include <functional>
#include "Debug.h"
/*
see also LeftistMinHeap.h
LeftistMinHeap and SkewMinHeap differ only in Merge()

Both Insert() and DeleteMin() are implemented in terms of Merge().
Insert/DeleteMin/Merge: O(logn) amortized time, O(n) worst case time
*/
class SkewMinHeap
{
public:
	struct HeapNode
	{
		HeapNode(const int & val) : val(val), left(nullptr), right(nullptr){ }
		HeapNode(int && val) : val(std::move(val)), left(nullptr), right(nullptr){ }
		~HeapNode(){}
		int val;
		HeapNode * left;
		HeapNode * right;
	};
private:
	HeapNode * m_root;
public:
	//ctor
	SkewMinHeap() : m_root(nullptr)
	{}
	SkewMinHeap(const std::vector<int> & v) : m_root(nullptr)
	{
		int N = v.size();
		for (int i = 0; i < N; ++i)
			this->Insert(v[i]);
	}
	//copy ctor: deep copy
	SkewMinHeap(const SkewMinHeap & rhs) : m_root(nullptr)
	{
		std::cout << "SkewMinHeap CopyCtor DeepCopy" << std::endl;
		m_root = this->cloneRecur(rhs.m_root);//only different from ctor
	}
	//copy ctor: move
	SkewMinHeap(SkewMinHeap && rhs) : m_root(rhs.m_root)
	{
		std::cout << "SkewMinHeap CopyCtor Move" << std::endl;
		rhs.m_root = nullptr;
	}
	//assignment: deep copy
	SkewMinHeap & operator=(const SkewMinHeap & rhs)
	{
		std::cout << "SkewMinHeap Assignment DeepCopy" << std::endl;
		SkewMinHeap copy = rhs;//copy ctor deep copy
		//because SkewMinHeap has defined ctor move and assignment move,
		//std::swap will use move semantics and call copy ctor move, assignment move, assignment move
		std::swap(*this, copy);
		return *this;
	}
	//assignment: move
	SkewMinHeap & operator=(SkewMinHeap && rhs)
	{
		std::cout << "SkewMinHeap Assignment Move" << std::endl;
		//because HeapNode hasn't defined ctor move and assignment move,
		//std::swap will use move semantics
		std::swap(m_root, rhs.m_root);
		return *this;
	}
	//dtor
	~SkewMinHeap()
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
			throw std::runtime_error("");
		std::cout << "SkewMinHeap FindMin: " << m_root->val << std::endl;
		return m_root->val;
	}
	void Insert(const int & val)
	{
		//merge a new node with root
		m_root = this->mergeRecur(new HeapNode(val), m_root);
		std::cout << "SkewMinHeap Insert: " << val << std::endl;
	}
	void Insert(int && val)
	{
		//merge a new node with root
		m_root = this->mergeRecur(new HeapNode(std::move(val)), m_root);
	}
	void DeleteMin(int & minItem)
	{
		if (this->IsEmpty())
			throw std::runtime_error("");
		minItem = m_root->val;
		HeapNode * oldRoot = m_root;

		//1. merge root's left and right child
		m_root = this->mergeRecur(m_root->left, m_root->right);

		//2. delete old root
		delete oldRoot;
		oldRoot = nullptr;

		std::cout << "SkewMinHeap DeleteMin: " << minItem << std::endl;
	}
	void DeleteMin()
	{
		int min;
		this->DeleteMin(min);
	}
	void Merge(SkewMinHeap & rhs)
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
		
		/*the only difference between LeftistMinHeap*/
		smaller->right = this->mergeRecur(smaller->right, bigger);
		std::swap(smaller->left, smaller->right);
		/*
		HeapNode * right = smaller->right;
		smaller->right = smaller->left;
		smaller->left = this->mergeRecur(right, bigger);
		*/

		return smaller;
	}
	HeapNode * cloneRecur(HeapNode * t) const
	{
		if (t == nullptr)
			return nullptr;
		else
		{
			HeapNode * c = new HeapNode(t->val);
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
		oss << "SkewMinHeap:" << std::endl;
		PrintBinaryTree<HeapNode, std::ostringstream>(m_root, oss);
		std::cout << oss.str() << std::endl;
	}
};
/*
SkewMinHeap Insert: 41
SkewMinHeap Insert: 67
SkewMinHeap Insert: 34
SkewMinHeap Insert: 0
SkewMinHeap Insert: 69
SkewMinHeap Insert: 24
SkewMinHeap Insert: 78
SkewMinHeap Insert: 58
SkewMinHeap Insert: 62
SkewMinHeap Insert: 64
SkewMinHeap Insert: 5
SkewMinHeap Insert: 45
SkewMinHeap Insert: 81
SkewMinHeap Insert: 27
SkewMinHeap Insert: 61
SkewMinHeap:
                                                              
                                                               1
                                ______________________________ 0______________________________
                               /                                                               \
                               2                                                               2
                ______________ 5______________                                  ______________24______________
               /                               \                               /                               \
               3                               3                               3                               3
        ______61______                  ______81______                  ______27______                  ______45______
       /               \               /               \               /               \               /               \
       4               X               X               X               4               X               4               X
    __62__          __ N__          __ N__          __ N__          __34__          __ N__          __58__          __ N__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   5       X       X       X       X       X       X       X       5       5       X       X       X       X       X       X
  69       N       N       N       N       N       N       N      64      41       N       N       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 6   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   6   X   X   X   X   X   X   X   X   X   X   X   X   X
78   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N  67   N   N   N   N   N   N   N   N   N   N   N   N   N


SkewMinHeap DeleteMin: 0
SkewMinHeap:
                                                              
                                                               1
                                ______________________________ 5______________________________
                               /                                                               \
                               2                                                               2
                ______________24______________                                  ______________61______________
               /                               \                               /                               \
               3                               3                               3                               X
        ______45______                  ______27______                  ______62______                  ______ N______
       /               \               /               \               /               \               /               \
       4               4               4               X               4               X               X               X
    __81__          __58__          __34__          __ N__          __69__          __ N__          __ N__          __ N__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       5       5       X       X       5       X       X       X       X       X       X       X
   N       N       N       N      64      41       N       N      78       N       N       N       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   6   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   N   N   N   N  67   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N


SkewMinHeap DeleteMin: 5
SkewMinHeap:
                                                              
                                                               1
                                ______________________________24______________________________
                               /                                                               \
                               2                                                               2
                ______________27______________                                  ______________45______________
               /                               \                               /                               \
               3                               3                               3                               3
        ______61______                  ______34______                  ______81______                  ______58______
       /               \               /               \               /               \               /               \
       4               X               4               4               X               X               X               X
    __62__          __ N__          __64__          __41__          __ N__          __ N__          __ N__          __ N__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   5       X       X       X       X       X       5       X       X       X       X       X       X       X       X       X
  69       N       N       N       N       N      67       N       N       N       N       N       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 6   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X
78   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N


SkewMinHeap DeleteMin: 24
SkewMinHeap:
                              
                               1
                ______________27______________
               /                               \
               2                               2
        ______34______                  ______61______
       /               \               /               \
       3               3               3               X
    __41__          __64__          __62__          __ N__
   /       \       /       \       /       \       /       \
   4       4       X       X       4       X       X       X
  45      67       N       N      69       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 5   5   X   X   X   X   X   X   5   X   X   X   X   X   X   X
81  58   N   N   N   N   N   N  78   N   N   N   N   N   N   N

*/
#endif