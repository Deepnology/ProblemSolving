#ifndef AVL_TREE_H
#define AVL_TREE_H
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
http://www.geeksforgeeks.org/avl-tree-set-1-insertion/
http://www.geeksforgeeks.org/avl-tree-set-2-deletion/
http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/AvlTree.h

AVLTree:
a binary search tree with balance condition (no node is allowed to get too deep)
which ensures the depth of the tree is O(logn).

Balance condition:
for every node in the tree, the height of the left and right subtree can differ by at most 1.
(the height of an empty tree is defined to be -1; the leaf node has height 0)

Balance rotation is performed in each recursion call of insertion and remove.

The AVL Trees are more balanced compared to Red Black Trees, but they may cause more rotations during insertion and deletion.
So if your application involves many frequent insertions and deletions, then Red Black Trees should be preferred.
And if the insertions and deletions are less frequent and search is more frequent, then AVL Trees should be preferred over Red Black Trees.

Insert/Delete: O(height) = O(logn) time

see also BinarySearchTree.h, RedBlackTree.h

*/
class AVLTree
{
public:
	struct TreeNode
	{
		TreeNode(const int & val, int height = 0) : val(val), height(height), left(nullptr), right(nullptr){}
		TreeNode(int && val, int height = 0) : val(std::move(val)), height(height), left(nullptr), right(nullptr){}
		~TreeNode(){}
		int val;
		TreeNode * left;
		TreeNode * right;
		int height;//0 for leaf node
	};
private:
	TreeNode * m_root;
public:
	AVLTree() : m_root(nullptr){}
	AVLTree(const std::vector<int> & v) : m_root(nullptr)
	{
		int N = v.size();
		for (int i = 0; i < N; ++i)
			this->Insert(v[i]);
	}
	~AVLTree()
	{
		this->MakeEmpty();
	}
	//copy ctor: deep copy
	AVLTree(const AVLTree & rhs) : m_root(nullptr)
	{
		m_root = this->cloneRecur(rhs.m_root);
	}
	//copy ctor: move
	AVLTree(AVLTree && rhs) : m_root(rhs.m_root)
	{
		rhs.m_root = nullptr;
	}
	//assignment: deep copy
	AVLTree & operator=(const AVLTree & rhs)
	{
		AVLTree copy = rhs;//copy ctor: deep copy
		std::swap(*this, copy);
		return *this;
	}
	//assignment: move
	AVLTree & operator=(AVLTree && rhs)
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
	}
	void Insert(const int & val)
	{
		this->insertRecur(val, m_root);
		std::cout << "AVLTree Insert: " << val << std::endl;
	}
	void Insert(int && val)
	{
		this->insertRecur(std::move(val), m_root);
	}
	void Remove(const int & val)
	{
		this->removeRecur(val, m_root);
		std::cout << "AVLTree Remove: " << val << std::endl;
	}
	int FindMin() const
	{
		if (this->IsEmpty())
			throw std::runtime_error("");
		int min = this->findMinRecur(m_root)->val;
		std::cout << "AVLTree FindMin: " << min << std::endl;
		return min;
	}
	int FindMax() const
	{
		if (this->IsEmpty())
			throw std::runtime_error("");
		int max = this->findMaxRecur(m_root)->val;
		std::cout << "AVLTree FindMax: " << max << std::endl;
		return max;
	}
	bool Contains(const int & val) const
	{
		bool res = this->containsRecur(val, m_root);
		std::cout << "AVLTree Contains \"" << val << "\": " << res << std::endl;
		return res;
	}
private:
	/*
	main diff methods from BinarySearchTree:
	height, rightRotateWLeftChild, leftRotateWRightChild, doubleRotateWLeftChild, doubleRotateWRightChild, balance
	*/
	int height(TreeNode * n) const //-1 for NULL, 0 for leaf node
	{
		return n == nullptr ? -1 : n->height;
	}
	/*
	right rotate (k2)

	         k2                k1
	        /  \              /  \
	      k1    T3	  -->   T1    k2
	     /  \                    /  \
	   T1    T2                T2    T3

	for the Left Left case: height(k1) > height(T3) && heihgt(T1) >= height(T2)

        	    k2                   k1
	           /  \                /    \
	         k1    T3	  -->   t1        k2
	        /  \               /  \      /  \
	      t1    T2           t2    t3  T2    T3
	     /  \
	   t2    t3

	simplified right rotate diagram: (V)

		  k2     k1       k2      k1
	     /         \     /          \
	   k1           right            k2
	     \                          /
	      right                right
	*/
	void rightRotateWLeftChild(TreeNode *& k2)
	{
		TreeNode * k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = std::max(this->height(k2->left), this->height(k2->right)) + 1;
		k1->height = std::max(this->height(k1->left), k2->height) + 1;
		k2 = k1;
	}
	/*
	left rotate (k1)

	      k1                  k2
	     /  \                /  \
	   T1    k2	    -->    k1    T3
	        /  \          /  \
	      T2    T3      T1    T2

	for the Right Right case: height(T1) < height(k2) && height(T2) <= height(T3)

	         k1                     k2
	        /  \                  /    \
	      T1    k2	    -->    k1        t1
	           /  \           /  \      /  \
	         T2    t1       T1    T2  t2    t3
			      /  \
				t2    t3

	simiplified left rotate diagram: )V(

		  k1      k1      k2      k2
	        \       \    /       /
	         k2      left      k1
	        /                    \
	    left                      left
	*/
	void leftRotateWRightChild(TreeNode *& k1)
	{
		TreeNode * k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;
		k1->height = std::max(this->height(k1->left), this->height(k1->right)) + 1;
		k2->height = std::max(this->height(k2->left), k1->height) + 1;
		k1 = k2;
	}
	/*
	left rotate (k1) and right rotate (k2)
	for the Left Right case: height(k1) > height(T3) && heihgt(T1) < height(T2)

	            k2               k2                   t1
	           /  \             /  \                /    \
	         k1    T3	-->   t1    T3    -->    k1        k2
	        /  \             /  \               /  \      /  \
	      T1    t1         k1    t3           T1    t2  t3    T3
	           /  \       /  \
	         t2    t3   T1    t2

	simplified right double rotate diagram:

		  k3             k3         k2
	     /              /          /  \
	   k1             k2         k1    k3
	     \           /             \   
	      k2       k1               left
		 /           \
	 left             left
	*/
	void doubleRotateWLeftChild(TreeNode *& k3)
	{
		this->leftRotateWRightChild(k3->left);
		this->rightRotateWLeftChild(k3);
	}
	/*
	right rotate (k2) and left rotate (k1)
	for the Right Left case: height(T1) < height(k2) && heihgt(T2) > height(T3)

	       k1                k1                         t1
	      /  \              /  \                      /    \
	    T1    k2 	-->   T1    t1       -->       k1        k2
	         /  \              /  \               /  \      /  \
	       t1    T3          t2    k2           T1    t2  t3    T3
	      /  \                    /  \
	    t2    t3                t3    T3

	simplified left double rotate diagram:

		  k3         k3             k1
	        \          \           /  \
	         k2         k1       k3    k2
	        /             \           /   
	      k1               k2    right
		    \             /
	         right   right
	*/
	void doubleRotateWRightChild(TreeNode *& k1)
	{
		this->rightRotateWLeftChild(k1->right);
		this->leftRotateWRightChild(k1);
	}

	static const int ALLOWED_IMBALANCE = 1;
	void balance(TreeNode *& n)
	{
		if (n == nullptr)
			return;
		if (this->height(n->left) - this->height(n->right) > ALLOWED_IMBALANCE)
			if (this->height(n->left->left) >= this->height(n->left->right))
				this->rightRotateWLeftChild(n);
			else
				this->doubleRotateWLeftChild(n);
		else if (this->height(n->right) - this->height(n->left) > ALLOWED_IMBALANCE)
			if (this->height(n->right->right) >= this->height(n->right->left))
				this->leftRotateWRightChild(n);
			else
				this->doubleRotateWRightChild(n);

		n->height = std::max(this->height(n->left), this->height(n->right)) + 1;
	}
	/*end*/

	void insertRecur(const int & val, TreeNode *& n)
	{
		if (n == nullptr)
			n = new TreeNode(val);
		else if (val < n->val)
			this->insertRecur(val, n->left);
		else if (val > n->val)
			this->insertRecur(val, n->right);

		this->balance(n);
	}
	void insertRecur(int && val, TreeNode *& n)
	{
		if (n == nullptr)
			n = new TreeNode(std::move(val));
		else if (val < n->val)
			this->insertRecur(std::move(val), n->left);
		else if (val > n->val)
			this->insertRecur(std::move(val), n->right);

		this->balance(n);
	}
	void removeRecur(const int & val, TreeNode *& n)
	{
		if (n == nullptr)
			return;
		if (val < n->val)
			this->removeRecur(val, n->left);
		else if (val > n->val)
			this->removeRecur(val, n->right);
		else
		{
			if (n->left != nullptr && n->right != nullptr)//two children
			{
				n->val = this->findMinRecur(n->right)->val;
				this->removeRecur(n->val, n->right);
			}
			else//1 or 0 child
			{
				TreeNode * oldNode = n;
				n = n->left != nullptr ? n->left : n->right;
				delete oldNode;
				oldNode = nullptr;
			}
		}
		this->balance(n);
	}
	TreeNode * findMinRecur(TreeNode * n) const
	{
		if (n == nullptr)
			return nullptr;
		if (n->left == nullptr)
			return n;
		return this->findMinRecur(n->left);
	}
	TreeNode * findMaxRecur(TreeNode * n) const
	{
		if (n == nullptr)
			return nullptr;
		if (n->right == nullptr)
			return n;
		return this->findMaxRecur(n->right);
	}
	TreeNode * findMinIterate(TreeNode * n) const
	{
		if (n != nullptr)
			while (n->left != nullptr)
				n = n->left;
		return n;
	}
	TreeNode * findMaxIterate(TreeNode * n) const
	{
		if (n != nullptr)
			while (n->right != nullptr)
				n = n->right;
		return n;
	}
	bool containsRecur(const int & val, TreeNode * n) const
	{
		if (n == nullptr)
			return false;
		else if (val < n->val)
			return this->containsRecur(val, n->left);
		else if (val > n->val)
			return this->containsRecur(val, n->right);
		else
			return true;
	}
	bool containsIterate(const int & val, TreeNode * n) const
	{
		while (n != nullptr)
			if (val < n->val)
				n = n->left;
			else if (val > n->val)
				n = n->right;
			else 
				return true;
		
		return false;
	}


	TreeNode * cloneRecur(TreeNode * n) const
	{
		if (n == nullptr)
			return nullptr;
		else
		{
			TreeNode * c = new TreeNode(n->val, n->height);
			c->left = this->cloneRecur(n->left);
			c->right = this->cloneRecur(n->right);
			return c;
		}
	}
	void deleteTreeRecur(TreeNode *& n)
	{
		if (n != nullptr)
		{
			this->deleteTreeRecur(n->left);
			this->deleteTreeRecur(n->right);
			delete n;
			n = nullptr;
		}
	}
public:
	void Print()
	{
		std::ostringstream oss;
		oss << "AVLTree (val2: height):" << std::endl;
		PrintBinaryTree<TreeNode, std::ostringstream>(m_root, oss);
		std::cout << oss.str() << std::endl;
	}
};

template<>
std::string PrintBinaryTree<AVLTree::TreeNode, std::ostringstream>::selectVal2(int depth, AVLTree::TreeNode * n)
{
	return std::to_string(n->height);
}
/*
AVLTree Insert: 10
AVLTree Insert: 85
AVLTree Insert: 15
AVLTree Insert: 70
AVLTree Insert: 20
AVLTree Insert: 60
AVLTree Insert: 30
AVLTree Insert: 50
AVLTree Insert: 65
AVLTree Insert: 80
AVLTree Insert: 90
AVLTree Insert: 40
AVLTree Insert: 5
AVLTree Insert: 55
AVLTree (val2: height):
                              
                               4
                ______________60______________
               /                               \
               3                               2
        ______20______                  ______70______
       /               \               /               \
       1               2               0               1
    __10__          __40__          __65__          __85__
   /       \       /       \       /       \       /       \
   0       0       0       1       X       X       0       0
   5      15      30      50       N       N      80      90
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   0   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   N  55   N   N   N   N   N   N   N   N


AVLTree FindMax: 90
AVLTree FindMin: 5
AVLTree Remove: 50
AVLTree (val2: height):
              
               3
        ______60______
       /               \
       2               2
    __20__          __70__
   /       \       /       \
   1       1       0       1
  10      40      65      85
 /   \   /   \   /   \   /   \
 0   0   0   0   X   X   0   0
 5  15  30  55   N   N  80  90

*/
#endif