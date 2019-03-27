#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
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
Leetcode: Kth Smallest Element in a BST
Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.
You may assume k is always valid, 1 <= k <= BST's total elements.
Follow up:
What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?
Elements of programming interview, BinaryTrees: Compute the kth node of inorder traversal (FindKthNode)
Elements of programming interview, BST: Find the first occurrence of k in a BST (FindLowerBound), Find the first key larger than k in a BST (FindUpperBound)
, Find the k largest elements in a BST (FindKLargest), Compute the LCA in a BST (FindLCA), Update a BST (Insert, Remove)
, The nearest restaurant problem (FindRange), Count the number of entries in an interval (CountRange)
Google
http://www.careercup.com/question?id=5165570324430848
http://www.careercup.com/question?id=20229674

http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/BinarySearchTree.h

The worst case time complexity of Binary Search Tree operations like search, insert, delete is O(n).
The worst case occurs when the tree is skewed.
We can get the worst case time complexity as O(height) = O(logn) with AVL Trees and Red Black Trees.

Leetcode: Insert into a Binary Search Tree
*/
class BinarySearchTree
{
public:
	struct TreeNode
	{
		TreeNode(const int & val, const int leftCount = 0) : val(val), leftCount(leftCount), left(nullptr), right(nullptr){}
		TreeNode(int && val, const int leftCount = 0) : val(std::move(val)), leftCount(leftCount), left(nullptr), right(nullptr){}
		~TreeNode(){}
		int val;
		TreeNode * left;
		TreeNode * right;
		int leftCount;/*the node count of left subtree, used to get the rank (sorted order index) of a node in O(logn) time*/
	};
private:
	TreeNode * m_root;
public:
	BinarySearchTree(): m_root(nullptr){}
	BinarySearchTree(const std::vector<int> & v) : m_root(nullptr)
	{
		int N = v.size();
		for (int i = 0; i < N; ++i)
			this->Insert(v[i]);
	}
	~BinarySearchTree()
	{
		this->MakeEmpty();
	}
	//copy ctor: deep copy
	BinarySearchTree(const BinarySearchTree & rhs) : m_root(nullptr)
	{
		m_root = this->cloneRecur(rhs.m_root);
	}
	//copy ctor: move
	BinarySearchTree(BinarySearchTree && rhs) : m_root(rhs.m_root)
	{
		rhs.m_root = nullptr;
	}
	//assignment: deep copy
	BinarySearchTree & operator=(const BinarySearchTree & rhs)
	{
		BinarySearchTree copy = rhs;//copy ctor: deep copy
		std::swap(*this, copy);
		return *this;
	}
	//assignment: move
	BinarySearchTree & operator=(BinarySearchTree && rhs)
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
		DeleteTreeIterate(m_root);
	}
	void Insert(const int & val)
	{
		//this->insertRecur(val, m_root);//approach1
		//m_root = insertRecur2(val, m_root);//approach2
		m_root = insertIterate(m_root, val);//approach3
		std::cout << "BinarySearchTree Insert: " << val << std::endl;
	}
	void Insert(int && val)
	{
		this->insertRecur(std::move(val), m_root);
	}
	void Remove(const int & val)
	{
		//this->removeRecur(val, m_root);//approach1
		m_root = removeRecur2(val, m_root);//approach2
		std::cout << "BinarySearchTree Remove: " << val << std::endl;
	}
	int FindMin() const
	{
		if (this->IsEmpty())
			throw std::runtime_error("");
		int min = this->findMinRecur(m_root)->val;
		std::cout << "BinarySearchTree FindMin: " << min << std::endl;
		return min;
	}
	int FindMax() const
	{
		if (this->IsEmpty())
			throw std::runtime_error("");
		int max = this->findMaxRecur(m_root)->val;
		std::cout << "BinarySearchTree FindMax: " << max << std::endl;
		return max;
	}
	bool Contains(const int & val) const
	{
		bool res = this->containsRecur(val, m_root);
		std::cout << "BinarySearchTree Contains \"" << val << "\": " << res << std::endl;
		return res;
	}
	std::vector<int> FindRange(const int & lower, const int & upper) const//O(K + logN) time, where K is the keys in the range, N is the number of nodes in the tree
	{
		std::vector<int> res;
		this->findRangeRecur(m_root, lower, upper, res);
		std::cout << "BinarySearchTree FindRange for \"" << lower << "," << upper << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
	std::vector<int> FindKLargest(int k) const//O(n) time even if k << n
	{
		std::vector<int> res;
		this->findKLargestRecur(m_root, k, res);
		std::cout << "BinarySearchTree FindKLargest for \"" << k << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
	std::pair<TreeNode *, int> GetRank(const int & val) const//the sorted order index of underlying node
	{
		std::pair<TreeNode *, int> res = this->getRankRecur(val, m_root);
		std::string found = res.first == nullptr ? "N" : std::to_string(res.second);
		std::cout << "BinarySearchTree GetRank for \"" << val << "\": " << found << std::endl;
		return res;
	}
	int CountSmallerEntries(const int & val) const
	{
		int res = this->getSmallerEntriesCountRecur(val, m_root);
		std::cout << "BinarySearchTree CountSmallerEntries for \"" << val << "\": " << res << std::endl;
		return res;
	}
	int CountSmallerEqualEntries(const int & val) const
	{
		int res = this->getSmallerEqualEntriesCountRecur(val, m_root);
		std::cout << "BinarySearchTree CountSmallerEqualEntries for \"" << val << "\": " << res << std::endl;
		return res;
	}
	int CountRange(const int & lower, const int & upper) const
	{
		int countSmallerThanLower = this->getSmallerEntriesCountRecur(lower, m_root);
		int countSmallerEqualThanUpper = this->getSmallerEqualEntriesCountRecur(upper, m_root);
		int res = countSmallerEqualThanUpper - countSmallerThanLower;
		std::cout << "BinarySearchTree CountRange for \"" << lower << "," << upper << "\": " << countSmallerEqualThanUpper << " - " << countSmallerThanLower << std::endl;
		return res;
	}
	TreeNode * FindCeil(const int & val) const
	{
		TreeNode * ceil = this->findCeilIterate(val, m_root);
		std::string res = ceil == nullptr ? "N" : std::to_string(ceil->val);
		std::cout << "BinarySearchTree FindCeil for \"" << val << "\": " << res << std::endl;
		return ceil;
	}
	TreeNode * FindFloor(const int & val) const
	{
		TreeNode * floor = this->findFloorIterate(val, m_root);
		std::string res = floor == nullptr ? "N" : std::to_string(floor->val);
		std::cout << "BinarySearchTree FindFloor for \"" << val << "\": " << res << std::endl;
		return floor;
	}
	//this lower bound returns the first node whose val equals val, and returns nullptr if found no node whose val equals val
	TreeNode * FindLowerBound(const int & val) const
	{
		TreeNode * lb = this->findLowerBoundIterate(val, m_root);
		std::string found = lb == nullptr ? "N" : std::to_string(lb->val);
		std::string left = lb && lb->left ? std::to_string(lb->left->val) : "N";
		std::string right = lb && lb->right ? std::to_string(lb->right->val) : "N";
		std::cout << "BinarySearchTree FindLowerBound for \"" << val << "\": " << found << " (" << left << "," << right << ")" << std::endl;
		return lb;
	}
	//this upper bound returns the first node whose val is bigger than val next to the node whose val equals val, and returns nullptr if found no node whose val equals val
	TreeNode * FindUpperBound(const int & val) const
	{
		bool foundVal = false;
		TreeNode * ub = this->findUpperBoundRecur(val, m_root, foundVal);
		std::string found = ub == nullptr ? "N" : std::to_string(ub->val);
		std::string left = ub && ub->left ? std::to_string(ub->left->val) : "N";
		std::string right = ub && ub->right ? std::to_string(ub->right->val) : "N";
		std::cout << "BinarySearchTree FindUpperBound for \"" << val << "\": " << found << " (" << left << "," << right << ")" << std::endl;
		return ub;
	}
	TreeNode * FindKthNode(int k) const
	{
		TreeNode * kth = this->findKthNodeIterate_2(m_root, k);
		std::string found = kth == nullptr ? "N" : std::to_string(kth->val);
		std::cout << "BinarySearchTree FindKthNode for \"" << k << "\": " << found << std::endl;
		return kth;
	}
	TreeNode * FindLCA(TreeNode * a, TreeNode * b) const
	{
		TreeNode * lca = this->findLCAIterate(m_root, a, b);
		std::string found = lca == nullptr ? "N" : std::to_string(lca->val);
		std::cout << "BinarySearchTree FindLCA for \"" << a->val << ", " << b->val << "\": " << found << std::endl;
		return lca;
	}
	TreeNode * Clone() const
	{
		TreeNode * root = this->cloneRecur(m_root);
		std::cout << "BinarySearchTree Clone:" << std::endl;
		std::ostringstream oss;
		PrintBinaryTree<TreeNode, std::ostringstream>(root, oss);
		std::cout << oss.str() << std::endl;
		return root;
	}
	TreeNode * CloneMirror() const
	{
		TreeNode * root = this->cloneMirrorIterate(m_root);
		std::cout << "BinarySearchTree CloneMirror:" << std::endl;
		std::ostringstream oss;
		PrintBinaryTree<TreeNode, std::ostringstream>(root, oss);
		std::cout << oss.str() << std::endl;
		return root;
	}

private:
	std::pair<TreeNode *, int> getRankRecur(const int & val, TreeNode * n) const
	{
		if (n == nullptr)
			return{ nullptr, 0 };
		else if (val < n->val)
			return this->getRankRecur(val, n->left);
		else if (val > n->val)
		{
			auto findRight = this->getRankRecur(val, n->right);
			return{ findRight.first, n->leftCount + 1 + findRight.second };//node count in left subtree + this node + recur down right subtree
		}
		else
		{
			auto findLeft = this->getRankRecur(val, n->left);//find the leftmost duplicate if possible
			if (findLeft.first != nullptr)
				return findLeft;
			else
				return{ n, n->leftCount };
		}
	}
	int getSmallerEntriesCountRecur(const int & val, TreeNode * n) const//also equivalent to the index of the leftmost duplicate node whose val equals val (val's lower bound index)
	{
		if (n == nullptr)
			return 0;
		else if (val <= n->val)//sine we are looking for lower bound, so go left when equal
			return this->getSmallerEntriesCountRecur(val, n->left);
		else
			return n->leftCount + 1 + this->getSmallerEntriesCountRecur(val, n->right);
	}
	int getSmallerEqualEntriesCountRecur(const int & val, TreeNode * n) const//also equivalent to the NEXT RIGHT index of the rightmost duplicate node whose val equals val (val's upper bound index)
	{
		if (n == nullptr)
			return 0;
		else if (val < n->val)
			return this->getSmallerEqualEntriesCountRecur(val, n->left);
		else//since we are looking for upper bound, so go right when equal
			return n->leftCount + 1 + this->getSmallerEqualEntriesCountRecur(val, n->right);
	}
	void findRangeRecur(TreeNode * curNode, const int & lower, const int & upper, std::vector<int> & res) const
	{
		if (curNode != nullptr)
		{
			if (lower <= curNode->val)
				this->findRangeRecur(curNode->left, lower, upper, res);

			//in-order
			if (lower <= curNode->val && curNode->val <= upper)
				res.push_back(curNode->val);

			if (curNode->val <= upper)
				this->findRangeRecur(curNode->right, lower, upper, res);
		}
	}
	//inorder traversal from right
	void findKLargestRecur(TreeNode * curNode, int k, std::vector<int> & res) const
	{
		if (curNode != nullptr && (int)res.size() < k)
		{
			this->findKLargestRecur(curNode->right, k, res);
			if ((int)res.size() < k)
			{
				res.push_back(curNode->val);//in-order
				this->findKLargestRecur(curNode->left, k, res);
			}
		}
	}
	TreeNode * insertIterate(TreeNode * root, int val)
	{
		TreeNode * node = new TreeNode(val);
		if (root == NULL) return node;
		TreeNode * cur = root;
		while (true)
		{
			if (cur->val >= node->val)//too big or equal: go left
			{
				++cur->leftCount;
				if (cur->left)
					cur = cur->left;
				else
				{
					cur->left = node;
					break;
				}
			}
			else//too small: go right
			{
				if (cur->right)
					cur = cur->right;
				else
				{
					cur->right = node;
					break;
				}
			}
		}
		return root;
	}
	void insertRecur(const int & val, TreeNode *& n) const
	{
		if (n == nullptr)
			n = new TreeNode(val);
		else if (val < n->val)
		{
			this->insertRecur(val, n->left);
			++n->leftCount;
		}
		else if (val > n->val)
			this->insertRecur(val, n->right);
		else//val == n->val
		{
			this->insertRecur(val, n->left);//can insert same val to either left child or right child
			++n->leftCount;
		}
	}
	void insertRecur(int && val, TreeNode *& n) const
	{
		if (n == nullptr)
			n = new TreeNode(std::move(val));
		else if (val < n->val)
		{
			this->insertRecur(std::move(val), n->left);
			++n->leftCount;
		}
		else if (val > n->val)
			this->insertRecur(std::move(val), n->right);
		else//val == n->val
		{
			this->insertRecur(std::move(val), n->left);//can insert same val to either left child or right child
			++n->leftCount;
		}
	}
	TreeNode * insertRecur2(const int & val, TreeNode * n) const
	{
		if (n == nullptr)
			return new TreeNode(val);
		else if (val < n->val)//too big: go left
		{
			n->left = insertRecur2(val, n->left);
			++n->leftCount;
			return n;
		}
		else if (val > n->val)
		{
			n->right = insertRecur2(val, n->right);
			return n;
		}
		else//val == n->val
		{
			n->left = insertRecur2(val, n->left);//can insert same val to either left child or right child
			++n->leftCount;
			return n;
		}
	}
	void removeRecur(const int & val, TreeNode *& n) const
	{
		if (n == nullptr)
			return;
		if (val < n->val)
		{
			this->removeRecur(val, n->left);
			--n->leftCount;
		}
		else if (val > n->val)
			this->removeRecur(val, n->right);
		else
		{
			if (n->left != nullptr && n->right != nullptr)//two children
			{
				/*found the target node, replace its value with the successor (min of RSubtree (RSubLmost)), then recur down to remove that successor*/
				TreeNode * RSubLmost = this->findMinRecur(n->right);
				n->val = RSubLmost->val;
				this->removeRecur(n->val, n->right);
			}
			else//1 or 0 child (a node with 1 child or a leaf node)
			{
				TreeNode * oldNode = n;
				n = n->left != nullptr ? n->left : n->right;//replace n with its child, or with nullptr
				delete oldNode;
				oldNode = nullptr;
			}
		}
	}
	TreeNode * removeRecur2(const int & val, TreeNode * n) const
	{
		if (n == nullptr)
			return nullptr;
		if (val < n->val)//too big: go left
		{
			n->left = removeRecur2(val, n->left);
			--n->leftCount;
			return n;
		}
		else if (val > n->val)
		{
			n->right = removeRecur2(val, n->right);
			return n;
		}
		else
		{
			if (n->left && n->right)//two children
			{
				TreeNode * RSubLmost = this->findMinRecur(n->right);
				n->val = RSubLmost->val;
				n->right = removeRecur2(n->val, n->right);
				return n;
			}
			else//1 or 0 child (a node with 1 child or a leaf node)
			{
				TreeNode * toDel = n;
				n = n->left != nullptr ? n->left : n->right;//return its child, or nullptr
				delete toDel;
				return n;
			}
		}
	}
	TreeNode * findMinRecur(TreeNode * n) const//find Lmost
	{
		if (n == nullptr)
			return nullptr;
		if (n->left == nullptr)
			return n;
		return this->findMinRecur(n->left);
	}
	TreeNode * findMaxRecur(TreeNode * n) const//find Rmost
	{
		if (n == nullptr)
			return nullptr;
		if (n->right == nullptr)
			return n;
		return this->findMaxRecur(n->right);
	}
	TreeNode * findMinIterate(TreeNode * n) const//find Lmost
	{
		if (n != nullptr)
			while (n->left != nullptr)
				n = n->left;
		return n;
	}
	TreeNode * findMaxIterate(TreeNode * n) const//find Rmost
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
		else if (val < n->val)//too big: go left
			return this->containsRecur(val, n->left);
		else if (val > n->val)//too small: go right
			return this->containsRecur(val, n->right);
		else
			return true;
	}
	bool containsIterate(const int & val, TreeNode * n) const
	{
		while (n != nullptr)
			if (val < n->val)//too big: go left
				n = n->left;
			else if (val > n->val)//too small: go right
				n = n->right;
			else
				return true;

			return false;
	}
	TreeNode * findCeilRecur(const int & val, TreeNode * n) const
	{
		if (n == nullptr)
			return nullptr;
		if (n->val > val)
		{
			TreeNode * findSmaller = this->findCeilRecur(val, n->left);
			if (findSmaller != nullptr)
				return findSmaller;
			else
				return n;
		}
		else
			return this->findCeilRecur(val, n->right);
	}
	TreeNode * findFloorRecur(const int & val, TreeNode * n) const
	{
		if (n == nullptr)
			return nullptr;
		if (n->val < val)
		{
			TreeNode * findBigger = this->findFloorRecur(val, n->right);
			if (findBigger != nullptr)
				return findBigger;
			else
				return n;
		}
		else
			return this->findFloorRecur(val, n->left);
	}
	TreeNode * findCeilIterate(const int & val, TreeNode * n) const
	{
		TreeNode * leftmost = nullptr;
		while (n)
		{
			if (n->val <= val)//too small: go right; for ceil, go right when equal
				n = n->right;
			else//(n->val > val), found, but try go left to see if there exists a closer one
			{
				leftmost = n;
				n = n->left;
			}
		}
		return leftmost;
	}
	TreeNode * findFloorIterate(const int & val, TreeNode * n) const
	{
		TreeNode * rightmost = nullptr;
		while (n)
		{
			if (n->val >= val)//too big: go left; for floor, go left when equal
				n = n->left;
			else//(n->val < val), found, but try go right to see if there exists a closer one
			{
				rightmost = n;
				n = n->right;
			}
		}
		return rightmost;
	}
	TreeNode * findLowerBoundRecur(const int & val, TreeNode * n) const
	{
		if (n == nullptr)
			return nullptr;
		if (n->val == val)//since we are looking for lower bound, so try go left when equal
		{
			TreeNode * findLefter = this->findLowerBoundRecur(val, n->left);
			if (findLefter != nullptr)
				return findLefter;
			else
				return n;
		}
		else if (n->val < val)
			return this->findLowerBoundRecur(val, n->right);
		else
			return this->findLowerBoundRecur(val, n->left);
	}
	TreeNode * findUpperBoundRecur(const int & val, TreeNode * n, bool & foundVal) const
	{
		if (n == nullptr)
			return nullptr;
		if (n->val == val)//since we are looking for upper bound, so try go right when equal
		{
			if (!foundVal)
				foundVal = true;
			return this->findUpperBoundRecur(val, n->right, foundVal);
		}
		else if (n->val > val)//found, but try go left to see if there exists a closer one
		{
			TreeNode * findLeft = this->findUpperBoundRecur(val, n->left, foundVal);
			if (findLeft)
				return findLeft;
			else if (foundVal)
				return n;
			else
				return nullptr;
		}
		else
			return this->findUpperBoundRecur(val, n->right, foundVal);
	}
	TreeNode * findLowerBoundIterate(const int & val, TreeNode * n) const
	{
		TreeNode * leftmost = nullptr;
		while (n)
		{
			if (n->val < val)
				n = n->right;
			else if (n->val > val)
				n = n->left;
			else//n->val == val
			{
				//search for the leftmost in the left subtree
				leftmost = n;
				n = n->left;
			}
		}
		return leftmost;
	}
	TreeNode * findUpperBoundIterate(const int & val, TreeNode * n) const
	{
		bool foundVal = false;
		TreeNode * leftmost = nullptr;
		while (n)
		{
			if (n->val < val)
				n = n->right;
			else if (n->val > val)
			{
				leftmost = n;
				n = n->left;
			}
			else//n->val == val
			{
				foundVal = true;
				n = n->right;
			}
		}
		if (foundVal)
			return leftmost;
		else
			return nullptr;
	}
	TreeNode * findKthNodeIterate(TreeNode * cur, int k) const
	{
		TreeNode * kth = nullptr;
		while (cur)
		{
			if (cur->leftCount < k - 1)
			{
				k -= (cur->leftCount + 1);
				cur = cur->right;
			}
			else if (cur->leftCount == k - 1)
			{
				kth = cur;
				break;
			}
			else
			{
				cur = cur->left;
			}
		}
		return kth;
	}
	TreeNode * findKthNodeIterate_2(TreeNode * cur, int k) const
	{
		TreeNode * kth = nullptr;
		while (cur)
		{
			int leftCount = this->nodeCountRecur(cur->left);//for the case without TreeNode::leftCount
			if (leftCount < k - 1)
			{
				k -= (leftCount + 1);
				cur = cur->right;
			}
			else if (leftCount == k - 1)
			{
				kth = cur;
				break;
			}
			else
			{
				cur = cur->left;
			}
		}
		return kth;
	}
	int nodeCountRecur(TreeNode * cur) const
	{
		if (cur == nullptr)
			return 0;
		return this->nodeCountRecur(cur->left) + this->nodeCountRecur(cur->right) + 1;
	}
	TreeNode * findLCAIterate(TreeNode * root, TreeNode * a, TreeNode * b) const
	{
		while (root)
		{
			if (root->val > a->val && root->val > b->val)
				root = root->left;
			else if (root->val < a->val && root->val < b->val)
				root = root->right;
			else
				break;
		}
		return root;
	}
	TreeNode * cloneRecur(TreeNode * n) const
	{
		if (n == nullptr)
			return nullptr;
		else
		{
			TreeNode * c = new TreeNode(n->val, n->leftCount);
			c->left = this->cloneRecur(n->left);
			c->right = this->cloneRecur(n->right);
			return c;
		}
	}
	TreeNode * cloneIterate(TreeNode * sub) const
	{
		if (sub == NULL)
			return NULL;

		//perform preorder traversal of oldTree and preorder traversal of newTree
		std::stack<TreeNode *> oldStk;
		std::stack<TreeNode *> newStk;
		oldStk.push(sub);
		TreeNode * root = new TreeNode(sub->val, sub->leftCount);
		newStk.push(root);
		while (!oldStk.empty())
		{
			TreeNode * cur = oldStk.top(); oldStk.pop();
			TreeNode * copy = newStk.top(); newStk.pop();
			if (cur->right)
			{
				oldStk.push(cur->right);
				copy->right = new TreeNode(cur->right->val, cur->right->leftCount);
				newStk.push(copy->right);
			}
			if (cur->left)
			{
				oldStk.push(cur->left);
				copy->left = new TreeNode(cur->left->val, cur->left->leftCount);
				newStk.push(copy->left);
			}
		}
		return root;
	}
	TreeNode * cloneMirrorRecur(TreeNode * n) const
	{
		if (n == nullptr)
			return nullptr;
		else
		{
			TreeNode * c = new TreeNode(n->val, n->leftCount);
			c->right = this->cloneMirrorRecur(n->left);
			c->left = this->cloneMirrorRecur(n->right);
			return c;
		}
	}
	TreeNode * cloneMirrorIterate(TreeNode * sub) const
	{
		if (sub == NULL)
			return NULL;

		//perform preorder traversal of oldTree and mirror-preorder traversal of newTree
		std::stack<TreeNode *> oldStk;
		std::stack<TreeNode *> newStk;
		oldStk.push(sub);
		TreeNode * root = new TreeNode(sub->val, sub->leftCount);
		newStk.push(root);
		while (!oldStk.empty())
		{
			TreeNode * cur = oldStk.top(); oldStk.pop();
			TreeNode * copy = newStk.top(); newStk.pop();
			if (cur->right)
			{
				oldStk.push(cur->right);
				copy->left = new TreeNode(cur->right->val, cur->right->leftCount);
				newStk.push(copy->left);
			}
			if (cur->left)
			{
				oldStk.push(cur->left);
				copy->right = new TreeNode(cur->left->val, cur->left->leftCount);
				newStk.push(copy->right);
			}
		}
		return root;
	}

public:
	static void DeleteTreeRecur(TreeNode *& n)
	{
		if (n)
		{
			DeleteTreeRecur(n->left);
			DeleteTreeRecur(n->right);
			delete n;//postorder
			n = nullptr;
		}
	}
	static void DeleteTreeIterate(TreeNode *& n)
	{
		//perform postorder traversal with stack
		std::stack<TreeNode *> stk;

		//push LRDeepest path nodes
		TreeNode * cur = n;
		while (cur)
		{
			stk.push(cur);
			if (cur->left) cur = cur->left;
			else cur = cur->right;
		}

		while (!stk.empty())
		{
			cur = stk.top();
			stk.pop();
			TreeNode * toDel = cur;

			//push LRDeepest path nodes
			if (!stk.empty() && cur == stk.top()->left)//going up from left subtree
			{
				cur = stk.top()->right;
				while (cur)
				{
					stk.push(cur);
					if (cur->left) cur = cur->left;
					else cur = cur->right;
				}
			}

			//delete cur
			delete toDel;
		}
		n = nullptr;
	}
public:
	void Print()
	{
		std::ostringstream oss;
		oss << "BinarySearchTree (val2: leftCount):" << std::endl;
		PrintBinaryTree<TreeNode, std::ostringstream>(m_root, oss);
		std::cout << oss.str() << std::endl;
	}
};

template<>
std::string PrintBinaryTree<BinarySearchTree::TreeNode, std::ostringstream>::selectVal2(int depth, BinarySearchTree::TreeNode * n)
{
	return std::to_string(n->leftCount);
}

/*
Elements of programming interview, BST: The nearest restaurant problem
Consider the problem of developing a web-service that takes a geographical location, and returns the nearest restaurant.
The service starts with a set S of n restaurant locations--each location is a pair of x,y-coordinates.
A query consists of a location, and should return the nearest restaurant (ties may be broken arbitrarily).

One approach is to build two BSTs on the restaurant locations:
Tx sorted on x coordinates, and Ty sorted on the y coordinates.
A query on location (p,q) can be performed by finding all the points P-delta whose x coordinate is in the range [p-delta,p+delta]
, and all the points Q-delta whose y coordinate is in the range [q-delta,q+delta]
, computing R-delta = P-delta Intersect Q-delta and finding the point in R-delta closest to (p,q).
Heuristically, if delta is chosen correctly, R-delta is a small subset of S
, and a brute-force search for the colsest point in R-delta is fast.
Of course, delta has to be chosen correctly--one approach is to start with a small value and keep doubling it until R-delta is nonempty.

This approach performs poorly on pathological data, but works well in practice.
Theoretically better approaches exist, e.g., Quadtrees, which decompose the plane into regions which are balanced with respect to the number of points they contain
, or k-d trees, which organize points in a k-dimentional space and provide range searches and nearest neighbor searches efficiently.

How would you efficiently perform a range query on a BST?
Specifically, write a function that takes as input a BST and a range [L,U] and returns a list of all the keys that lie in [L,U]?
*/

/*
BinarySearchTree Insert: 50
BinarySearchTree Insert: 90
BinarySearchTree Insert: 15
BinarySearchTree Insert: 70
BinarySearchTree Insert: 10
BinarySearchTree Insert: 23
BinarySearchTree Insert: 64
BinarySearchTree Insert: 32
BinarySearchTree Insert: 77
BinarySearchTree Insert: 7
BinarySearchTree Insert: 95
BinarySearchTree Insert: 32
BinarySearchTree Insert: 13
BinarySearchTree Insert: 13
BinarySearchTree Insert: 13
BinarySearchTree Insert: 18
BinarySearchTree Insert: 96
BinarySearchTree Insert: 92
BinarySearchTree Insert: 70
BinarySearchTree Insert: 70
BinarySearchTree Insert: 96
BinarySearchTree Insert: 96
BinarySearchTree Insert: 23
BinarySearchTree Insert: 32
BinarySearchTree Insert: 23
BinarySearchTree Insert: 8
BinarySearchTree Insert: 9
BinarySearchTree Insert: 4
BinarySearchTree Insert: 14
BinarySearchTree Insert: 14
BinarySearchTree Insert: 3
BinarySearchTree Insert: 5
BinarySearchTree Insert: 8
BinarySearchTree Insert: 73
BinarySearchTree Insert: 77
BinarySearchTree Insert: 79
BinarySearchTree Insert: 83
BinarySearchTree Insert: 17
BinarySearchTree Insert: 16
BinarySearchTree Insert: 37
BinarySearchTree Insert: 47
BinarySearchTree Insert: 55
BinarySearchTree Insert: 58
BinarySearchTree Insert: 71
BinarySearchTree Insert: 92
BinarySearchTree Insert: 78
BinarySearchTree Insert: 92
BinarySearchTree Insert: 97
BinarySearchTree Insert: 95
BinarySearchTree Insert: 95
BinarySearchTree Insert: 97
BinarySearchTree Insert: 99
BinarySearchTree Insert: 33
BinarySearchTree Insert: 51
BinarySearchTree (val2: leftCount):
                                                              
                                                              26
                                ______________________________50______________________________
                               /                                                               \
                              13                                                              14
                ______________15______________                                  ______________90______________
               /                               \                               /                               \
               7                               5                               6                               5
        ______10______                  ______23______                  ______70______                  ______95______
       /               \               /               \               /               \               /               \
       3               2               2               2               3               3               2               2
    __ 7__          __13__          __18__          __32__          __64__          __77__          __92__          __96__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   1       1       1       1       1       1       1       1       1       1       1       1       1       1       1       1
   4       8      13      14      17      23      32      37      55      70      73      79      92      95      96      97
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 0   0   0   0   0   X   0   X   0   X   0   X   0   X   0   0   0   0   0   X   0   0   0   0   0   X   0   X   0   X   0   0
 3   5   8   9  13   N  14   N  16   N  23   N  32   N  33  47  51  58  70   N  71  77  78  83  92   N  95   N  96   N  97  99

BinarySearchTree Clone:
                                                              
                                                              26
                                ______________________________50______________________________
                               /                                                               \
                              13                                                              14
                ______________15______________                                  ______________90______________
               /                               \                               /                               \
               7                               5                               6                               5
        ______10______                  ______23______                  ______70______                  ______95______
       /               \               /               \               /               \               /               \
       3               2               2               2               3               3               2               2
    __ 7__          __13__          __18__          __32__          __64__          __77__          __92__          __96__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   1       1       1       1       1       1       1       1       1       1       1       1       1       1       1       1
   4       8      13      14      17      23      32      37      55      70      73      79      92      95      96      97
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 0   0   0   0   0   X   0   X   0   X   0   X   0   X   0   0   0   0   0   X   0   0   0   0   0   X   0   X   0   X   0   0
 3   5   8   9  13   N  14   N  16   N  23   N  32   N  33  47  51  58  70   N  71  77  78  83  92   N  95   N  96   N  97  99


BinarySearchTree CloneMirror:
                                                              
                                                              26
                                ______________________________50______________________________
                               /                                                               \
                              14                                                              13
                ______________90______________                                  ______________15______________
               /                               \                               /                               \
               5                               6                               5                               7
        ______95______                  ______70______                  ______23______                  ______10______
       /               \               /               \               /               \               /               \
       2               2               3               3               2               2               2               3
    __96__          __92__          __77__          __64__          __32__          __18__          __13__          __ 7__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   1       1       1       1       1       1       1       1       1       1       1       1       1       1       1       1
  97      96      95      92      79      73      70      55      37      32      23      17      14      13       8       4
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 0   0   X   0   X   0   X   0   0   0   0   0   X   0   0   0   0   0   X   0   X   0   X   0   X   0   X   0   0   0   0   0
99  97   N  96   N  95   N  92  83  78  77  71   N  70  58  51  47  33   N  32   N  23   N  16   N  14   N  13   9   8   5   3

BinarySearchTree FindLowerBound for "70": 70 (N,N)
BinarySearchTree FindLowerBound for "60": N (N,N)
BinarySearchTree FindLowerBound for "23": 23 (N,N)
BinarySearchTree FindLowerBound for "79": 79 (78,83)
BinarySearchTree FindUpperBound for "70": 71 (N,N)
BinarySearchTree FindUpperBound for "60": N (N,N)
BinarySearchTree FindUpperBound for "9": 10 (7,13)
BinarySearchTree FindUpperBound for "15": 16 (N,N)
BinarySearchTree FindUpperBound for "79": 83 (N,N)
BinarySearchTree FindUpperBound for "83": 90 (70,95)
BinarySearchTree FindUpperBound for "23": 32 (N,N)
BinarySearchTree FindUpperBound for "32": 33 (N,N)
BinarySearchTree FindUpperBound for "55": 58 (N,N)
BinarySearchTree FindUpperBound for "47": 50 (15,90)
BinarySearchTree FindUpperBound for "70": 71 (N,N)
BinarySearchTree FindUpperBound for "83": 90 (70,95)
BinarySearchTree FindUpperBound for "99": N (N,N)
BinarySearchTree FindLCA for "70, 71": 70
BinarySearchTree FindKthNode for "5": 8
BinarySearchTree FindKthNode for "13": 14
BinarySearchTree FindCeil for "17": 18
BinarySearchTree FindCeil for "65": 70
BinarySearchTree FindCeil for "89": 90
BinarySearchTree FindCeil for "87": 90
BinarySearchTree FindCeil for "12": 13
BinarySearchTree FindCeil for "22": 23
BinarySearchTree FindCeil for "31": 32
BinarySearchTree FindCeil for "69": 70
BinarySearchTree FindFloor for "89": 83
BinarySearchTree FindFloor for "70": 64
BinarySearchTree FindFloor for "6": 5
BinarySearchTree FindFloor for "19": 18
BinarySearchTree FindFloor for "12": 10
BinarySearchTree FindFloor for "22": 18
BinarySearchTree FindFloor for "31": 23
BinarySearchTree FindFloor for "69": 64
BinarySearchTree FindRange for "13,70": 13, 13, 13, 14, 14, 15, 16, 17, 18, 23, 23, 23, 32, 32, 32, 33, 37, 47, 50, 51, 55, 58, 64, 70, 70, 70
BinarySearchTree CountRange for "13,70": 34 - 8
BinarySearchTree CountRange for "11,75": 36 - 8
BinarySearchTree CountSmallerEntries for "96": 48
BinarySearchTree CountSmallerEqualEntries for "96": 51
BinarySearchTree CountSmallerEntries for "23": 17
BinarySearchTree CountSmallerEqualEntries for "32": 23
BinarySearchTree CountSmallerEntries for "15": 13
BinarySearchTree CountSmallerEqualEntries for "15": 14
BinarySearchTree CountSmallerEntries for "10": 7
BinarySearchTree CountSmallerEqualEntries for "10": 8
BinarySearchTree CountSmallerEntries for "13": 8
BinarySearchTree CountSmallerEqualEntries for "13": 11
BinarySearchTree CountSmallerEntries for "70": 31
BinarySearchTree CountSmallerEqualEntries for "70": 34
BinarySearchTree CountSmallerEntries for "65": 31
BinarySearchTree CountSmallerEqualEntries for "65": 31
BinarySearchTree FindKLargest for "9": 99, 97, 97, 96, 96, 96, 95, 95, 95
BinarySearchTree FindMax: 99
BinarySearchTree FindMin: 3
BinarySearchTree GetRank for "13": 8
BinarySearchTree GetRank for "15": 13
BinarySearchTree GetRank for "70": 31
BinarySearchTree GetRank for "86": N
BinarySearchTree GetRank for "96": 48
BinarySearchTree GetRank for "33": 23
BinarySearchTree Remove: 15
BinarySearchTree (val2: leftCount):
                                                              
                                                              25
                                ______________________________50______________________________
                               /                                                               \
                              13                                                              14
                ______________16______________                                  ______________90______________
               /                               \                               /                               \
               7                               4                               6                               5
        ______10______                  ______23______                  ______70______                  ______95______
       /               \               /               \               /               \               /               \
       3               2               1               2               3               3               2               2
    __ 7__          __13__          __18__          __32__          __64__          __77__          __92__          __96__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   1       1       1       1       0       1       1       1       1       1       1       1       1       1       1       1
   4       8      13      14      17      23      32      37      55      70      73      79      92      95      96      97
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 0   0   0   0   0   X   0   X   X   X   0   X   0   X   0   0   0   0   0   X   0   0   0   0   0   X   0   X   0   X   0   0
 3   5   8   9  13   N  14   N   N   N  23   N  32   N  33  47  51  58  70   N  71  77  78  83  92   N  95   N  96   N  97  99


BinarySearchTree Remove: 50
BinarySearchTree (val2: leftCount):
                                                              
                                                              25
                                ______________________________51______________________________
                               /                                                               \
                              13                                                              13
                ______________16______________                                  ______________90______________
               /                               \                               /                               \
               7                               4                               5                               5
        ______10______                  ______23______                  ______70______                  ______95______
       /               \               /               \               /               \               /               \
       3               2               1               2               2               3               2               2
    __ 7__          __13__          __18__          __32__          __64__          __77__          __92__          __96__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   1       1       1       1       0       1       1       1       0       1       1       1       1       1       1       1
   4       8      13      14      17      23      32      37      55      70      73      79      92      95      96      97
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 0   0   0   0   0   X   0   X   X   X   0   X   0   X   0   0   X   0   0   X   0   0   0   0   0   X   0   X   0   X   0   0
 3   5   8   9  13   N  14   N   N   N  23   N  32   N  33  47   N  58  70   N  71  77  78  83  92   N  95   N  96   N  97  99


BinarySearchTree Remove: 70
BinarySearchTree (val2: leftCount):
                                                              
                                                              25
                                ______________________________51______________________________
                               /                                                               \
                              13                                                              12
                ______________16______________                                  ______________90______________
               /                               \                               /                               \
               7                               4                               5                               5
        ______10______                  ______23______                  ______71______                  ______95______
       /               \               /               \               /               \               /               \
       3               2               1               2               2               2               2               2
    __ 7__          __13__          __18__          __32__          __64__          __77__          __92__          __96__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   1       1       1       1       0       1       1       1       0       1       0       1       1       1       1       1
   4       8      13      14      17      23      32      37      55      70      73      79      92      95      96      97
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 0   0   0   0   0   X   0   X   X   X   0   X   0   X   0   0   X   0   0   X   X   0   0   0   0   X   0   X   0   X   0   0
 3   5   8   9  13   N  14   N   N   N  23   N  32   N  33  47   N  58  70   N   N  77  78  83  92   N  95   N  96   N  97  99


BinarySearchTree Remove: 70
BinarySearchTree (val2: leftCount):
                                                              
                                                              25
                                ______________________________51______________________________
                               /                                                               \
                              13                                                              11
                ______________16______________                                  ______________90______________
               /                               \                               /                               \
               7                               4                               4                               5
        ______10______                  ______23______                  ______71______                  ______95______
       /               \               /               \               /               \               /               \
       3               2               1               2               2               2               2               2
    __ 7__          __13__          __18__          __32__          __64__          __77__          __92__          __96__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   1       1       1       1       0       1       1       1       0       0       0       1       1       1       1       1
   4       8      13      14      17      23      32      37      55      70      73      79      92      95      96      97
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 0   0   0   0   0   X   0   X   X   X   0   X   0   X   0   0   X   0   X   X   X   0   0   0   0   X   0   X   0   X   0   0
 3   5   8   9  13   N  14   N   N   N  23   N  32   N  33  47   N  58   N   N   N  77  78  83  92   N  95   N  96   N  97  99


BinarySearchTree Remove: 51
BinarySearchTree (val2: leftCount):
                                                              
                                                              25
                                ______________________________55______________________________
                               /                                                               \
                              13                                                              10
                ______________16______________                                  ______________90______________
               /                               \                               /                               \
               7                               4                               3                               5
        ______10______                  ______23______                  ______71______                  ______95______
       /               \               /               \               /               \               /               \
       3               2               1               2               1               2               2               2
    __ 7__          __13__          __18__          __32__          __64__          __77__          __92__          __96__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   1       1       1       1       0       1       1       1       0       0       0       1       1       1       1       1
   4       8      13      14      17      23      32      37      58      70      73      79      92      95      96      97
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 0   0   0   0   0   X   0   X   X   X   0   X   0   X   0   0   X   X   X   X   X   0   0   0   0   X   0   X   0   X   0   0
 3   5   8   9  13   N  14   N   N   N  23   N  32   N  33  47   N   N   N   N   N  77  78  83  92   N  95   N  96   N  97  99


BinarySearchTree Remove: 90
BinarySearchTree (val2: leftCount):
                                                              
                                                              25
                                ______________________________55______________________________
                               /                                                               \
                              13                                                              10
                ______________16______________                                  ______________92______________
               /                               \                               /                               \
               7                               4                               3                               4
        ______10______                  ______23______                  ______71______                  ______95______
       /               \               /               \               /               \               /               \
       3               2               1               2               1               2               2               2
    __ 7__          __13__          __18__          __32__          __64__          __77__          __95__          __96__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   1       1       1       1       0       1       1       1       0       0       0       1       1       0       1       1
   4       8      13      14      17      23      32      37      58      70      73      79      92      95      96      97
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 0   0   0   0   0   X   0   X   X   X   0   X   0   X   0   0   X   X   X   X   X   0   0   0   0   X   X   X   0   X   0   0
 3   5   8   9  13   N  14   N   N   N  23   N  32   N  33  47   N   N   N   N   N  77  78  83  92   N   N   N  96   N  97  99

*/
#endif