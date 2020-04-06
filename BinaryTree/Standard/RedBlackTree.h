#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H
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
http://www.geeksforgeeks.org/red-black-tree-set-1-introduction-2/
http://www.geeksforgeeks.org/red-black-tree-set-2-insert/
http://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/
http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/RedBlackTree.h
Red-Black Tree is a self-balancing Binary Search Tree where every node follows following rules:
1. every node has a color either red or black
2. root of tree is always black
3. there are no two adjacent red nodes
   (a red node cannot have a red parent or red child)
4. every path from root to a NULL node has same number of black nodes
(NULL node is considered as black)

The height of a Red Black Tree is always O(logn).

Compare with AVL Tree:
The AVL Trees are more balanced compared to Red Black Trees, but they may cause more rotations during insertion and deletion.
So if your application involves many frequent insertions and deletions, then Red Black Trees should be preferred.
And if the insertions and deletions are less frequent and search is more frequent, then AVL Trees should be preferred over Red Black Trees.

Every Red Black Tree with n nodes has height <= 2*log(n+1)

*/
class RedBlackTree
{
public:
	enum { RED = 0, BLACK = 1 };
	struct TreeNode
	{
		//NULL node is considered BLACK
		TreeNode(int val, int color = BLACK): val(val), color(color), left(nullptr), right(nullptr), nullNode(false){}
		~TreeNode(){}
		int val;
		TreeNode * left;
		TreeNode * right;
		int color;
		bool nullNode;//for PrintBinaryTree only (used in Treap, RedBlackTree, SplayTree, AATree)
	};
private:
	TreeNode * m_header;
	TreeNode * m_nullNode;

	/*used in Insert() (logically static)*/
	TreeNode * m_current;
	TreeNode * m_parent;
	TreeNode * m_grand;
	TreeNode * m_great;
public:
	explicit RedBlackTree(const int & negInf)
	{
		m_nullNode = new TreeNode(0);
		m_nullNode->left = m_nullNode->right = m_nullNode;
		m_nullNode->nullNode = true;//for PrintBinaryTree only

		m_header = new TreeNode(negInf);
		m_header->left = m_header->right = m_nullNode;
	}
	RedBlackTree(const int & negInf, const std::vector<int> & v)
	{
		m_nullNode = new TreeNode(0);
		m_nullNode->left = m_nullNode->right = m_nullNode;
		m_nullNode->nullNode = true;//for PrintBinaryTree only

		m_header = new TreeNode(negInf);
		m_header->left = m_header->right = m_nullNode;

		//now insert all vals from v
		int N = v.size();
		for (int i = 0; i < N; ++i)
			//this->Insert_TopDownIterate(v[i]);
			this->Insert_Recur(v[i]);
	}
	~RedBlackTree()
	{
		this->MakeEmpty();
		delete m_nullNode;
		m_nullNode = nullptr;
		delete m_header;
		m_header = nullptr;
	}
	//copy ctor: deep copy
	RedBlackTree(const RedBlackTree & rhs)
	{
		m_nullNode = new TreeNode(0);
		m_nullNode->left = m_nullNode->right = m_nullNode;
		m_nullNode->nullNode = true;//for PrintBinaryTree only

		m_header = new TreeNode(rhs.m_header->val);
		m_header->left = m_nullNode;
		m_header->right = this->cloneRecur(rhs.m_header->right);
	}
	//copy ctor: move
	RedBlackTree(RedBlackTree && rhs) : m_nullNode(rhs.m_nullNode), m_header(rhs.m_header)
	{
		rhs.m_nullNode = nullptr;
		rhs.m_header = nullptr;
	}
	//assignment: deep copy
	RedBlackTree & operator=(const RedBlackTree & rhs)
	{
		RedBlackTree copy = rhs;//copy ctor: deep copy
		std::swap(*this, copy);
		return *this;
	}
	//assignment: move
	RedBlackTree & operator=(RedBlackTree && rhs)
	{
		std::swap(m_header, rhs.m_header);
		std::swap(m_nullNode, rhs.m_nullNode);
		return *this;
	}

	bool IsEmpty() const
	{
		return m_header->right == m_nullNode;
	}
	void MakeEmpty()
	{
		if (m_header == nullptr)
			return;
		this->deleteTreeRecur(m_header->right);
		m_header->right = m_nullNode;
	}
	bool Contains(const int & val) const
	{
		m_nullNode->val = val;
		TreeNode * curNode = m_header->right;
		while (true)
		{
			if (val < curNode->val)
				curNode = curNode->left;
			else if (val > curNode->val)
				curNode = curNode->right;
			else
			{
				bool res = curNode != m_nullNode ? true : false;
				std::cout << "RedBlackTree Contains \"" << val << "\": " << res << std::endl;
				return res;
			}
		}
	}
	const int & FindMin() const
	{
		if (this->IsEmpty())
			throw std::runtime_error("");
		TreeNode * Lmost = m_header->right;
		while (Lmost->left != m_nullNode)
			Lmost = Lmost->left;
		return Lmost->val;
	}
	const int & FindMax() const
	{
		if (this->IsEmpty())
			throw std::runtime_error("");
		TreeNode * Rmost = m_header->right;
		while (Rmost->right != m_nullNode)
			Rmost = Rmost->right;
		return Rmost->val;
	}

	void Insert_Iterate(const int & val)
	{
		// initialization
		m_current = m_parent = m_grand = m_header;
		m_nullNode->val = val;

		while (m_current->val != val)
		{
			// move down one level
			m_great = m_grand; 
			m_grand = m_parent; 
			m_parent = m_current;
			m_current = val < m_current->val ? m_current->left : m_current->right;

			// Check if two red children; fix if so
			if (m_current->left->color == RED && m_current->right->color == RED)
				this->handleReorient_Insert(val);// (1)
		}

		// Insertion fails if already present
		if (m_current != m_nullNode)
			return;

		// else, current == nullNode, Insert x as a new node
		m_current = new TreeNode(val);
		m_current->left = m_nullNode;
		m_current->right = m_nullNode;

		// Attach to parent
		if (val < m_parent->val)
			m_parent->left = m_current;
		else
			m_parent->right = m_current;

		this->handleReorient_Insert(val);// (2)
		std::cout << "RedBlackTree Insert_Iterate: " << val << std::endl;
	}
	void Remove_TopDownIterate(const int & val)
	{
		//initialization
		m_current = m_parent = m_grand = m_header;
		m_nullNode->val = val;

		while (m_current->val != val)
		{
			//move down one level
			m_great = m_grand; 
			m_grand = m_parent; 
			m_parent = m_current;
			m_current = val < m_current->val ? m_current->left : m_current->right;

			this->handleReorient_Remove();
		}

		// Deletion fails if not found
		if (m_current == m_nullNode)
			return;
		else if (m_current->left != m_nullNode && m_current->right != m_nullNode)//case1: two children
		{
			TreeNode * replaced;
			replaced = m_current->right;
			while (replaced->left != m_nullNode)
			{
				replaced = replaced->left;
			}
			//now replaced points to the smallest node in the right subtree
			m_current->val = replaced->val;

			//replaced = replaced->right;

			TreeNode* oldNode = replaced;
			replaced = replaced->right;//true : false
			delete oldNode;
			oldNode = nullptr;
		}
		else if (m_current->right != m_nullNode && m_current->left == m_nullNode)//case2: only right child
		{
			TreeNode * replaced;
			replaced = m_current->right;
			while (replaced->left != m_nullNode)
			{
				replaced = replaced->left;
			}
			//now replaced points to the smallest node in the right subtree
			m_current->val = replaced->val;

			//replaced = replaced->right;
			TreeNode * oldNode = replaced;
			replaced = replaced->right;//true : false
			delete oldNode;
			oldNode = nullptr;
		}
		else if (m_current->left != m_nullNode && m_current->right == m_nullNode)//case3: only left child
		{
			TreeNode * replaced;
			replaced = m_current->left;
			while (replaced->right != m_nullNode)
			{
				replaced = replaced->right;
			}
			//now replaced points to the largest node in the left subtree
			m_current->val = replaced->val;

			//replaced = replaced->right;
			TreeNode * oldNode = replaced;
			replaced = replaced->right;//true : false
			delete oldNode;
			oldNode = nullptr;
		}
		else // current is a leaf
		{
			//current = current->right;
			TreeNode * oldNode = m_current;
			m_current = m_nullNode;//true : false
			delete oldNode;
			oldNode = nullptr;
		}
		this->handleReorient_Remove();
		std::cout << "RedBlackTree RemoveTopDownIterate: " << val << std::endl;
	}
private:
	/*
	called in Insert() 
	1. if current node has two red children, do the color flip
	2. mark the inserted node red
	*/
	void handleReorient_Insert(const int & val)
	{
		//do the color flip
		m_current->color = RED;
		m_current->left->color = BLACK;
		m_current->right->color = BLACK;

		if (m_parent->color == RED)//have to rotate
		{
			m_grand->color = RED;
			if (val < m_grand->val != val < m_parent->val)//val is in between grand and parent
				m_parent = this->rotate(val, m_grand);//rotate grand->left (if val<grand) or grand->right (if val>grand)  ==> double rotate, zig-zag rotate
			m_current = this->rotate(val, m_great);//rotate great->left (if val<great) or great->right (if val>great) ==> single rotate, zig rotate
			m_current->color = BLACK;
		}
		m_header->right->color = BLACK;//make root black
	}
	void handleReorient_Remove()
	{
		if (m_parent->color == RED && m_current->left->color == BLACK && m_current->right->color == BLACK) //caseI
		{
			if ((m_current == m_parent->left && m_parent->right->left->color == BLACK && m_parent->right->right->color == BLACK) ||
				(m_current == m_parent->right && m_parent->left->left->color == BLACK && m_parent->left->right->color == BLACK)) //case1: current's sibling has two black children, flip color
			{
				m_parent->color = BLACK;
				m_parent->left->color = RED;
				m_parent->right->color = RED;
			}
			else if (m_current == m_parent->left)//case2: current's sibling (parent->right) has one red child
			{
				if (m_parent->right->left->color == RED)//do zig-zag rotation
				{
					this->rightRotateWLeftChild(m_parent->right);
					m_parent->color = BLACK;
					m_current->color = RED;
					this->leftRotateWRightChild(m_parent);
				}
				else if (m_parent->right->right->color == RED)//do zig rotation
				{
					m_parent->color = BLACK;
					m_current->color = RED;
					m_parent->right->color = RED;
					m_parent->right->right->color = BLACK;
					this->leftRotateWRightChild(m_parent);
				}
			}
			else if (m_current == m_parent->right)//case3: current's sibling (parent->left) has one red child
			{
				if (m_parent->left->left->color == RED)//do zig rotation
				{
					m_parent->color = BLACK;
					m_current->color = RED;
					m_parent->left->color = RED;
					m_parent->left->left->color = BLACK;
					this->rightRotateWLeftChild(m_parent);
				}
				else if (m_parent->left->right->color == RED)//do zig-zag rotation
				{
					this->leftRotateWRightChild(m_parent->left);
					m_parent->color = BLACK;
					m_current->color = RED;
					this->rightRotateWLeftChild(m_parent);
				}
			}
		}
		else//caseII, do nothing
		{

		}
	}
	/*
	called in handleReorient()
	*/
	TreeNode * rotate(const int & val, TreeNode * parent)
	{
		if (val < parent->val)//rotate parent->left
		{
			val < parent->left->val ?
				this->rightRotateWLeftChild(parent->left) :
				this->leftRotateWRightChild(parent->left);
			return parent->left;
		}
		else//rotate parent->right
		{
			val < parent->right->val ?
				this->rightRotateWLeftChild(parent->right) :
				this->leftRotateWRightChild(parent->right);
			return parent->right;
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
	void rightRotateWLeftChild(TreeNode *& k2)
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
	void leftRotateWRightChild(TreeNode *& k1)
	{
		TreeNode * k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;
		k1 = k2;
	}
	TreeNode * cloneRecur(TreeNode * n) const
	{
		if (n == n->left)//cannot test against nullNode!
			return m_nullNode;
		else
		{
			TreeNode * c = new TreeNode(n->val, n->color);
			c->left = this->cloneRecur(n->left);
			c->right = this->cloneRecur(n->right);
			return c;
		}
	}
	void deleteTreeRecur(TreeNode * n)
	{
		if (n != n->left)
		{
			this->deleteTreeRecur(n->left);
			this->deleteTreeRecur(n->right);
			delete n;
			n = nullptr;
		}
	}

	
public:
	void Insert_Recur(const int & val)
	{
		m_current = m_parent = m_grand = m_header;
		m_nullNode->val = val;
		this->insert_Recur(val, m_header->right);
		std::cout << "RedBlackTree Insert_Recur: " << val << std::endl;
	}
private:
	/*
	The main property that violates after insertion is two consecutive reds.

	*/
	void insert_Recur(const int & val, TreeNode *& t)
	{
		TreeNode * theParent;
		TreeNode * theGrandParent;
		TreeNode * theGreatParent;
		TreeNode * theCurrent;
		
		//temporarily save these nodes in each level
		theCurrent = m_current = t;
		theParent = m_parent;
		theGrandParent = m_grand;
		theGreatParent = m_great;

		if (val != m_current->val)
		{
			if (m_current->left->color == RED && m_current->right->color == RED)
				this->handleReorient_Insert(val);//(1)

			if (val < m_current->val)
			{
				//move down
				m_great = m_grand;
				m_grand = m_parent;
				m_parent = m_current;
				this->insert_Recur(val, m_current->left);
				//restore nodes
				m_great = theGreatParent;
				m_grand = theGrandParent;
				m_parent = theParent;
				m_current = theCurrent;
			}
			else
			{
				//move down
				m_great = m_grand;
				m_grand = m_parent;
				m_parent = m_current;
				this->insert_Recur(val, m_current->right);
				//restore nodes
				m_great = theGreatParent;
				m_grand = theGrandParent;
				m_parent = theParent;
				m_current = theCurrent;
			}
		}

		else//position found, do the insertion
		{
			if (m_current != m_nullNode)//already exists (duplication); do nothing
				return;
			else//m_current == m_nullNode
			{
				m_current = new TreeNode(val);
				m_current->left = m_nullNode;
				m_current->right = m_nullNode;
				if (val < m_parent->val)
					m_parent->left = m_current;
				else
					m_parent->right = m_current;
				this->handleReorient_Insert(val);//(2)
			}
		}
	}
public:
	void Remove_ButtomUpRecur(const int & val)
	{
		this->removeButtomUpRecur(val, m_header->right);
		std::cout << "RedBlackTree RemoveButtomUpRecur: " << val << std::endl;
	}
private:
	void removeButtomUpRecur(const int & val, TreeNode *& t)
	{

	}

public:
	void Print()
	{
		std::ostringstream oss;
		oss << "RedBlackTree (val2: color):" << std::endl;
		PrintBinaryTree<TreeNode, std::ostringstream>(m_header, oss);
		std::cout << oss.str() << std::endl;
	}
};

template<>
std::string PrintBinaryTree<RedBlackTree::TreeNode, std::ostringstream>::selectVal2(int depth, RedBlackTree::TreeNode * n)
{
	switch (n->color)
	{
	case 0:
		return std::string("R");
	case 1:
		return std::string("B");
	default:
		return std::string();
	}
}
template<>
RedBlackTree::TreeNode * PrintBinaryTree<RedBlackTree::TreeNode, std::ostringstream>::getLeft(RedBlackTree::TreeNode * n)
{
	if (n->left->nullNode)
		return nullptr;
	else
		return n->left;
}
template<>
RedBlackTree::TreeNode * PrintBinaryTree<RedBlackTree::TreeNode, std::ostringstream>::getRight(RedBlackTree::TreeNode * n)
{
	if (n->right->nullNode)
		return nullptr;
	else
		return n->right;
}
#endif