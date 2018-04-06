#ifndef LOWEST_COMMON_ANCESTOR_BINARY_TREE_H
#define LOWEST_COMMON_ANCESTOR_BINARY_TREE_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <stack>
#include "Debug.h"
#include "PrintBinaryTree.h"
/*
Leetcode: Lowest Common Ancestor of a Binary Tree
Elements of programming interview, BinaryTree: Find_Recur, Find_Iterate_WParentPtr O(h) time, O(1) space
Elements of programming interview, HashTable: Find_IterateHashTable_WParentPtr O(max(depthA, depthB)-depthLCA) time and space
http://www.geeksforgeeks.org/lowest-common-ancestor-binary-tree-set-1/

Cracking the coding interview 4.6
Design an algorithm and write code to find the first common ancestor of two nodes in a binary tree.
Avoid storing additional nodes in a data structure. NOTE: This is not necessarily a binary search tree.

Top 20 coding interview: Find_IterateStack_WParentPtr, Find_Iterate_WParentPtr, Find_XOR2PathSum

O(n) time

See also CartesianTree.h
*/
class LowestCommonAncestorBinaryTree
{
public:
	LowestCommonAncestorBinaryTree(){}
	~LowestCommonAncestorBinaryTree(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL), parent(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
		TreeNode * parent;
	};

	//1.0.a the best
	TreeNode * FindRecur(TreeNode * root, TreeNode * a, TreeNode * b)
	{
		TreeNode * res = recur(root, a, b);
		return res;
	}
private:
	TreeNode * recur(TreeNode * cur, TreeNode * a, TreeNode * b)
	{
		if (cur == NULL) return NULL;
		if (cur == a || cur == b) return cur;
		TreeNode * left = recur(cur->left, a, b);
		TreeNode * right = recur(cur->right, a, b);
		if (left && right) return cur;
		return left != NULL ? left : right;
	}
public:
	//1.0.b
	TreeNode * FindIteratePostorderStack_LeftSibStk(TreeNode * root, TreeNode * a, TreeNode * b)
	{
		if (root == NULL) return NULL;
		std::stack<TreeNode *> stk;
		std::stack<TreeNode *> leftSibStk;
		TreeNode * LCA = NULL;
		TreeNode * leftFound = NULL;
		TreeNode * rightFound = NULL;
		TreeNode * cur = root;
		//Push LR Deepest Nodes
		while (cur)
		{
			stk.push(cur);
			if (cur->left) cur = cur->left;
			else cur = cur->right;
		}
		while (!stk.empty())
		{
			cur = stk.top(); stk.pop();
			TreeNode * top = cur;


			if (cur == a || cur == b) LCA = cur;//found a or b
			else if (leftFound && rightFound) LCA = cur;//found LCA
			else if (leftFound) LCA = leftFound;//nodes above LCA
			else if (rightFound) LCA = rightFound;//nodes above LCA
			else LCA = NULL;//!leftFound && !rightFound


			//Push LR Deepest Nodes
			if (!stk.empty() && stk.top()->left == cur)//going up from left subtree
			{
				cur = stk.top()->right;//right sibling
				if (cur) leftSibStk.push(LCA);
				while (cur)
				{
					stk.push(cur);
					if (cur->left) cur = cur->left;
					else cur = cur->right;
				}
			}

			//3 cases
			cur = top;
			if (!stk.empty() && stk.top()->left == cur)//going up from left subtree w/o right sibling
			{
				leftFound = LCA;
				rightFound = NULL;//must reset
			}
			else if (!stk.empty() && stk.top()->right == cur)//going up from right subtree
			{
				rightFound = LCA;
				if (stk.top()->left) leftFound = leftSibStk.top(), leftSibStk.pop();
			}
			else//going (down) to right sibling leaf
			{
				leftFound = NULL;//must reset
				rightFound = NULL;//must reset
			}
		}
		return LCA;
	}

	//1.1 top down from root, without parent ptr
	TreeNode * Find_Recur(TreeNode * root, TreeNode * a, TreeNode * b)
	{
		std::pair<int, TreeNode *> res = this->find_Recur(root, a, b);
		std::string node = res.second == nullptr ? "N" : std::to_string(res.second->val);
		std::cout << "LowestCommonAncestorBinaryTree Find_Recur for \"" << a->val << "," << b->val << "\": " << node << std::endl;
		return res.second;
	}
private:
	std::pair<int, TreeNode *> find_Recur(TreeNode * root, TreeNode * a, TreeNode * b)
	{
		if (root == nullptr)
			return{ 0, nullptr };

		std::pair<int, TreeNode *> left = this->find_Recur(root->left, a, b);
		if (left.first == 2)//found both nodes in left subtree
			return left;

		std::pair<int, TreeNode *> right = this->find_Recur(root->right, a, b);
		if (right.first == 2)//found both nodes in right subtree
			return right;

		int foundCount = left.first + right.first + (root == a || root == b);

		return{ foundCount, foundCount == 2 ? root : nullptr };
	}

	//2. bottom up, with parent ptr
	//2.0.1 construct ChdToParent map
    TreeNode * Find_Iterate_ChdToP(TreeNode * root, TreeNode * a, TreeNode * b)
    {
        if (root == NULL) return NULL;
        std::unordered_map<TreeNode *, TreeNode *> chdToP;
        build_ChdToP_Recur(root, chdToP);
        chdToP[root] = NULL;
        TreeNode * LCA = NULL;
        std::unordered_set<TreeNode *> visit;
        while (a || b)
        {
            if (a)
            {
                if (visit.count(a))
                {
                    LCA = a;
                    break;
                }
                visit.insert(a);
                a = chdToP[a];
            }
            if (b)
            {
                if (visit.count(b))
                {
                    LCA = b;
                    break;
                }
                visit.insert(b);
                b = chdToP[b];
            }
        }
        return LCA;
    }
    //2.0.2 construct ChdToParent map
    TreeNode * Find_Iterate_ChdToP_Queue(TreeNode * root, TreeNode * a, TreeNode * b)
    {
        if (root == NULL) return NULL;
        std::unordered_map<TreeNode *, TreeNode *> chdToP;
        build_ChdToP_Recur(root, chdToP);
        chdToP[root] = NULL;
        TreeNode * LCA = NULL;
        std::unordered_set<TreeNode *> visit;
        std::queue<TreeNode *> que;
        que.push(a); que.push(b);
        while (!que.empty())
        {
            TreeNode * cur = que.front(); que.pop();
            if (visit.count(cur))
            {
                LCA = cur;
                break;
            }
            visit.insert(cur);
            if (chdToP.count(cur) && chdToP[cur])
                que.push(chdToP[cur]);
        }
        return LCA;
    }
    void build_ChdToP_Recur(TreeNode * cur, std::unordered_map<TreeNode*, TreeNode*> & chdToP)
    {
        if (cur == NULL) return;
        if (cur->left)
        {
            chdToP[cur->left] = cur;
            build_ChdToP_Recur(cur->left, chdToP);
        }
        if (cur->right)
        {
            chdToP[cur->right] = cur;
            build_ChdToP_Recur(cur->right, chdToP);
        }
    }
	//2.1 count depth difference
public:
	TreeNode * Find_Iterate_WParentPtr(TreeNode * a, TreeNode * b)
	{
		TreeNode * lower = a;
		TreeNode * higher = b;
		int depthA = this->GetDepth_ParentPtr(a);
		int depthB = this->GetDepth_ParentPtr(b);
		if (depthB > depthA)
			std::swap(lower, higher);

		/*advance lower node up first*/
		int diff = std::abs(depthA - depthB);
		while (diff--)
			lower = lower->parent;

		/*advance both lower and higher nodes up until they meet*/
		while (lower != higher)
		{
			lower = lower->parent;
			higher = higher->parent;
		}

		std::string node = lower == nullptr ? "N" : std::to_string(lower->val);
		std::cout << "LowestCommonAncestorBinaryTree Find_Iterate_WParentPtr for \"" << a->val << "," << b->val << "\": " << node << std::endl;
		return lower;
	}
private:
	int GetDepth_ParentPtr(TreeNode * node)
	{
		int d = 0;
		while (node)
		{
			++d;
			node = node->parent;
		}
		return d;
	}

	//2.2 use hash table
public:
	TreeNode * Find_IterateHashTable_WParentPtr(TreeNode * a, TreeNode * b)
	{
		std::unordered_set<TreeNode *> visited;
		TreeNode * res = nullptr;
		TreeNode * i = a;
		TreeNode * j = b;
		while (i || j)
		{
			if (i)
			{
				if (visited.emplace(i).second == false)//add i failed because i already exists in visited
				{
					res = i;
					break;
				}
				i = i->parent;
			}
			if (j)
			{
				if (visited.emplace(j).second == false)//add j failed because j already exists in visited
				{
					res = j;
					break;
				}
				j = j->parent;
			}
		}

		std::string node = res == nullptr ? "N" : std::to_string(res->val);
		std::cout << "LowestCommonAncestorBinaryTree Find_IterateHashTable_WParentPtr for \"" << a->val << "," << b->val << "\": " << node << std::endl;
		return res;
	}

	//2.3 use stack
	TreeNode * Find_IterateStack_WParentPtr(TreeNode * a, TreeNode * b)
	{
		TreeNode * i = a;
		TreeNode * j = b;
		std::stack<TreeNode *> stk1;
		std::stack<TreeNode *> stk2;
		while (i)
		{
			stk1.push(i);
			i = i->parent;
		}
		while (j)
		{
			stk2.push(j);
			j = j->parent;
		}

		TreeNode * res = nullptr;
		while (!stk1.empty() && !stk2.empty() && stk1.top() == stk2.top())
		{
			res = stk1.top();
			stk1.pop();
			stk2.pop();
		}

		std::string node = res == nullptr ? "N" : std::to_string(res->val);
		std::cout << "LowestCommonAncestorBinaryTree Find_IterateStack_WParentPtr for \"" << a->val << "," << b->val << "\": " << node << std::endl;
		return res;
	}

	//3. top down from root with given val, need to check exist of nodes (NOTE: root is not BST!)
public:
	TreeNode * Find_Recur(TreeNode * root, int val1, int val2)
	{
		bool visit1 = false;
		bool visit2 = false;
		/*1. find the candidate LCA*/
		TreeNode * res = this->find_Recur(root, val1, val2, visit1, visit2);
		/*
		2. check if both val1 and val2 exist
		3 cases:
		1. the LCA isn't either val1 or val2
		2. the LCA is val1 itself
		3. the LCA is val2 itself
		*/
		if (visit1 && visit2 || visit1 && this->exist(root, val2) || visit2 && this->exist(root, val1))
		{ }
		else
			res = NULL;
		std::cout << "LowestCommonAncestorBinaryTree Find_Recur for \"" << val1 << "," << val2 << "\": ";
		(res == NULL) ? std::cout << "NULL" : std::cout << res->val;
		std::cout << std::endl;
		return res;
	}
private:
	/*
	returns the lowest common ancestor of the two nodes if both exist in the tree, OR
	returns the existing node if the other one doesn't exist, OR
	returns nullptr if both don't exist
	*/
	TreeNode * find_Recur(TreeNode * curNode, int val1, int val2, bool & visit1, bool & visit2)
	{
		if (curNode == NULL)
			return NULL;
		if (curNode->val == val1)
		{
			visit1 = true;
			return curNode;
		}
		if (curNode->val == val2)
		{
			visit2 = true;
			return curNode;
		}
		TreeNode * leftLCA = this->find_Recur(curNode->left, val1, val2, visit1, visit2);
		TreeNode * rightLCA = this->find_Recur(curNode->right, val1, val2, visit1, visit2);

		if (leftLCA && rightLCA)
			return curNode;
		return leftLCA != NULL ? leftLCA : rightLCA;
	}
	bool exist(TreeNode * root, int val)
	{
		if (root == NULL)
			return false;
		if (root->val == val || this->exist(root->left, val) || this->exist(root->right, val))
			return true;
		return false;
	}

public:
	//4. XOR 2 PathSum
	int Find_XOR2PathSum(TreeNode * root, TreeNode * a, TreeNode * b)
	{
		//1. compute max depth
		int maxDepth = this->maxDepthRecur(root);

		//2. construct path sum for each node
		this->computePathSumPreorderRecur(root, 0, 0, maxDepth);

		//3. compute xor of a's path sum and b's path sum
		int XOR = a->val ^ b->val;

		//4. the LCA node's path sum is: the highest common bits of a's path sum and b's path sum + digit_1 + padded 0s
		int posHighestBitSet = 0;
		int xor1 = XOR;
		while (xor1 >>= 1)
			++posHighestBitSet;

		int prefix0Mask = 0;
		int prefix0Count = 31 - posHighestBitSet;
		while (prefix0Count--)
		{
			//push 1 to the left!!!!
			prefix0Mask >>= 1;
			prefix0Mask |= (1 << 31);
		}
		
		int res = a->val & prefix0Mask;//keep the prefix0 part on left side of the highest set bit of XOR
		res |= (1 << posHighestBitSet);//insert 1 as the highest set bit of XOR

		std::cout << "LowestCommonAncestorBinaryTree Find_XOR2PathSum for \"" << a->val << "," << b->val << "\": " << res << std::endl;
		return res;
	}
private:
	void computePathSumPreorderRecur(TreeNode * root, int pathSum, int depth, int maxDepth)
	{
		if (root == nullptr)
			return;
		//node val = pathSumDigits + Digit_1 (for Node itself) + Padded_Digit_0s
		root->val = ((pathSum << 1) | 1) << (maxDepth - depth - 1);
		this->computePathSumPreorderRecur(root->left, (pathSum << 1), depth + 1, maxDepth);//left: append Digit_0 to pathSum
		this->computePathSumPreorderRecur(root->right, (pathSum << 1) | 1, depth + 1, maxDepth);//right: append Digit_1 to pathSum
	}
	int maxDepthRecur(TreeNode * cur)
	{
		if (cur == NULL)
			return 0;
		return std::max(this->maxDepthRecur(cur->left), this->maxDepthRecur(cur->right)) + 1;
	}

public:
	static void DeleteTree(TreeNode * root)
	{
		if (root == 0)
			return;

		DeleteTree(root->left);
		DeleteTree(root->right);

		//post order
		delete root;
		root = 0;
	}
};

template<>
std::string PrintBinaryTree<LowestCommonAncestorBinaryTree::TreeNode, std::ostringstream>::selectVal2(int depthY, LowestCommonAncestorBinaryTree::TreeNode * n)
{
	std::ostringstream oss;
	if (n->parent)
		oss << n->parent->val;
	else
		oss << "N";
	return oss.str();
};

/*
Top 20 coding interview
Find LCA with XOR 2 PathSum:
PathSum of Each Node = PathSum + Digit_1 + Padded 0s
Left Child Edge Path Sum: append a 0
Right Child Edge Path Sum: append a 1

                  ___________1000___________
                 /                          \
          ___0100___                      ___1100___
         /          \                    /          \
     0010            0110            1010            1110
    /    \          /    \          /    \          /    \
0001      0011  0101      0111  1001      1011  1101      1111

LCA(0010,0111) = 0100
0010
XOR
0111
----
0101
^^-----highest set bit
\------prefix 0's are highest common bits

LCA = Keep the highest common bits, insert the highest set bit, pad 0's = 0100

LCA(1001,1011) = 1010
1001
XOR
1011
----
0010
\/^-----highest set bit
 \------prefix 0's are highest common bits

LCA = Keep the highest common bits, insert the highest set bit, pad 0's = 1010
*/

/*
LowestCommonAncestorBinaryTree Find_Recur for "4,3": 3
LowestCommonAncestorBinaryTree Find_Recur for "4,5": 5
LowestCommonAncestorBinaryTree Find_Recur for "4,7": 7
LowestCommonAncestorBinaryTree Find_Recur for "4,4": 4
LowestCommonAncestorBinaryTree Find_Recur for "8,9": 9
LowestCommonAncestorBinaryTree Find_Recur for "8,13": 11
LowestCommonAncestorBinaryTree Find_Iterate_WParentPtr for "8,9": 9
LowestCommonAncestorBinaryTree Find_Iterate_WParentPtr for "8,13": 11
LowestCommonAncestorBinaryTree Find_IterateHashTable_WParentPtr for "8,9": 9
LowestCommonAncestorBinaryTree Find_IterateHashTable_WParentPtr for "8,13": 11
LowestCommonAncestorBinaryTree Find_IterateStack_WParentPtr for "8,9": 9
LowestCommonAncestorBinaryTree Find_IterateStack_WParentPtr for "8,13": 11
LowestCommonAncestorBinaryTree Find_XOR2PathSum for "9,10": 10
LowestCommonAncestorBinaryTree Find_XOR2PathSum for "9,14": 12
              
               N
        ______ 7______
       /               \
       7               7
    __ 3__          __11__
   /       \       /       \
   3       3      11      11
   1       5       9      13
 /   \   /   \   /   \   /   \
 1   1   5   5   9   9  13  13
 0   2   4   6   8  10  12  14

              
               N
        ______ 8______
       /               \
       8               8
    __ 4__          __12__
   /       \       /       \
   4       4      12      12
   2       6      10      14
 /   \   /   \   /   \   /   \
 2   2   6   6  10  10  14  14
 1   3   5   7   9  11  13  15

*/
#endif