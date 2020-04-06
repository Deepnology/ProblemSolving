#ifndef MIN_FIRST_BST_H
#define MIN_FIRST_BST_H
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "PrintBinaryTree.h"
/*
Elements of programming interview, BST: Test if a binary tree is a min-first BST (Contains, Insert, Remove, ConvertMinFirstBSTtoMaxFirstBST(not implemented))
A min-first BST is one in which the minimum key is stored at the root (which is similar to minHeap);
each key in the left subtree is less than every key in the right subtree.
The subtrees themselves are min-first BSTs.

See also CartesianTree.h, Treap.h
*/
class MinFirstBST
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
	MinFirstBST(): m_root(nullptr) {}
	~MinFirstBST(){}

	void Insert(const int & val)
	{
		this->insertRecur(val, m_root);
		std::cout << "MinFirstBST Insert: " << val << std::endl;
	}
	void Remove(const int & val)
	{
		this->removeRecur(val, m_root);
		std::cout << "MinFirstBST Remove: " << val << std::endl;
	}
	bool Contains(const int & val) const
	{
		bool res = this->containsRecur(val, m_root);
		std::cout << "MinFirstBST Contains \"" << val << "\": " << res << std::endl;
		return res;
	}
	TreeNode * FindLowerBound(const int & val) const
	{
		TreeNode * lb = this->findLowerBoundRecur(val, m_root);
		std::string found = lb == nullptr ? "N" : std::to_string(lb->val);
		std::string left = lb && lb->left ? std::to_string(lb->left->val) : "N";
		std::string right = lb && lb->right ? std::to_string(lb->right->val) : "N";
		std::cout << "MinFirstBST FindLowerBound \"" << val << "\": " << found << " (" << left << "," << right << ")" << std::endl;
		return lb;
	}
	TreeNode * FindUpperBound(const int & val) const
	{
		bool foundVal = false;
		TreeNode * ub = this->findUpperBoundRecur(val, m_root, foundVal);
		std::string found = ub == nullptr ? "N" : std::to_string(ub->val);
		std::string left = ub && ub->left ? std::to_string(ub->left->val) : "N";
		std::string right = ub && ub->right ? std::to_string(ub->right->val) : "N";
		std::cout << "MinFirstBST FindUpperBound \"" << val << "\": " << found << " (" << left << "," << right << ")" << std::endl;
		return ub;
	}
	std::vector<int> GetSortedKeys()
	{
		std::vector<int> res;
		this->preorderTraversal(m_root, res);
		std::cout << "MinFirstBST GetSortedKeys: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void insertRecur(int val, TreeNode *& n)
	{
		if (n == nullptr)
			n = new TreeNode(val);
		else
		{
			if (val < n->val)
			{
				int curVal = n->val;
				n->val = val;
				val = curVal;
			}
			if (val == n->val)//1
				this->insertRecur(val, n->left);
			else if (n->right && val < n->right->val)//2
				this->insertRecur(val, n->left);
			else if (n->left && val == n->left->val)//3
				this->insertRecur(val, n->left);
			else//4
				this->insertRecur(val, n->right);
		}
	}
	void removeRecur(const int & val, TreeNode *& n)
	{
		if (n == nullptr || val < n->val)
			return;
		if (val == n->val)//1
		{
			if (n->left)
			{
				if (val == n->left->val)
					this->removeRecur(val, n->left);
				else
				{
					n->val = n->left->val;
					this->removeRecur(n->val, n->left);
				}
			}
			else if (n->right)
			{
				n->val = n->right->val;
				this->removeRecur(n->val, n->right);
			}
			else//leaf
			{
				TreeNode * toDel = n;
				n = nullptr;
				delete toDel;
			}
		}
		else if (n->right && val < n->right->val)//2
			this->removeRecur(val, n->left);
		else if (n->left && val == n->left->val)//3
			this->removeRecur(val, n->left);
		else//4
			this->removeRecur(val, n->right);
	}
	bool containsRecur(const int & val, TreeNode * n) const
	{
		if (n == nullptr || val < n->val)
			return false;
		else if (val == n->val)//1
			return true;

		else if (n->right && val < n->right->val)//2
			return this->containsRecur(val, n->left);
		else if (n->left && val == n->left->val)//3
			return this->containsRecur(val, n->left);
		else//4
			return this->containsRecur(val, n->right);
	}
	TreeNode * findLowerBoundRecur(const int & val, TreeNode * n) const
	{
		if (n == nullptr || val < n->val)
			return nullptr;
		else if (val == n->val)//1
		{
			TreeNode * findLeft = this->findLowerBoundRecur(val, n->left);
			if (findLeft != nullptr)
				return findLeft;
			else
				return n;
		}

		else if (n->right && val < n->right->val)//2
			return this->findLowerBoundRecur(val, n->left);
		else if (n->left && val == n->left->val)//3
			return this->findLowerBoundRecur(val, n->left);
		else//4
			return this->findLowerBoundRecur(val, n->right);
	}
	TreeNode * findUpperBoundRecur(const int & val, TreeNode * n, bool & foundVal) const
	{
		if (n == nullptr || (!foundVal && val < n->val))
			return nullptr;
		else if (foundVal && val < n->val)
			return n;
		else if (val == n->val)//1
		{
			if (!foundVal)
				foundVal = true;
			TreeNode * findLeft = this->findUpperBoundRecur(val, n->left, foundVal);
			if (findLeft != nullptr)
				return findLeft;
			else
				return this->findUpperBoundRecur(val, n->right, foundVal);
		}

		else if (n->right && val < n->right->val)//2
		{
			TreeNode * foundLeft = this->findUpperBoundRecur(val, n->left, foundVal);
			if (foundLeft)
				return foundLeft;
			else if (foundVal)
				return this->findUpperBoundRecur(val, n->right, foundVal);
			else
				return nullptr;
		}
		else if (n->left && val == n->left->val)//3
			return this->findUpperBoundRecur(val, n->left, foundVal);
		else//4
			return this->findUpperBoundRecur(val, n->right, foundVal);
	}
	void preorderTraversal(TreeNode * n, std::vector<int> & res)
	{
		if (n == nullptr)
			return;
		res.push_back(n->val);
		this->preorderTraversal(n->left, res);
		this->preorderTraversal(n->right, res);
	}
public:
	void Print()
	{
		std::ostringstream oss;
		oss << "MinFirstBST (val2: leftCount-not implemented):" << std::endl;
		PrintBinaryTree<TreeNode, std::ostringstream>(m_root, oss);
		std::cout << oss.str() << std::endl;
	}
private:
	TreeNode * m_root;
};

template<>
std::string PrintBinaryTree<MinFirstBST::TreeNode, std::ostringstream>::selectVal2(int depth, MinFirstBST::TreeNode * n)
{
	return std::to_string(n->leftCount);
}
/*
MinFirstBST Insert: 4
MinFirstBST Insert: 11
MinFirstBST Insert: 3
MinFirstBST Insert: 2
MinFirstBST Insert: 1
MinFirstBST Insert: 3
MinFirstBST Insert: 11
MinFirstBST Insert: 17
MinFirstBST Insert: 5
MinFirstBST Insert: 4
MinFirstBST Insert: 2
MinFirstBST Insert: 3
MinFirstBST Insert: 7
MinFirstBST Insert: 18
MinFirstBST Insert: 4
MinFirstBST Insert: 19
MinFirstBST Insert: 14
MinFirstBST Insert: 17
MinFirstBST Insert: 11
MinFirstBST Insert: 9
MinFirstBST Insert: 14
MinFirstBST Insert: 11
MinFirstBST Insert: 12
MinFirstBST Insert: 13
MinFirstBST Insert: 15
MinFirstBST Insert: 15
MinFirstBST Insert: 6
MinFirstBST Insert: 5
MinFirstBST Insert: 17
MinFirstBST Insert: 17
MinFirstBST Insert: 19
MinFirstBST Insert: 18
MinFirstBST Insert: 5
MinFirstBST Insert: 4
MinFirstBST Contains "6": 1
MinFirstBST Contains "9": 1
MinFirstBST Contains "13": 1
MinFirstBST Contains "15": 1
MinFirstBST FindLowerBound "11": 11 (N,N)
MinFirstBST FindLowerBound "17": 17 (N,N)
MinFirstBST FindLowerBound "7": 7 (N,9)
MinFirstBST FindLowerBound "2": 2 (3,N)
MinFirstBST FindUpperBound "11": 12 (N,13)
MinFirstBST FindUpperBound "17": 18 (18,19)
MinFirstBST FindUpperBound "13": 14 (14,15)
MinFirstBST FindUpperBound "5": 6 (N,N)
MinFirstBST FindUpperBound "9": 11 (11,17)
MinFirstBST FindUpperBound "7": 9 (N,N)
MinFirstBST FindUpperBound "19": N (N,N)
MinFirstBST FindUpperBound "6": 7 (N,9)
MinFirstBST GetSortedKeys: 1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 6, 7, 9, 11, 11, 11, 11, 12, 13, 14, 14, 15, 15, 17, 17, 17, 17, 18, 18, 19, 19
MinFirstBST (val2: leftCount-not implemented):
                                                              
                                                               0
                                ______________________________ 1______________________________
                               /                                                               \
                               0                                                               0
                ______________ 2______________                                  ______________11______________
               /                               \                               /                               \
               0                               0                               0                               0
        ______ 2______                  ______ 4______                  ______11______                  ______17______
       /               \               /               \               /               \               /               \
       0               X               0               0               0               0               0               0
    __ 3__          __ N__          __ 4__          __ 5__          __11__          __14__          __17__          __18__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   0       X       X       X       0       X       0       0       0       0       0       0       0       X       0       0
   3       N       N       N       4       N       5       7      11      12      14      15      17       N      18      19
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 0   X   X   X   X   X   X   X   0   X   X   X   0   0   X   0   X   X   X   0   X   X   0   X   0   X   X   X   X   X   0   X
 3   N   N   N   N   N   N   N   4   N   N   N   5   6   N   9   N   N   N  13   N   N  15   N  17   N   N   N   N   N  19   N


MinFirstBST Remove: 1
MinFirstBST Remove: 17
MinFirstBST (val2: leftCount-not implemented):
                                                              
                                                               0
                                ______________________________ 2______________________________
                               /                                                               \
                               0                                                               0
                ______________ 2______________                                  ______________11______________
               /                               \                               /                               \
               0                               0                               0                               0
        ______ 3______                  ______ 4______                  ______11______                  ______17______
       /               \               /               \               /               \               /               \
       0               X               0               0               0               0               0               0
    __ 3__          __ N__          __ 4__          __ 5__          __11__          __14__          __17__          __18__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   0       X       X       X       0       X       0       0       0       0       0       0       0       X       0       0
   3       N       N       N       4       N       5       7      11      12      14      15      17       N      18      19
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   0   X   X   X   0   0   X   0   X   X   X   0   X   X   0   X   X   X   X   X   X   X   0   X
 N   N   N   N   N   N   N   N   4   N   N   N   5   6   N   9   N   N   N  13   N   N  15   N   N   N   N   N   N   N  19   N


MinFirstBST Remove: 11
MinFirstBST Remove: 18
MinFirstBST (val2: leftCount-not implemented):
                                                              
                                                               0
                                ______________________________ 2______________________________
                               /                                                               \
                               0                                                               0
                ______________ 2______________                                  ______________11______________
               /                               \                               /                               \
               0                               0                               0                               0
        ______ 3______                  ______ 4______                  ______11______                  ______17______
       /               \               /               \               /               \               /               \
       0               X               0               0               0               0               0               0
    __ 3__          __ N__          __ 4__          __ 5__          __11__          __14__          __17__          __18__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   0       X       X       X       0       X       0       0       X       0       0       0       0       X       X       0
   3       N       N       N       4       N       5       7       N      12      14      15      17       N       N      19
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   0   X   X   X   0   0   X   0   X   X   X   0   X   X   0   X   X   X   X   X   X   X   0   X
 N   N   N   N   N   N   N   N   4   N   N   N   5   6   N   9   N   N   N  13   N   N  15   N   N   N   N   N   N   N  19   N


MinFirstBST Remove: 4
MinFirstBST Remove: 14
MinFirstBST (val2: leftCount-not implemented):
                                                              
                                                               0
                                ______________________________ 2______________________________
                               /                                                               \
                               0                                                               0
                ______________ 2______________                                  ______________11______________
               /                               \                               /                               \
               0                               0                               0                               0
        ______ 3______                  ______ 4______                  ______11______                  ______17______
       /               \               /               \               /               \               /               \
       0               X               0               0               0               0               0               0
    __ 3__          __ N__          __ 4__          __ 5__          __11__          __14__          __17__          __18__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   0       X       X       X       0       X       0       0       X       0       X       0       0       X       X       0
   3       N       N       N       4       N       5       7       N      12       N      15      17       N       N      19
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   0   0   X   0   X   X   X   0   X   X   0   X   X   X   X   X   X   X   0   X
 N   N   N   N   N   N   N   N   N   N   N   N   5   6   N   9   N   N   N  13   N   N  15   N   N   N   N   N   N   N  19   N


MinFirstBST Remove: 2
MinFirstBST (val2: leftCount-not implemented):
                                                              
                                                               0
                                ______________________________ 2______________________________
                               /                                                               \
                               0                                                               0
                ______________ 3______________                                  ______________11______________
               /                               \                               /                               \
               0                               0                               0                               0
        ______ 3______                  ______ 4______                  ______11______                  ______17______
       /               \               /               \               /               \               /               \
       0               X               0               0               0               0               0               0
    __ 3__          __ N__          __ 4__          __ 5__          __11__          __14__          __17__          __18__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       0       X       0       0       X       0       X       0       0       X       X       0
   N       N       N       N       4       N       5       7       N      12       N      15      17       N       N      19
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   0   0   X   0   X   X   X   0   X   X   0   X   X   X   X   X   X   X   0   X
 N   N   N   N   N   N   N   N   N   N   N   N   5   6   N   9   N   N   N  13   N   N  15   N   N   N   N   N   N   N  19   N


MinFirstBST Remove: 11
MinFirstBST Remove: 18
MinFirstBST (val2: leftCount-not implemented):
                                                              
                                                               0
                                ______________________________ 2______________________________
                               /                                                               \
                               0                                                               0
                ______________ 3______________                                  ______________11______________
               /                               \                               /                               \
               0                               0                               0                               0
        ______ 3______                  ______ 4______                  ______11______                  ______17______
       /               \               /               \               /               \               /               \
       0               X               0               0               0               0               0               0
    __ 3__          __ N__          __ 4__          __ 5__          __12__          __14__          __17__          __19__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       0       X       0       0       X       0       X       0       0       X       X       0
   N       N       N       N       4       N       5       7       N      13       N      15      17       N       N      19
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   0   0   X   0   X   X   X   X   X   X   0   X   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   N   N   N   N   N   N   5   6   N   9   N   N   N   N   N   N  15   N   N   N   N   N   N   N   N   N


MinFirstBST Remove: 5
MinFirstBST Remove: 11
MinFirstBST (val2: leftCount-not implemented):
                                                              
                                                               0
                                ______________________________ 2______________________________
                               /                                                               \
                               0                                                               0
                ______________ 3______________                                  ______________11______________
               /                               \                               /                               \
               0                               0                               0                               0
        ______ 3______                  ______ 4______                  ______12______                  ______17______
       /               \               /               \               /               \               /               \
       0               X               0               0               0               0               0               0
    __ 3__          __ N__          __ 4__          __ 5__          __13__          __14__          __17__          __19__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       0       X       0       0       X       X       X       0       0       X       X       0
   N       N       N       N       4       N       5       7       N       N       N      15      17       N       N      19
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   X   0   X   0   X   X   X   X   X   X   0   X   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   N   N   N   N   N   N   N   6   N   9   N   N   N   N   N   N  15   N   N   N   N   N   N   N   N   N


MinFirstBST Remove: 4
MinFirstBST Remove: 11
MinFirstBST (val2: leftCount-not implemented):
                                                              
                                                               0
                                ______________________________ 2______________________________
                               /                                                               \
                               0                                                               0
                ______________ 3______________                                  ______________12______________
               /                               \                               /                               \
               0                               0                               0                               0
        ______ 3______                  ______ 4______                  ______13______                  ______17______
       /               \               /               \               /               \               /               \
       0               X               0               0               X               0               0               0
    __ 3__          __ N__          __ 4__          __ 5__          __ N__          __14__          __17__          __19__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       X       X       0       0       X       X       X       0       0       X       X       0
   N       N       N       N       N       N       5       7       N       N       N      15      17       N       N      19
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   X   0   X   0   X   X   X   X   X   X   0   X   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   N   N   N   N   N   N   N   6   N   9   N   N   N   N   N   N  15   N   N   N   N   N   N   N   N   N

*/
#endif