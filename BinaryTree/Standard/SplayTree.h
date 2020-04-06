#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H
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
http://www.geeksforgeeks.org/splay-tree-set-1-insert/
http://www.geeksforgeeks.org/splay-tree-set-2-insert-delete/
http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/SplayTree.h
Chapter 4.5, 11.5, 12.1
Like AVL and Red Black Trees, Splay Tree is also self-balancing BST.
The main idea of splay tree is to bring the recently accessed item to root of the tree, this makes the recently searched item to be accessible in O(1) time if accessed again.
The idea is to use locality of reference.
(In a typical application, 80% of the access are to 20% of the items).

All splay tree operations run in O(logn) time on average, where n is the number of entires in the tree.
Any single operation can take Theta(n) time in the worst case.

Splay trees are simpler compared to AVL Trees and Red Black Trees as no extra field is required in tree node.
Unlike AVL Trees, splay trees can change even with read-only operations like search.

Splay(val, root): move the node whose value is closest to val to root, and rotate the whole tree accordingly to preserve BST property.
SplayRecur: buttom up
SplayIterate: top down
*/
class SplayTree
{
public:
	struct TreeNode
	{
		TreeNode() : left(nullptr), right(nullptr), nullNode(false){}
		TreeNode(const int & val) : val(val), left(nullptr), right(nullptr), nullNode(false){}
		TreeNode(int && val) : val(std::move(val)), left(nullptr), right(nullptr), nullNode(false){}
		~TreeNode(){}
		int val;
		TreeNode * left;
		TreeNode * right;
		bool nullNode;//for PrintBinaryTree only (used in Treap, RedBlackTree, SplayTree, AATree)
	};
private:
	TreeNode * m_root;
	TreeNode * m_nullNode;
public:
	SplayTree()
	{
		m_nullNode = new TreeNode;
		m_nullNode->left = m_nullNode;
		m_nullNode->right = m_nullNode;
		m_nullNode->nullNode = true;//for PrintBinaryTree only
		m_root = m_nullNode;
	}
	SplayTree(const std::vector<int> & v)
	{
		m_nullNode = new TreeNode;
		m_nullNode->left = m_nullNode;
		m_nullNode->right = m_nullNode;
		m_nullNode->nullNode = true;//for PrintBinaryTree only
		m_root = m_nullNode;

		int N = v.size();
		for (int i = 0; i < N; ++i)
			this->Insert(v[i]);
	}
	~SplayTree()
	{
		this->MakeEmptyRecur();
		delete m_nullNode;
		m_nullNode = nullptr;
	}
	//copy ctor: deep copy
	SplayTree(const SplayTree & rhs)
	{
		m_nullNode = new TreeNode;
		m_nullNode->left = m_nullNode;
		m_nullNode->right = m_nullNode;
		m_nullNode->nullNode = true;//for PrintBinaryTree only
		m_root = this->cloneRecur(rhs.m_root);
	}
	//copy ctor: move
	SplayTree(SplayTree && rhs) : m_root(rhs.m_root), m_nullNode(rhs.m_nullNode)
	{
		rhs.m_root = nullptr;
		rhs.m_nullNode = nullptr;
	}
	//assignment: deep copy
	SplayTree & operator=(const SplayTree & rhs)
	{
		SplayTree copy = rhs;
		std::swap(*this, copy);
		return *this;
	}
	//assignment: move
	SplayTree & operator=(SplayTree && rhs)
	{
		std::swap(m_root, rhs.m_root);
		std::swap(m_nullNode, rhs.m_nullNode);
		return *this;
	}


	bool IsEmpty() const
	{
		return m_root == m_nullNode;
	}
	void MakeEmptyRecur()
	{
		this->deleteTreeRecur(m_root);
		m_root = m_nullNode;
	}
	void MakeEmptyIterate()
	{
		while (!this->IsEmpty())
		{
			this->FindMax();//splay max item to root
			this->Remove(m_root->val);
		}
	}
	bool Contains(const int & val)
	{
		if (this->IsEmpty())
			return false;
		//1. Move the closest node to root and rotate the whole tree accordingly
		this->splayRecur(val, m_root);
		//2. Check if root's val equal to target
		bool res = m_root->val == val ? true : false;
		std::cout << "SplayTree Contains \"" << val << "\": " << res << std::endl;
		return res;
	}
	const int & FindMax()
	{
		if (this->IsEmpty())
			throw std::runtime_error("");
		//1. Find Rmost
		TreeNode * Rmost = m_root;
		while (Rmost->right != m_nullNode)
			Rmost = Rmost->right;
		//2. Move Rmost to root and rotate the whole tree accordingly
		this->splayRecur(Rmost->val, m_root);
		std::cout << "SplayTree FindMax: " << Rmost->val << std::endl;
		return Rmost->val;
	}
	const int & FindMin()
	{
		if (this->IsEmpty())
			throw std::runtime_error("");
		//1. Find Lmost
		TreeNode * Lmost = m_root;
		while (Lmost->left != m_nullNode)
			Lmost = Lmost->left;
		//2. Move Lmost to root and rotate the whole tree accordingly
		this->splayRecur(Lmost->val, m_root);
		std::cout << "SplayTree FindMin: " << Lmost->val << std::endl;
		return Lmost->val;
	}
	void Insert(const int & val)
	{
		std::cout << "SplayTree Insert: " << val << std::endl;
		if (m_root == m_nullNode)
		{
			TreeNode * newNode = new TreeNode(val);
			newNode->left = m_nullNode;
			newNode->right = m_nullNode;
			m_root = newNode;
		}
		else
		{
			//1. move the closest node to root and rotate the whole tree accordingly
			this->splayRecur(val, m_root);

			if (val == m_root->val)//already exists
				return;

			TreeNode * newNode = new TreeNode(val);
			if (val < m_root->val)
			{
				/*
				2. create a new node with val to be the root
				make old root a right child of the new root
				make old root's left child a left child of the new root
				*/
				newNode->left = m_root->left;
				newNode->right = m_root;
				m_root->left = m_nullNode;
				m_root = newNode;
			}
			else// if (val > m_root->val)
			{
				/*
				2. create a new node with val to be the root
				make old root a left child of the new root
				make old root's right child a right child of the new root
				*/
				newNode->right = m_root->right;
				newNode->left = m_root;
				m_root->right = m_nullNode;
				m_root = newNode;
			}
		}
	}
	void Remove(const int & val)
	{
		if (!this->Contains(val))
			return;
		//now the target node has been moved to root

		std::cout << "SplayTree Remove: " << val << std::endl;

		/*
		the old root, which is the target, is going to be deleted
		find the max in the left subtree
		splay it to the old root's left
		make old root's left become the new root
		attach old root's right to new root's right
		*/
		TreeNode * newRoot;
		if (m_root->left == m_nullNode)
			newRoot = m_root->right;
		else
		{
			newRoot = m_root->left;
			this->splayRecur(val, newRoot);
			newRoot->right = m_root->right;
		}
		delete m_root;
		m_root = newRoot;
	}


private:
	/*
                y                                     x
               / \     Zig (Right Rotation)          /  \
              x   T3   �V - �V - �V - �V - - ->         T1   y 
             / \       < - - - - - - - - -              / \
            T1  T2     Zag (Left Rotation)            T2   T3
	*/
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
		k2->left = k1->right;//y->left=T2
		k1->right = k2;//x->right=y
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
		k1->right = k2->left;//x->right=T2
		k2->left = k1;//y->left=x
		k1 = k2;
	}
	/*
	Buttom Up Splay Cases:
	1. Zig-Zig (Left Left Case):
       G                        P                           X       
      / \                     /   \                        / \      
     P  T4   rightRotate(P)  X     G     rightRotate(P)  T1   P     
    / \      ============>  / \   / \    ============>       / \    
   X  T3                   T1 T2 T3 T4                      T2  G
  / \                                                          / \ 
 T1 T2                                                        T3  T4 

2. Zag-Zag (Right Right Case):
  G                          P                           X       
 /  \                      /   \                        / \      
T1   P     leftRotate(P)  G     X     leftRotate(P)    P   T4
    / \    ============> / \   / \    ============>   / \   
   T2   X               T1 T2 T3 T4                  G   T3
       / \                                          / \ 
      T3 T4                                        T1  T2
	
	3. Zig-Zag (Left Right Case):
       G                        G                            X       
      / \                     /   \                        /   \      
     P   T4  leftRotate(P)   X     T4    rightRotate(G)   P     G     
   /  \      ============>  / \          ============>   / \   /  \    
  T1   X                   P  T3                       T1  T2 T3  T4 
      / \                 / \                                       
    T2  T3              T1   T2                                     

4. Zag-Zig (Right Left Case):
  G                          G                           X       
 /  \                      /  \                        /   \      
T1   P    rightRotate(P)  T1   X     leftRotate(P)    G     P
    / \   =============>      / \    ============>   / \   / \   
   X  T4                    T2   P                 T1  T2 T3  T4
  / \                           / \                
 T2  T3                        T3  T4
	*/
	void splayRecur(const int & val, TreeNode *& curNode)//buttom up
	{
		//null node or found target
		if (curNode == m_nullNode || curNode->val == val)
			return;

		//target in left subtree
		if (val < curNode->val)
		{
			//target not found, done
			if (curNode->left == m_nullNode)
				return;

			//Zig-Zig (Left Left Case)
			if (val < curNode->left->val)
			{
				//move target to curNode->left->left
				this->splayRecur(val, curNode->left->left);
				//do 1st rotation for curNode
				this->rightRotateWLeftChild(curNode);
			}
			//Zig-Zag (Left Right Case)
			else if (val > curNode->left->val)
			{
				//move target to curNode->left->right
				this->splayRecur(val, curNode->left->right);
				//do 1st rotation for curNode->left
				if (curNode->left->right != m_nullNode)
					this->leftRotateWRightChild(curNode->left);
			}

			//do second rotation for curNode
			if (curNode->left != m_nullNode)
				this->rightRotateWLeftChild(curNode);
		}
		//target in right subtree
		else
		{
			//target not found, done
			if (curNode->right == m_nullNode)
				return;

			//Zag-Zig (Right Left Case)
			if (val < curNode->right->val)
			{
				//move target to curNode->right->left
				this->splayRecur(val, curNode->right->left);
				//do 1st rotation for curNode->right
				if (curNode->right->left != m_nullNode)
					this->rightRotateWLeftChild(curNode->right);
			}
			//Zag-Zag (Right Right Case)
			else if (val > curNode->right->val)
			{
				//move target to curNode->right->right
				this->splayRecur(val, curNode->right->right);
				//do 1st rotation for curNode
				this->leftRotateWRightChild(curNode);
			}

			//do 2nd rotation for curNode
			if (curNode->right != m_nullNode)
				this->leftRotateWRightChild(curNode);
		}
	}
	/*
	Top Down Splay Cases:
	1. Zig:
	       L          P           R                    L          X          R
	      /          / \           \                  /          / \        / \
		T1          X   T2          T5     --->     T1         T3   T4     P   T5   (R is updated to P)
		           / \                                                      \
                 T3   T4                                                     T2

	2. Zig-Zig (right rotate G):
	       L          G           R                    L          X          R
	      /          / \           \                  /          / \        / \
		T1          P   T2          T6     --->     T1         T4   T5     P   T6   (R is updated to P)
		           / \                                                      \
                  X   T3                                                     G
				 / \                                                        / \
			   T4   T5                                                    T3   T2

	3. Simplified Zig-Zag:
	       L          G           R                    L          P          R
	      /          / \           \                  /          / \        / \
		T1          P   T2          T6     --->     T1         T3   X      G   T6   (R is updated to G)
		           / \                                             / \      \
                 T3   X                                          T4   T5     T2
				     / \
			       T4   T5

	4. Reassemble:
	       L          X           R                        X
	      /          / \           \                    /     \
		T1         T2   T3          T4     --->       L         R
		                                             / \       / \
                                                   T1   T2   T3   T4
	*/
	void splayIterate(const int & val, TreeNode *& n)//top down
	{
		TreeNode * leftTreeMax;//left tree max node (left tree root)
		TreeNode * rightTreeMin;//right tree min node (right tree root)
		static TreeNode header;
		header.left = m_nullNode;
		header.right = m_nullNode;
		leftTreeMax = &header;
		rightTreeMin = &header;
		m_nullNode->val = val;
		/*
		n is P
		leftTreeMax is L
		rightTreeMin is R
		*/
		while (true)
		{
			//1. zig
			if (val < n->val)
			{
				//2. zig-zig
				if (val < n->left->val)
					this->rightRotateWLeftChild(n);
				//else: 3. simplified zig-zag

				if (n->left == m_nullNode)
					break;

				//link right
				rightTreeMin->left = n;//R->left = P
				rightTreeMin = n;//R = P
				n = n->left;//n = X
			}
			//1. zig
			else if (val > n->val)
			{
				//2. zig-zig
				if (val > n->right->val)
					this->leftRotateWRightChild(n);
				//else: 3. simplified zig-zag

				if (n->right == m_nullNode)
					break;

				//link left
				leftTreeMax->right = n;
				leftTreeMax = n;
				n = n->right;
			}
			else
				break;
		}
		//4. reassemble
		leftTreeMax->right = n->left;
		rightTreeMin->left = n->right;
		n->left = header.right;
		n->right = header.left;
	}




	TreeNode * cloneRecur(TreeNode * n) const
	{
		if (n == n->left)//cannot test against nullNode!
			return m_nullNode;
		else
		{
			TreeNode * c = new TreeNode(n->val);
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
	void Print()
	{
		std::ostringstream oss;
		oss << "SplayTree:" << std::endl;
		PrintBinaryTree<TreeNode, std::ostringstream>(m_root, oss);
		std::cout << oss.str() << std::endl;
	}
};

template<>
SplayTree::TreeNode * PrintBinaryTree<SplayTree::TreeNode, std::ostringstream>::getLeft(SplayTree::TreeNode * n)
{
	if (n->left->nullNode)
		return nullptr;
	else
		return n->left;
}
template<>
SplayTree::TreeNode * PrintBinaryTree<SplayTree::TreeNode, std::ostringstream>::getRight(SplayTree::TreeNode * n)
{
	if (n->right->nullNode)
		return nullptr;
	else
		return n->right;
}
/*
SplayTree Insert: 50
SplayTree Insert: 85
SplayTree Insert: 15
SplayTree Insert: 70
SplayTree Insert: 10
SplayTree Insert: 23
SplayTree Insert: 64
SplayTree Insert: 32
SplayTree Insert: 77
SplayTree:
                                                              
                                                               1
                                ______________________________77______________________________
                               /                                                               \
                               2                                                               2
                ______________50______________                                  ______________85______________
               /                               \                               /                               \
               3                               3                               X                               X
        ______32______                  ______70______                  ______ N______                  ______ N______
       /               \               /               \               /               \               /               \
       4               X               4               X               X               X               X               X
    __23__          __ N__          __64__          __ N__          __ N__          __ N__          __ N__          __ N__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   5       X       X       X       X       X       X       X       X       X       X       X       X       X       X       X
  15       N       N       N       N       N       N       N       N       N       N       N       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 6   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X
10   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N


SplayTree FindMax: 85
SplayTree FindMin: 10
SplayTree Contains "70": 1
SplayTree:
                                                              
                                                               1
                                ______________________________70______________________________
                               /                                                               \
                               2                                                               2
                ______________10______________                                  ______________77______________
               /                               \                               /                               \
               X                               3                               X                               3
        ______ N______                  ______50______                  ______ N______                  ______85______
       /               \               /               \               /               \               /               \
       X               X               4               4               X               X               X               X
    __ N__          __ N__          __32__          __64__          __ N__          __ N__          __ N__          __ N__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       5       X       X       X       X       X       X       X       X       X       X       X
   N       N       N       N      15       N       N       N       N       N       N       N       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   6   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   N   N   N  23   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N


SplayTree Contains "32": 1
SplayTree:
              
               1
        ______32______
       /               \
       2               2
    __10__          __70__
   /       \       /       \
   X       3       3       3
   N      15      50      77
 /   \   /   \   /   \   /   \
 X   X   X   4   X   4   X   4
 N   N   N  23   N  64   N  85


SplayTree Contains "63": 0
SplayTree:
                              
                               1
                ______________64______________
               /                               \
               2                               2
        ______32______                  ______70______
       /               \               /               \
       3               3               X               3
    __10__          __50__          __ N__          __77__
   /       \       /       \       /       \       /       \
   X       4       X       X       X       X       X       4
   N      15       N       N       N       N       N      85
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   5   X   X   X   X   X   X   X   X   X   X   X   X
 N   N   N  23   N   N   N   N   N   N   N   N   N   N   N   N


SplayTree Contains "14": 0
SplayTree:
                                                              
                                                               1
                                ______________________________15______________________________
                               /                                                               \
                               2                                                               2
                ______________10______________                                  ______________32______________
               /                               \                               /                               \
               X                               X                               3                               3
        ______ N______                  ______ N______                  ______23______                  ______64______
       /               \               /               \               /               \               /               \
       X               X               X               X               X               X               4               4
    __ N__          __ N__          __ N__          __ N__          __ N__          __ N__          __50__          __70__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       X       X       X       X       X       X       X       X       X       X       X       5
   N       N       N       N       N       N       N       N       N       N       N       N       N       N       N      77
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   6
 N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N  85


SplayTree Contains "23": 1
SplayTree Remove: 23
SplayTree:
                                                              
                                                               1
                                ______________________________15______________________________
                               /                                                               \
                               2                                                               2
                ______________10______________                                  ______________32______________
               /                               \                               /                               \
               X                               X                               X                               3
        ______ N______                  ______ N______                  ______ N______                  ______64______
       /               \               /               \               /               \               /               \
       X               X               X               X               X               X               4               4
    __ N__          __ N__          __ N__          __ N__          __ N__          __ N__          __50__          __70__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       X       X       X       X       X       X       X       X       X       X       X       5
   N       N       N       N       N       N       N       N       N       N       N       N       N       N       N      77
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   6
 N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N  85

*/
#endif