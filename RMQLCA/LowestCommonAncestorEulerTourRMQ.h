#ifndef LOWEST_COMMON_ANCESTOR_EULER_TOUR_RMQ_H
#define LOWEST_COMMON_ANCESTOR_EULER_TOUR_RMQ_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include "Debug.h"
/*
http://www.topcoder.com/tc?d1=tutorials&d2=lowestCommonAncestor&module=Static

Euler tour tree:
The tree is viewed as a directed graph that contains two directed edges for each edge in the tree.
Recall the condition that there exists a Euler tour in an directed graph:
iff at most 1 vertex has (out-degree) - (in-degree) = 1, at most 1 vertex has (in-degree) - (out-degree) = 1, every other vertex has equal in-degree and out-degree, and all of its vertices with nonzero degree belong to a single connected component
Now, for an Euler tour tree, each undirected edge now becomes a pair of in/out degree edges, so all the vertices in the tree must have equal in-degree and out-degree edges.
=> Euler tour tree qualifies the definition.
Eulerian trail: a path that traverses all edges exactly once
Since every node in the tree has euqal in-degree and out-degree edges, there must exist a Euler path starting at any node in the tree.

The lowest common ancestor problem can be reduced to a RMQ problem.
What we need is to prepare 3 arrays:
1. a euler tour array that contains each node in euler tour order
2. a level number array that contains the recursion depth level of each node in euler tour order
3. a table that maps each node to its 1st occurrence index in the euler tour

Then the lowest common ancestor of any 2 nodes in the tree can be found by finding the shallowest level number between the level number of the 2 nodes in the level array, which is performing RMQ in the level array.
LCA node of p and q = EulerTour[RMQ(Level, 1stEulerTourIdx[p], 1stEulerTourIdx[q])]


    ______1______
   /      |      \
  6       2     __9__
 / \           /  |  \
3   5         10  4   8
                  |
				  7

				   0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18
EulerTour:         1  6  3  6  5  6  1  2  1  9  10  9  4  7  4  9  8  9  1
Level:             0  1  2  1  2  1  0  1  0  1   2  1  2  3  2  1  2  1  0
FirstEulerTourIdx:
1: 0
2: 7
3: 2
4: 12
5: 4
6: 1
7: 13
8: 16
9: 9
10: 10

LCA(10,7) = EulerTour[ RMQ( Level[FirstEulerTourIdx[10]:FirstEulerTourIdx[7]] ) ]
          = EulerTour[ RMQ( Level[10:13] ) ]
		  = EulerTour[ 11 ]
		  = 9

*/
class LowestCommonAncestorEulerTourRMQ
{
public:
	LowestCommonAncestorEulerTourRMQ(){}
	~LowestCommonAncestorEulerTourRMQ(){}
	struct TreeNode//not binary!
	{
		TreeNode(int x) : val(x), children() {}
		int val;
		std::vector<TreeNode *> children;
	};

	TreeNode * Find(TreeNode * root, TreeNode * p, TreeNode * q)
	{
		std::vector<TreeNode *> eulerTour;
		std::vector<int> level;
		std::unordered_map<TreeNode *, int> firstEulerTourIdx;
		int levelCount = -1;
		this->dFS_Euler_Tour(root, eulerTour, level, firstEulerTourIdx, levelCount);

		std::ostringstream oss;
		oss << "EulerTour:" << std::endl;
		for (auto i : eulerTour)
			oss << i->val << ",";
		oss << std::endl << "Level:" << std::endl;
		for (auto i : level)
			oss << i << ",";
		oss << std::endl << "FirstEulerTourIndex:" << std::endl;
		for (auto i : firstEulerTourIdx)
			oss << "[" << i.first->val << "," << i.second << "]" << std::endl;
		std::cout << oss.str() << std::endl;

		/*
		now the lowest common ancestor can be reduced to a RMQ problem:
		the lca of 2 nodes is the corresponding node that has the minimum level number between the 1st visit of the 2 nodes in the level array
		*/
		TreeNode * lca = 
			eulerTour[this->RMQ_Naive(level, firstEulerTourIdx[p], firstEulerTourIdx[q])];

		std::cout << "LowestCommonAncestorEulerTourRMQ for \"" << p->val << "," << q->val << "\": " << lca->val << std::endl;
		return lca;
	}

private:
	void dFS_Euler_Tour(TreeNode * root, std::vector<TreeNode *> & eulerTour, std::vector<int> & level, std::unordered_map<TreeNode *, int> & firstEulerTourIdx, int levelCount)
	{
		++levelCount;
		eulerTour.push_back(root);
		level.push_back(levelCount);
		if (firstEulerTourIdx.count(root) == 0)
			firstEulerTourIdx.insert({ root, eulerTour.size() - 1 });
		int N = root->children.size();
		for (int i = 0; i < N; ++i)
		{
			TreeNode * child = root->children[i];
			this->dFS_Euler_Tour(child, eulerTour, level, firstEulerTourIdx, levelCount);
			eulerTour.push_back(root);
			level.push_back(levelCount);
		}
	}
	int RMQ_Naive(const std::vector<int> & v, int from, int to)
	{
		int min = INT_MAX;
		int minIdx = -1;
		for (int i = from; i <= to; ++i)
			if (v[i] < min)
			{
				min = v[i];
				minIdx = i;
			}
		return minIdx;
	}
public:
	static void DeleteTree(TreeNode * root)
	{
		if (root == 0)
			return;

		int N = root->children.size();
		for (int i = 0; i < N; ++i)
			DeleteTree(root->children[i]);

		//post order
		delete root;
		root = 0;
	}
};
/*
    ______1______
   /      |      \
  6       2     __9__
 / \           /  |  \
3   5         10  4   8
                  |
				  7
EulerTour:
1,6,3,6,5,6,1,2,1,9,10,9,4,7,4,9,8,9,1,
Level:
0,1,2,1,2,1,0,1,0,1,2,1,2,3,2,1,2,1,0,
FirstEulerTourIndex:
[1,0]
[6,1]
[2,7]
[3,2]
[9,9]
[10,10]
[4,12]
[5,4]
[7,13]
[8,16]

LowestCommonAncestorEulerTourRMQ for "10,7": 9

  ___________1___________
 /           |           \
2   _________3_________   4
   /         |         \
  5        __6__      __7__
          /     \    /     \
	     8       9  10     11
	               /  \
			      12  13
EulerTour:
1,2,1,3,5,3,6,8,6,9,6,3,7,10,12,10,13,10,7,11,7,3,1,4,1,
Level:
0,1,0,1,2,1,2,3,2,3,2,1,2,3,4,3,4,3,2,3,2,1,0,1,0,
FirstEulerTourIndex:
[12,14]
[1,0]
[2,1]
[9,9]
[3,3]
[8,7]
[5,4]
[4,23]
[6,6]
[7,12]
[10,13]
[11,19]
[13,16]

LowestCommonAncestorEulerTourRMQ for "9,12": 3

EulerTour:
1,2,1,3,5,3,6,8,6,9,6,3,7,10,12,10,13,10,7,11,7,3,1,4,1,
Level:
0,1,0,1,2,1,2,3,2,3,2,1,2,3,4,3,4,3,2,3,2,1,0,1,0,
FirstEulerTourIndex:
[12,14]
[1,0]
[2,1]
[6,6]
[3,3]
[13,16]
[5,4]
[8,7]
[9,9]
[7,12]
[4,23]
[11,19]
[10,13]

LowestCommonAncestorEulerTourRMQ for "2,11": 1
*/
#endif