#ifndef AA_TREE_H
#define AA_TREE_H
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
http://users.cis.fiu.edu/~weiss/dsaa_c++3/code/AATree.h
AA tree is a variation of red-black tree, a balanced BST that support efficient insertion and deletion.
*/
class AATree
{
public:
	struct TreeNode
	{
		TreeNode() : left(nullptr), right(nullptr), level(1), nullNode(false){}
		TreeNode(const int & val, int level = 1) : val(val), level(level), left(nullptr), right(nullptr), nullNode(false){}
		TreeNode(int && val, int level = 1) : val(std::move(val)), level(level), left(nullptr), right(nullptr), nullNode(false){}
		~TreeNode(){}
		int val;
		TreeNode * left;
		TreeNode * right;
		int level;
		bool nullNode;//for PrintBinaryTree only (used in Treap, RedBlackTree, SplayTree, AATree)
	};
private:
	TreeNode * m_root;
	TreeNode * m_nullNode;
public:
	AATree()
	{
		m_nullNode = new TreeNode;
		m_nullNode->left = m_nullNode;
		m_nullNode->right = m_nullNode;
		m_nullNode->level = 0;
		m_nullNode->nullNode = true;//for PrintBinaryTree only
		m_root = m_nullNode;
	}
	AATree(const std::vector<int> & v)
	{
		m_nullNode = new TreeNode;
		m_nullNode->left = m_nullNode;
		m_nullNode->right = m_nullNode;
		m_nullNode->level = 0;
		m_nullNode->nullNode = true;//for PrintBinaryTree only
		m_root = m_nullNode;

		int N = v.size();
		for (int i = 0; i < N; ++i)
			this->Insert(v[i]);
	}
	~AATree()
	{
		this->MakeEmpty();
		delete m_nullNode;
	}
	//copy ctor: deep copy
	AATree(const AATree & rhs)
	{
		m_nullNode = new TreeNode;
		m_nullNode->left = m_nullNode;
		m_nullNode->right = m_nullNode;
		m_nullNode->level = 0;
		m_nullNode->nullNode = true;//for PrintBinaryTree only
		m_root = this->cloneRecur(rhs.m_root);
	}
	//assignment: deep copy
	AATree & operator=(const AATree & rhs)
	{
		AATree copy = rhs;//copy ctor: deep copy
		std::swap(*this, copy);
		return *this;
	}

	bool IsEmpty() const
	{
		return m_root == m_nullNode;
	}
	void MakeEmpty()
	{
		this->deleteTreeRecur(m_root);
	}
	void Insert(const int & val)
	{
		this->insertRecur(val, m_root);
		std::cout << "AATree Insert: " << val << std::endl;
	}
	void Remove(const int & val)
	{
		this->removeRecur(val, m_root);
		std::cout << "AATree Remove: " << val << std::endl;
	}
	bool Contains(const int & val) const
	{
		TreeNode * curNode = m_root;
		m_nullNode->val = val;
		while (true)
		{
			if (val < curNode->val)
				curNode = curNode->left;
			else if (val > curNode->val)
				curNode = curNode->right;
			else
			{
				bool res = curNode != m_nullNode ? true : false;
				std::cout << "AATree Contains \"" << val << "\": " << res << std::endl;
				return res;
			}
		}
	}
	const int & FindMin() const
	{
		if (this->IsEmpty())
			throw std::runtime_error("");
		TreeNode * Lmost = m_root;
		while (Lmost->left != m_nullNode)
			Lmost = Lmost->left;
		std::cout << "AATree FindMin: " << Lmost->val << std::endl;
		return Lmost->val;
	}
	const int & FindMax() const
	{
		if (this->IsEmpty())
			throw std::runtime_error("");
		TreeNode * Rmost = m_root;
		while (Rmost->right != m_nullNode)
			Rmost = Rmost->right;
		std::cout << "AATree FindMax: " << Rmost->val << std::endl;
		return Rmost->val;
	}

private:
	void skew(TreeNode *& n)
	{
		if (n->left->level == n->level)
			this->rotateWithLeftChild(n);
	}
	void split(TreeNode *& n)
	{
		if (n->right->right->level == n->level)
		{
			this->rotateWithRightChild(n);
			++n->level;
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
	void rotateWithLeftChild(TreeNode *& k2)
	{
		TreeNode * k1 = k2->left;
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
	void rotateWithRightChild(TreeNode *& k1)
	{
		TreeNode * k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;
		k1 = k2;
	}

	void insertRecur(const int & val, TreeNode *& n)
	{
		if (n == m_nullNode)
		{
			n = new TreeNode(val);
			n->left = m_nullNode;
			n->right = m_nullNode;
		}
		else if (val < n->val)
			this->insertRecur(val, n->left);
		else if (val > n->val)
			this->insertRecur(val, n->right);
		else
			return;//duplicate, do nothing

		this->skew(n);
		this->split(n);
	}
	void removeRecur(const int & val, TreeNode *& n)
	{
		static TreeNode * lastNode = m_nullNode;
		static TreeNode * deletedNode = m_nullNode;

		if (n != m_nullNode)
		{
			//1. search down the tree and set lastNode and deletedNode
			lastNode = n;
			if (val < n->val)
				this->removeRecur(val, n->left);
			else
			{
				deletedNode = n;
				this->removeRecur(val, n->right);
			}

			//2. if at the bottom of the tree and val is present, remove it
			if (n == lastNode)
			{
				if (deletedNode == m_nullNode || val != deletedNode->val)
					return;//item not found, do nothing
				deletedNode->val = n->val;
				deletedNode = m_nullNode;
				n = n->right;
				delete lastNode;
			}

			//3. otherwise, we are not at the bottom; rebalance
			else
			{
				if (n->left->level < n->level - 1 ||
					n->right->level < n->level - 1)
				{
					if (n->right->level > --n->level)
						n->right->level = n->level;

					this->skew(n);
					this->skew(n->right);
					this->skew(n->right->right);
					this->split(n);
					this->split(n->right);
				}
			}
		}
	}


	void deleteTreeRecur(TreeNode *& n)
	{
		if (n != m_nullNode)
		{
			this->deleteTreeRecur(n->left);
			this->deleteTreeRecur(n->right);
			delete n;
			n = m_nullNode;
		}
	}
	TreeNode * cloneRecur(TreeNode * n) const
	{
		if (n == n->left)//cannot test against nullNode!
			return m_nullNode;
		else
		{
			TreeNode * c = new TreeNode(n->val, n->level);
			c->left = this->cloneRecur(n->left);
			c->right = this->cloneRecur(n->right);
			return c;
		}
	}
public:
	void Print()
	{
		std::ostringstream oss;
		oss << "AATree (val2: level)" << std::endl;
		PrintBinaryTree<TreeNode, std::ostringstream>(m_root, oss);
		std::cout << oss.str() << std::endl;
	}
};

template<>
AATree::TreeNode * PrintBinaryTree<AATree::TreeNode, std::ostringstream>::getLeft(AATree::TreeNode * n)
{
	if (n->left->nullNode)
		return nullptr;
	else
		return n->left;
}
template<>
AATree::TreeNode * PrintBinaryTree<AATree::TreeNode, std::ostringstream>::getRight(AATree::TreeNode * n)
{
	if (n->right->nullNode)
		return nullptr;
	else
		return n->right;
}
template<>
std::string PrintBinaryTree<AATree::TreeNode, std::ostringstream>::selectVal2(int depth, AATree::TreeNode * n)
{
	return std::to_string(n->level);
}
/*
AATree Insert: 10
AATree Insert: 85
AATree Insert: 15
AATree Insert: 70
AATree Insert: 20
AATree Insert: 60
AATree Insert: 30
AATree Insert: 50
AATree Insert: 65
AATree Insert: 80
AATree Insert: 90
AATree Insert: 40
AATree (val2: level)
                              
                               3
                ______________30______________
               /                               \
               2                               3
        ______15______                  ______70______
       /               \               /               \
       1               1               2               2
    __10__          __20__          __60__          __85__
   /       \       /       \       /       \       /       \
   X       X       X       X       1       1       1       1
   N       N       N       N      40      65      80      90
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   1   X   X   X   X   X   X
 N   N   N   N   N   N   N   N   N  50   N   N   N   N   N   N


AATree FindMax: 90
AATree FindMin: 10
AATree Remove: 50
AATree (val2: level)
              
               3
        ______30______
       /               \
       2               3
    __15__          __70__
   /       \       /       \
   1       1       2       2
  10      20      60      85
 /   \   /   \   /   \   /   \
 X   X   X   X   1   1   1   1
 N   N   N   N  40  65  80  90

*/
#endif