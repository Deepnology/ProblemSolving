#ifndef KD_TREE_H
#define KD_TREE_H
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
#include "DeleteBinaryTree.h"
/*
Chapter 12.5 k-d Trees
http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/KdTree.cpp
http://algs4.cs.princeton.edu/92search/
http://www.geeksforgeeks.org/k-dimensional-tree/
2-dimention tree for 2-dimentional range query
The 2-dimentional search tree has the simple property that branching on odd levels
is done with respect to the first key, and branching on even levels is done with respect
to the second key.
The root is arbitrarily chosen to be an odd level.
                         _________[53,14]________
					    /                        \
              ____[27,28]____                    [67,51]
			 /               \                   /     \
       [30,11]               [31,85]        [70,3]     [99,90]
	  /       \              /     \                   /
[29,16]       [40,26]   [7,39]     [32,29]       [82,64]
              /              \                         \
        [38,23]              [15,61]                   [73,75]
*/
class KdTree
{
public:
	struct TreeNode
	{
		TreeNode(const std::vector<int> & item) : val(item), left(nullptr), right(nullptr){}
		~TreeNode(){}
		std::vector<int> val;//a pair of data. 1st data: dimension=0, 2nd data: dimension=1
		TreeNode * left;
		TreeNode * right;
	};
private:
	TreeNode * m_root;
	int K;
public:
	explicit KdTree(int k): m_root(nullptr), K(k) {}
	KdTree(int k, const std::vector<std::vector<int> > & v) : m_root(nullptr), K(k)
	{
		int N = v.size();
		for (int i = 0; i < N; ++i)
			this->Insert(v[i]);
	}
	~KdTree()
	{
		DeleteBinaryTree<TreeNode>().LeftRotate_Iterate(m_root);
	}
	void Insert(const std::vector<int> & val)
	{
		//this->insertRecur(val, m_root, 0);//approach1
		m_root = insertRecur2(val, m_root, 0);//approach2
		std::cout << "KdTree Insert: " << val[0] << "," << val[1] << std::endl;
	}
	/*
	find nodes in between (low[0],high[0]) and (low[1],high[1]), which are satisfying
	low[0] <= val[0] <= high[0]
	low[1] <= val[1] <= high[1]
	*/
	std::vector<std::vector<int>> FindRange(const std::vector<int> & low, const std::vector<int> & high)//O(sqrt(N)+K) time, where K is num of points in range
	{
		std::vector<std::vector<int> > res;
		this->findRangeRecur(low, high, m_root, 0, res);//preorder traversal
		std::cout << "KdTree FindRange for low=\"" << Debug::ToStr1D<int>()(low) << "\", high=\"" << Debug::ToStr1D<int>()(high) << "\": " << std::endl;
		Debug::Print2D<int>()(res, false);
		return res;
	}
	/*
	find nodes in a circle centered at point with radius
	sqrt(deltaX*deltaX+deltaY*deltaY) <= radius
	*/
	std::vector<std::vector<int>> FindRange(const std::vector<int> & point, double radius)//worst case: O(N) time, avg case: O(logN) time
	{
		std::vector<std::vector<int> > res;
		this->findRangeRecur(m_root, 0, point, radius, res);//preorder traversal
		std::cout << "KdTree FindRange for point=\"" << Debug::ToStr1D<int>()(point) << "\", radius=\"" << radius << "\": " << std::endl;
		Debug::Print2D<int>()(res, false);
		return res;
	}

	std::vector<int> FindNearest(const std::vector<int> & point)//worst case: O(N) time, avg case: O(logN) time
	{
		std::vector<int> res;
		double minDist = INT_MAX;
		this->findNearestRecur(m_root, 0, point, minDist, res);
		std::cout << "KdTree FindNearest for point=\"" << Debug::ToStr1D<int>()(point) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
	std::vector<std::vector<int>> FindKNearest(std::vector<int> & point, int K)
	{
		//use maxHeap
		std::vector<std::vector<int>> res;
		return res;
	}
	int FindMin(int tgtDimension)
	{
		TreeNode * res = findMinRecur(m_root, 0, tgtDimension);
		std::cout << "KdTree FindMin for dimension=\"" << tgtDimension << "\": " << (res == NULL ? INT_MAX : res->val[tgtDimension]) << std::endl;
		return res == NULL ? INT_MAX : res->val[tgtDimension];
	}
	void Remove(const std::vector<int> & val)
	{
		m_root = removeRecur(m_root, 0, val);
		std::cout << "KdTree Remove: " << val[0] << "," << val[1] << std::endl;
	}
	int Count() const
	{
		return 0;
	}
	bool Empty() const
	{
		return false;
	}

private:
	void insertRecur(const std::vector<int> & val, TreeNode *& curNode, int depth)//dimention=0: 1st data, dimention=1: 2nd data
	{
		int dimension = depth % K;
		if (curNode == nullptr)
			curNode = new TreeNode(val);
		else if (val[dimension] < curNode->val[dimension])//too big: go left
			this->insertRecur(val, curNode->left, depth + 1);
		else//too small or equal: go right
			this->insertRecur(val, curNode->right, depth + 1);
	}
	TreeNode * insertRecur2(const std::vector<int> & val, TreeNode * cur, int depth)
	{
		int dimension = depth % K;
		if (cur == nullptr)
			return new TreeNode(val);
		else if (val[dimension] < cur->val[dimension])//too big: go left
		{
			cur->left = insertRecur2(val, cur->left, depth + 1);
			return cur;
		}
		else//too small or equal: go right
		{
			cur->right = insertRecur2(val, cur->right, depth + 1);
			return cur;
		}
	}
	void findRangeRecur(const std::vector<int> & low, const std::vector<int> & high, TreeNode * curNode, int depth, std::vector<std::vector<int>> & res)
	{
		int dimension = depth % K;
		if (curNode == nullptr) return;
		if (low[0] <= curNode->val[0] && high[0] >= curNode->val[0] &&//loX <= cur->x <= hiX
			low[1] <= curNode->val[1] && high[1] >= curNode->val[1])//loY <= cur->y <= hiY
		{
			res.push_back(curNode->val);
		}
		if (low[dimension] <= curNode->val[dimension])//1. check lower boundary: if cur->xORy is covered by tgt xORy lower boundary, need to search left (too big: go left)
			this->findRangeRecur(low, high, curNode->left, depth + 1, res);
		if (high[dimension] >= curNode->val[dimension])//2. check higher boundary: if cur->xORy is covered by tgt xORy higher boundary, need to search right (too small: go right)
			this->findRangeRecur(low, high, curNode->right, depth + 1, res);
	}
	void findRangeRecur(TreeNode * cur, int depth, const std::vector<int> & origin, double radius, std::vector<std::vector<int>> & res)
	{
		int dimension = depth % K;
		if (cur == NULL) return;
		double deltaX = cur->val[0] - origin[0];
		double deltaY = cur->val[1] - origin[1];
		double dist = sqrt(deltaX*deltaX + deltaY*deltaY);
		std::cout << "dist \"" << Debug::ToStr1D<int>()(cur->val) << "\"<->\"" << Debug::ToStr1D<int>()(origin) << "\": " << dist << std::endl;
		if (dist <= radius)
			res.push_back(cur->val);

		//use the fact that "the square centered at origin with length radius*2 must cover the circle centered at origin with radius"
		if (origin[dimension] - radius <= cur->val[dimension])//1. check lower boundary: if cur->xORy is covered by tgt xORy lower boundary, need to search left (too big: go left)
			findRangeRecur(cur->left, depth + 1, origin, radius, res);
		if (origin[dimension] + radius >= cur->val[dimension])//2. check higher boundary: if cur->xORy is covered by tgt xORy higher boundary, need to search right (too small: go right)
			findRangeRecur(cur->right, depth + 1, origin, radius, res);
	}
	void findNearestRecur(TreeNode * cur, int depth, const std::vector<int> & point, double & minDist, std::vector<int> & res)//similar to findRangeRecur w/ a center and radius
	{
		int dimension = depth % K;
		if (cur == NULL) return;
		double deltaX = cur->val[0] - point[0];
		double deltaY = cur->val[1] - point[1];
		double dist = sqrt(deltaX*deltaX + deltaY*deltaY);
		std::cout << "dist \"" << Debug::ToStr1D<int>()(cur->val) << "\"<->\"" << Debug::ToStr1D<int>()(point) << "\": " << dist << std::endl;
		if (dist < minDist)
		{
			res = cur->val;
			minDist = dist;
		}

		//use the fact that "the square centered at origin with length radius*2 must cover the circle centered at origin with radius"
		if ((double)point[dimension] - minDist <= (double)cur->val[dimension])//1. check lower boundary: if cur->xORy is covered by tgt xORy lower boundary, need to search left (too big: go left)
			findNearestRecur(cur->left, depth + 1, point, minDist, res);
		if ((double)point[dimension] + minDist >= (double)cur->val[dimension])//2. check higher boundary: if cur->xORy is covered by tgt xORy higher boundary, need to search right (too small: go right)
			findNearestRecur(cur->right, depth + 1, point, minDist, res);
	}
	TreeNode * findMinRecur(TreeNode * cur, int depth, int tgtDimension)//find the node w/ min val in tgtDimension
	{
		int dimension = depth % K;
		if (cur == NULL) return NULL;

		if (dimension == tgtDimension)//same dimension
		{
			if (cur->left == NULL)//can't go left: cur must be smallest
				return cur;
			else
				return findMinRecur(cur->left, depth + 1, tgtDimension);
		}

		//if current dimension is different from tgtDimension, then min val[tgtDimension] can be anywhere in the subtree
		TreeNode * left = findMinRecur(cur->left, depth + 1, tgtDimension);
		TreeNode * right = findMinRecur(cur->right, depth + 1, tgtDimension);
		TreeNode * res = cur;
		if (left && left->val[tgtDimension] < res->val[tgtDimension])
			res = left;
		if (right && right->val[tgtDimension] < res->val[tgtDimension])
			res = right;
		return res;
	}
	TreeNode * removeRecur(TreeNode * cur, int depth, std::vector<int> val)
	{
		if (cur == NULL) return NULL;
		int dimension = depth % K;
		
		bool isSame = true;
		for (int i = 0; i < K && isSame; ++i)
			if (val[i] != cur->val[i])
				isSame = false;
		if (isSame)
		{
			if (cur->left == NULL && cur->right == NULL)//leaf
			{
				delete cur;
				return NULL;
			}
			else if (cur->right)
			{
				TreeNode * minNode = findMinRecur(cur->right, depth + 1, dimension);
				for (int i = 0; i < K; ++i)
					cur->val[i] = minNode->val[i];//copy minNode's val to cur
				cur->right = removeRecur(cur->right, depth + 1, minNode->val);//look for minNode to delete
				return cur;
			}
			else//cur->left
			{
				TreeNode * minNode = findMinRecur(cur->left, depth + 1, dimension);
				for (int i = 0; i < K; ++i)
					cur->val[i] = minNode->val[i];//copy minNode's val to cur
				cur->right = removeRecur(cur->left, depth + 1, minNode->val);//look for minNode to delete. move left subtree to right !!!
				cur->left = NULL;//don't forget !!!
				return cur;
			}
		}
		else if (cur->val[dimension] > val[dimension])//too big: go left
		{
			cur->left = removeRecur(cur->left, depth + 1, val);
			return cur;
		}
		else//too small or equal: go right
		{
			cur->right = removeRecur(cur->right, depth + 1, val);
			return cur;
		}
	}
public:
	void Print()
	{
		std::ostringstream oss;
		oss << "KdTree:" << std::endl;
		PrintBinaryTree<TreeNode, std::ostringstream>(m_root, oss);
		std::cout << oss.str() << std::endl;
	}
};

template<>
std::string PrintBinaryTree<KdTree::TreeNode, std::ostringstream>::getVal(KdTree::TreeNode * n)
{
	return std::to_string(n->val[1]);//the second data
}
template<>
std::string PrintBinaryTree<KdTree::TreeNode, std::ostringstream>::selectVal2(int depth, KdTree::TreeNode * n)
{
	return std::to_string(n->val[0]);//the first data
}


template<>
std::string DeleteBinaryTree<KdTree::TreeNode>::GetVal(KdTree::TreeNode * root)
{
	std::ostringstream oss;
	oss << "(" << root->val[0] << "," << root->val[1] << ")";
	return oss.str();
}

/*
KdTree Insert: 38,23
KdTree Insert: 40,26
KdTree Insert: 29,16
KdTree Insert: 30,11
KdTree Insert: 27,28
KdTree Insert: 31,85
KdTree Insert: 7,39
KdTree Insert: 15,61
KdTree Insert: 32,29
KdTree Insert: 53,14
KdTree Insert: 70,3
KdTree Insert: 67,51
KdTree Insert: 99,90
KdTree Insert: 82,64
KdTree Insert: 73,75
KdTree:
                                                              
                                                              38
                                ______________________________23______________________________
                               /                                                               \
                              29                                                              40
                ______________16______________                                  ______________26______________
               /                               \                               /                               \
              30                              27                              53                              67
        ______11______                  ______28______                  ______14______                  ______51______
       /               \               /               \               /               \               /               \
       X               X               7              31               X              70               X              99
    __ N__          __ N__          __39__          __85__          __ N__          __ 3__          __ N__          __90__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       X      15      32       X       X       X       X       X       X       X      82       X
   N       N       N       N       N      61      29       N       N       N       N       N       N       N      64       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X  73   X   X   X
 N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N  75   N   N   N


KdTree FindRange for low="13, 34", high="76, 80": 
[rY][cX]
Row#0	= 15, 61
Row#1	= 67, 51
Row#2	= 73, 75

dist "38, 23"<->"50, 50": 29.5466
dist "29, 16"<->"50, 50": 39.9625
dist "30, 11"<->"50, 50": 43.8292
dist "27, 28"<->"50, 50": 31.8277
dist "7, 39"<->"50, 50": 44.3847
dist "15, 61"<->"50, 50": 36.6879
dist "31, 85"<->"50, 50": 39.8246
dist "32, 29"<->"50, 50": 27.6586
dist "40, 26"<->"50, 50": 26
dist "53, 14"<->"50, 50": 36.1248
dist "70, 3"<->"50, 50": 51.0784
dist "67, 51"<->"50, 50": 17.0294
dist "99, 90"<->"50, 50": 63.2535
dist "82, 64"<->"50, 50": 34.9285
dist "73, 75"<->"50, 50": 33.9706
KdTree FindRange for point="50, 50", radius="50":
[rY][cX]
Row#0	= 38, 23
Row#1	= 29, 16
Row#2	= 30, 11
Row#3	= 27, 28
Row#4	= 7, 39
Row#5	= 15, 61
Row#6	= 31, 85
Row#7	= 32, 29
Row#8	= 40, 26
Row#9	= 53, 14
Row#10	= 67, 51
Row#11	= 82, 64
Row#12	= 73, 75

dist "38, 23"<->"50, 50": 29.5466
dist "29, 16"<->"50, 50": 39.9625
dist "27, 28"<->"50, 50": 31.8277
dist "7, 39"<->"50, 50": 44.3847
dist "15, 61"<->"50, 50": 36.6879
dist "31, 85"<->"50, 50": 39.8246
dist "32, 29"<->"50, 50": 27.6586
dist "40, 26"<->"50, 50": 26
dist "53, 14"<->"50, 50": 36.1248
dist "70, 3"<->"50, 50": 51.0784
dist "67, 51"<->"50, 50": 17.0294
dist "99, 90"<->"50, 50": 63.2535
dist "82, 64"<->"50, 50": 34.9285
dist "73, 75"<->"50, 50": 33.9706
KdTree FindRange for point="50, 50", radius="26":
[rY][cX]
Row#0	= 40, 26
Row#1	= 67, 51

dist "38, 23"<->"50, 50": 29.5466
dist "29, 16"<->"50, 50": 39.9625
dist "27, 28"<->"50, 50": 31.8277
dist "31, 85"<->"50, 50": 39.8246
dist "32, 29"<->"50, 50": 27.6586
dist "40, 26"<->"50, 50": 26
dist "67, 51"<->"50, 50": 17.0294
dist "99, 90"<->"50, 50": 63.2535
dist "82, 64"<->"50, 50": 34.9285
dist "73, 75"<->"50, 50": 33.9706
KdTree FindRange for point="50, 50", radius="18":
[rY][cX]
Row#0	= 67, 51

dist "38, 23"<->"50, 50": 29.5466
dist "40, 26"<->"50, 50": 26
dist "67, 51"<->"50, 50": 17.0294
KdTree FindRange for point="50, 50", radius="5":
dist "38, 23"<->"50, 50": 29.5466
dist "29, 16"<->"50, 50": 39.9625
dist "27, 28"<->"50, 50": 31.8277
dist "7, 39"<->"50, 50": 44.3847
dist "15, 61"<->"50, 50": 36.6879
dist "31, 85"<->"50, 50": 39.8246
dist "32, 29"<->"50, 50": 27.6586
dist "40, 26"<->"50, 50": 26
dist "53, 14"<->"50, 50": 36.1248
dist "70, 3"<->"50, 50": 51.0784
dist "67, 51"<->"50, 50": 17.0294
dist "99, 90"<->"50, 50": 63.2535
dist "82, 64"<->"50, 50": 34.9285
dist "73, 75"<->"50, 50": 33.9706
KdTree FindNearest for point="50, 50": 67, 51
dist "38, 23"<->"39, 24": 1.41421
dist "29, 16"<->"39, 24": 12.8062
dist "27, 28"<->"39, 24": 12.6491
dist "31, 85"<->"39, 24": 61.5224
dist "32, 29"<->"39, 24": 8.60233
dist "40, 26"<->"39, 24": 2.23607
dist "53, 14"<->"39, 24": 17.2047
KdTree FindNearest for point="39, 24": 38, 23
dist "38, 23"<->"41, 25": 3.60555
dist "29, 16"<->"41, 25": 15
dist "27, 28"<->"41, 25": 14.3178
dist "31, 85"<->"41, 25": 60.8276
dist "32, 29"<->"41, 25": 9.84886
dist "40, 26"<->"41, 25": 1.41421
dist "53, 14"<->"41, 25": 16.2788
dist "67, 51"<->"41, 25": 36.7696
KdTree FindNearest for point="41, 25": 40, 26
dist "38, 23"<->"73, 75": 62.6817
dist "29, 16"<->"73, 75": 73.6003
dist "30, 11"<->"73, 75": 77.1038
dist "27, 28"<->"73, 75": 65.7647
dist "7, 39"<->"73, 75": 75.1798
dist "15, 61"<->"73, 75": 59.6657
dist "31, 85"<->"73, 75": 43.1741
dist "32, 29"<->"73, 75": 61.6198
dist "40, 26"<->"73, 75": 59.0762
dist "67, 51"<->"73, 75": 24.7386
dist "99, 90"<->"73, 75": 30.0167
dist "82, 64"<->"73, 75": 14.2127
dist "73, 75"<->"73, 75": 0
KdTree FindNearest for point="73, 75": 73, 75

KdTree Insert: 7,39
KdTree Insert: 27,28
KdTree Insert: 29,16
KdTree:
                                                                                                                              
                                                                                                                              38
                                                                ______________________________________________________________23______________________________________________________________
                                                               /                                                                                                                               \
                                                              29                                                                                                                              40
                                ______________________________16______________________________                                                                  ______________________________26______________________________
                               /                                                               \                                                               /                                                               \
                              30                                                              27                                                              53                                                              67
                ______________11______________                                  ______________28______________                                  ______________14______________                                  ______________51______________
               /                               \                               /                               \                               /                               \                               /                               \
               X                               X                               7                              31                               X                              70                               X                              99
        ______ N______                  ______ N______                  ______39______                  ______85______                  ______ N______                  ______ 3______                  ______ N______                  ______90______
       /               \               /               \               /               \               /               \               /               \               /               \               /               \               /               \
       X               X               X               X               X              15              32               X               X               X               X               X               X               X              82               X
    __ N__          __ N__          __ N__          __ N__          __ N__          __61__          __29__          __ N__          __ N__          __ N__          __ N__          __ N__          __ N__          __ N__          __64__          __ N__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       X       X       X       X       X       X       7       X      27       X       X       X       X       X       X       X       X       X       X       X       X       X       X       X      73       X       X       X
   N       N       N       N       N       N       N       N       N       N      39       N      28       N       N       N       N       N       N       N       N       N       N       N       N       N       N       N      75       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X  29   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N  16   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N


KdTree Remove: 99,90
KdTree:
                                                                                                                              
                                                                                                                              38
                                                                ______________________________________________________________23______________________________________________________________
                                                               /                                                                                                                               \
                                                              29                                                                                                                              40
                                ______________________________16______________________________                                                                  ______________________________26______________________________
                               /                                                               \                                                               /                                                               \
                              30                                                              27                                                              53                                                              67
                ______________11______________                                  ______________28______________                                  ______________14______________                                  ______________51______________
               /                               \                               /                               \                               /                               \                               /                               \
               X                               X                               7                              31                               X                              70                               X                              82
        ______ N______                  ______ N______                  ______39______                  ______85______                  ______ N______                  ______ 3______                  ______ N______                  ______64______
       /               \               /               \               /               \               /               \               /               \               /               \               /               \               /               \
       X               X               X               X               X              15              32               X               X               X               X               X               X               X               X              73
    __ N__          __ N__          __ N__          __ N__          __ N__          __61__          __29__          __ N__          __ N__          __ N__          __ N__          __ N__          __ N__          __ N__          __ N__          __75__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       X       X       X       X       X       X       7       X      27       X       X       X       X       X       X       X       X       X       X       X       X       X       X       X       X       X       X       X
   N       N       N       N       N       N       N       N       N       N      39       N      28       N       N       N       N       N       N       N       N       N       N       N       N       N       N       N       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X  29   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N  16   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N


KdTree Remove: 29,16
KdTree:
                                                              
                                                              38
                                ______________________________23______________________________
                               /                                                               \
                              29                                                              40
                ______________16______________                                  ______________26______________
               /                               \                               /                               \
              30                              27                              53                              67
        ______11______                  ______28______                  ______14______                  ______51______
       /               \               /               \               /               \               /               \
       X               X               7              31               X              70               X              82
    __ N__          __ N__          __39__          __85__          __ N__          __ 3__          __ N__          __64__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       X      15      32       X       X       X       X       X       X       X       X      73
   N       N       N       N       N      61      29       N       N       N       N       N       N       N       N      75
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   7   X  27   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   N   N   N   N  39   N  28   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N


KdTree Remove: 27,28
KdTree:
                                                              
                                                              38
                                ______________________________23______________________________
                               /                                                               \
                              29                                                              40
                ______________16______________                                  ______________26______________
               /                               \                               /                               \
              30                              27                              53                              67
        ______11______                  ______28______                  ______14______                  ______51______
       /               \               /               \               /               \               /               \
       X               X               7              31               X              70               X              82
    __ N__          __ N__          __39__          __85__          __ N__          __ 3__          __ N__          __64__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       X      15      32       X       X       X       X       X       X       X       X      73
   N       N       N       N       N      61      29       N       N       N       N       N       N       N       N      75
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   7   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   N   N   N   N  39   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N


KdTree Remove: 38,23
KdTree:
                                                              
                                                              40
                                ______________________________26______________________________
                               /                                                               \
                              29                                                              67
                ______________16______________                                  ______________51______________
               /                               \                               /                               \
              30                              27                              53                              73
        ______11______                  ______28______                  ______14______                  ______75______
       /               \               /               \               /               \               /               \
       X               X               7              31               X              70               X              82
    __ N__          __ N__          __39__          __85__          __ N__          __ 3__          __ N__          __64__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       X      15      32       X       X       X       X       X       X       X       X       X
   N       N       N       N       N      61      29       N       N       N       N       N       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   7   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   N   N   N   N  39   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N


Delete (30,11)
Delete (29,16)
Delete (7,39)
Delete (15,61)
Delete (27,28)
Delete (32,29)
Delete (31,85)
Delete (38,23)
Delete (53,14)
Delete (70,3)
Delete (40,26)
Delete (67,51)
Delete (73,75)
Delete (82,64)
Delete (99,90)
*/
#endif