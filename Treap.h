#ifndef TREAP_H
#define TREAP_H
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
#include "UniformRandom.h"
#include "Debug.h"
#include "PrintBinaryTree.h"
/*
Chapter 12.3
http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/Treap.h
Treap is a binary tree (TreapNode::val) with heap order (TreapNode::priority)
All operations run in expected O(logn) time

Each node in the tree sotres an item, a left and right pointer, and a priority that is randomly assigned when the node is created.
A treap is a binary search tree with the property that the node priorities satisfy heap order:
Any node's priority must be at least as large as its parent's.

Insertion into the treap is smiple:
After an item is added as a leaf, we rotate it up the treap until its priority satisfies heap order.
It can be shown that the expected number of rotations is less than 2.
Deletion:
After the item to be deleted has been found, it can be deleted by increasing its priority to infinity and rotating down
through the path of low-priority children.
Once it is a leaf, it can be removed.

Note also that our implementation assumes that there are no duplicates; if this is not true, then the remove could fail.

See also CartesianTree.h, MinFirstBST.h
*/
class Treap
{
public:
	struct TreapNode
	{
		TreapNode(int val, int priority) : val(val), priority(priority), left(nullptr), right(nullptr), nullNode(false){}
		~TreapNode(){}
		int val;
		TreapNode * left;
		TreapNode * right;
		int priority;
		bool nullNode;//for PrintBinaryTree only (used in Treap, RedBlackTree, SplayTree, AATree)
	};
private:
	TreapNode * m_nullNode;
	TreapNode * m_root;
	UniformRandom m_randomNums;
public:
	Treap()
	{
		m_nullNode = new TreapNode(0, INT_MAX);
		m_nullNode->left = m_nullNode;
		m_nullNode->right = m_nullNode;
		m_nullNode->nullNode = true;//for PrintBinaryTree only
		m_root = m_nullNode;
	}
	Treap(const std::vector<int> & v)
	{
		m_nullNode = new TreapNode(0, INT_MAX);
		m_nullNode->left = m_nullNode;
		m_nullNode->right = m_nullNode;
		m_nullNode->nullNode = true;//for PrintBinaryTree only
		m_root = m_nullNode;
		int N = v.size();
		for (int i = 0; i < N; ++i)
			this->Insert(v[i]);
	}
	~Treap()
	{
		this->MakeEmpty();
		delete m_nullNode;
		m_nullNode = nullptr;
	}
	/*copy ctor: deep copy*/
	Treap(const Treap & rhs)
	{
		m_nullNode = new TreapNode(0, INT_MAX);
		m_nullNode->left = m_nullNode;
		m_nullNode->right = m_nullNode;
		m_nullNode->nullNode = true;//for PrintBinaryTree only
		m_root = this->cloneRecur(rhs.m_root);//only difference from ctor
	}
	/*copy ctor: move*/
	Treap(Treap && rhs) : m_root(rhs.m_root), m_nullNode(rhs.m_nullNode)
	{
		rhs.m_root = nullptr;
		rhs.m_nullNode = nullptr;
	}
	/*assignment: deep copy*/
	Treap & operator=(const Treap & rhs)
	{
		Treap copy = rhs;//copy ctor deep copy
		std::swap(*this, copy);
		return *this;
	}
	/*assignment: move*/
	Treap & operator=(Treap && rhs)
	{
		std::swap(m_root, rhs.m_root);
		std::swap(m_nullNode, rhs.m_nullNode);
		return *this;
	}


	const int & FindMin() const//find the leftmost node
	{
		if (this->IsEmpty())
			throw std::runtime_error("");
		TreapNode * LmostNode = m_root;
		while (LmostNode->left != m_nullNode)
			LmostNode = LmostNode->left;
		std::cout << "Treap FindMin: " << LmostNode->val << std::endl;
		return LmostNode->val;
	}
	const int & FindMax() const//find the rightmost node
	{
		if (this->IsEmpty())
			throw std::runtime_error("");
		TreapNode * RmostNode = m_root;
		while (RmostNode->right != m_nullNode)
			RmostNode = RmostNode->right;
		std::cout << "Treap FindMax: " << RmostNode->val << std::endl;
		return RmostNode->val;
	}
	bool Contains(const int & val) const
	{
		TreapNode * curNode = m_root;
		m_nullNode->val = val;
		while (true)
		{
			if (val < curNode->val)
				curNode = curNode->left;
			else if (val > curNode->val)
				curNode = curNode->right;
			else//val == curNode->val
			{
				bool res = curNode != m_nullNode ? true : false;
				std::cout << "Treap Contains \"" << val << "\": " << res << std::endl;
				return res;
			}
		}
	}
	bool IsEmpty() const
	{
		return m_root == m_nullNode;
	}
	void MakeEmpty()
	{
		this->deleteTreapRecur(m_root);
	}
	void Insert(const int & val)
	{
		this->insertRecur(val, m_root);
		std::cout << "Treap Insert: " << val << std::endl;
	}
	void Remove(const int & val)
	{
		this->removeRecur(val, m_root);
		std::cout << "Treap Remove: " << val << std::endl;
	}
private:
	void insertRecur(const int & val, TreapNode *& root)
	{
		if (root == m_nullNode)//root's parent is a leaf node
		{
			root = new TreapNode(val, m_randomNums.nextInt(100));//create a new node with val and random priority
			root->left = m_nullNode;
			root->right = m_nullNode;
		}
		else if (val < root->val)
		{
			this->insertRecur(val, root->left);
			if (root->left->priority < root->priority)
				this->rotateWithLeftChild(root);
		}
		else if (val > root->val)
		{
			this->insertRecur(val, root->right);
			if (root->right->priority < root->priority)
				this->rotateWithRightChild(root);
		}
		//else duplicate; do nothing
	}
	void removeRecur(const int & val, TreapNode *& root)//not understood
	{
		if (root != m_nullNode)
		{
			if (val < root->val)
				this->removeRecur(val, root->left);
			else if (val > root->val)
				this->removeRecur(val, root->right);
			else//val == root->val
			{
				if (root->left->priority < root->right->priority)
					this->rotateWithLeftChild(root);//in this case, root->left != m_nullNode, after rotation, continue to removeRecur(val, root)
				else
					this->rotateWithRightChild(root);//in this case, root==m_nullNode, after rotation, the target node will become root->left, then delete root->left
				//?
				if (root != m_nullNode)
					this->removeRecur(val, root);
				else
				{
					delete root->left;
					root->left = m_nullNode;//at a leaf
				}
			}
		}
		//else root's parent is a leaf => cannot find; do nothing
	}
	void deleteTreapRecur(TreapNode *& t)
	{
		if (t != m_nullNode)
		{
			this->deleteTreapRecur(t->left);
			this->deleteTreapRecur(t->right);
			delete t;
			t = m_nullNode;
		}
	}

	/*
	rotate with left child: (V)
	      k2     k1       k2      k1
	     /         \     /          \
	   k1           right            k2
	     \                          /
	      right                right
	*/
	void rotateWithLeftChild(TreapNode *& k2)
	{
		TreapNode * k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2 = k1;
	}

	/*
	rotate with right child: )V(
	      k1      k1      k2      k2
	        \       \    /       /
	         k2      left      k1
	        /                    \
	    left                      left
	*/
	void rotateWithRightChild(TreapNode *& k1)
	{
		TreapNode * k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;
		k1 = k2;
	}
	TreapNode * cloneRecur(TreapNode * t) const
	{
		if (t == t->left)//cannot test against nullNode!
			return m_nullNode;
		else
		{
			TreapNode * c = new TreapNode(t->val, t->priority);
			c->left = this->cloneRecur(t->left);
			c->right = this->cloneRecur(t->right);
			return c;
		}
	}
public:
	void Print()
	{
		std::ostringstream oss;
		oss << "Treap (val2: priority of heap order):" << std::endl;
		PrintBinaryTree<TreapNode, std::ostringstream>(m_root, oss);
		std::cout << oss.str() << std::endl;
	}
};

template<>
std::string PrintBinaryTree<Treap::TreapNode, std::ostringstream>::selectVal2(int depth, Treap::TreapNode * n)
{
	return std::to_string(n->priority);
}
template<>
Treap::TreapNode * PrintBinaryTree<Treap::TreapNode, std::ostringstream>::getLeft(Treap::TreapNode * n)
{
	if (n->left->nullNode)
		return nullptr;
	else
		return n->left;
}
template<>
Treap::TreapNode * PrintBinaryTree<Treap::TreapNode, std::ostringstream>::getRight(Treap::TreapNode * n)
{
	if (n->right->nullNode)
		return nullptr;
	else
		return n->right;
}
/*
Treap Insert: 4
Treap Insert: 3
Treap Insert: 5
Treap Insert: 7
Treap Insert: 8
Treap Insert: 10
Treap Insert: 15
Treap Insert: 13
Treap Insert: 18
Treap Insert: 17
Treap (val2: priority of heap order):
                              
                              16
                ______________ 8______________
               /                               \
              21                              16
        ______ 7______                  ______17______
       /               \               /               \
      27               X              20              58
    __ 3__          __ N__          __13__          __18__
   /       \       /       \       /       \       /       \
   X      59       X       X      74      87       X       X
   N       5       N       N      10      15       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X  67   X   X   X   X   X   X   X   X   X   X   X   X   X
 N   N   4   N   N   N   N   N   N   N   N   N   N   N   N   N


Treap Contains "17": 1
Treap FindMax: 18
Treap FindMin: 3
Treap Remove: 5
Treap (val2: priority of heap order):
              
              16
        ______ 8______
       /               \
      21              16
    __ 7__          __17__
   /       \       /       \
  27       X      20      58
   3       N      13      18
 /   \   /   \   /   \   /   \
 X  67   X   X  74  87   X   X
 N   4   N   N  10  15   N   N


Treap Remove: 15
Treap (val2: priority of heap order):
              
              16
        ______ 8______
       /               \
      21              16
    __ 7__          __17__
   /       \       /       \
  27       X      20      58
   3       N      13      18
 /   \   /   \   /   \   /   \
 X  67   X   X  74   X   X   X
 N   4   N   N  10   N   N   N


Treap Remove: 4
Treap (val2: priority of heap order):
              
              16
        ______ 8______
       /               \
      21              16
    __ 7__          __17__
   /       \       /       \
  27       X      20      58
   3       N      13      18
 /   \   /   \   /   \   /   \
 X   X   X   X  74   X   X   X
 N   N   N   N  10   N   N   N


Treap Remove: 13
Treap (val2: priority of heap order):
      
      16
    __ 8__
   /       \
  21      16
   7      17
 /   \   /   \
27   X  74  58
 3   N  10  18


Treap Remove: 7
Treap (val2: priority of heap order):
      
      16
    __ 8__
   /       \
  27      16
   3      17
 /   \   /   \
 X   X  74  58
 N   N  10  18
*/
#endif